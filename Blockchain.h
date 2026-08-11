#pragma once

#include <vector>
#include <iostream>
#include "Block.h"

using namespace std;

class Blockchain{
    private:
        vector<Block> chain;

        Block createGenesisBlock(){
            return Block(0,"Genesis Block Data","0");
        }

    public: 
        Blockchain(){
            chain.push_back(createGenesisBlock());
        }

        Block getLatestBlock() const {
            return chain.back();
        }

        void addBlock(string data){
            int nextIndex=chain.size();
            string prevHash=getLatestBlock().hash;

            Block newBlock(nextIndex,data,prevHash);
            chain.push_back(newBlock);
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
            std::cout << "Index: " << block.index << std::endl;
            std::cout << "Timestamp: " << block.timestamp << std::endl;
            std::cout << "Data: " << block.data << std::endl;
            std::cout << "Prev Hash: " << block.previousHash << std::endl;
            std::cout << "Hash: " << block.hash << std::endl;
        }
        std::cout << "----------------------------------------" << std::endl;
    }


    // Expose direct reference to test tampering scenarios
    vector<Block>& getChainMutable(){
        return chain;
    }
        
};