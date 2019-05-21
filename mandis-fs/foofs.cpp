#include "../include/foofs.h"
#include <cassert>
#include <fstream>
#include <sstream>
#include <boost/filesystem/path.hpp>
#include "../include/hashlib.h"

namespace foofs {

    FooFS::FooFS(config::Config *config, p2pnet::P2Pnet *p2pnet, logger::Logger *logger)
        : config_(config),
        p2pnet_(p2pnet), 
        logger_(logger)
    {
        cbfn = this;

        int ret = 0;
        char buffer[1024];
        std::vector<std::string> vec;

        std::ifstream fin(config_->block_filepath());
        while (fin) {
            fin.getline(buffer, sizeof(buffer));
            vec.clear();
            ret = Split(vec, buffer, '|');
            if (ret != Block::NR_ATTRIBUTE) {
                assert(0);
                continue;
            }

            std::set<std::string>::iterator iter = block_set_.find(vec[0]);
            if (iter != block_set_.end()) {
                // message: current block existed
                continue;
            }

            Block *block = new Block(vec[0], Str2Int(vec[1]), Str2Int(vec[2]));
            hash_to_block_.insert(std::pair<std::string, Block*>(block->hash_key(), block));
            block_set_.insert(block->hash_key());
            block_vec_.push_back(block);
        }
        fin.close();
        
        fin.open(config_->file_filepath());
        while (fin) {
            fin.getline(buffer, sizeof(buffer));
            vec.clear();
            ret = Split(vec, buffer, '|');
            if (ret != File::NR_ATTRIBUTE) {
                assert(0);
                continue;
            }

            File *file = new File(vec[0], vec[1], vec[2]);
            name_to_file_.insert(std::pair<std::string, File*>(file->file_name(), file));
            hash_to_file_.insert(std::pair<std::string, File*>(file->hash_key(), file));
            file_vec_.push_back(file);
        }
        fin.close();
    }

    FooFS::~FooFS() {
        for (auto iter = block_vec_.begin(); iter != block_vec_.end(); iter++)
            delete (*iter);
        for (auto iter = file_vec_.begin(); iter != file_vec_.end(); iter++)
            delete (*iter);
    }

    int FooFS::Write(std::string &filepath) {
        std::ifstream fin(filepath, std::ios::binary);
        if (!fin) {
            assert(0);
            // message: cannot open the file 'filepath'
            return -1;
        }

        std::string buffer_key;
        int buffer_size, buffer_flag;
        char buffer[1024 * 512];
        std::vector<std::string> buffer_key_vec;
        while (fin) {
            fin.read(buffer, 1024 * 512);
            buffer_size = fin.gcount();
            if (buffer_size <= 0) {
                assert(0);
                continue;
            }

            buffer_key = hashlib::Sha1::GetSha1(buffer, buffer_size);
            buffer_flag = 0;
            buffer_key_vec.push_back(buffer_key);

            std::set<std::string>::iterator iter = block_set_.find(buffer_key);
            if (iter != block_set_.end()) {
                // message: current block existed
                continue;
            }

            boost::filesystem::path out_path = boost::filesystem::path(config_->block_path()) / buffer_key;
            std::ofstream fout(out_path.string(), std::ios::binary);
            fout.write(buffer, buffer_size);
            fout.close();

            Block *block = new Block(buffer_key, buffer_size, buffer_flag);
            hash_to_block_.insert(std::pair<std::string, Block*>(block->hash_key(), block));
            block_set_.insert(block->hash_key());
            block_vec_.push_back(block);
        }
        fin.close();

        std::stringstream ss;
        for (auto iter = buffer_key_vec.begin(); iter != buffer_key_vec.end(); iter++) 
            ss << (*iter);
        strcpy(buffer, ss.str().c_str());
        buffer_size = (int)strlen(buffer);
        buffer_key = hashlib::Sha1::GetSha1(buffer, buffer_size);
        buffer_flag = 1;

        std::set<std::string>::iterator iter = block_set_.find(buffer_key);
        if (iter == block_set_.end()) {
            boost::filesystem::path out_path = boost::filesystem::path(config_->block_path()) / buffer_key;
            std::ofstream fout(out_path.string(), std::ios::binary);
            fout.write(buffer, buffer_size);
            fout.close();

            Block *block = new Block(buffer_key, buffer_size, buffer_flag);
            hash_to_block_.insert(std::pair<std::string, Block*>(block->hash_key(), block));
            block_set_.insert(block->hash_key());
            block_vec_.push_back(block);
        }

        std::string file_name = boost::filesystem::path(filepath).filename().string();
        std::string description;
        File *file = new File(file_name, description, buffer_key);
        name_to_file_.insert(std::pair<std::string, File*>(file->file_name(), file));
        hash_to_file_.insert(std::pair<std::string, File*>(file->hash_key(), file));
        file_vec_.push_back(file);

        return 0;
    }

    int FooFS::ReadByName(std::string &file_name, std::string &dest_path) {
        File *file = (*name_to_file_.find(file_name)).second;
        if (file == nullptr)
            return -1;


        return 0;
    }
    
    int FooFS::ReadByHash(std::string &file_hash) {
        File *file = (*hash_to_file_.find(file_hash)).second;
        if (file == nullptr)
            return 0;
        // TODO: not use
        assert(0);
        return 0;
    }

    int FooFS::Delete() {

        return 0;
    }

    int FooFS::ReadMetaData() {

        return 0;
    }

    void FooFS::Run() {

    }

    void FooFS::Start() {

    }

    void FooFS::Stop() {

    }

    void FooFS::Join() {

    }


    int FooFS::Split(std::vector<std::string> &vec, const std::string &str, const char pattern)
    {
        std::stringstream input(str);
        std::string temp;
        while (getline(input, temp, pattern))
        {
            vec.push_back(temp);
        }
        return (int)vec.size();
    }

    int FooFS::Str2Int(std::string &str) {
        int ret = 0;
        std::istringstream iss(str);
        iss >> ret;
        return ret;
    }

    ///for callback
    void CallBack(int cbtype, void* ptr) {
        FooFS *foofs = (FooFS*)cbfn;
        //foofs->DispatchSpi(cbtype, ptr);
    }
}