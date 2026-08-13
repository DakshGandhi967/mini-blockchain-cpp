#pragma once
#include "Transaction.h"
#include <vector>
#include <iostream>
#include "Block.h"

using namespace std;

class Blockchain{
    private:
        vector<Block> chain;
        vector<Transaction> pendingTransactions;

        Block createGenesisBlock(){
            vector<Transaction> genesisTxs;
            genesisTxs.push_back(Transaction("System", "Genesis", 0.0));
            return Block(0,genesisTxs,"0");
        }

    public: 
        Blockchain(){
            chain.push_back(createGenesisBlock());
        }

        Block getLatestBlock() const {
            return chain.back();
        }

        void createTransaction(Transaction tx) {
        pendingTransactions.push_back(tx);
    }

        void minePendingTransactions(string minerAddress){
            int nextIndex=chain.size();

            string prevHash=getLatestBlock().hash;
            Block newBlock(nextIndex,pendingTransactions,prevHash);
            chain.push_back(newBlock);

            pendingTransactions.clear();
            pendingTransactions.push_back(Transaction("System", minerAddress, 10.0));
        }

        double getBalanceOfAddress(string address) const{
            double balance=0.0;

            for (const auto& block : chain) {
            for (const auto& tx : block.transactions) {
                if (tx.sender == address) {
                    balance -= tx.amount; // Deduct if address spent money
                }
                if (tx.reciever == address) {
                    balance += tx.amount; // Add if address received money
                }
            }
        }
        return balance;
        }
     




        bool isChainValid() const{
            for(size_t i=1 ;i<chain.size();++i){

                const Block& currentBlock = chain[i];
            const Block& previousBlock = chain[i - 1];

                if (currentBlock.hash != currentBlock.calculateHash()) {
                std::cout << "Validation Error: Block #" << currentBlock.index 
                          << " has been tampered with!" << std::endl;
                return false;
            }

            if (currentBlock.previousHash != previousBlock.hash) {
                std::cout << "Validation Error: Block #" << currentBlock.index 
                          << "'s previousHash does not match Block #" 
                          << previousBlock.index << "'s hash!" << std::endl;
                return false;
            }


            }
            return true;
        }

    void printChain() const {
       for (const auto& block : chain) {
            std::cout << "----------------------------------------" << std::endl;
            std::cout << "Block #" << block.index << " [Hash: " << block.hash.substr(0, 10) << "...]" << std::endl;
            std::cout << "Prev Hash: " << block.previousHash.substr(0, 10) << "..." << std::endl;
            std::cout << "Transactions:" << std::endl;
            for (const auto& tx : block.transactions) {
                tx.printTransaction();
            }
        }
        std::cout << "----------------------------------------" << std::endl;
    }
    


    // Expose direct reference to test tampering scenarios
    vector<Block>& getChainMutable(){
        return chain;
    }
        
};