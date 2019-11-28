#ifndef BENCH_CLIENT_MANAGER_H
#define BENCH_CLIENT_MANAGER_H

#include "bench_client.h"
#include "message_queue.h"
#include "common.h"
#include <vector>
#include <string>

class BenchClientManager {
public:
    BenchClientManager(int force, int reload, int method, int clients, std::string proxyHost, int proxyPort, std::string url);
    ~BenchClientManager();
    void BenchMark(int benchTime);
    std::string BuildRequest(std::string url);
	std::string GetHost(){ return _proxyHost; }
	int GetPort() { return _proxyPort; }
	int GetForce() { return _force; }
	int GetMethod() { return _method; }
	int GetReload() { return _reload; }
	int GetClientsNum() { return _clientNum; }
	std::string GetUrl() { return _url; }
	MessageQueue<BenchInfo>* GetQueue() { return _messageQueue; }
	std::vector<BenchClient*> GetClients() { return _clients; }

private:
    int _force;
    int _reload;
    int _method;
    int _clientNum;
    int _proxyPort;
    clock_t _sTime;
    clock_t _eTime;
    std::string _url;
    std::string _proxyHost;
    MessageQueue<BenchInfo> *_messageQueue;
    std::vector<BenchClient*> _clients;
};

#endif // BENCH_CLIENT_MANAGER_H
