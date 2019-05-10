#ifndef MANDIS_MANDIS_FILE_H_
#define MANDIS_MANDIS_FILE_H_

#include <string>
#include <vector>

namespace foofs {

    class File {
    public:
        File();
        ~File();

    private:
        std::string file_name_;
        std::string description_;
        /* hash value of current file */
        std::string hash_key_;
        /* hash list: blocks set of current file */
        std::vector<std::string> hash_list_;    
        
    };
}

#endif // !MANDIS_MANDIS_FILE_H_

