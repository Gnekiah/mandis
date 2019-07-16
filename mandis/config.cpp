#include "../include/config.h"
#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>
using boost::property_tree::ini_parser::read_ini;

namespace config {
    Config::Config(std::string &config_filepath) 
        : config_filepath_(config_filepath)
    {
        std::ifstream fin(config_filepath.c_str());
        if (!fin) {
            std::cerr << "Config File Not Found, Do GenConfig()" << std::endl;
            GenConfig();
            boost::property_tree::ini_parser::write_ini(config_filepath, pt_);
            exit(0);
        }

        boost::property_tree::ini_parser::read_ini(config_filepath, pt_);
            std::cerr << "1" << std::endl;

        logging_filepath_ = pt_.get<std::string>("Logger.LoggingPath", "mandis.log");
            std::cerr << "2" << std::endl;
        logging_level_ = pt_.get<int>("Logger.LoggingLevel", 3);
            std::cerr << "3" << std::endl;

        entry_port_ = pt_.get<unsigned short>("Mandis.Port", 60001);
            std::cerr << "4" << std::endl;

        block_path_ = pt_.get<std::string>("MandisFS.BlockPath", "block");
            std::cerr << "5" << std::endl;
        block_filepath_ = pt_.get<std::string>("MandisFS.BlockInfoPath", "");
            std::cerr << "6" << std::endl;
        file_filepath_ = pt_.get<std::string>("MandisFS.FileInfoPath", "");
            std::cerr << "7" << std::endl;

        p2pnet_port_ = pt_.get<unsigned short>("MandisP2P.Port", 60002);
            std::cerr << "8" << std::endl;
        p2pnet_filepath_ = pt_.get<std::string>("MandisP2P.NetInfoPath", "");
            std::cerr << "9" << std::endl;
        rsa_key_length_ = pt_.get<int>("MandisP2P.RSAKeyLength", 2048);
            std::cerr << "10" << std::endl;
        rsa_password_ = pt_.get<std::string>("MandisP2P.RSAPassword", "");
            std::cerr << "11" << std::endl;
        rsa_public_key_path_ = pt_.get<std::string>("MandisP2P.RSAPublicKeyPath", "");
            std::cerr << "12" << std::endl;
        rsa_private_key_path_ = pt_.get<std::string>("MandisP2P.RSAPrivateKeyPath", "");
            std::cerr << "13" << std::endl;

        if (!boost::filesystem::exists(block_path()) || !boost::filesystem::is_directory(block_path()))
            boost::filesystem::create_directories(block_path());
            std::cerr << "14" << std::endl;
    }

    Config::~Config() {

    }

    void Config::GenConfig() {
        pt_.put<std::string>("Logger.LoggingPath", "mandis.log");
        pt_.put<std::string>("Logger.LoggingLevel", "3");

        pt_.put<std::string>("Mandis.Port", "60001");

        pt_.put<std::string>("MandisFS.BlockPath", "block");
        pt_.put<std::string>("MandisFS.BlockInfoPath", "");
        pt_.put<std::string>("MandisFS.FileInfoPath", "");

        pt_.put<std::string>("MandisP2P.Port", "60002");
        pt_.put<std::string>("MandisP2P.NetInfoPath", "");
        pt_.put<std::string>("MandisP2P.RSAKeyLength", "");
        pt_.put<std::string>("MandisP2P.RSAPassword", "");
        pt_.put<std::string>("MandisP2P.RSAPublicKeyPath", "");
        pt_.put<std::string>("MandisP2P.RSAPrivateKeyPath", "");
    }

}
