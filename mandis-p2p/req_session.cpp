#include "req_session.h"

namespace p2pnet {

    ReqSession::ReqSession(boost::asio::io_context& ioc, const std::string ip, const int port,
        std::string& msg, logger::Logger* logger)
        : ioc_(ioc),
        socket_(ioc),
        msg_(msg),
        logger_(logger),
        ep_(boost::asio::ip::address::from_string(ip), port)
    {
        LOG_INFO(logger_, "Req Session Init");
    }

    int ReqSession::DoReqStore(std::string key, std::string block_path) {
        boost::asio::connect(socket_, ep_);
        boost::asio::write(socket_, boost::asio::buffer());
        return 0;
    }

    int ReqSession::DoReqAccess(std::string key) {

        return 0;
    }

    int ReqSession::DoReqSync(std::string msg) {

        return 0;
    }

    int ReqSession::DoReqFind(std::string key) {

        return 0;
    }

    int ReqSession::DoPing() {
        ///not used
        return 0;
    }
}