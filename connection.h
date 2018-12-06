//using namespace std;

class Connection
{
    public:
    Connection(int id);
    void read(); //for clients (children)
    void write(char* buf); //for host
    void answer();
    char* buf;
    int id;
    ~Connection();
};

