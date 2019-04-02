#include "server.h"

#include "session.h"

namespace p2pnet {    

    Server::Server(boost::asio::io_service& ios, logger::Logger *logger, int port)
        : ios_(ios),
        logger_(logger),
        acceptor_(ios, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
    {
        Start();
    }

    Server::~Server() {

    }
    
    void Server::Run() {
        ios_.run();
    }

    void Server::Start() {
        session_ptr session(new Session(ios_));
        acceptor_.async_accept(session->socket(), boost::bind(&Relay::AcceptHandler, 
            this, session, boost::asio::placeholders::error));
    }

    void Server::Stop() {
        ios_.stop();
    }

    void Server::AcceptHandler(session_ptr session, const boost::system::error_code& ec) {
        if (ec || !session) {
            LOG_WARNING(logger_, ec.message);
            return;
        }
        session->Start();
        Start();
    }

    void Server::CallbackSession(const boost::system::error_code& ec) {

    }

}