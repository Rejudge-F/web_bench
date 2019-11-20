#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

class Socket {
public: 
    Socket(const char *host, int clientPort);
    ~Socket();
    // get socket
    int GetSocket();
    ssize_t Write(char *buff);
    ssize_t Read(char *buff);
private:
    int sock;
};
