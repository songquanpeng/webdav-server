#ifndef HTTP_SERVER_SERVER_H
#define HTTP_SERVER_SERVER_H

#include <thread>
#include <iostream>
#include "utils.h"
#include "constants.h"

// Initialize the server socket and return the file descriptor.
int initialize_server(u_short port) {
    // Create a socket
    int server_fd; // fd means file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) { // AF_INET: ipv4, SOCK_STREAM: TCP
        fatal("Unable to initialize the server socket.");
    }
    // Bind a address to this socket
    struct sockaddr_in address{};
    memset((char *) &address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY); // INADDR_ANY means 0.0.0.0
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *) &address, sizeof(address)) < 0) {
        fatal("Cannot bind address to socket");
    }
    // Listen the incoming connection
    if (listen(server_fd, BACKLOG) < 0) {
        fatal("Unable to listen incoming connections.");
    }

    return server_fd;
}

int process_request(int socket_fd) {
    std::cout << "[Log] Thread " << std::this_thread::get_id() << " at your service" << std::endl;
    char buffer[READ_BUFFER_SIZE] = {0};
    if (read(socket_fd, buffer, READ_BUFFER_SIZE) < 0) {
        printf("nothing to read");
    }
    write(socket_fd, buffer, strlen(buffer));
    close(socket_fd);
    return 0;
}


#endif //HTTP_SERVER_SERVER_H
