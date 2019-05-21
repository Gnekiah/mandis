#ifndef MANDIS_MANDIS_P2PNET_SESSION_H_
#define MANDIS_MANDIS_P2PNET_SESSION_H_

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

namespace p2pnet {
    
    class P2PnetSession {

    public:
        P2PnetSession(boost::asio::io_context& ioc);
        ~P2PnetSession();

        void Start();

        boost::asio::ip::tcp::socket& socket();

    private:
        /* Handle completion of a read operation. */
        void HandleRead(const boost::system::error_code &ec, std::size_t bytes_transferred);
        /* Handle completion of a write operation. */
        void HandleWrite(const boost::system::error_code &ec);
        /* Close the session. */
        void Close();

    private:
        boost::asio::ip::tcp::socket socket_;

    };
}

#endif // !MANDIS_MANDIS_P2PNET_SESSION_H_
