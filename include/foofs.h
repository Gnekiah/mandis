#ifndef MANDIS_MANDIS_FOOFS_H_
#define MANDIS_MANDIS_FOOFS_H_

#include <set>
#include <map>
#include <vector>
#include "../include/logger.h"
#include "../include/config.h"
#include "../include/p2pnet.h"
#include "../mandis-fs/file.h"
#include "../mandis-fs/block.h"

namespace foofs {

    class FooFS {
    public:
        FooFS(config::Config *config, p2pnet::P2Pnet *p2pnet, logger::Logger *logger);
        ~FooFS();

        void Write(std::string &filepath);
        void ReadByName(std::string &filename);
        void ReadByHash(std::string &filehash);
        void Delete();
        void ReadMetaData();

        void Run();
        void Start();
        void Stop();
        void Join();

    private:
        std::map<std::string, File*> name_to_file_;
        std::map<std::string, File*> hash_to_file_;
        std::map<std::string, Block*> hash_to_block_;
        std::set<std::string> block_set_;

        std::vector<File*> file_vec_;
        std::vector<Block*> block_vec_;

        config::Config *config_ = nullptr;
        p2pnet::P2Pnet *p2pnet_ = nullptr;
        logger::Logger *logger_ = nullptr;
    };
}

#endif // !#define MANDIS_MANDIS_FOOFS_H_

