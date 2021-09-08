// Static visitor

#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>

#include "model1.hpp"

using namespace std;

int main() {
	Paragraph p{ "Here are some colors: "};
	ListItem red{ "red" };
	ListItem green{ "green" };
	ListItem blue{ "blue" };
	List colors{ red, green, blue};

	vector<Element*> document{ &p, &colors };

	ostringstream oss;
	for_each(document.begin(), document.end(), 
		[&](const Element *e) 
		{ 
			e->print(oss); 
			// here oss acts as a visitor.
			// it visits each of the elements and accumulating data
			// But suppose now we wish to print in Markdown format then this breaks the OCP
			// Then we will have to create a new funciton say print_markdown() not only
			// in the base class but also in every single inheritor
		});

	cout << oss.str() << endl;


	// TextElement t{"try this"}; 
	// error: variable type 'TextElement' is an abstract class

	return 0;
}