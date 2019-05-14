#include "../include/config.h"

#include <fstream>
using boost::property_tree::ini_parser::read_ini;

namespace config {
    Config::Config(std::string &config_filepath) 
        : config_filepath_(config_filepath)
    {
        std::ifstream fin(config_filepath);
        if (!fin) {
            GenConfig();
            boost::property_tree::ini_parser::write_ini(config_filepath, pt_);
            exit(0);
        }

        boost::property_tree::ini_parser::read_ini(config_filepath, pt_);

        logging_filepath_ = pt_.get<std::string>("Logger.LoggingPath", "mandis.log");
        logging_level_ = pt_.get<int>("Logger.LoggingLevel", 0);

        entry_port_ = pt_.get<unsigned short>("Mandis.Port", 60001);

        block_path_ = pt_.get<std::string>("MandisFS.BlockPath", "");
        block_filepath_ = pt_.get<std::string>("MandisFS.BlockInfoPath", "");
        file_filepath_ = pt_.get<std::string>("MandisFS.FileInfoPath", "");

        p2pnet_port_ = pt_.get<unsigned short>("MandisP2P.Port", 60002);
        p2pnet_filepath_ = pt_.get<std::string>("MandisP2P.NetInfoPath", "");
    }

    Config::~Config() {

    }

    void Config::GenConfig() {
        pt_.put<std::string>("Logger.LoggingPath", "mandis.log");
        pt_.put<std::string>("Logger.LoggingLevel", "debug");

        pt_.put<std::string>("Mandis.Port", "60001");

        pt_.put<std::string>("MandisFS.BlockPath", "");
        pt_.put<std::string>("MandisFS.BlockInfoPath", "");
        pt_.put<std::string>("MandisFS.FileInfoPath", "");

        pt_.put<std::string>("MandisP2P.Port", "60002");
        pt_.put<std::string>("MandisP2P.NetInfoPath", "");
    }

}