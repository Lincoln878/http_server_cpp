#include "http_server.hpp"

#include <iostream>
#include <sstream>
#include <unistd.h>

const unsigned int BUFFER_SIZE = 1024;

namespace {
    void log(const std::string &message) {
        std::cout<<message<<'\n';
    }
    void exitWithError(const std::string &errorMessage) {
        log("ERROR: "+errorMessage);
        exit(1);
    }
}

namespace http {
    Server::Server(std::string ip_address, int port):
        m_ip_address(ip_address), m_port(port), m_socket(),
        m_new_socket(), m_incomingMessage(), m_socketAddress(),
        m_socketAddress_len(sizeof(m_socketAddress)),
        m_serverMessage()
    {

        m_socketAddress.sin_addr.s_addr = inet_addr(m_ip_address.c_str());
        m_socketAddress.sin_port = htons(port);
        startServer();
    }
    Server::~Server() {
        closeServer();
    }

    int Server::startServer() {
        m_socket = socket(AF_INET, SOCK_STREAM, 0);

        if (m_socket<0) {
            exitWithError("Cannot create socket");
            return 1;
        }

        if (bind(m_socket, (sockaddr*)&m_socketAddress, m_socketAddress_len)<0) {
            exitWithError("Cannot connect socket to address");
            return 1;
        }

        return 0;
    }

    void Server::closeServer() {
        close(m_socket);
        close(m_new_socket);
        exit(0);
    }

    void Server::startListen() {
        if (listen(m_socket, 20)<0) {
            exitWithError("Socket listen failed");
        }

        std::ostringstream ss;
        ss<<"\n*** Listening on: "<<inet_ntoa(m_socketAddress.sin_addr)<<":"<<ntohs(m_socketAddress.sin_port)<<" ***\n\n";
        log(ss.str());

        int bytesReceived;
        
        while (1) {
            log("===== Waiting for connection =====\n");
            acceptConnection(m_new_socket);

            char buffer[BUFFER_SIZE] = {0};
            bytesReceived = read(m_new_socket, buffer, BUFFER_SIZE);
            if (bytesReceived<0) {
                exitWithError("Failied to read bytes from client socket connection");
            }

            ss.clear();
            ss<<"----- Received request from client -----\n";
            log(ss.str());

            std::string type, content, response;
            type = "application/json";
            content = "{\"content\": 123}";
            response = buildResponse(type, content);
            setResponse(response);

            sendResponse();
            close(m_new_socket);
        }
    }

    void Server::acceptConnection(int &new_socket) {
        new_socket = accept(m_socket, (sockaddr*)&m_socketAddress, &m_socketAddress_len);
        if (new_socket<0) {
            std::ostringstream ss;
            ss<<"Server failed to accept connection from "<<inet_ntoa(m_socketAddress.sin_addr)<<":"<<ntohs(m_socketAddress.sin_port)<<"'\n";
            exitWithError(ss.str());
        }
    }

    std::string Server::buildResponse(std::string &type, std::string &content) {
        std::string header;
        header = "HTTP/1.1 200 OK\nContent-Type: "+type+"\nContent-Length: "+std::to_string(content.size())+"\n\n";
        return header+content;
    }

    void Server::setResponse(std::string &response) {
        m_serverMessage = response;
    }

    void Server::sendResponse() {
        long bytesSent;

        bytesSent = write(m_new_socket, m_serverMessage.c_str(), m_serverMessage.size());

        if (bytesSent==m_serverMessage.size()) {
            log("----- Server response sent to client -----\n");
        } else {
            log("Error sending response to client\n");
        }
    }
}