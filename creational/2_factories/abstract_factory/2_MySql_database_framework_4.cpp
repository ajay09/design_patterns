/*
	Using Preprocessor directive to switch between database types.


	But his doesn't solve the problem.
	A user can instantiate a SqlConnection object and a MySqlCommand object
	There is nothing stopping him/her to do this.

	So the behavior will be UB when user tries to execute the query.
	The classes, connection, command and recordset are meant to work together.
	If you are working with SQL server you need to use only the classes corresponding
	to the SQL server. You can't mix classes from different kinds of DBs.

	Thus we want 2 things here : 
	- Client should not know the classes it instantiates.
	- Whenever it instantiates the classes, the intances should always be from the same DB or set.

	
	Using Macros made our design quite inflexible. If a new db is introduced and we want 
	our applications to use that, then we have to modify a lot existing code. This is due
	to the fact that our application is tightly coupled with the DB classes.

	So we need to instantiate the classes without depending on their concrete types.
	That means we can use the Factory Method design pattern.

*/

//////////////////////////////////////////
/////////////////////  Connection.h
//////////////////////////////////////////
// #pragma once
#include <string>

class Connection {
	std::string m_ConnectionString;
public:
	void SetConnectionString(const std::string &connStr) {
		m_ConnectionString = connStr;
	}
	const std::string& GetConnectionString() const {
		return m_ConnectionString;
	}
	virtual void Open() = 0;
	virtual ~Connection() = default;
};


//////////////////////////////////////////
/////////////////////  Command.h
//////////////////////////////////////////
// #pragma once
class RecordSet;

class Command {
	std::string m_CommandString;
protected: // 	because we need to access this in the child classes.
	Connection *m_pConnection;
public:
	Connection *GetConnection() const {
		return m_pConnection;
	}
	void SetConnection(Connection *pConnection) {
		m_pConnection = pConnection;
	}
	const std::string& GetCommandString() const {
		return m_CommandString;
	}
	void SetCommandString(const std::string &commandStr) {
		m_CommandString = commandStr;
	}

	virtual void ExecuteCommand() = 0;

	virtual RecordSet *ExecuteQuery() = 0;
	

	virtual ~Command() = default;

};



//////////////////////////////////////////
/////////////////////  RecordSet.h
//////////////////////////////////////////
// #pragma once
class RecordSet {
public:
	virtual const std::string& Get() = 0;
	virtual bool HasNext() = 0;
	virtual ~RecordSet() = default;
};



//////////////////////////////////////////
/////////////////////  SqlRecordSet.h
//////////////////////////////////////////
// #pragma once
#include <vector>
class SqlRecordSet : public RecordSet {
	const std::vector<std::string> m_Db {
		"Terminator",
		"Matrix",
		"End of days",
		"Rocky",
		"Disturbia",
		"Expendables"
	};
	std::vector<std::string>::const_iterator m_Cursor;
public:
	SqlRecordSet();
	const std::string& Get() override;
	bool HasNext() override;
};


//////////////////////////////////////////
/////////////////////  SqlRecordSet.cpp
//////////////////////////////////////////

SqlRecordSet::SqlRecordSet() {
	m_Cursor = m_Db.begin();
}

const std::string& SqlRecordSet::Get() {
	return *m_Cursor++;
}

bool SqlRecordSet::HasNext() {
	return m_Cursor != m_Db.end();
}



//////////////////////////////////////////
/////////////////////  SqlCommand.h
//////////////////////////////////////////
// #pragma once

class SqlCommand : public Command{
public:
	void ExecuteCommand() override;

	// this returns a RecordSet
	// RecordSet *ExecuteQuery();
	// But we would require SqlRecordSet for our SQL db, thus we will have to do a down-cast
	// the RecordSet to SqlRecordSet before using it. To avoid downcast we can use the 
	// covariant return-type instead.
	SqlRecordSet *ExecuteQuery() override;

};


//////////////////////////////////////////
/////////////////////  SqlCommand.cpp
//////////////////////////////////////////
#include <iostream>
class SqlRecordSet;

void SqlCommand::ExecuteCommand() {
	std::cout << "[SqlCommand] Executing command on"
			  << m_pConnection->GetConnectionString()
			  << std::endl;
}

// Since ExecuteQuery returns an instance of a class.
// So it behaves like a factory method design pattern.
SqlRecordSet* SqlCommand::ExecuteQuery() {
	std::cout << "[SqlCommand] Executing query\n";
	return new SqlRecordSet{};
}


//////////////////////////////////////////
/////////////////////  SqlConnection.h
//////////////////////////////////////////
// #pragma once
class SqlConnection : public Connection {
public:
	void Open() override;
};


//////////////////////////////////////////
/////////////////////  SqlConnection.cpp
//////////////////////////////////////////
void SqlConnection::Open() {
	std::cout << "[SqlConnection] Connection opened\n";
}







// -------------------------------------------------------
//////////////////////////////////////////
/////////////////////  MySqlRecordSet.h
//////////////////////////////////////////
// #pragma once
#include <vector>
class MySqlRecordSet : public RecordSet {
	const std::vector<std::string> m_Db {
		"Newton",
		"Shagird",
		"Training Day",
		"Luca",
		"Coco",
		"Mule"
	};
	std::vector<std::string>::const_iterator m_Cursor;
public:
	MySqlRecordSet() { m_Cursor = m_Db.begin(); }
	const std::string& Get() override { return *m_Cursor++; }
	bool HasNext() override { return m_Cursor != m_Db.end(); }
};

//////////////////////////////////////////
/////////////////////  MySqlCommand.h
//////////////////////////////////////////
// #pragma once

class MySqlCommand : public Command{
public:
	void ExecuteCommand() override {
		std::cout << "[MySqlCommand] Executing command on"
			  << m_pConnection->GetConnectionString()
			  << std::endl;
	}

	// covariant return-type instead.
	MySqlRecordSet *ExecuteQuery() override {
		std::cout << "[MySqlCommand] Executing query\n";
		return new MySqlRecordSet{};
	}

};

//////////////////////////////////////////
/////////////////////  MySqlConnection.h
//////////////////////////////////////////
// #pragma once
class MySqlConnection : public Connection {
public:
	void Open() override {
		std::cout << "[MySqlConnection] Connection opened\n";
	}
};

// Factory Method
//////////////////////////////////////////
/////////////////////  DbFactory.h
//////////////////////////////////////////
// #pragma once
#include <string>
class DbFactory {
public:
	static Connection* CreateConnection(const std::string &type) {
		if (type == "sql")
			return new SqlConnection();
		else if (type == "mysql")
			return new MySqlConnection();
		else return nullptr;
	}
	static Command* CreateCommand(const std::string &type) {
		if (type == "sql")
			return new SqlCommand();
		else if (type == "mysql")
			return new MySqlCommand();
		else return nullptr;
	}
};


///////////////////////////////////////////////////
///////////////////////////////////////////////////
///////////////////////   Client code
///////////////////////////////////////////////////
///////////////////////////////////////////////////

void FactoryMethodUse() {
	/*
		Using Factory Method design patter we have made the client code
		independent of the name of the classes it wants to instantiate.

		Even though the dependency on the concrete classes has been removed.
		There is still one problem. What if the client specify "mysql" as the
		connection type and "sql" as the Command type?
		There is no way to ensure that the same string is used in all the places.

		Thus we must ensure that the factory must return instances from the same
		kind of database.
		The Factory Method can return instances of different classes without depending
		on their type, but it cannot return instances from a specific set.
		That's why we need to implement the Abstract Factory Pattern.
	*/
	Connection *pCon{DbFactory::CreateConnection("mysql")};
	pCon->SetConnectionString("uid=ajay;db=movies;table=actors");
	pCon->Open();

	Command *pCmd {DbFactory::CreateCommand("mysql")};


	RecordSet *pRec = pCmd->ExecuteQuery();
	while (pRec->HasNext()) {
		std::cout << pRec->Get() << std::endl;
	}

	delete pCon;
	delete pCmd;
	delete pRec;
}


#define SQL

int main() {
	Connection *pCon {};
#ifdef SQL
	pCon = new SqlConnection{};
#else
	pCon = new MySqlConnection{};
#endif
	pCon->SetConnectionString("uid=ajay;db=movies;table=actors");
	pCon->Open();

	Command *pCmd {};
#ifdef SQL
	pCmd = new SqlCommand{};
#else
	pCmd = new MySqlCommand{};
#endif
	pCmd->SetConnection(pCon);
	pCmd->SetCommandString("select * from actors");

	RecordSet *pRec = pCmd->ExecuteQuery();
	while (pRec->HasNext()) {
		std::cout << pRec->Get() << std::endl;
	}


	FactoryMethodUse();

	delete pCon;
	delete pCmd;
	delete pRec;

	return 0;
}



