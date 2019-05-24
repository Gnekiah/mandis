#include "../include/p2pnet.h"

namespace p2pnet {
    P2Pnet::P2Pnet(config::Config *config, logger::Logger *logger, config::callback_fn callback, 
        boost::asio::io_context& ioc)
        : key_(config->rsa_private_key_path(), config->rsa_public_key_path(), config->rsa_password(), logger),
        config_(config),
        logger_(logger),
        callback_(callback),
        ioc_(ioc),
        acceptor_(ioc_, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 60002))
    {
        // run callback demo: (*quote_callback)(CB_QUOTE_FRONT_CONNECTED, nullptr);
        StartAccept();
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

    void P2Pnet::StartAccept() {
        session_ptr session(new P2PnetSession(ioc_));
        acceptor_.async_accept(session->socket(), boost::bind(&P2Pnet::HandleAccept, this,
            session, boost::asio::placeholders::error));
    }

    void P2Pnet::HandleAccept(session_ptr session, const boost::system::error_code& ec) {
        if (!ec)
        {
            session->Start();
        }
        StartAccept();
    }

    int P2Pnet::ReqStore(std::string key, std::string block_path) {
        return 0;
    }

    int P2Pnet::ReqAccess(std::string key) {
        return 0;

    }

    int P2Pnet::ReqSync(std::string msg) {
        return 0;

    }

    int P2Pnet::ReqFind(std::string key) {
        return 0;

    }

    int P2Pnet::Ping() {
        ///not used
        return 0;
    }

    int P2Pnet::RspStore(std::string block_path) {
        return 0;

    }

    int P2Pnet::RspAccess(std::string key) {
        return 0;

    }

    int P2Pnet::RspSync(std::string msg) {
        return 0;

    }

    int P2Pnet::RspFind(std::string key) {
        return 0;

    }

    int P2Pnet::Pong() {
        ///not used
        return 0;
    }







}