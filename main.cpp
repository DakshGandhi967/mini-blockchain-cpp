#include <iostream>
#include "Blockchain.h"

int main() {
    Blockchain myChain(3, 50.0);

    cout << "\n=== Stage 5: Balance & Double-Spend Testing ===\n";

    // 1. Miner earns initial reward by mining
    cout << "\nMiner1 mining first block...\n";
    myChain.minePendingTransactions("Miner1");

    cout << "Miner1 Balance: " << myChain.getBalanceOfAddress("Miner1") << " coins\n";
    cout << "Alice Balance:  " << myChain.getBalanceOfAddress("Alice") << " coins\n";

    // 2. Miner1 transfers 20 coins to Alice (Valid)
    cout << "\nAttempting valid transfer: Miner1 -> Alice (20 coins)\n";
    myChain.createTransaction(Transaction("Miner1", "Alice", 20.0));

    // 3. Alice attempts to transfer 30 coins before receiving (Invalid / Overdraft)
    cout << "\nAttempting invalid transfer: Alice -> Bob (30 coins)\n";
    myChain.createTransaction(Transaction("Alice", "Bob", 30.0));

    // 4. Mine pending transactions to commit Miner1 -> Alice
    cout << "\nMining second block...\n";
    myChain.minePendingTransactions("Miner2");

    // 5. Final balances
    cout << "\nFinal Balances:\n";
    cout << "Miner1 Balance: " << myChain.getBalanceOfAddress("Miner1") << " coins\n";
    cout << "Alice Balance:  " << myChain.getBalanceOfAddress("Alice") << " coins\n";
    cout << "Miner2 Balance: " << myChain.getBalanceOfAddress("Miner2") << " coins\n";

    cout << "\nIs Chain Valid? " << (myChain.isChainValid() ? "Yes" : "No") << "\n";

    return 0;
}