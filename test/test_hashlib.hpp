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

const int TestSha1Case3(const std::string &msg1, const std::string &msg2, std::string &res) {
    int ret = 0;
    hashlib::DigestField d1, d2, retd1, retd2, retd3;
    hashlib::Sha1::Str2Bytes(msg1, d1);
    hashlib::Sha1::Str2Bytes(msg2, d2);
    std::string rets1 = hashlib::Sha1::XorMetric(msg1, msg2);
    std::string rets2 = hashlib::Sha1::XorMetric(msg1, d2);
    std::string rets3 = hashlib::Sha1::XorMetric(d1, d2);
    hashlib::Sha1::XorMetric(msg1, msg2, retd1);
    hashlib::Sha1::XorMetric(msg1, d2, retd2);
    hashlib::Sha1::XorMetric(d1, d2, retd3);

    if (rets1 != rets2)
        ret++;
    if (rets1 != rets3)
        ret++;
    if (hashlib::Sha1::Bytes2Str(retd1) != hashlib::Sha1::Bytes2Str(retd2))
        ret++;
    if (hashlib::Sha1::Bytes2Str(retd1) != hashlib::Sha1::Bytes2Str(retd3))
        ret++;
    if (hashlib::Sha1::Bytes2Str(retd1) != rets1)
        ret++;
    res = rets1;
    return ret;
}

#endif // !MANDIS_TEST_HASHLIB_HPP_