#include "connection.h"

#define BUFFER_SIZE 80

static int pipe_file_desc[2];

Connection::Connection(int id)
{
    this->id = id;
	if (pipe(pipe_file_desc))
    {
		syslog(LOG_INFO, "Error piping");
	}
}

int Connection::read_c()
{     
    char str[BUFFER_SIZE];	
    void* str_buf = (void*)str;

 
    if (read(pipe_file_desc[0], str_buf, BUFFER_SIZE) == -1)
    {
		syslog(LOG_INFO, "Error reading");
		return 1;
	}

    char const *newStr = (char const *)str_buf;

    if (strcmp(newStr, EXIT_STR) == 0)
        return 1;

    printf("id  %d: the answer is: %s\n", this->id, newStr);
    return 0;
    
}

void Connection::write_s(const char* str)
{   
    void* str_buf = (void*)str;

	if (write(pipe_file_desc[1], str_buf,  BUFFER_SIZE) == -1)
    {
	    syslog(LOG_INFO, "Error writing");
	    exit(1);
	}
}

Connection::~Connection()
{
    close(pipe_file_desc[0]);
	close(pipe_file_desc[1]);
}


