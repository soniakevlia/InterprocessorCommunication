#include "connection.h"

static int shm_file_desc = 0;

Connection::Connection(int id)
{
    this->id = id;
    if ((shm_file_desc = shm_open("/shm", O_CREAT | O_RDWR, S_IRWXU)) == -1) {
	    syslog(LOG_INFO, "Error opening shm");
    }

    this->buf = (char*)mmap(NULL, BUFFER_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, shm_file_desc, 0);


}

int Connection::read_c()
{     

    char str_buf[BUFFER_SIZE];	
    void* str = (void*)str_buf;
    str = memcpy(str, this->buf, BUFFER_SIZE);


    if (str == NULL)
    {
   		syslog(LOG_INFO, "Error memcpy");	
		return 1;	
    }

    char const *newStr = (char const *)str;

    if (strcmp(newStr, EXIT_STR) == 0)
    {
        return 1;
    }
    else
        printf("id  %d: the answer is: %s\n", this->id, newStr);
    return 0;
    
}

void Connection::write_s(const char* str)
{   

    void* str_buf = (void*)this->buf;
    str_buf = memcpy(str_buf, str, BUFFER_SIZE);
    
    if (str_buf == NULL)
    {
    	syslog(LOG_INFO, "Error memcpy");	
		exit(1);
	}

    char const *newStr = (char const *)str_buf;
    strcpy(this->buf, newStr);

    //printf("id  %d: the string in buffer is: %s\n", this->id, this->buf);   
}



Connection::~Connection() {
	munmap(this->buf, BUFFER_SIZE);
	shm_unlink("/shm");
}



