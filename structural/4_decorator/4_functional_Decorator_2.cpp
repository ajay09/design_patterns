/*
	Functional Decorator

		The string  "Result is : "
	is repeated everytime we try to print the output of an expression.
	To avoid repetition we can create a decorator through which we can decorate
	the output of any such function call.


	As there are no classes here so we can't use static or dynamic decorators.
	Thus we have to use functional decorator.


	A functional decorator should be able to decorate any kind of function
	irrespective of the number of parameters and the return type. Thus
	we use function template
*/

#include <iostream>


template<typename Function>
auto PrintResult(Function func) {
	auto result = [func](auto&&...args) {
		std::cout << "Result is : ";
		return func(args...);
	};
	return result; // or we can directly return the lambda expression.
}

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
	/*
		We only pass the name of the function that we wish to decorate here.
		The return from PrintResult will be a lambda that has decorated the Square function.
		This lambda will be invoked later.
	*/
	auto result = PrintResult(Square);
	std::cout << result(5) << std::endl;

	auto add = PrintResult(Add);
	std::cout << add(8, 2) << std::endl;

	auto div = PrintResult(Divide);
	std::cout << div(4, 0) << std::endl;
	// We wish to avoid division by zero.
	// We can create another decorator that can check division by 0.
	return 0;
}