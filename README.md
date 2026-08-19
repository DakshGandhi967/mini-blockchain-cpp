# C++ Blockchain & Cryptographic Ledger Engine

A modular, dependency-free decentralized blockchain ledger implemented in Modern C++ (C++17). The project simulates core blockchain primitives including Proof-of-Work (PoW) consensus, dynamic difficulty target mining, transaction pool verification, balance accounting, and cryptographic digital signatures.

---

## Key Features

* **Modular Architecture:** Clean object-oriented design separating `Block`, `Blockchain`, `Transaction`, and `Wallet` abstractions.
* **Proof-of-Work (PoW) Consensus:** Dynamic nonce-based hashing meeting adjustable difficulty targets (leading zero prefixes).
* **Double-Spending Prevention:** Real-time balance verification and state reconstruction from confirmed on-chain history.
* **Wallet & Digital Signatures:** Asymmetric key-pair abstraction binding secret authorization tokens to transaction hashes, preventing replay attacks and payload tampering.
* **Ledger Integrity Validation:** O(N) chain audit verifying cryptographic link integrity (`previousHash`) and block payload tampering.

---

## System Architecture