/*
	Standart C++ doesn't provide any support for writing colored text onto the console.
	Because different OS will have different ways of printing color text on the console
	and some may even not support it.

	
*/

#include <iostream>
#include <string>

enum class Color{RED, GREEN, BLUE, WHITE};
class Console {
public:
	Console() = default;
	static void SetColor(Color color) {
		switch (color) {
			case Color::RED :
				std::cout << "\033[31m";
				break;
			case Color::GREEN :
				std::cout << "\033[32m";
				break;
			case Color::BLUE :
				std::cout << "\033[34m";
				break;
			case Color::WHITE :
				std::cout << "\033[00m";
				break;
		}
	}

public:
	static void Write(const std::string &text, Color color = Color::WHITE) {
		SetColor(color);
		std::cout << text;
		SetColor(Color::WHITE);
	}

	static void WriteLine(const std::string &text, Color color = Color::WHITE) {
		Write(text + "\n", color);
	}
};


int main() {
	std::cout << "\033[31m" << "RED\n";
	std::cout << "\033[32m" << "GREEN\n";
	std::cout << "\033[34m" << "BLUE\n";
	std::cout << "\033[00m" << "DEFAULT\n";


	Console::WriteLine("Hello world", Color::RED);
	std::cout << "Using cout\n";
	printf("Using printf\n");
	Console::Write("Different color", Color::GREEN);
	std::cout << std::endl;

	return 0;
}