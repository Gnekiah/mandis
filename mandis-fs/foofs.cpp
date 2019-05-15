#include "../include/foofs.h"
#include <cassert>
#include <fstream>

namespace foofs {

    FooFS::FooFS(config::Config *config, p2pnet::P2Pnet *p2pnet, logger::Logger *logger) 
        : config_(config),
        p2pnet_(p2pnet), 
        logger_(logger)
    {
        std::ifstream fin(config_->block_filepath());
        while (fin) {
            
        }
        //std::map<std::string, Block*> hash_to_block_;
        //std::set<std::string> block_set_;
        //std::vector<Block*> block_vec_;
        fin.close();
        
        fin.open(config_->file_filepath());
        /*
        std::map<std::string, File*> name_to_file_;
        std::map<std::string, File*> hash_to_file_;
        std::vector<File*> file_vec_;
        */
        fin.close();
    }

    FooFS::~FooFS() {

    }

    void FooFS::Write(std::string &filepath) {
        
    }

    void FooFS::ReadByName(std::string &filename) {  
        File *file = (*name_to_file_.find(filename)).second;
        if (file == nullptr)
            return;
    }
    
    void FooFS::ReadByHash(std::string &filehash) {
        File *file = (*hash_to_file_.find(filehash)).second;
        if (file == nullptr)
            return;

        // TODO: not use
        assert(0);
    }

    void FooFS::Delete() {

    }

    void FooFS::ReadMetaData() {

    }

    void FooFS::Run() {

    }

    void FooFS::Start() {

    }

    void FooFS::Stop() {

    }

    void FooFS::Join() {

    }
}