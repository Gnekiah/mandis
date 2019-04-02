#ifndef MANDIS_MANDIS_P2P_NET_H_
#define MANDIS_MANDIS_P2P_NET_H_

#include <map>

#include "../include/ssllib.h"
#include "../include/hashlib.h"
#include "../include/logger.h"
#include "../mandis-p2p/kadbucket.h"

namespace p2pnet {
    
    class P2Pnet {
    public:
        P2Pnet();
        ~P2Pnet();

    private:
        ssllib::RsaPair key_;
        hashlib::DigestField id_;
        std::map<int, KadBucket*> * bucket_ = nullptr;
        logger::Logger *logger_ = nullptr;

    };
}

#endif // !MANDIS_MANDIS_P2P_NET_H_

