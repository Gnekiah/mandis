#include "req_session.h"
#include <fstream>
#include <boost/lexical_cast.hpp>

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
        socket_.connect(ep_);
    }

    int ReqSession::DoReqStore(std::string key, std::string block_path) {
        int block_buffer_size;
        char block_buffer[1024 * 512];
        std::ifstream fin(block_path, std::ios::binary);
        if (!fin) {
            LOG_WARNING(logger_, "Block File Not Found");
            return -1;
        }

        fin.read(block_buffer, 1024 * 512);
        block_buffer_size = fin.gcount();
        fin.close();

        /// command: store|<key>|<buffer_size>
        std::string cmd = "store|" + key + "|" + boost::lexical_cast<std::string>(block_buffer_size);
        LOG_TRACE(logger_, "Send Command: " + cmd);
        boost::asio::write(socket_, boost::asio::buffer(cmd.data(), cmd.length()));
        LOG_TRACE(logger_, "Send Data, Size=" + boost::lexical_cast<std::string>(block_buffer_size));
        boost::asio::write(socket_, boost::asio::buffer(block_buffer, block_buffer_size));
        socket_.close();
        return 0;
    }

    int ReqSession::DoReqAccess(std::string key, std::string block_path) {
        int block_buffer_size;
        char block_buffer[1024 * 512];

        /// command: access|<key>
        std::string cmd = "access|" + key;
        LOG_TRACE(logger_, "Send Command: " + cmd);
        boost::asio::write(socket_, boost::asio::buffer(cmd.data(), cmd.length()));
        block_buffer_size = socket_.read_some(boost::asio::buffer(block_buffer, 1024 * 512));
        LOG_TRACE(logger_, "Receive Data, Size=" + boost::lexical_cast<std::string>(block_buffer_size));
        boost::asio::read(socket_, boost::asio::buffer(block_buffer, block_buffer_size));

        std::ofstream fout(block_path, std::ios::binary);
        if (!fout) {
            LOG_WARNING(logger_, "Block File Cannot Open");
            return -1;
        }
        fout.write(block_buffer, block_buffer_size);
        fout.close();
        socket_.close();
        return 0;
    }

    int ReqSession::DoReqSync(std::string msg) {
        /// command: sync|<msg>
        std::string cmd = "sync|" + msg;
        LOG_TRACE(logger_, "Send Command: " + cmd);
        boost::asio::write(socket_, boost::asio::buffer(cmd.data(), cmd.length()));
        socket_.close();
        return 0;
    }

    std::string ReqSession::DoReqFind(std::string key) {
        int block_buffer_size;
        char block_buffer[1024 * 512];

        /// command: sync|<msg>
        std::string cmd = "sync|" + key;
        LOG_TRACE(logger_, "Send Command: " + cmd);
        boost::asio::write(socket_, boost::asio::buffer(cmd.data(), cmd.length()));
        block_buffer_size = socket_.read_some(boost::asio::buffer(block_buffer, 1024 * 512));

        LOG_TRACE(logger_, "Receive Data, Size=" + boost::lexical_cast<std::string>(block_buffer_size));
        boost::asio::read(socket_, boost::asio::buffer(block_buffer, block_buffer_size));
        socket_.close();
        ///TODO
        block_buffer[block_buffer_size] = '\0';
        std::string found_buffer = std::string(block_buffer);
        LOG_TRACE(logger_, "On Response ReqFind: " + found_buffer);
        return found_buffer;
    }

    int ReqSession::DoPing() {
        ///not used
        return 0;
    }
}