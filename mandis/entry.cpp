#include "../include/entry.h"

namespace frontend {

    Entry::Entry(config::Config &config, foofs::FooFS &foofs, logger::Logger *logger)
        : config_(config), logger_(logger), foofs_(foofs)
    {

    }

    Entry::~Entry() {

    }
}