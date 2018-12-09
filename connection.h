//using namespace std;

class Connection
{
    public:
    Connection(int id);
    int read(); //for clients (children)
    void write(const char* str); //for host
    void answer();
    char* buf;
    int id;
    ~Connection();
};

