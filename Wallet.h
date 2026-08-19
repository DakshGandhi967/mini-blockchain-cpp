#pragma once
#include<bits/stdc++.h>
#include"sha256.h"
#include"Transaction.h"

using namespace std;


class Wallet {
    private:

    string privateKey;

    string generateRandomKey(){
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<uint64_t> dis;
        
        return  picosha256::hash256_hex_string(to_string(dis(gen))+to_string(dis(gen)));
    }

    public:
        string publicKey;

        Wallet(){
            privateKey=generateRandomKey();
            publicKey=picosha256::hash256_hex_string(privateKey);

        }

        string getAddress() const{
            return publicKey;
        }

        void signTransaction(Transaction& tx) const{
            if(tx.sender!=publicKey){
                cout << "[ERROR] Cannot sign: wallet address does not match sender!\n";
            return;
            }
        std::string txHash = tx.calculateHash();
        std::string proof = picosha256::hash256_hex_string(txHash + privateKey);
        tx.signature = privateKey + ":" + proof;
        }


};