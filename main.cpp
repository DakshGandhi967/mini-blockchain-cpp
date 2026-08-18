#include <iostream>
#include "Blockchain.h"

int main() {
    Blockchain myChain(3, 10.0); // Difficulty: 3 leading zeros, Reward: 10 coins

    std::cout << "\nAdding transactions...\n";
    myChain.createTransaction(Transaction("Alice", "Bob", 50.0));
    myChain.createTransaction(Transaction("Bob", "Charlie", 25.0));

    std::cout << "\nStarting miner for Miner1...\n";
    myChain.minePendingTransactions("Miner1");

    std::cout << "\nAdding more transactions...\n";
    myChain.createTransaction(Transaction("Charlie", "Alice", 10.0));

    std::cout << "\nStarting miner for Miner2...\n";
    myChain.minePendingTransactions("Miner2");

    std::cout << "\nIs Blockchain Valid? " 
              << (myChain.isChainValid() ? "Yes (Valid)" : "No (Corrupted)") 
              << "\n";

    return 0;
}