#include "connector.h"

#include <ostream>

namespace p2pnet {
    Connector::Connector(const std::string &ip, int port, logger::Logger *log) {
        socket_ = boost::asio::ip::tcp::socket(ioc_);
        boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string(ip), port);
        socket_.async_connect(ep, boost::bind(&Connector::HandleConnect, this,
            boost::asio::placeholders::error));
    }

    Connector::~Connector() {

    }

    void Connector::HandleConnect(const boost::system::error_code& ec) {


    }

    void Connector::ReqPing() {

    }

    void Connector::ReqFind() {

    }

    void Connector::ReqStore() {

    }

    void Connector::ReqSync() {

    }

    void Connector::StartConnector() {

    }

    void Connector::Start() {

    }

    void Connector::Join() {

    }

    void Connector::Stop() {

    }
}