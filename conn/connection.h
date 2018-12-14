#include <iostream>
#include <semaphore.h>
#include <string.h>
#include <unistd.h>
#include <mqueue.h>
#include <fcntl.h>
#include <syslog.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/socket.h>

#define BUFFER_SIZE 80
#define EXIT_STR "exit\0"

class Connection
{
    public:
    Connection(int id);
    int read_c(); //for clients
    void write_s(const char* str); //for server
    void answer();
    char* buf;
    int id;
    ~Connection();
};

