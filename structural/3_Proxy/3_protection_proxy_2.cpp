/*

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

	
	Now we implement the Proxy class.
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




///////////////////////////////////////////////
//////////////////  RepositoryProxy.h
///////////////////////////////////////////////
#include <vector>

class RepositoryProxy : public Storage {
	Repository *m_pRepo;
	std::vector<std::string> m_AuthorizedRoles;

	bool IsAuthorized() const {
		if (m_AuthorizedRoles.empty()) {
			throw std::runtime_error{"Authorized roles not set.\n"};
		}
		return std::any_of(begin(m_AuthorizedRoles), end(m_AuthorizedRoles),
							   [this](const std::string &role) {
							   	    return GetUser()->GetRole() == role;
						});
	}
public:
	Employee* GetUser() const {
		return m_pRepo->GetUser();
	}

	void SetUser(Employee *emp) {
		m_pRepo->SetUser(emp);
	}

	RepositoryProxy(const std::string &path) : m_pRepo{new Repository{path}} {}


	void SetAuthorizedRoles(std::initializer_list<std::string> authorizedRoles) {
		m_AuthorizedRoles.assign(authorizedRoles);
	}

	~RepositoryProxy() {
		delete m_pRepo;
	}


	void CreateFile(const std::string &filename) {
		if (IsAuthorized()) {
			m_pRepo->CreateFile(filename);
		} else {
			std::cout << GetUser()->GetInfo() << "is not authorized to create a file.\n";
		}
	}

	void UpdateFile(const std::string &filename) {
		if (IsAuthorized()) {
			m_pRepo->UpdateFile(filename);
		} else {
			std::cout << GetUser()->GetInfo() << "is not authorized to update a file.\n";
		}
	}

	void DeleteFile(const std::string &filename) {
		if (IsAuthorized()) {
			m_pRepo->DeleteFile(filename);
		} else {
			std::cout << GetUser()->GetInfo() << "is not authorized to delete a file.\n";
		}
	}

	void ViewFile(const std::string &filename) {
		if (IsAuthorized()) {
			m_pRepo->ViewFile(filename);
		} else {
			std::cout << GetUser()->GetInfo() << "is not authorized to view a file.\n";
		}
	}
};



int main() {
	RepositoryProxy repo{"./"};
	repo.SetAuthorizedRoles({"Developer", "Researcher"});
	Employee e1{"Ajay", "Developer"};
	Employee e2{"Sandhya", "Researcher"};
	Employee e3{"Unknown", "Outsider"};
	
	repo.SetUser(&e1);
	repo.CreateFile("file");

	repo.SetUser(&e2);
	repo.ViewFile("file");

	repo.SetUser(&e3);
	repo.ViewFile("file");

	repo.SetUser(&e2);
	repo.DeleteFile("file");
}











