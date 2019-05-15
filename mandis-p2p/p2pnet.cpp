#include "../include/p2pnet.h"

namespace p2pnet {
    P2Pnet::P2Pnet(config::Config *config, logger::Logger *logger)
        : key_(config->rsa_private_key_path, config->rsa_public_key_path, config->rsa_password, logger),
        config_(config),
        logger_(logger)
    {

    }

    P2Pnet::~P2Pnet() {

    }

    void P2Pnet::Run() {

    }

    void P2Pnet::Start() {

    }

    void P2Pnet::Stop() {

    }

    void P2Pnet::Join() {

    }
}