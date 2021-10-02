/*
	Functional Decorator

	- A functional decorator wraps a function instead of a class or an object.
	- They accept functions and callable objects as arguments.
	- They add features to such callables and return another callable.
		A callable is an entitiy that can be invoked like a function.
		e.g. a function, a function pointer, a pointer to member funtion, a lambda expression.
	- 
*/

#include <iostream>


int Square(int x) {
	return x * x;
}

int Add(int x, int y) {
	return x + y;
}

float Divide(float x, float y) {
	return x / y;
}


int main() {
	auto result = Square(5);
	std::cout << "Result is : " << result << std::endl;
	result = Add(8, 2);
	std::cout << "Result is : " << result << std::endl;
	return 0;
}

/*
	The string  "Result is : "
	is repeated everytime we try to print the output of an expression.
	To avoid repetition we can create a decorator through which we can decorate
	the output of any such function call.
*/