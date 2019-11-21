#ifndef BENCH_CLIENT_MANAGER_H
#define BENCH_CLIENT_MANAGER_H

#include "bench_client.h"
#include "message_queue.h"
#include "common.h"
#include <vector>
#include <string>

class BenchClientManager {
public:
    BenchClientManager();
    BenchClientManager(force, reload, method, clients, proxyHost, proxyPort);
    ~BenchClientManager();
    void BenchMark();
private:
    int _force;
    int _reload;
    int _method;
    int _clients;
    int _proxyPort;
    clock_t sTime;
    clock_t eTime;
    std::string _proxyHost;
    MessageQueue<BenchInfo> _messageQueue;
    std::vector<std::shared_ptr<BenchClient> > _clients;
};

#endif // BENCH_CLIENT_MANAGER_H
