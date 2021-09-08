/*
	Stack class in the STL
	A stack could have been implemented as its own container with its own semantics
	But actually in STL the Stack is actually an adapter over an existing container.
	
	If you look at the type parameters std::stack<class T, class Container = deque<T>>

	template<class T, class Container = std::Deque<T>>
	class stack;

	Thus stack is a container adaptor designed to operate in a LIFO context.
	Container Adaptors are classes that use an encapsulted object of a specific container class
	as its underlying container, providing a specific set of member functions to access its elements.

	The underlying container must specify requirements of s SequenceContainer and provide
		- back()
		- push_back()
		- pop_back()
	std::vector, std::deque and std::list satisfy these requirements
*/

#include <vector>
#include <stack>

using namespace std;

int main() {
	stack<int, vector<int>> s; // would use vector<int> as an unterlying container
	return 0;
}