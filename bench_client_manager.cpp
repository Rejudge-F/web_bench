#include "bench_client_manager.h"
#include <stdlib.h> // impllement for itoa

// global variable 
static int HttpVersion=10;
static volatile int timerExpired=0;

BenchClientManager::BenchClientManager(int force, int reload, int method, int clients, std::string proxyHost, int proxyPort, std::string url):
    _force(force),
    _reload(reload),
    _method(method),
    _clientNum(clients),
    _proxyPort(proxyPort),
    _sTime(clock()),
    _eTime(clock()),
    _url(url),
    _proxyHost(proxyHost),
    _messageQueue(new MessageQueue<BenchInfo>())
{}

BenchClientManager::~BenchClientManager() {
    _eTime = clock();
    SPDLOG_INFO("bench mark: elpased time {0} us", (double)(_eTime-_sTime));
    for(int i = 0; i < (int)_clients.size(); i++) {
        _clients[i].reset();
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
    if(_method == METHOD_TRACE || _method == METHOD_OPTIONS) HttpVersion = HTTP_11;
    
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
    request += "Host: " + _proxyHost + ":" + std::to_string(_proxyPort) + "\r\n";
    if(_reload) {
        request += "Pragma: no-cache\r\n";
    }
    request += "Connection: close\r\n";
    request += "\r\n";

    SPDLOG_INFO("request info:\n{0}\n", request);

    return request;
}

void BenchClientManager::BenchMark() {
    // Form Arguments
    std::shared_ptr<ClientArguments> clientArguments(new ClientArguments);
    clientArguments->httpMethod = _method;
    clientArguments->force = _force;
    clientArguments->forceReload = _reload;
    clientArguments->request = BuildRequest(_url);
    clientArguments->messageQeueue = _messageQueue;

    for(int i = 0; i < _clientNum; i++) {
        // start thread to test        
    } 
    
}

