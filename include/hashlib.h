#ifndef MANDIS_HASHLIB_H_
#define MANDIS_HASHLIB_H_

#include <cstdint>
#include <string>

namespace hashlib {
    class Sha1 {
    public:
        Sha1(const char *msg, size_t len);
        Sha1(const std::string &str);
        ~Sha1() { }

        const uint32_t* sha1() const { return sha1_; }
        const uint8_t* sha1_str() const { return sha1_str_; }

        static std::string GetSha1(const char *msg, size_t len);
        static std::string GetSha1(const std::string &str);

    private:
        uint32_t sha1_[5];
        uint8_t sha1_str_[41];
    };

} // namespace hashlib 

#endif // !MANDIS_HASHLIB_H_

