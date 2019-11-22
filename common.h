#ifndef COMMON_H_
#define COMMON_H_

enum HttpProtocolVersion {
    HTTP_10 = 10,
    HTTP_11 
};

enum HttpMethod {
    METHOD_GET = 1,
    METHOD_POST,
    METHOD_OPTIONS,
    METHOD_HEAD,
    METHOD_TRACE
};

struct BenchInfo {
    int speed;
    int failed;
    int bytes;
};



#endif // COMMON_H_
