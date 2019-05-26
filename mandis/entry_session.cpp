#include "entry_session.h"
#include <sstream>
#include <boost/lexical_cast.hpp>

namespace frontend {

    EntrySession::EntrySession(boost::asio::io_context& ioc, logger::Logger *logger, foofs::FooFS *foofs)
        : socket_(ioc),
        logger_(logger),
        foofs_(foofs)
    {

    }

    EntrySession::~EntrySession() {

    }

    void EntrySession::Start() {
        LOG_TRACE(logger_, "Start Session");
        socket_.async_read_some(boost::asio::buffer(buffer_.data(), 1024 * 512),
            boost::bind(&EntrySession::HandleRead, shared_from_this(), boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
    }

    boost::asio::ip::tcp::socket& EntrySession::socket() {
        return socket_;
    }

    void EntrySession::HandleRead(const boost::system::error_code &ec, std::size_t bytes_transferred) {
        LOG_TRACE(logger_, "Handle Read");
        if (ec) {
            LOG_WARNING(logger_, "ecode= " + boost::lexical_cast<std::string>(ec.value()) + ", msg= " + ec.message());
            return;
        }
        
        int ret = 0;
        std::vector<std::string> vec;
        std::string cmdstr = buffer_.data();
        ret = foofs_->Split(vec, cmdstr, '|');

        if (ret != 3) {
            LOG_WARNING(logger_, "Error On Command Parsing");
            std::string msg = "Command Error";
            boost::asio::async_write(socket_, boost::asio::buffer(msg.data(), msg.length()),
                boost::bind(&EntrySession::HandleWrite, this, boost::asio::placeholders::error));
            return;
        }

        std::string cmd_ops = vec[0];
        std::string cmd_filepath = vec[1];
        std::string cmd_filename = vec[2];
        std::stringstream ss;
        ss << "Mandis-cli: ops= " << cmd_ops << ", filepath= " << cmd_filepath << ", filename= " << cmd_filename;
        LOG_TRACE(logger_, ss);

        std::string msgback;
        if (cmd_ops == "list") {
            char msg[4096];
            ret = foofs_->ReadMetaData(msg);
            if (ret > 0) {
                msg[ret] = '\0';
                msgback = msg;
            }
            else
                msgback = "Failed";
        }
        else if (cmd_ops == "writ") {
            ret = foofs_->Write(cmd_filepath);
            if (ret == 0) {
                LOG_INFO(logger_, "File Wrote: " + cmd_filepath);
                msgback = "Completed";
            }
            else {
                msgback = "Failed"; 
            }
        }
        else if (cmd_ops == "read") {
            ret = foofs_->ReadByName(cmd_filename, cmd_filepath);
            if (ret == 0) {
                LOG_INFO(logger_, "File Read: " + cmd_filename);
                msgback = "Completed";
            }
            else {
                msgback = "Failed";
            }
        } 
        else {
            LOG_WARNING(logger_, "Error Command");
            msgback = "Error Command";
        }

        boost::asio::async_write(socket_, boost::asio::buffer(msgback.c_str(), msgback.length()),
            boost::bind(&EntrySession::HandleWrite, this, boost::asio::placeholders::error));
    }

    void EntrySession::HandleWrite(const boost::system::error_code &ec) {
        if (ec) {
            LOG_WARNING(logger_, "ecode= " + boost::lexical_cast<std::string>(ec.value()) + ", msg= " + ec.message());
            return;
        }
        //Close();
    }

    void EntrySession::Close() {
        boost::system::error_code ignored_ec;
        try {
            socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
        }
        catch (std::exception &e) {
            LOG_TRACE(logger_, e.what());
        }

    }
}
