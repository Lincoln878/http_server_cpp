#ifndef http_server_hpp
#define http_server_hpp

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>


namespace http {
    class Server {
    public:
        Server(std::string ip_address, int port);
        ~Server();
        void startListen();
        

    private:
        std::string m_ip_address;
        int m_port;
        int m_socket;
        long m_incomingMessage;
        struct sockaddr_in m_socketAddress;
        unsigned int m_socketAddress_len;
        std::string m_serverMessage;

        int startServer();
        void closeServer();
        void acceptConnection(int &new_socket);
        void handleConnection(int client_socket);
        std::string buildResponse(std::string &type, std::string &content);
        void setResponse(std::string &response);
        void sendResponse(int client_socket);
    };
}

#endif