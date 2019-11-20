#include "bench_client.h"

BenchClient::BenchClient(const std::string host, const int port, std::shared_ptr<ClientArguments> &args_): sock(new Socket(host.c_str(), port)),args(args_) {
    sTime = clock();
}

BenchClient::~BenchClient() {
    eTime = clock();
    SPDLOG_DEBUG("end: {0}: Method: {1} force: {2} forceReload: {3} eplased: {4}s", __FUNCTION__, args->httpMethod, args->force, args->forceReload, (double)(eTime-sTime)/CLOCKS_PER_SEC);
    args.reset();
    sock.reset();
}
