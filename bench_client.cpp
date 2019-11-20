#include "bench_client.h"

BenchClient::BenchClient(const std::string host, const int port, std::shared_ptr<ClientArguments> &args_): sock(new Socket(host.c_str(), port)),args(args_) {
    sTime = clock();
}

BenchClient::~BenchClient() {
    eTime = clock();
    SPDLOG_DEBUG("end: {0}: Method: {1} force: {2} forceReload: {3} eplased: {4} us", __FUNCTION__, args->httpMethod, args->force, args->forceReload, (double)(eTime-sTime));
    args.reset();
    sock.reset();
}

// BuildRequest Form a request in light of method and url
std::string BenchClient::BuildRequest(std::string url) {
    memset(host, 0, MAXHOSTNAMELEN);
    string request;
    request.clear();
    switch(args->httpMethod) {
        case METHOD_GET:   request += "GET"; break;
        case METHOD_POST:  request += "POST"; break;
        case METHON_HEAD:  request += "HEAD"; break;
        case METHOD_TRACE: request += "TRACE"; break;
        default:
    }
}

// Bench Benchmark Callback function
void BenchClient::Bench() {
}
