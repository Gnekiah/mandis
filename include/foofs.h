#ifndef MANDIS_MANDIS_FOOFS_H_
#define MANDIS_MANDIS_FOOFS_H_

#include "../include/logger.h"

namespace foofs {

    class FooFS {
    public:
        FooFS();
        ~FooFS();

        void Write();
        void Read();
        void Delete();
        void ReadMetaData();

    private:
        

    };
}

#endif // !#define MANDIS_MANDIS_FOOFS_H_

