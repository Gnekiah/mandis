#ifndef MANDIS_MANDIS_P2P_NET_H_
#define MANDIS_MANDIS_P2P_NET_H_

#include <map>
#include <boost/asio.hpp>

#include "../include/config.h"
#include "../include/ssllib.h"
#include "../include/hashlib.h"
#include "../include/logger.h"
#include "../mandis-p2p/kadbucket.h"
#include "../mandis-p2p/p2pnet_session.h"

namespace p2pnet {
    
    typedef boost::shared_ptr<P2PnetSession> session_ptr;

    class P2Pnet {
    public:
        P2Pnet(config::Config *config, logger::Logger *logger, config::callback_fn callback, boost::asio::io_context& ioc);
        ~P2Pnet();

        void Run();
        void Start();
        void Stop();
        void Join();

    private:
        ssllib::RsaPair key_;
        hashlib::DigestField id_;
        std::map<int, KadBucket*> * bucket_ = nullptr;
        logger::Logger *logger_ = nullptr;
        config::Config *config_ = nullptr;
        config::callback_fn callback_ = nullptr;

    private:
        void StartAccept();
        void HandleAccept(session_ptr session, const boost::system::error_code& ec);

    private:
        boost::asio::io_context& ioc_;
        boost::asio::ip::tcp::acceptor acceptor_;
    };
}

#endif // !MANDIS_MANDIS_P2P_NET_H_

