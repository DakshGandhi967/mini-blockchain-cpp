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
        int difficulty;
        double mining_reward;

        Block createGenesisBlock(){
            vector<Transaction> genesisTxs;
            genesisTxs.push_back(Transaction("System", "Genesis", 0.0));

            Block genesis(0,genesisTxs,"0");
            genesis.mineBlock(difficulty);
            return genesis;
        }

    public: 
        Blockchain(int diff=3 , double reward=40) : difficulty(diff) , mining_reward(reward){
            chain.push_back(createGenesisBlock());
        }

        Block getLatestBlock() const {
            return chain.back();
        }

        bool createTransaction(const Transaction& tx){
            if(tx.amount<=0){
               cout << "[ERROR] Transaction amount must be positive.\n";
                return false; 
            }

            if (tx.sender != "SYSTEM" && tx.sender != "System") {
        double senderBalance = getBalanceOfAddress(tx.sender);
        if (senderBalance < tx.amount) {
            std::cout << "[ERROR] Insufficient balance for " << tx.sender 
                      << " (Current Balance: " << senderBalance 
                      << ", Requested: " << tx.amount << ")\n";
            return false;
        }
    }       

        pendingTransactions.push_back(tx);

        cout << "[SUCCESS] Transaction queued: " << tx.sender << " -> " 
              << tx.reciever << " (" << tx.amount << " coins)\n";
    return true;


        }

        void minePendingTransactions(string minerAddress){
            Block newBlock(chain.size(),pendingTransactions,getLatestBlock().hash);
            newBlock.mineBlock(difficulty);

            chain.push_back(newBlock);

            pendingTransactions= {Transaction("SYSTEM",minerAddress,mining_reward)};
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

            string target(difficulty,'0');
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
            if (currentBlock.hash.substr(0, difficulty) != target) return false;


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