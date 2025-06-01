#include "http_server.hpp"

int main() {

    http::Server server = http::Server("0.0.0.0", 8080);

    server.startListen();

    return 0;
}