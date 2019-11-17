#include "Socket.h"
#include <string.h>
#include <iostream>

Socket::Socket(const char *host, int clientPort) {
    memset(&ad, 0, sizeof(ad));
    ad.sin_family = AF_INET;

    inaddr = inet_addr(host);
    if(inaddr != INADDR_NONE) {
        memcpy(&ad.sin_addr, &inaddr, sizeof(inaddr));
    } else {
        hp = gethostbyname(host);
        if(hp == nullptr) {
            std::cerr << "gethostbyname failed" << std::endl;
            exit(1);
        }
        memcpy(&ad.sin_addr, hp->h_addr, hp->h_length);
    }
    ad.sin_port = htons(clientPort);

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0) {
        std::cerr << __FILE__ << " " << __LINE__ << "get socket failed" << std::endl;
        exit(1);
    } else {
        if(connect(sock, (struct sockaddr*)&ad, sizeof(ad)) < 0) {
            std::cerr << __FILE__ << " " << __LINE__ << "connect failed" << std::endl;
            exit(1);
        }
    }
}

Socket::~Socket() {
    close(sock);
}
