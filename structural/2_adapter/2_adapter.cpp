/*
	Simple String Adapter
*/

#include <vector>
#include <stack>
#include <boost/algorithm/string.hpp>
#include <iostream>

using namespace std;

/*
int main() {

	string s{"Hello    World"};

	boost::to_lower(s);
	vector<string> parts;
	boost::split(parts, s, boost::is_any_of(" "));

	for (auto &p : parts)
		cout << "<" << p << ">" << endl;

	//	but we would like to have this functionality in the string class itself.
	//	and write something like
	//		auto parts s.split(" ");

	return 0;
}
*/

// One additional benefit of this is that the new code becomes part of intellisence (code completion)
class String {
	string s;
public:
	String(const string &s) : s{s} {}

	vector<string> split(const string& token) {
		vector<string> result;
		boost::split(result, s, boost::is_any_of(token), boost::token_compress_on);
		return result;
	}

	size_t get_length() const { return s.length(); }
};

int main() {
	String s{"hello  world"};

	for (auto &word : s.split(" "))
		cout << word << endl;

	return 0;
}