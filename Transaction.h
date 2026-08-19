#pragma once
#include"sha256.h"
#include<bits/stdc++.h>
using namespace std;

class Transaction{
    public:

        string sender;
        string reciever;
        double amount;
        string signature;

       Transaction() 
        : sender(""), reciever(""), amount(0.0), signature("") {}

     Transaction(string from, string to, double amnt)
        : sender(from), reciever(to), amount(amnt), signature("") {}


        string calculateHash() const {
        return picosha256::hash256_hex_string(sender + reciever + to_string(amount));
    }

    bool isValid() const {
     
        if (sender == "SYSTEM" || sender == "System") {
            return true;
        }

        if (signature.empty()) {
            cout << "[ERROR] Transaction has no signature!\n";
            return false;
        }

       size_t delimiterPos = signature.find(':');
        if (delimiterPos == string::npos) {
            cout << "[SECURITY ERROR] Malformed signature!\n";
            return false;
        }

        string revealedKey = signature.substr(0, delimiterPos);
        string proof = signature.substr(delimiterPos + 1);


        if (picosha256::hash256_hex_string(revealedKey) != sender) {
            cout << "[SECURITY ERROR] Signature does not match sender's public address!\n";
            return false;
        }



        string expectedProof = picosha256::hash256_hex_string(calculateHash() + revealedKey);
        if (proof != expectedProof) {
            cout << "[SECURITY ERROR] Signature proof does not match transaction data (Tampered)!\n";
            return false;
        }

        return true;


    }

        void printTransaction() const {
        std::cout << "  [" << sender << " -> " << reciever << " : $" << amount << "]" << std::endl;
    }
};