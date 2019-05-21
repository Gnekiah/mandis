#include <iostream>
#include <boost/asio.hpp>

#include "../include/logger.h"
#include "../include/config.h"
#include "../include/entry.h"
#include "../include/foofs.h"
#include "../include/p2pnet.h"

int main(int argc, char **argv)
{
    std::string config_path = "mandis.cfg";
    config::Config *config = new config::Config(config_path);

    boost::asio::io_context ioc;

    logger::Logger *logger = new logger::Logger(config->logging_filepath());
    logger->Start();
    p2pnet::P2Pnet *p2pnet = new p2pnet::P2Pnet(config, logger, foofs::CallBack, ioc);
    p2pnet->Start();
    foofs::FooFS *foofs = new foofs::FooFS(config, p2pnet, logger);
    foofs->Start();
    frontend::Entry *entry = new frontend::Entry(config, foofs, logger, ioc);
    entry->Start();

    ioc.run();

    entry->Join();
    foofs->Join();
    p2pnet->Join();
    logger->Join();

    delete entry;
    delete foofs;
    delete p2pnet;
    delete logger;

    return 0;
}
 