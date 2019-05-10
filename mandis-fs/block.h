#ifndef MANDIS_MANDIS_BLOCK_H_
#define MANDIS_MANDIS_BLOCK_H_

#include <string>

namespace foofs {

    class Block {
    public:
        Block();
        ~Block();

    private:
        std::string hash_key_;
        int buffer_size_;
        unsigned char buffer_[1024 * 256];
    };

}

#endif // !MANDIS_MANDIS_BLOCK_H_

