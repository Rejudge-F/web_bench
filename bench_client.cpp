#include "bench_client.h"

BenchClient::BenchClient(const std::string host, const int port, std::shared_ptr<ClientArguments> &args_): 
    sock(new Socket(host.c_str(), port)),
    args(args_)
{
    sTime = clock();
}

BenchClient::~BenchClient() {
    args.reset();
    sock.reset();
}

// Bench Benchmark Callback function
void BenchClient::Bench() {
    BenchInfo benchInfo;
    ssize_t requestLen = args->request.length();
    memset(&benchInfo, 0, sizeof(benchInfo));
    nexttry:;
    while(true) {
        if(sock->GetSocket() < 0) {
            benchInfo.failed++;
            break;
        }

        // generate request not const request
        char request[2048];
        strcpy(request, args->request.c_str());

        // send request to server 
        if(sock->Write(request) != requestLen) {
            benchInfo.failed++;
            goto nexttry;
        }

        // recv response from server 
        if(args->force == 0) {
            size_t responseLen = sock->Read();
            if(responseLen < 0) {
                benchInfo.failed++;
                goto nexttry;
            }
            benchInfo.bytes += responseLen;
            benchInfo.speed++;
            break;
        }
    }

    eTime = clock();
    SPDLOG_DEBUG("finish: {0}: Method: {1} force: {2} forceReload: {3} eplased: {4} us", __FUNCTION__, args->httpMethod, args->force, args->forceReload, (double)(eTime-sTime));
    args->messageQeueue->Push(benchInfo);
}

