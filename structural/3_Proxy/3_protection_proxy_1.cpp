/*
	Protection Proxy :

	It restricts the access to the real object. e.g. a Repository.

	There is a Repository that different employees can access and can perform different
	kinds of operation on it. They can create, update, delete or view the files.


	Thus we have a Repository class which inherits from a base class called Storage.
	And different kinds of employees will have access to this repo.

	All employees can perform file operations using the Repository class.
	But we wish to restrict access of some employees to the Repository.
	They should not be ablet ot perform any file operations.
	Only certain employess should be albe to modify the files in the Repository.


	So for this we will create a proxy class.


	Emplyee ----------------->  | Storage   |
	                            -----------
	                               /_\
	                                |
	                                |-------------------------------|
	                                |								|
	                                |								|
	                                |								|
	                            |  Repository   | <------------ |  Proxy   |
	                            -----------------				------------

	Proxy also inherits from the Storage class and will have a reference to Repository.
	And it will only allow certain employees to access the Repository.
	                            
*/


///////////////////////////////////////////////
//////////////////  Storage.h
///////////////////////////////////////////////
#include <string>

class Storage {
public:
	virtual void CreateFile(const std::string &filename) = 0;
	virtual void UpdateFile(const std::string &filename) = 0;
	virtual void DeleteFile(const std::string &filename) = 0;
	virtual void ViewFile(const std::string &filename) = 0;

	virtual ~Storage() = default;
};


///////////////////////////////////////////////
//////////////////  Employee.h
///////////////////////////////////////////////
#include <string>
#include <sstream>

class Employee {
	std::string m_Name;
	std::string m_Role;
public:
	Employee(const std::string &name, const std::string &role) : m_Name{name}, m_Role{role} {}

	std::string GetInfo() const {
		std::ostringstream os;
		os << "[" << m_Role << "] " << m_Name << " ";
		return os.str();
	}

	const std::string GetName() const {
		return m_Name;
	}

	const std::string GetRole() const {
		return m_Role;
	}
};



// When an employee wants to access a Repository we will set the instance
// of the employee in the Repository class
///////////////////////////////////////////////
//////////////////  Repository.h
///////////////////////////////////////////////
#include <string>
#include <iostream>
#include <cstdlib> // for std::system
#include <sstream>
#include <fstream>
#include <stdexcept>

class Repository : public Storage {
	Employee *m_pEmployee;
	std::string m_FilePath;
public:
	Employee* GetUser() const {
		return m_pEmployee;
	}

	void SetUser(Employee *emp) {
		m_pEmployee = emp;
	}

	Repository(const std::string &path) : m_FilePath{path} {}

	void CreateFile(const std::string &filename) {
		std::system("pwd > temp_path");
		std::stringstream is;
		is << std::ifstream("temp_path").rdbuf();
		std::system("rm temp_path");

		std::string path{is.str()};
		path.pop_back();
		path = path + "/" + filename;
		std::cout << "[Repository] " << path << std::endl;
		std::ofstream out(path);
		if (!out.is_open()) {
			throw std::runtime_error{"Could not create file."};
		}
		std::cout << GetUser()->GetInfo() << "is creating a file.\n";
		std::string fileData;
		std::cout << "[CREATE] Enter data : ";
		getline(std::cin, fileData);
		out << fileData;
		std::cout << "File created successfully!\n";
	}

	void UpdateFile(const std::string &filename) {
		std::system("pwd > temp_path");
		std::stringstream is;
		is << std::ifstream("temp_path").rdbuf();
		std::system("rm temp_path");

		std::string path{is.str()};
		// std::cout << "[Repository] " << path << std::endl;
		path.pop_back();
		path = path + "/" + filename;
		std::ofstream out(path);
		if (!out.is_open()) {
			throw std::runtime_error{"Could not create file."};
		}
		std::cout << GetUser()->GetInfo() << "is updating a file.\n";
		std::string fileData;
		std::cout << "[UPDATE] Enter data : ";
		getline(std::cin, fileData);
		out << "\n######## UPDATE ########\n";
		out << fileData;
		std::cout << "File updated successfully!\n";
	}

	void DeleteFile(const std::string &filename) {
		std::system("pwd > temp_path");
		std::stringstream is;
		is << std::ifstream("temp_path").rdbuf();
		std::system("rm temp_path");

		std::string path{is.str()};
		// std::cout << "[Repository] " << path << std::endl;

		path.pop_back();
		path = path + "/" + filename;
		std::string command = "rm " + path;
		std::system(command.c_str());
		std::cout << "File deleted successfully!\n";
	}

	void ViewFile(const std::string &filename) {
		std::system("pwd > temp_path");
		std::stringstream is;
		is << std::ifstream("temp_path").rdbuf();
		std::system("rm temp_path");

		std::string path{is.str()};
		// std::cout << "[Repository] " << path << std::endl;

		path.pop_back();
		path = path + "/" + filename;
		std::ifstream in{path};
		if (!in.is_open()) {
			throw std::runtime_error{"Could not create file."};
		}
		std::cout << GetUser()->GetInfo() << "is viewing a file.\n";
		std::string line;
		while (std::getline(in, line)) {
			std::cout << line ;
		}
		std::cout << std::endl;
	}

};




int main() {
	Repository r{"./"};
	Employee e1{"Ajay", "Developer"};
	Employee e2{"Sandhya", "Researcher"};
	
	r.SetUser(&e1);
	r.CreateFile("file");

	r.SetUser(&e2);
	r.ViewFile("file");

	r.DeleteFile("file");
}


/*
	Currently all the employees can access the Repository, we want to ensure only 
	 those employees with specific roles can perform the 
	 file operations in the Repository.

	So we will create a proxy that will restrict the access of the employees
	 to the Repository.
*/









