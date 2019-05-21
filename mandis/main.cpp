#include <iostream>
#include <boost/asio/io_context.hpp>

#include "../include/logger.h"
#include "../include/config.h"
#include "../include/entry.h"
#include "../include/foofs.h"
#include "../include/p2pnet.h"

int main(int argc, char **argv)
{
    std::cout << "Begin..." << std::endl;
    std::cout << "[config::Config] Init..." << std::endl;
    std::string config_path = "mandis.cfg";
    config::Config *config = new config::Config(config_path);
    boost::asio::io_context ioc;

    std::cout << "[logger::Logger] Init..." << std::endl;
    logger::Logger *logger = new logger::Logger(config->logging_filepath());
    logger->Start();

    std::cout << "[p2pnet::P2Pnet] Init..." << std::endl;
    p2pnet::P2Pnet *p2pnet = new p2pnet::P2Pnet(config, logger, foofs::CallBack, ioc);
    p2pnet->Start();
    std::cout << "[foofs::FooFS] Init..." << std::endl;
    foofs::FooFS *foofs = new foofs::FooFS(config, p2pnet, logger);
    foofs->Start();
    std::cout << "[frontend::Entry] Init..." << std::endl;
    frontend::Entry *entry = new frontend::Entry(config, foofs, logger, ioc);
    entry->Start();

    std::cout << "mandis onroad" << std::endl;
    ioc.run();
    std::cout << "mandis unmount" << std::endl;

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
 