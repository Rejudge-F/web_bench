#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/spdlog.h" // implement for SPDLOG_...
#include "bench_socket.h"
#include "common.h"
#include <iostream>
#include <string>
#include <sys/param.h> // implement for MAXHOSTNAMELEN


// ClientArguments client option defination
struct ClientArguments {
    int httpMethod;
    int force;
    int forceReload;
};

// BenchClient single bench client defination
class BenchClient {
public:
    BenchClient(const std::string host, const int port, std::shared_ptr<ClientArguments> &args_);
    ~BenchClient();
    std::string BuildRequest(std::string url);
    void Bench();
private:
    char host[MAXHOSTNAMELEN];
    std::shared_ptr<Socket> sock; 
    std::shared_ptr<ClientArguments> args;
    clock_t sTime, eTime;
};
