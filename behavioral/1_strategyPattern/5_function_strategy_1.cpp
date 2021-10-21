/*

	Printing the array is not the responsibility of the array class.

	Although we have overriden the << operator but that may not satisfy all our needs.

		- Suppose you create an array of names and want to print each name on separate lines.
		  With current implementation that can't be done. Even if you try to modify and add 
		  conditional statements to achieve it, you will end up violating SRP and OCP.

		- Suppose you wish to print the array in a dialog box and not on the command line.
		  This can't be done without violating SRP and OCP.

	
	Solution to the issues : 
		- Use Strategy Pattern. (define a family of algo, encapuslate each one and use interchangably)
		  You can create different classes with different implementations of the print
		  function and they can inherit from a common base-class which then you can 
		  use in the Array class and inject the implementation that you want at runtime.

		- If the algo are very simple and small then you don't need to encapsulate them in a class.
		  Instead you can simply reuse them as functions.
		  Use functions as strategies.
	
*/

#include <vector>
#include <iostream>


#include <functional>



template<typename T>
// using PrinterFunction = void (*)(const std::vector<T>&, std::ostream&);             // Using Function Pointer
using PrinterFunction = std::function<void (const std::vector<T>&, std::ostream&)>;    // Using std::function

template <typename T>
class Array {
	std::vector<T> m_Vector;
	
	PrinterFunction<T> m_Printer;
public:
	void Add(const T& element) {
		m_Vector.push_back(element);
	}

	void Insert(size_t index, const T& element) {
		m_Vector.insert(begin(m_Vector) + index, element);
	}

	void Erase(size_t index) {
		m_Vector.erase(begin(m_Vector) + index);
	}

	T& operator[](size_t index) {
		return m_Vector[index];
	}

	const T& operator[](size_t index) const {
		return m_Vector[index];
	}

	size_t Size() const {
		return m_Vector.size();
	}

	void SetPrinter(PrinterFunction<T> pFunc) {
		m_Printer = pFunc;
	}

	template <typename K>
	friend std::ostream& operator<<(std::ostream& os, const Array<K>& arr);
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Array<T>& arr) {
	if (arr.m_Printer)
		arr.m_Printer(arr.m_Vector, os);
	return os;
}



void StringPrinter(const std::vector<std::string>& list, std::ostream &os) {
	for (auto entry : list) {
		os << entry << "\n";
	}
}


void WindowPrinter(const std::vector<std::string>& list, std::ostream &os) {
	os << "\n" << "\n";
	os << "==========================================\n";
	for (auto entry : list) {
		os << "|\t\t" << entry << "\t\t\t|\n";
	}
	os << "==========================================\n";
}


int main() {
	Array<std::string> data;

	data.Add("ajay");
	data.Add("sandhya");
	data.Add("manish");
	data.Add("piyush");

	data.SetPrinter(StringPrinter);
	std::cout << data;

	data.SetPrinter(WindowPrinter);
	std::cout << data;

	return 0;
	
}




