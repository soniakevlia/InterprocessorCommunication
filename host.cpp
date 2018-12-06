#define _GLIBCXX_USE_CXX11_ABI 1

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include <semaphore.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string>
#include <cstdio>
#include "conn_mmap.cpp"

#define CLIENTS_NUM 4
#define BUFFER_SIZE 80

const char* EXIT_STR = "exit\0";
Connection* connection[CLIENTS_NUM];
const char* result[CLIENTS_NUM];

void run_clients(sem_t* main_sem, sem_t** sem);
void run_host(sem_t* main_sem, sem_t** sem);
void print_answer(const char* result);
void unlink(void);

int main(void)
{
    sem_t* main_sem;
    sem_t* sem[CLIENTS_NUM];
    char str[20];
    //unlink();

    //sem for host
    main_sem = sem_open("/semsem", O_CREAT,  S_IRWXU, 0);
    if(main_sem == SEM_FAILED)
    {
        printf("Something went wrong with semaphore...\n");
    }

    //sems for clients
    for (int i = 0; i < CLIENTS_NUM; i++)
    {
        connection[i] = new Connection(i);

        std::string s = std::to_string(i);
        const char* number = s.c_str();
        str[0] = 0;
        strcat(str, "/semsem");//main semaphore name
        strcat(str, number);

        printf("%s\n", str);
 
        sem[i] = sem_open(str, O_CREAT, S_IRWXU, 0);
        if(sem[i] == SEM_FAILED)
        {
            printf("%i, Something went wrong with semaphore...\n", errno);
        }      

    }

    run_clients(main_sem, sem); 
    unlink();

    return 0;
}

void run_clients(sem_t* main_sem, sem_t** sem){
    //Clients
    int pid; 

    for (int i = 0; i < CLIENTS_NUM; i++)
    {
        pid = fork();
        if(pid == 0)
        {          
            while(1)
            {                
                sem_post(main_sem);
                sem_wait(sem[i]);
                connection[i]->read();
            }
            exit(0);
        }

    }
    run_host(main_sem, sem);
}

void run_host(sem_t* main_sem, sem_t** sem)
{
    //Host
    char str[20];
    while(1)
    {
        str[0] = 0;
        std::cin >> str;
        sem_post(main_sem);      
        
        if (strcmp(str, EXIT_STR) == 0)     
        {       
            exit(0);
        }

        for (int i = 0; i < CLIENTS_NUM; i++)
        {   
            connection[i]->write(str); 
            sem_post(sem[i]);
            sem_wait(main_sem);                 
        }
    }
}

void unlink(void)
{
    char str[20];
    sem_unlink("/semsem");
    for (int i = 0; i < CLIENTS_NUM; i++)
    {
        std::string s = std::to_string(i);
        const char* number = s.c_str();
        str[0] = 0;
        strcat(str, "/semsem");//main semaphore name
        strcat(str, number);
        sem_unlink(str);
    }
}

