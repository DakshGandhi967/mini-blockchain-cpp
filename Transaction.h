#pragma once

#include<bits/stdc++.h>
using namespace std;

class Transaction{
    public:

        string sender;
        string reciever;
        double amount;

        Transaction() : sender(""), reciever(""),amount(0.0){}

        Transaction(string from , string to , double amnt){
            sender = from;
            reciever = to ;
            amount = amnt;
        }

        void printTransaction() const {
        std::cout << "  [" << sender << " -> " << reciever << " : $" << amount << "]" << std::endl;
    }
};