#include <sstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include <openssl/sha.h>

class Block {
	public:
		int index;
		std::string data;
		std::string prevHash;
		std::string hash;
		long timestamp;
		int nonce;

		Block(int index, const std::string& data, const std::string& prevHash) : index(index), data(data), prevHash(prevHash), nonce(0) {
			timestamp = std::time(nullptr);
			hash = calculateHash();
		}

		std::string sha256(const std::string& input) const {
			unsigned char hash[SHA256_DIGEST_LENGTH];
			SHA256_CTX sha256;
			SHA256_Init(&sha256);
			SHA256_Update(&sha256, input.c_str(), input.size());
			SHA256_Final(hash, &sha256);

			std::stringstream ss;
			for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
				ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
			}
			return (ss.str());
		}

		std::string calculateHash() const {
			std::stringstream ss;
			ss << index << timestamp << data << prevHash << nonce;
			return (sha256(ss.str()));
		}

		void mineBlock(int difficulty) {
			std::string prefix(difficulty, '0');
			while (hash.substr(0, difficulty) != prefix) {
				nonce++;
				hash = calculateHash();
			}
			std::cout << "Block found: " << hash << std::endl;
		}
};

class Blockchain {
	public:
		std::vector<Block> chain;
		int difficulty;

		Blockchain() {
			difficulty = 5;
			chain.emplace_back(genesisBlock());
		}

		Block genesisBlock() {
			return (Block(0, "start here..", "0"));
		}

		Block getLastestBlock() const {
			return chain.back();
		}

		void addBlock(Block newBlock) {
			newBlock.timestamp = std::time(nullptr);
			newBlock.prevHash = getLastestBlock().hash;
			newBlock.mineBlock(difficulty);
			chain.push_back(newBlock);
		}

		bool isValidChain() const {
			for (int i = 1; i < chain.size(); i++) {
				const Block& current = chain[i];
				const Block& prev = chain[i - 1];
				if (current.hash != current.calculateHash())
					return (std::cout << "Invalid hash at block, " << i << std::endl, false);
				if (current.prevHash != prev.hash)
					return (std::cout << "Invalid previous hash at block, " << i << std::endl, false);

			}
			return true;
		}
};
