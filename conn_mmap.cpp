#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <cstdio>
#include <iostream>
#include <sys/mman.h>
#include <fcntl.h>
#include "connection.h"

#define BUFFER_SIZE 80

Connection::Connection(int id)
{
   this->id = id;
   this->buf = (char*)mmap(NULL, BUFFER_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
}

void Connection::read()
{     
    printf("id  %d: the answer is: %s\n", this->id, this->buf);
    
}

void Connection::write(char* str)
{   
    strcpy(this->buf, str);
   // printf("id  %d: the string in buffer is: %s\n", this->id, this->buf);   
}




