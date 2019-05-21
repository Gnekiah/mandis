#include "entry_session.h"

namespace frontend {

    EntrySession::EntrySession(boost::asio::io_context& ioc) 
        : socket_(ioc)
    {

    }

    EntrySession::~EntrySession() {

    }

    void EntrySession::Start() {
        boost::asio::async_read(socket_, boost::asio::buffer(buffer_.data(), 1024 * 512), 
            boost::bind(&EntrySession::HandleRead, shared_from_this(), boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
    }

    boost::asio::ip::tcp::socket& EntrySession::socket() {
        return socket_;
    }

    void EntrySession::HandleRead(const boost::system::error_code &ec, std::size_t bytes_transferred) {
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
            socket_.async_read_some(boost::asio::buffer(buffer_), boost::bind(&EntrySession::HandleRead,
                shared_from_this(), boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
        }
        */
    }

    void EntrySession::HandleWrite(const boost::system::error_code &ec) {
        if (ec) {
            return;
        }
        ///TODO: handle write
    }

    int EntrySession::ParsePackage(unsigned char* buff, size_t offset) {

        return 0;
    }

    void EntrySession::Close() {
        boost::system::error_code ignored_ec;
        socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
    }
}
