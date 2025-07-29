#include "rest_server.h"

CRPGRestServer g_RestServer;

static bool check_auth(const httplib::Request &req) {
    if (CRPG_GlobalSettings::rest_auth[0] == '\0')
        return true;
    auto it = req.headers.find("Authorization");
    if (it == req.headers.end())
        return false;
    return strcmp(it->second.c_str(), CRPG_GlobalSettings::rest_auth) == 0;
}

void CRPGRestServer::Start() {
    srv.Post("/command", [](const httplib::Request &req, httplib::Response &res) {
        if (!check_auth(req)) { res.status = 401; return; }
        s_engine->ServerCommand((req.body + "\n").c_str());
        res.set_content("ok", "text/plain");
    });

    srv.Get("/players", [](const httplib::Request &req, httplib::Response &res) {
        if (!check_auth(req)) { res.status = 401; return; }
        std::string out = "[";
        for (unsigned int i=0;i<CRPG_Player::player_count;i++) {
            CRPG_Player *p = CRPG_Player::players[i];
            if (!p) continue;
            char buf[256];
            snprintf(buf, sizeof(buf),
                "{\"name\":\"%s\",\"level\":%u,\"exp\":%u}",
                p->name(), p->level, p->exp);
            if (out.size()>1) out += ",";
            out += buf;
        }
        out += "]";
        res.set_content(out, "application/json");
    });

    thread = std::thread([this]() {
        srv.listen("0.0.0.0", CRPG_GlobalSettings::rest_port);
    });
}

void CRPGRestServer::Stop() {
    srv.stop();
    if (thread.joinable())
        thread.join();
}
