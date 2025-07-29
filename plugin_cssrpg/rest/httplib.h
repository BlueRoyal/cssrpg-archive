#ifndef CPP_HTTPLIB_H
#define CPP_HTTPLIB_H
#include <string>
#include <map>
#include <functional>
namespace httplib {
struct Request {
    std::string body;
    std::map<std::string,std::string> headers;
};
struct Response {
    int status = 200;
    std::string body;
    void set_content(const std::string &b, const char*) { body = b; }
};
class Server {
public:
    using Handler = std::function<void(const Request&, Response&)>;
    void Post(const char*, Handler) {}
    void Get(const char*, Handler) {}
    void listen(const char*, int) {}
    void stop() {}
};
}
#endif
