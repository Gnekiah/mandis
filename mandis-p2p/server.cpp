#include "server.h"

#include "session.h"

namespace p2pnet {    

    Server::Server(logger::Logger *logger, int port)
        : logger_(logger),
        acceptor_(ios_, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
    {
        Run();
    }

    Server::~Server() {

    }
    
    void Server::Start() {
        ios_.run();
    }

    void Server::Stop() {
        ios_.stop();
    }

    void Server::Run() {
        session_ptr session(new Session(ios_, rsp_find_callback_, rsp_store_callback_,
            rsp_sync_callback_));
        acceptor_.async_accept(session->socket(), boost::bind(&Server::HandleAccept, 
            this, session, boost::asio::placeholders::error));
    }

    
    void Server::HandleAccept(session_ptr session, const boost::system::error_code& ec) {
        if (ec || !session) {
            LOG_WARNING(logger_, ec.message);
            return;
        }
        session->Start();
        Run();
    }
}