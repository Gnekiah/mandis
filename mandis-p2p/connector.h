#ifndef MANDIS_MANDIS_P2P_CONNECTOR_H_
#define MANDIS_MANDIS_P2P_CONNECTOR_H_

namespace p2pnet {
    class Connector {
    public:

        void ReqPing();
        void ReqFind();
        void ReqStore();
        void ReqSync();

    private:

    };
}

#endif // !MANDIS_MANDIS_P2P_CONNECTOR_H_
