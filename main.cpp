#include "includes/main.hpp"

int main(void) {
	Blockchain coin;

	std::cout << "Mining block (1)..." << std::endl;
	coin.addBlock(Block(1, "send 1 'coin' to Bob", ""));
}
