#ifndef MANDIS_TEST_SOCKET_SERVER_HPP_
#define MANDIS_TEST_SOCKET_SERVER_HPP_

#include "../include/logger.h"
#include "../include/timelib.h"
#include "../mandis-p2p/server.h"

const int TestSocketServerCase1(logger::Logger *log) {
    p2pnet::Server server(log, 12345);
    server.Start();

    ///TODO: connect to server and send message

    server.Stop();
    server.Join();
    return 0;
}

#endif // !MANDIS_TEST_SOCKET_SERVER_HPP_

