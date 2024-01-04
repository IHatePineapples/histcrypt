#include <iostream>
#include <ostream>
#include <string>

// Imcomplete
static std::string shift(int key, const std::string& in_text){
	std::string out_text{};
	for (const auto& c : in_text) out_text += (c + key);
	return out_text;
}

int main(int argc, const char* argv[]){

	int key{std::stoi(argv[1])};
	while ( key != 0 && key < 0) key += 26;
	key %= 26;

	std::cout << shift(key, argv[2]) << std::endl;
}

