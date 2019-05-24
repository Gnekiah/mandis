#ifndef MANDIS_MANDIS_P2P_NET_H_
#define MANDIS_MANDIS_P2P_NET_H_

#include <map>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/array.hpp>

#include "../include/config.h"
#include "../include/ssllib.h"
#include "../include/hashlib.h"
#include "../include/logger.h"
#include "../mandis-p2p/kadbucket.h"
#include "../mandis-p2p/p2pnet_session.h"
#include "../mandis-p2p/req_session.h"

namespace p2pnet {
    
    typedef boost::shared_ptr<P2PnetSession> session_ptr;
    typedef boost::shared_ptr<ReqSession> req_session_ptr;

    class P2Pnet : public boost::enable_shared_from_this<P2PnetSession> {
    public:
        P2Pnet(config::Config *config, logger::Logger *logger, config::callback_fn callback, boost::asio::io_context& ioc);
        ~P2Pnet();

        void Run();
        void Start();
        void Stop();
        void Join();

    public:
        /// store|<key>|<buffer_size>
        /// access|<key>
        /// sync|<msg>
        /// find|<key>
        /// ping
        int ReqStore(std::string key, std::string block_path);
        int ReqAccess(std::string key);
        int ReqSync(std::string msg);
        int ReqFind(std::string key);
        int Ping(); ///not used

    private:
        int RspStore(std::string block_path);
        int RspAccess(std::string key);
        int RspSync(std::string msg);
        int RspFind(std::string key);
        int Pong(); ///not used

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

