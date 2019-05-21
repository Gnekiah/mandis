#ifndef MANDIS_MANDIS_ENTRY_SESSION_H_
#define MANDIS_MANDIS_ENTRY_SESSION_H_

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/enable_shared_from_this.hpp>

namespace frontend {

    class EntrySession : public boost::enable_shared_from_this<EntrySession> {
    public:
        EntrySession(boost::asio::io_context& ioc);
        ~EntrySession();

        void Start();

        boost::asio::ip::tcp::socket& socket();

    private:
        /* Handle completion of a read operation. */
        void HandleRead(const boost::system::error_code &ec, std::size_t bytes_transferred);
        /* Handle completion of a write operation. */
        void HandleWrite(const boost::system::error_code &ec);
        int ParsePackage(unsigned char* buff, size_t offset);
        /* Close the session. */
        void Close();

    private:
        size_t buffer_length_;
        boost::array<unsigned char, 1024 * 512> buffer_;
        boost::asio::ip::tcp::socket socket_;
    };
}

#endif // !MANDIS_MANDIS_ENTRY_SESSION_H_

