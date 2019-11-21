#include "bench_client_manager.h"

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
{};
BenchClientManager::~BenchClientManager() {
    eTime = clock();
    SPDLOG_INFO("bench mark: elpased time {0} us", (double)(eTime-sTime));
    for(auto clientPtr : _clients) {
        clientPtr->reset();
    }
}
void BenchClientManager::BenchMark();

