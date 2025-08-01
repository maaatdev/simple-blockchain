# Simple Blockchain

This project implements a basic blockchain in C++ with a Proof of Work system.

## Features

- Blocks containing index, data, previous hash, timestamp, and nonce.
- SHA256 hash calculation based on block contents.
- Mining blocks with adjustable difficulty (number of leading zeros).
- Chain validation to ensure integrity.

## Usage

1. Compile the project:
   ```bash
   c++ main.cpp -o blockchain -lssl -lcrypto -Wno-deprecated-declarations
