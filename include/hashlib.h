#ifndef MANDIS_HASHLIB_H_
#define MANDIS_HASHLIB_H_

#include <cstdint>
#include <string>

namespace hashlib {

    typedef uint32_t DigestField[5];
        
    class Sha1 {
    public:
        static std::string GetSha1(const char *msg, size_t len);
        static std::string GetSha1(const std::string &str);
        static int GetSha1(const char *msg, size_t len, DigestField &bytes);
        static int GetSha1(const std::string &str, DigestField &bytes);

        static std::string Bytes2Str(const DigestField &bytes);
        static int Str2Bytes(const std::string &str, DigestField &bytes);
    };

} // namespace hashlib 

#endif // !MANDIS_HASHLIB_H_

