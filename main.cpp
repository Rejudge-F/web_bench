#include "bench_client_manager.h"
#include "util.h"
#include <iostream>
#include "common.h"
#include <getopt.h>
#include <signal.h>
#include <unistd.h>
#include <string>

#define PROGRAM_VERSION "version: 1.0" 

// define initial variables
int force = 0;
int reload = 0;
int method = METHOD_GET;
int clientsNum = 1;
std::string proxyHost = "localhost";
int proxyPort=80;
std::string url="http://localhost:80/index.html";
int benchTime=30;

// long option set 
static const struct option long_options[] {
	{"force", no_argument, &force, 1},
	{"reload", no_argument, &reload, 1},
	{"time", required_argument, &benchTime,	't'},
	{"get", no_argument, &method, METHOD_GET},
	{"head", no_argument, &method, METHOD_HEAD},
	{"trace", no_argument, &method, METHOD_TRACE},
	{"options", no_argument, &method, METHOD_OPTIONS},
	{"version", no_argument, nullptr, 'V'},
	{"url", required_argument, nullptr, 'u'},
	{"clients", required_argument, &clientsNum, 'c'},
	{"help", no_argument, nullptr, '?'},
	{nullptr, 0, nullptr, 0}
};

// usage help 
static void usage() {
	std::cerr << "webbench [option]... URL\n";
	std::cerr << "-f|--force                Don't wait for server reply.\n";
	std::cerr << "-r|--reload               Send reload request - Pragma:no-cache.\n";
	std::cerr << "-t|--time <sec>           Run benchmark for <sec> seconds. Default 30.\n";
    std::cerr << "-u|--url <server:port>    Request URL for this benchmark.\n";
	std::cerr << "-c|--clients <n>          Run <n> clients in this benchmark.\n";
	std::cerr << "-?|-h|--help              This Infomation.\n";
	std::cerr << "--get                     Use GET request method.\n";
	std::cerr << "--head                    Use HEAD request method.\n";
	std::cerr << "--trace                   Use TRACE request method.\n";
	std::cerr << "--options                 Use OPTIONS request method.\n";
	std::cerr << "-V|--version              Display program version.\n";
}

int main(int argc, char *argv[])
{
	int opt = 0;
	int options_index = 0;

	if(argc < 3) {
		usage();
		return 1;
	}
	
	InitLogger("./logs/bench.log");

    while((opt = getopt_long(argc, argv, "Vfrt:u:c:?h", long_options, &options_index)) != EOF) {
        switch (opt) {
            case 'f':
                force = 1;
                break;
            case 'r':
                reload = 1;
                break;
            case 't':
                benchTime = atoi(optarg);
                break;
            case 'V':
                std::cout << PROGRAM_VERSION << std::endl;
                exit(0);
                break;
            case 'u':
            {
                url = static_cast<std::string>(optarg); 
                unsigned int index = url.find("http://", 0);
                if (index != 0 || index == url.npos) {
                    std::cerr << "URL support http protocol only.\n";
                    exit(1);        
                }
                
                // fine delimiter ':',  <server>:<port>
                index = url.find(":", 7);
                if (index == url.npos) {
                    std::cerr << "URL losed port info.\n";
                    exit(1);
                }
                // get host 
                proxyHost = url.substr(7, index-7);

                // get delimiter '/', <server>:<port>/URI
                int tIndex = index + 1;
                index = url.find("/", tIndex);
                if (index == url.npos) {
                    std::cerr << "URI has losed.\n";
                    exit(1);
                }
                proxyPort = atoi(url.substr(tIndex, index - tIndex).c_str());
                
                break;
            }
            case 'c':
                clientsNum = atoi(optarg);
                break;
            case '?':
                usage();
                break;
            case 'h':
                usage();
                break;
            default:
                break;        
        }
    }

    printf("* Bench mark Info...\n"); 
    printf("* force:           %s\n", force?"true":"false");
    printf("* reload:          %s\n", reload?"true":"false");
    printf("* method:          %s\n", method==METHOD_GET?"GET":(method==METHOD_HEAD?"HEAD":(method==METHOD_OPTIONS?"OPTIONS":"TRACE")));
    printf("* bench time:      %d sec\n", benchTime);
    printf("* clients:         %d \n", clientsNum);
    printf("* host:            %s\n", proxyHost.c_str());
    printf("* port:            %d\n", proxyPort);
    printf("* url:             %s\n", url.c_str());

	BenchClientManager *benchClientManager = 
		new BenchClientManager(force, reload, method, 
				clientsNum, proxyHost, proxyPort, url);
	benchClientManager->BenchMark(benchTime);
	return 0;
}
