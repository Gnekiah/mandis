#ifndef MANDIS_MANDIS_ENTRY_H_
#define MANDIS_MANDIS_ENTRY_H_

#include "../include/logger.h"
#include "../include/config.h"
#include "../include/foofs.h"

namespace frontend {

    class Entry {
    public:
        Entry(config::Config *config, foofs::FooFS *foofs, logger::Logger *logger);
        ~Entry();

    private:
        config::Config *config_ = nullptr;
        foofs::FooFS *foofs_ = nullptr;
        logger::Logger *logger_ = nullptr;

    };
}

#endif // !MANDIS_MANDIS_ENTRY_H_

