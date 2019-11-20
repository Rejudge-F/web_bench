#include "bench_socket.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include <string.h>
#include <iostream>
#include <stdio.h>

Socket::Socket(const char *host, int clientPort) {
    // init logger and put log into logs/basic.log
    auto fileLogger = spdlog::basic_logger_mt("basic_logge", "logs/basic.log");
    spdlog::set_default_logger(fileLogger);

    unsigned long inaddr;
    sockaddr_in ad;
    hostent *hp;
    memset(&ad, 0, sizeof(ad));
    ad.sin_family = AF_INET;

    inaddr = inet_addr(host);
    if(inaddr != INADDR_NONE) {
        memcpy(&ad.sin_addr, &inaddr, sizeof(inaddr));
    } else {
        hp = gethostbyname(host);
        if(hp == nullptr) {
            char errInfo[256];
            sprintf(errInfo, "%s", strerror(errno));
            SPDLOG_ERROR(errInfo);
            exit(1);
        }
        memcpy(&ad.sin_addr, hp->h_addr, hp->h_length);
    }
    ad.sin_port = htons(clientPort);

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0) {
        char errInfo[256];
        sprintf(errInfo, "%s", strerror(errno));
        SPDLOG_ERROR(errInfo);
        exit(1);
    } else {
        if(connect(sock, (struct sockaddr*)&ad, sizeof(ad)) < 0) {
            char errInfo[265];
            sprintf(errInfo, "%s", strerror(errno));
            SPDLOG_ERROR(errInfo);
            exit(1);
        }
        SPDLOG_INFO("{0}:{1} has connect", *host, clientPort);
    }
}

Socket::~Socket() {
    close(sock);
}

int Socket::GetSocket() {
    if(sock < 0) {
        return -1;
    }
    return sock;
}

ssize_t Socket::Write(char *buff) {
    size_t remainSize = strlen(buff);
    ssize_t retSize = 0;
    while(remainSize > 0) {
        size_t writeSize = write(sock, static_cast<void*>(buff), remainSize);
        if(writeSize <= 0) {
            break;
        }

        remainSize -= writeSize;
        retSize += writeSize;
        buff = buff + writeSize; 
    }
    return retSize;
}

ssize_t Socket::Read(char *buff) {
    ssize_t retSize = 0;
    char tmpBuff[1024];
    while(true) {
        size_t readSize = read(sock, tmpBuff, 1024);
        if(readSize <= 0) {
            break;
        }
        retSize += readSize;
        buff = strcat(buff, tmpBuff);
    }
    return retSize; 
}
