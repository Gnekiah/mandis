#ifndef MANDIS_MANDIS_P2P_SERVER_H_
#define MANDIS_MANDIS_P2P_SERVER_H_

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>

#include "../include/logger.h"
#include "session.h"
#include "request_handler.h"

namespace p2pnet {
    typedef boost::shared_ptr<Session> session_ptr;

    class Server : private boost::noncopyable
    {
    public:
        explicit Server(logger::Logger *logger, int port, size_t thread_pool_size);
        virtual ~Server();

        void Run();
        void Start();
        void Join();
        void Stop();

    private:
        void HandleAccept(session_ptr session, const boost::system::error_code& ec);
        void CallbackSession(const boost::system::error_code& ec);

    private:
        boost::asio::io_service& ios_;
        boost::asio::ip::tcp::acceptor acceptor_;
        logger::Logger * logger_ = nullptr;
    };

}

#endif // !MANDIS_MANDIS_P2P_SERVER_H_

