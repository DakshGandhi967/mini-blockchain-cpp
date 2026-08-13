#pragma once
#include"sha256.h"
#include<bits/stdc++.h>
#include"Transaction.h"
using namespace std;
class Block{
    public:

    int index;
    int64_t timestamp;
    string hash;
    string previousHash;
    vector<Transaction> transactions;
    int64_t nonce;

    Block(int idx, vector<Transaction> txs , string prevHash){
        index=idx;
        timestamp=time(nullptr);
        transactions=txs;
        previousHash=prevHash;
        nonce=0;
        hash=calculateHash();
    }

    string getTransactionsString() const {
        string txStr = "";
        for (const auto& tx : transactions) {
            txStr += tx.sender + tx.reciever + std::to_string(tx.amount);
        }
        return txStr;
    }

    string calculateHash() const{
        string toHash= to_string(index)+to_string(timestamp)+getTransactionsString()+previousHash+to_string(nonce);

        return picosha256::hash256_hex_string(toHash);

    }



};