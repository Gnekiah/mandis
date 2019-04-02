#ifndef MANDIS_MANDIS_P2P_SESSION_H_
#define MANDIS_MANDIS_P2P_SESSION_H_

#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>

namespace p2pnet {
    typedef void pSessionCallback(std::string, std::string);

    class Session : public boost::enable_shared_from_this<Session> {
    public:
        Session(boost::asio::io_service& ios);
        virtual ~Session();

        void Start();
        void SetCallback(pSessionCallback* callback) { callback_ = callback; }

        boost::asio::ip::tcp::socket& socket(void);

    private:
        void InitHandler(const boost::system::error_code &error);
        void ParseHandler(const boost::system::error_code &error);
        void DoneHandler(const boost::system::error_code &error);
        void ReadHandler(const boost::system::error_code &error, size_t read_size);
        void WriteHandler(const boost::system::error_code &error);
       
    private:
        char buffer_[1024];
        int buffer_size_;
        boost::asio::ip::tcp::socket socket_;
        pSessionCallback *callback_;
    };

}

#endif // !MANDIS_MANDIS_P2P_SESSION_H_
