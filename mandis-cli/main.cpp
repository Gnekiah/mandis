#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>

class Session : public boost::enable_shared_from_this<Session> {
public:
    Session(boost::asio::io_context& ioc, const boost::asio::ip::tcp::endpoint& ep, std::string& msg)
        : ioc_(ioc),
        socket_(ioc),
        msg_(msg) {
        socket_.async_connect(ep, boost::bind(&Session::HandleConnect, this,
            boost::asio::placeholders::error));
    }

private:
    void HandleConnect(const boost::system::error_code& ec) {
        if (ec) {
            std::cerr << "Fatal: Error on HandleConnect" << std::endl;
            std::cerr << ec.message() << std::endl;
            return;
        }
        boost::asio::async_write(socket_, boost::asio::buffer(msg_.data(), msg_.length()), 
            boost::bind(&Session::HandleWrite, this, boost::asio::placeholders::error));
    }

    void HandleWrite(const boost::system::error_code& ec) {
        if (ec) {
            std::cerr << "Fatal: Error on HandleWrite" << std::endl;
            return;
        }
        boost::asio::async_read(socket_, boost::asio::buffer(buffer_.data(), 1024 * 512),
            boost::bind(&Session::HandleRead, shared_from_this(), boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
    }

    void HandleRead(const boost::system::error_code& ec, std::size_t bytes_transferred) {
        if (ec) {
            std::cerr << "Fatal: Error on HandleRead" << std::endl;
            return;
        }
    }

private:
    std::string &msg_;
    boost::asio::io_context& ioc_;
    boost::asio::ip::tcp::socket socket_;
    size_t buffer_length_;
    boost::array<unsigned char, 1024 * 512> buffer_;
};


int DoConnect(std::string ops="", std::string filepath="", std::string filename="") {
    /// ops = list, writ, read
    boost::asio::io_context ioc;
    boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string("127.0.0.1"), 60001);
    std::string msg = ops + "|" + filepath + "|" + filename;
    Session session(ioc, ep, msg);
    ioc.run();
    return 0;
}

int PrintUsage() {
    std::cerr << "[Usage]: mandis-cli [option] <target>" << std::endl
        << "  e.g.: " << std::endl
        << "      mandis-cli list" << std::endl
        << "      mandis-cli read filename filepath" << std::endl
        << "      mandis-cli write filepath" << std::endl
        << "      mandis-cli help" << std::endl;
    return 1;
}

int main(int argc, char** argv) {
    if (argc == 1)
        return PrintUsage();
    std::string option = argv[1];
    if (argc == 2) {
        if (option == "list") {
            std::cout << "read metadata ..." << std::endl;
            /// read metadata and show
            DoConnect("list");
            return 0;
        }
        else if (option == "help") {
            return PrintUsage();
        }
        else {
            std::cerr << "Fatal: unknown the option '" << option << "'" << std::endl;
            return PrintUsage();
        }
    }
    
    if (option == "write") {
        if (argc != 3) {
            std::cerr << "Fatal: command error" << std::endl;
            return PrintUsage();
        }
        std::string filepath = argv[2];
        std::cout << "write: " << filepath << std::endl;
        /// write [filepath] to mandis
        DoConnect("writ", filepath);
        return 0;
    }

    if (option == "read") {
        if (argc != 4) {
            std::cerr << "Fatal: command error" << std::endl;
            return PrintUsage();
        }
        std::string filename = argv[2];
        std::string filepath = argv[3];
        std::cout << "read: " << filename << " from mandis to " << filepath << std::endl;
        /// read [filename] from mandis to [filepath]
        DoConnect("read", filepath, filename);
        return 0;
    }

    return 0;
}