#include <iostream>
#include "Blockchain.h"
#include "Wallet.h"

int main() {
    // Initialize blockchain with difficulty 2 and mining reward of 50 coins
    Blockchain myChain(2, 50.0);

    // 1. Create Wallets for Alice and Bob
    Wallet alice;
    Wallet bob;
    Wallet attacker;

    std::cout << "==================================================\n";
    std::cout << "          BLOCKCHAIN WALLET & SIGNATURE DEMO      \n";
    std::cout << "==================================================\n";
    std::cout << "Alice Address:    " << alice.getAddress() << "\n";
    std::cout << "Bob Address:      " << bob.getAddress() << "\n";
    std::cout << "Attacker Address: " << attacker.getAddress() << "\n\n";

    // 2. Mine an initial block to fund Alice's wallet
    std::cout << "[STEP 1] Mining block to fund Alice with initial 50 coins...\n";
    myChain.minePendingTransactions(alice.getAddress());
    std::cout << "Alice Balance: " << myChain.getBalanceOfAddress(alice.getAddress()) << " coins\n\n";

    // 3. Test Case 1: Unsigned Transaction (Should Fail)
    std::cout << "[STEP 2] Attempting to submit an unsigned transaction...\n";
    Transaction txUnsigned(alice.getAddress(), bob.getAddress(), 10.0);
    myChain.createTransaction(txUnsigned);
    std::cout << "\n";

    // 4. Test Case 2: Forgery / Impersonation Attempt (Should Fail)
    std::cout << "[STEP 3] Attacker tries to spend Alice's money using Attacker's signature...\n";
    Transaction txForged(alice.getAddress(), attacker.getAddress(), 20.0);
    attacker.signTransaction(txForged); // Fails internal check, or manually forged:
    txForged.signature = "fakeKey:fakeProof";
    myChain.createTransaction(txForged);
    std::cout << "\n";

    // 5. Test Case 3: Legitimate Signed Transaction (Should Succeed)
    std::cout << "[STEP 4] Alice creates and legitimately signs a 15.0 coin transfer to Bob...\n";
    Transaction txValid(alice.getAddress(), bob.getAddress(), 15.0);
    alice.signTransaction(txValid);
    myChain.createTransaction(txValid);
    std::cout << "\n";

    // 6. Test Case 4: In-Transit Tampering Attempt (Should Fail)
    std::cout << "[STEP 5] Attacker intercepts a signed transaction and alters amount (15 -> 40)...\n";
    Transaction txTampered = txValid;
    txTampered.amount = 40.0; // Payload changed after signing
    myChain.createTransaction(txTampered);
    std::cout << "\n";

    // 7. Mine pending transactions to commit the valid block
    std::cout << "[STEP 6] Miner mines the valid pending transaction...\n";
    myChain.minePendingTransactions("MinerAddress");
    std::cout << "\n";

    // 8. Final Balance Inspection
    std::cout << "==================================================\n";
    std::cout << "                 FINAL BALANCES                   \n";
    std::cout << "==================================================\n";
    std::cout << "Alice Balance:    " << myChain.getBalanceOfAddress(alice.getAddress()) << " coins\n";
    std::cout << "Bob Balance:      " << myChain.getBalanceOfAddress(bob.getAddress()) << " coins\n";
    std::cout << "Attacker Balance: " << myChain.getBalanceOfAddress(attacker.getAddress()) << " coins\n";
    std::cout << "Miner Balance:    " << myChain.getBalanceOfAddress("MinerAddress") << " coins\n";

    std::cout << "\nIs Blockchain Valid? " 
              << (myChain.isChainValid() ? "YES (All blocks authentic)" : "NO (Corrupted)") 
              << "\n";

    return 0;
}