#include "p2pnet_session.h"
#include <boost/lexical_cast.hpp>

namespace p2pnet {
    P2PnetSession::P2PnetSession(boost::asio::io_context& ioc, logger::Logger* logger)
        : socket_(ioc),
        logger_(logger)
    {

    }

    P2PnetSession::~P2PnetSession() {

    }

    void P2PnetSession::Start() {
        LOG_TRACE(logger_, "Start Session");
        socket_.async_read_some(boost::asio::buffer(buffer_.data(), 1024 * 512),
            boost::bind(&P2PnetSession::HandleRead, shared_from_this(), boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
    }

    boost::asio::ip::tcp::socket& P2PnetSession::socket() {
        return socket_;
    }

    void P2PnetSession::HandleRead(const boost::system::error_code &ec, std::size_t bytes_transferred) {
        LOG_TRACE(logger_, "Handle Read");
        if (ec) {
            LOG_WARNING(logger_, "ecode= " + boost::lexical_cast<std::string>(ec.value()) + ", msg= " + ec.message());
            return;
        }

        int ret = 0;
        std::vector<std::string> vec;
        std::string cmdstr = buffer_.data();
        ret = Split(vec, cmdstr, '|');

        /// store|<key>|<buffer_size>
        /// access|<key>
        /// sync|<msg>
        /// find|<key>
        /// ping
        if (ret == 3 && vec[0] == "store") {
            LOG_TRACE(logger_, "Rsp Store");

        }
        else if (ret == 2 && vec[0] == "access") {

        }
        else if (ret == 2 && vec[0] == "sync") {

        }
        else if (ret == 2 && vec[0] == "find") {

        }
        else if (ret == 1 && vec[0] == "ping") {
            // not used
        }
        else {
            LOG_WARNING(logger_, "Command Error, cmd=" + cmdstr);
            Close();
        }
        /*
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
        */

    }

    void P2PnetSession::HandleWrite(const boost::system::error_code &ec) {
        
    }

    void P2PnetSession::Close() {
        boost::system::error_code ignored_ec;
        socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
    }

    int P2PnetSession::Split(std::vector<std::string>& vec, const std::string& str, const char pattern)
    {
        std::stringstream input(str);
        std::string temp;
        while (getline(input, temp, pattern))
        {
            vec.push_back(temp);
        }
        return (int)vec.size();
    }
}