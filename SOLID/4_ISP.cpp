// Interface Segregation Princliple

// No client(end user) should be forced to depend on methods(member functions) it does not use.


#include <vector>

struct Document;

/*
// create a multi-function device for printing, scanning and fax
// Since we should work with abstractions rather than concrete implementations 
struct IMachine {
	virtual void print(std::vector<Document*> docs) = 0;
	virtual void scan(std::vector<Document*> docs) = 0;
	virtual void fax(std::vector<Document*> docs) = 0;
}

// Now you gave your interface to someone and if they want to use it
// they would have to make it a part of their code.
struct MFP : IMachine {
	void print(std::vector<Document*> docs) override;
	void scan(std::vector<Document*> docs) override;
	void fax(std::vector<Document*> docs)  override;
}
// As per ISP this is a bad idea.
//  - Every time you wish to change a chunck of functionality say just the printing mechanism
//     you would have to recompile the entire code.
//  - Perhaps the client only needs the print functionality but not the scan and fax parts.
//  - You are forcing the client to implement the functionality they might not use

*/

// Using the ISP we break the single interface into multiple interfaces

struct IPrinter {
	virtual void print(std::vector<Document*> docs) = 0;
};

struct IScanner {
	virtual void scan(std::vector<Document*> docs) = 0;
};

// Now the client can selectively implement the interface that he requires.

struct Printer : IPrinter {
	void print(std::vector<Document*> docs) override;
};

struct Scanner : IScanner {
	void scan(std::vector<Document*> docs) override;
};


// The client can even club these seperate interfaces to design the whole machine
struct IMachine : IPrinter, IScanner {};

struct Machine : IMachine {
	IPrinter &printer;
	IScanner &scanner;

	Machine(IPrinter &printer, IScanner &scanner) : printer{printer}, scanner{scanner} {}

	void print(std::vector<Document*> docs) override {
		printer.print(docs);
	}
	void scan(std::vector<Document*> docs) override {
		scanner.scan(docs);
	}
};

int main() {
	return 0;
}