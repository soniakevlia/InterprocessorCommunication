#include "connection.h"

Connection::Connection(int id)
{
   this->id = id;
   this->buf = (char*)mmap(NULL, BUFFER_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
}

int Connection::read_c()
{     
    if (strcmp(this->buf, EXIT_STR) == 0)
        return 1;
    else
        printf("id  %d: the answer is: %s\n", this->id, this->buf);
    return 0;
    
}

void Connection::write_s(const char* str)
{   
    strcpy(this->buf, str);
    //printf("id  %d: the string in buffer is: %s\n", this->id, this->buf);   
}

Connection::~Connection() {
	munmap(this->buf, BUFFER_SIZE);
}


