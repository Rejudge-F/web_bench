#include <iostream>
#include "common.h"
#include <sys/params>
#include <getopt.h>
#include <signal.h>

// define initial variables
int force = 0;
int reload = 0;
int method = METHOD_GET;
int clientsNum = 0;
std::string proxyHost;
int proxyPort;
std::string url;
int benchTime=1;

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
	{"url", required_argument, &url, 'u'},
	{"clients", required_argument, &clientsNum, 'c'},
	{"help", no_argument, nullptr, '?'},
	{nullptr, 0, nullptr, 0}
};

int main(int argc, char *argv[])
{
	
	return 0;
}
