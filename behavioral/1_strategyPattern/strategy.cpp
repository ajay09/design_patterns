// Change strategy at run-time
// e.g. of transforming of text. Output a list of elements with different output formats

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>

using namespace std;

// We will output a list:
// - In markdown a list is just words followed by *
// - In html a list will have a preable <li> and <ul> or <ol>
enum class OutputFormat {
	Markdown,
	Html
};


// Base class
struct ListStrategy {
	virtual ~ListStrategy() = default;
	// start and end helps us do the starting and closing tags for html, although not that useful for markdown.
	virtual void start(ostringstream &oss) = 0;
	virtual void end(ostringstream &oss) = 0;
	// adding a single list item
	virtual void add_list_item(ostringstream &oss, const string &item) = 0;
};

struct MarkdownListStrategy : ListStrategy {
	void start(ostringstream &oss) override { }
	void end(ostringstream &oss) override { }
	void add_list_item(ostringstream &oss, const string &item) override { 
		oss << " * " << item << endl;
	}
};

struct HtmlListStrategy : ListStrategy {
	void start(ostringstream &oss) override {
		oss << "<ul>" << endl;
	}
	void end(ostringstream &oss) override { 
		oss << "</ul>" << endl;
	}
	void add_list_item(ostringstream &oss, const string &item) override { 
		oss << "<li>" << item << "</li>" << endl;
	}
};


// The high level algo, that is common to both the strategies.
// Will help us make our list.
struct TextProcessor {
	void clear() {
		oss.str("");
		oss.clear();
	}

	string str() const { return oss.str(); }

	// add the items to ostringstream in the correct format
	void append_list(const vector<string> items) {
		list_strategy->start(oss);
		for (auto &item : items)
			list_strategy->add_list_item(oss, item);
		list_strategy->end(oss);
	}

	// For switching the strategy from one to another
	void set_output_format(OutputFormat format) {
		switch (format) {
			case OutputFormat::Markdown:
				// make_unique requires #include <memory> and c++14
				list_strategy = make_unique<MarkdownListStrategy>();
				break;
			case OutputFormat::Html:
				list_strategy = make_unique<HtmlListStrategy>();
				break;
			default:
				break;
		}
	}

private:
	ostringstream oss; // collate all the text result
	unique_ptr<ListStrategy> list_strategy;
};



int main() {
	TextProcessor tp;
	tp.set_output_format(OutputFormat::Markdown);
	tp.append_list({"foo", "bar", "baz"});
	cout << tp.str() << endl;

	tp.clear();
	tp.set_output_format(OutputFormat::Html);
	tp.append_list({"foo", "bar", "baz"});
	cout << tp.str() << endl;

	return 0;
}