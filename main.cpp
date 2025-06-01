#include "http_server.hpp"

int main() {

    http::Server server = http::Server("127.0.0.1", 8080);

    server.startListen();

    return 0;
}