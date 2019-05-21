#include "../include/entry.h"

namespace frontend {

    Entry::Entry(config::Config *config, foofs::FooFS *foofs, logger::Logger *logger, boost::asio::io_context& ioc)
        : config_(config), 
        logger_(logger), 
        foofs_(foofs),
        ioc_(ioc),
        acceptor_(ioc_, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 60001))
    {
        StartAccept();
    }

    Entry::~Entry() {

    }

    void Entry::Run() {

    }

    void Entry::Start() {

    }

    void Entry::Stop() {

    }

    void Entry::Join() {

    }

    void Entry::StartAccept() {
        session_ptr session(new EntrySession(ioc_));
        acceptor_.async_accept(session->socket(), boost::bind(&Entry::HandleAccept, this, 
            session, boost::asio::placeholders::error));
    }

    void Entry::HandleAccept(session_ptr session, const boost::system::error_code& ec) {
        if (!ec)
        {
            session->Start();
        }
        StartAccept();
    }
}