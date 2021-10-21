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


	std::function is very flexible. You can provide any kind of callable and it will call it.
		- Function
		- Member Function
		- Lambda Function
		- Functor



	This kind of strategy is already used inside the standard library.
	Algo such as  sort, count_if, remove_if  expect a callback that modifies the
	behavior of the algo. Those callbacks are strategies.	
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


class Logger {
public:
	void Log(const std::vector<std::string> &list, std::ostream &os) {
		for (auto entry : list) {
			os << entry << "\n";
		}
	}
};

#include <fstream>


// we can either use a lambda function or use a functor to bind the function to the arguments.
auto my_bind_function(void(Logger::*fun)(const std::vector<std::string>&, std::ostream&), Logger *obj) {
	return [&](const std::vector<std::string>& a, std::ostream& b){ return (obj->*fun)(a,b); };
}


struct SimplePrinter {
public:
	void operator()(const std::vector<std::string>& list, std::ostream& os) const {
		for (auto entry : list) {
			os << entry << "\n";
		} 
	}
};

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


	std::ofstream m_Logger{"elements.txt"};

/*
	data.SetPrinter(&Logger::Log);  // This will give error

	error: no viable conversion from 
	'void (Logger::*)(const std::vector<std::string> &, std::ostream &)' to 
	'function<void (const std::vector<std::string> &, std::ostream &)>'
	
	Because in Logger::Log the first argument is a Logger object and the second and third arguments are the parameters specified.
	Thus its signature doesn't match with the signature of the function pointer we have defined.

	This is because to invoke the Log function we will have to specify the instance and that modifies the signature of the function.
	We can use another wrapper Bind
*/


	// Using std::bind
	Logger myLogger;
	auto fn = std::bind(&Logger::Log, &myLogger, std::placeholders::_1, std::placeholders::_2);
	// auto fn = my_bind_function(&Logger::Log, &myLogger);
	data.SetPrinter(fn);
	m_Logger << data;



	// using a lambda expression
	data.SetPrinter(
		[&myLogger](const std::vector<std::string>& a, std::ostream& b) {
			myLogger.Log(a, b);
		}
	);
	m_Logger << data;



	// Using a Functor
	data.SetPrinter(SimplePrinter{});
	std::cout << data;

	return 0;
	
}




/*

std::bind is for partial function application.

That is, suppose you have a function object f which takes 3 arguments:

f(a,b,c);
You want a new function object which only takes two arguments, defined as:

g(a,b) := f(a, 4, b);
g is a "partial application" of the function f: the middle argument has already been specified, and there are two left to go.

You can use std::bind to get g:

auto g = bind(f, _1, 4, _2);





pointers to non-static member functions are not like normal function pointers: 
member functions need to be called on an object which is passed as an implicit argument 
to the function. The signature of your member function above is, thus

		void (aClass::*)(int, int)
rather than the type you try to use

		void (*)(int, int)



One approach could consist in making the member function static in which case it doesn't 
require any object to be called on and you can use it with the type void (*)(int, int).

*/


/*
		std::bind1st(std::ptr_fun(f), 5)(x);   // f(5, x)
		bind(f, 5, _1)(x);                     // f(5, x)
		bind can handle functions with more than two arguments, and its argument substitution mechanism is more general:

		bind(f, _2, _1)(x, y);                 // f(y, x)

		bind(g, _1, 9, _1)(x);                 // g(x, 9, x)

		bind(g, _3, _3, _3)(x, y, z);          // g(z, z, z)

		bind(g, _1, _1, _1)(x, y, z);          // g(x, x, x)

*/





/*
how to use a function pointer to call a member function, here is an example:

				// the function using the function pointers:
				void somefunction(void (*fptr)(void*, int, int), void* context) {
				    fptr(context, 17, 42);
				}

				void non_member(void*, int i0, int i1) {
				    std::cout << "I don't need any context! i0=" << i0 << " i1=" << i1 << "\n";
				}

				struct foo {
				    void member(int i0, int i1) {
				        std::cout << "member function: this=" << this << " i0=" << i0 << " i1=" << i1 << "\n";
				    }
				};

				void forwarder(void* context, int i0, int i1) {
				    static_cast<foo*>(context)->member(i0, i1);
				}

				int main() {
				    somefunction(&non_member, nullptr);
				    foo object;
				    somefunction(&forwarder, &object);
				}


*/