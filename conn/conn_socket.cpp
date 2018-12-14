#include "connection.h"

static int socket_data[2];

Connection::Connection(int id)
{
    this->id = id;
    if (socketpair(AF_UNIX, SOCK_STREAM, 0, socket_data) == -1)
    {
		syslog(LOG_INFO, "Error socketpair");
	}
}

int Connection::read_c()
{     
    char str[BUFFER_SIZE];	
    void* str_buf = (void*)str;

    if (read(socket_data[0], str_buf, BUFFER_SIZE) == -1)
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

	if (write(socket_data[1], str_buf, BUFFER_SIZE) == -1)
    {
		syslog(LOG_INFO, "Error writing");
        exit(1);
	}
}

Connection::~Connection()
{
	close(socket_data[0]);
	close(socket_data[1]);
}


