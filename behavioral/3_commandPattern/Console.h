#pragma once
#include <string>
#include <iostream>
#include <sstream>

enum class Color { RED, GREEN, BLUE, WHITE, DEFAULT };

class Console {
	static std::string GetColor(Color color) {
		switch (color) {
			case Color::RED: 
				return "\033[1;31m";
			case Color::GREEN: 
				return "\033[1;32m";
			case Color::BLUE: 
				return "\033[1;34m";
			case Color::WHITE: 
				return "\033[1;97m";
		}
		return "\033[1;39m"; // Default color
	}
	Console() = default;
public:
	static void Write(const std::string& text, Color color, bool bold) {
		std::string fgColor = GetColor(color);
		std::stringstream ss;
		ss << fgColor;
		if (bold) {
			ss << "\033[1;21m";
		}
		ss << text;
		ss << "\033[1;0m";

		std::cout << ss.str();
	}

	static void WriteLine(const std::string& text, Color color, bool bold) {
		Write(text + '\n', color, bold);
	}
};

