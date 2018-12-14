#include "connection.h"

static int fifo_file_desc = 0;

Connection::Connection(int id)
{
    this->id = id;
    if (mkfifo("fifo", S_IRWXU) == -1)
    {
		syslog(LOG_INFO, "Error making fifo");
	}
	
	if ((fifo_file_desc = open("fifo", O_RDWR | O_NONBLOCK)) == -1 )
    {
		syslog(LOG_INFO, "Error opening fifo");	
	}
}

int Connection::read_c()
{     
    char str[BUFFER_SIZE];	
    void* str_buf = (void*)str;

   
	if (read(fifo_file_desc, str_buf, BUFFER_SIZE) == -1) {
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

	if (write(fifo_file_desc, str_buf, BUFFER_SIZE) == -1) {
		syslog(LOG_INFO, "Error writing");
		exit(1);
	}
}

Connection::~Connection()
{
    close(fifo_file_desc);
	unlink("fifo");
}


