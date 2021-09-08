// Dependecy Inversion Principle
/*
	- High level modules should not depend on low-level modules. Both should depend on abstractions.
	  High level module -> e.g. a reporting component.
	  Low level module  -> e.g. a logging mechanism that can write to console.
	  Replace concrete dependencies with some form of abstractions which are easier to substitute.
	  e.g. reporting component should depend on a ConsoleLogger, but can depend on an ILogger

	- Abstractions should not depend upon details. Details should depend upon abstractions.
	  In other words, dependencies on interfaces and supertypes is better than dependencies
	  on concrete types.


Inversion of Control(IoC)
	The actual process of creating abstractions and getting them to replace dependencies.
	It is the central piece of software that manages the dependency injection.

Dependency Injection
	use of software frameworks to ensure that when a component depends on something else, then those 
	dependencies are specified. (the dependencies could be interfaces or concrete types.)

	The term injection basically means that if a class specifies certain dependencies (e.g. by having
	 them as constructor parameters) then the Inversion of Control container will actually initialize
	 those dependencies correctly.
*/