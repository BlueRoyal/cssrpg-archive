#ifndef CSSRPG_REST_SERVER_H
#define CSSRPG_REST_SERVER_H

#include "../cssrpg.h"
#include "httplib.h"
#include <thread>

class CRPGRestServer {
public:
    void Start();
    void Stop();
private:
    httplib::Server srv;
    std::thread thread;
};

extern CRPGRestServer g_RestServer;

#endif // CSSRPG_REST_SERVER_H
