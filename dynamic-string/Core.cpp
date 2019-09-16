#include "dynamic-string.h"

#include <iostream>

int main() {
	rbi::string str1 = "Hello World";

	std::cout << (const char*)str1;
}