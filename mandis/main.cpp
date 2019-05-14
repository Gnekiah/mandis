#include <iostream>

#include "../include/logger.h"
#include "../include/config.h"
#include "../include/entry.h"
#include "../include/foofs.h"
#include "../include/p2pnet.h"

int main(int argc, char **argv)
{
    std::string config_path = "mandis.cfg";
    config::Config *config = new config::Config(config_path);

    logger::Logger *logger = new logger::Logger(config->logging_filepath());
    logger->Start();

    p2pnet::P2Pnet *p2pnet = new p2pnet::P2Pnet(config, logger);
    foofs::FooFS *foofs = new foofs::FooFS(config, p2pnet, logger);
    frontend::Entry *entry = new frontend::Entry(config, foofs, logger);
    
    // entry->Join();
    // foofs->Join();
    // p2pnet->Join();
    logger->Join();

    return 0;
}
 