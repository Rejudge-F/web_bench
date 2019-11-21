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
    void BenchMark();
    std::string BuildRequest(std::string url);
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
    std::vector<std::shared_ptr<BenchClient> > _clients;
};

#endif // BENCH_CLIENT_MANAGER_H
