#pragma once

#include <string>
#include <vector>
#include <sstream>

struct Element {
	virtual ~Element() = default;
	virtual void print(std::ostringstream &oss) const = 0;
};

// Since TextElement is not implementing the pure virtual function of the Element class
// so creating an object of type TextElement would give error since it is an abstract class.
struct TextElement : Element {
	explicit TextElement(const std::string &text) : text(text) {}
	std::string text;
};

struct Paragraph : TextElement {
	explicit Paragraph(const std::string &text) : TextElement(text) {}
	
	void print(std::ostringstream &oss) const override {
		oss << "<p>" << text << "</p>\n";
	}
};

struct ListItem : TextElement {
	explicit ListItem(const std::string &text) : TextElement(text) {}

	void print(std::ostringstream &oss) const override {
		oss << "<li>" << text << "</li>\n";
	}
};

struct List : std::vector<ListItem>, Element {
	List(const std::initializer_list<value_type> &Ilist) : vector<ListItem>(Ilist) {}

	void print(std::ostringstream &oss) const override {
		oss << "<ul>\n";
		for (auto li : *this)
			li.print(oss);
		oss << "</ul>\n";
	}
};
