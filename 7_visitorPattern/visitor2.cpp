// Double Dispatch

#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>

#include "visitor2.hpp"
#include "model2.hpp"


using namespace std;

/*
This is not a very good solution to the visitor1 problem (Static visitor)
A lot of dynamic casting and if statements.
struct HtmlPrinter {

	void print(const Element *e) {
		const Paragraph *p = dynamic_cast<const Paragraph*>(e);
		if (p) {
			oss << "<p>" << p->text << "</p" << endl;
		}
		// And we can write such dynamic_cast and if for each of the subclass of Element
		// to deduce the actual type of "e"

		// A better solution is to do a doulbe dispatch.
		// Idea is that we modify the hierarchy only once. We specify code which allows us to visit
		// the elements in a hierarchy.
	}
	

	string str() const { return oss.str(); }
private:
	ostringstream oss;
};
*/


struct HtmlVisitor : Visitor {
	// this is where the magic happens we know p is a paragraph and we need not do a dynamic cast explicitly.
	void visit(const Paragraph &p) override {
		oss << "<p>" << p.text << "</p" << endl;
	}

	void visit(const ListItem &p) override {
		oss << "<li>" << p.text << "</li>\n";
	}

	void visit(const List &p) override {
		oss << "<ul>\n";
		for (auto li : p)
			li.accept(*this);
		oss << "</ul>\n";
	}

	std::string str() const override {
		return oss.str();
	}
private:
	ostringstream oss;
};


int main() {
	Paragraph p{ "Here are some colors: "};
	ListItem red{ "red" };
	ListItem green{ "green" };
	ListItem blue{ "blue" };
	List colors{ red, green, blue};

	vector<Element*> document{ &p, &colors };
	// HtmlPrinter pr;

	// for (auto x : document) {
	// 	pr.print(x);
	// }

	HtmlVisitor hv;
	for (auto x : document) {
		x->accept(hv);
	}

	cout << hv.str() << endl;
	// Now if we wish to add a Mardown printer.
	// We simply create a Markdown visitor and need not change anything in the hierarchy.


	return 0;
}