#ifndef MANDIS_TEST_HASHLIB_HPP_
#define MANDIS_TEST_HASHLIB_HPP_

#include <iostream>

#include "../include/hashlib.h"

const char* TestSha1Case1(const char* msg, int len) {
    char hashstr[41];
    hashstr[40] = '\0';
    hashlib::Sha1 sha1(msg, len);
    const uint8_t* ptr = sha1.sha1_str();
    memcpy(hashstr, ptr, 40);
    return hashstr;
}

const std::string TestSha1Case2(const char* msg, int len) {
    return hashlib::Sha1::GetSha1(msg, len);
}

const char* TestSha1Case3(const std::string msg) {
    char hashstr[41];
    hashstr[40] = '\0';
    hashlib::Sha1 sha1(msg);
    const uint8_t* ptr = sha1.sha1_str();
    memcpy(hashstr, ptr, 40);
    return hashstr;
}

const std::string TestSha1Case4(const std::string msg) {
    return hashlib::Sha1::GetSha1(msg);
}


#endif // !MANDIS_TEST_HASHLIB_HPP_