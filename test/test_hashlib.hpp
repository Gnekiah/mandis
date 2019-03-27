#ifndef MANDIS_TEST_HASHLIB_HPP_
#define MANDIS_TEST_HASHLIB_HPP_

#include <iostream>

#include "../include/hashlib.h"

const std::string TestSha1Case1(const std::string msg) {
    hashlib::DigestField digest;
    hashlib::Sha1::GetSha1(msg, digest);
    return hashlib::Sha1::Bytes2Str(digest);
}

const bool TestSha1Case2(const char* msg, int len) {
    hashlib::DigestField digest1, digest2;
    std::string hashval = hashlib::Sha1::GetSha1(msg, len);
    hashlib::Sha1::GetSha1(msg, len, digest2);

    hashlib::Sha1::Str2Bytes(hashval, digest1);
    for (int i = 0; i < 5; i++) {
        if (digest1[i] != digest2[i])
            return 1;
    }
    return 0;
}

#endif // !MANDIS_TEST_HASHLIB_HPP_