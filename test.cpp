#include <iostream>
#include <fstream>
#include <string>

int main() {
	std::ifstream ifs("test.txt");
  std::string content((std::istreambuf_iterator<char>(ifs)),
                      (std::istreambuf_iterator<char>()));

	std::cout << content;

	return 0;
}
