#pragma once

#include <string>
#include <vector>
#include <sstream>

struct Visitor;
// Visitor can be an Html visitor, a markdown visitor or Latex visitor etc.

struct Element {
	virtual ~Element() = default;
	virtual void accept(Visitor &v) const = 0;
	// Now every subcall will have an implementation for this except the abstract ones.
};

// Since TextElement is not implementing the pure virtual function of the Element class
// so creating an object of type TextElement would give error since it is an abstract class.
struct TextElement : Element {
	explicit TextElement(const std::string &text) : text(text) {}
	std::string text;
};

struct Paragraph : TextElement {
	explicit Paragraph(const std::string &text) : TextElement(text) {}
	
	void accept(Visitor &v) const override {
		v.visit(*this);
	}
};

struct ListItem : TextElement {
	explicit ListItem(const std::string &text) : TextElement(text) {}

	void accept(Visitor &v) const override {
		v.visit(*this);
	}
};

struct List : std::vector<ListItem>, Element {
	List(const std::initializer_list<value_type> &Ilist) : vector<ListItem>(Ilist) {}

	void accept(Visitor &v) const override {
		v.visit(*this);
	}
};
