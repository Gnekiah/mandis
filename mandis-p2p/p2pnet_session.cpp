#include "p2pnet_session.h"

namespace p2pnet {
    P2PnetSession::P2PnetSession(boost::asio::io_context& ioc) 
        : socket_(ioc)
    {

    }

    P2PnetSession::~P2PnetSession() {

    }

    void P2PnetSession::Start() {

    }

    boost::asio::ip::tcp::socket& P2PnetSession::socket() {
        return socket_;
    }

    void P2PnetSession::HandleRead(const boost::system::error_code &ec, std::size_t bytes_transferred) {
        if (ec) {
            return;
        }
        /*
        int ret = request_parser_.Parse(request_, buffer_.data(), bytes_transferred);
        if (ret == REQUEST_PARSE_SUCCESSFUL) {
            ///TODO: handle request and generate reply info
            //boost::asio::async_write(socket_, )
            ///TODO: return response package, and handle write

        }
        else if (ret == REQUEST_PARSE_DATA_INVALID) {
            ///TODO: generate reply info and return response package, and handle write
        }
        else {
            socket_.async_read_some(boost::asio::buffer(buffer_), boost::bind(&Session::HandleRead,
                shared_from_this(), boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
        }
        */
    }

    void P2PnetSession::HandleWrite(const boost::system::error_code &ec) {
        if (ec) {
            return;
        }
        ///TODO: handle write
    }

    void P2PnetSession::Close() {
        boost::system::error_code ignored_ec;
        socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
    }
}