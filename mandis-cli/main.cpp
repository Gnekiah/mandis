#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/array.hpp>





#include <cstdlib>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>




class Session {
public:
    Session(boost::asio::io_context& ioc, const boost::asio::ip::tcp::endpoint& ep)
        : ioc_(ioc),
        socket_(ioc) {
        boost::asio::async_connect(socket_, ep, boost::bind(&Session::HandleConnect, this, 
            boost::asio::placeholders::error));
    }

private:
    void HandleConnect(const boost::system::error_code& ec) {

    }

private:
    boost::asio::io_context& ioc_;
    boost::asio::ip::tcp::socket socket_;
    size_t buffer_length_;
    boost::array<unsigned char, 1024 * 512> buffer_;
};

class chat_client
{
public:
    void write(const chat_message& msg)
    {
        boost::asio::post(io_context_,
            boost::bind(&chat_client::do_write, this, msg));
    }

    void close()
    {
        boost::asio::post(io_context_,
            boost::bind(&chat_client::do_close, this));
    }

private:

    void handle_connect(const boost::system::error_code& error)
    {
        if (!error)
        {
            boost::asio::async_read(socket_,
                boost::asio::buffer(read_msg_.data(), chat_message::header_length),
                boost::bind(&chat_client::handle_read_header, this,
                    boost::asio::placeholders::error));
        }
    }

    void handle_read_header(const boost::system::error_code& error)
    {
        if (!error && read_msg_.decode_header())
        {
            boost::asio::async_read(socket_,
                boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
                boost::bind(&chat_client::handle_read_body, this,
                    boost::asio::placeholders::error));
        }
        else
        {
            do_close();
        }
    }

    void handle_read_body(const boost::system::error_code& error)
    {
        if (!error)
        {
            std::cout.write(read_msg_.body(), read_msg_.body_length());
            std::cout << "\n";
            boost::asio::async_read(socket_,
                boost::asio::buffer(read_msg_.data(), chat_message::header_length),
                boost::bind(&chat_client::handle_read_header, this,
                    boost::asio::placeholders::error));
        }
        else
        {
            do_close();
        }
    }

    void do_write(chat_message msg)
    {
        bool write_in_progress = !write_msgs_.empty();
        write_msgs_.push_back(msg);
        if (!write_in_progress)
        {
            boost::asio::async_write(socket_,
                boost::asio::buffer(write_msgs_.front().data(),
                    write_msgs_.front().length()),
                boost::bind(&chat_client::handle_write, this,
                    boost::asio::placeholders::error));
        }
    }

    void handle_write(const boost::system::error_code& error)
    {
        if (!error)
        {
            write_msgs_.pop_front();
            if (!write_msgs_.empty())
            {
                boost::asio::async_write(socket_,
                    boost::asio::buffer(write_msgs_.front().data(),
                        write_msgs_.front().length()),
                    boost::bind(&chat_client::handle_write, this,
                        boost::asio::placeholders::error));
            }
        }
        else
        {
            do_close();
        }
    }

    void do_close()
    {
        socket_.close();
    }

private:
    boost::asio::io_context& io_context_;
    boost::asio::ip::tcp::socket socket_;
    chat_message read_msg_;
    chat_message_queue write_msgs_;
};

int main(int argc, char* argv[])
{

        chat_client c(io_context, endpoints);
        boost::thread t(boost::bind(&boost::asio::io_context::run, &io_context));

        char line[chat_message::max_body_length + 1];
        while (std::cin.getline(line, chat_message::max_body_length + 1))
        {
            using namespace std; // For strlen and memcpy.
            chat_message msg;
            msg.body_length(strlen(line));
            memcpy(msg.body(), line, msg.body_length());
            msg.encode_header();
            c.write(msg);
        }

        c.close();
        t.join();

    return 0;
}






















int DoConnect(std::string ops="", std::string filepath="", std::string filename="") {
    /// ops = list, writ, read
    boost::asio::io_context ioc;
    boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string("127.0.0.1"), 60001);
    Session session(ioc, ep);


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