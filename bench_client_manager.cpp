#include "bench_client_manager.h"
#include <stdlib.h> // impllement for itoa

BenchClientManager::BenchClientManager():
    _force(0),
    _reload(0),
    _method(METHOD_GET),
    _clients(1),
    _proxyPort(0),
    _proxyHost("http://127.0.0.1"),
    sTime(clock())
{}

BenchClientManager::BenchClientManager(force, reload, method, clients, proxyHost, proxyPort):
    _force(force),
    _reload(reload),
    _method(method),
    _clients(clients),
    _proxyHost(_proxyHost),
    _proxyPort(_proxyPort)
{}

BenchClientManager::~BenchClientManager() {
    eTime = clock();
    SPDLOG_INFO("bench mark: elpased time {0} us", (double)(eTime-sTime));
    for(auto clientPtr : _clients) {
        clientPtr->reset();
    }
}

std::string BenchClientManager::BuildRequest(std::string url) {
    /************************
     * METHOD URI PROTOCOL  *
     * HEADER               *
     * ...                  *
     * ...                  *
     * ...                  *
     ***********************/
    // prepare 
    int urlLen = url.length();


    // swich a protocol by method
    if(_method == METHOD_TRACE || _method == METHOD_OPTION) httpVersion = HTTP_11;
    
    // form request
    std::string request;
    // insert method
    switch(_method) 
    {
        default:
        case METHOD_GET: request += "GET"; break;
        case METHOD_HEAD: request += "HEAD"; break;
        case METHOD_TRACE: request += "TRACE"; break;
        case METHOD_OPTIONS: request += "OPTIONS"; break;
    }
    request += " ";

    // check url valid 
    // 1. http protocol
    // 2. url length < 1500 
    if(url.find("://") == url.npos) {
        SPDLOG_ERROR("{0} is not a valid URL", url);
        exit(2);
    }
    if(urlLen > 1500) {
        SPDLOG_ERROR("URL is too long");
        exit(2);
    }
    if(0 != url.find("http://")) {
        SPDLOG_ERROR("Support http protocol only, set --proxy for others.");
        exit(2);
    }

    /* get delimiter :// position */
    int delimiterIndex = url.find("://");
    url = url.substr(delimiterIndex + 3);

    // get URI from url
    if(url.find("/") == url.npos) {
        SPDLOG_ERROR("Invalid URL syntax - hostname don't end with /");
        exit(2);
    }
    int uriIndex = url.find("/");
    request += url.substr(uriIndex);
    request += " ";

    // insert httpVersion
    // 1. HTTP_10 HTTP/1.0
    // 2. HTTP_11 HTTP/1.1
    switch(HttpVersion) 
    {
        case HTTP_10: request += "HTTP/1.0"; break;
        case HTTP_11: request += "HTTP/1.1"; break;
        default: request += "HTTP/1.0"; break;
    }
    request += "\r\n";
    request += "User-Agent: Zephyr's WebBench\r\n";
    request += "Host: " + _proxyHost + ":" + itoa(_proxyPort) + "\r\n";
    if(_reload) {
        request += "Pragma: no-cache\r\n";
    }
    request += "Connection: close\r\n";
    request += "\r\n";

    SPDLOG_INFO("request info:\n{0}\n", request);

    return request;
}

void BenchClientManager::BenchMark() {
    
}

