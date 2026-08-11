#pragma once
#include"sha256.h"
#include<bits/stdc++.h>
using namespace std;
class Block{
    public:

    int index;
    int64_t timestamp;
    string hash;
    string previousHash;
    string data;
    int64_t nonce;

    Block(int idx, string blkData , string prevHash){
        index=idx;
        timestamp=time(nullptr);
        data=blkData;
        previousHash=prevHash;
        nonce=0;
        hash=calculateHash();
    }

    string calculateHash() const{
        string toHash= to_string(index)+to_string(timestamp)+data+previousHash+to_string(nonce);

        return picosha256::hash256_hex_string(toHash);

    }



};