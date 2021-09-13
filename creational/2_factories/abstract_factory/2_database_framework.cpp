/*
	This framework will allow the clients to work with differnt kinds of databases
	such as SQL Server, MySQL, Oracle, etc.
	Initially we will just add support for SQL server.

	Requirements :
	- First you need to make a connection.
		Connection object is responsible for connecting to a specific database.
		You have to specify a connection string (that may be userid, or name of db, name of table)
	- After creating the connection you need to prepare a command
		Command is represented with a different class. It specifies the command that
		you ant to execute. The command could be any of the CRUD operations.
		When you execute a command you get results in some object - called Cursor.
	- Using the Cursor we can access the records.

	Thus we will have the following classes Connection, Command, RecordSet
										    Transaction(to help perform transactions), 
										    Parameters(to help create parameterized commands)

										    for now we will design using only the first 3 classes


	Also first we will focus on designing it only for SQL server.
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






int main() {
	SqlConnection *pCon = new SqlConnection{};
	pCon->SetConnectionString("uid=ajay;db=movies;table=actors");
	pCon->Open();

	SqlCommand *pCmd = new SqlCommand{};
	pCmd->SetConnection(pCon);
	pCmd->SetCommandString("select * from actors");

	SqlRecordSet *pRec = pCmd->ExecuteQuery();
	while (pRec->HasNext()) {
		std::cout << pRec->Get() << std::endl;
	}

	delete pCon;
	delete pCmd;
	delete pRec;

	return 0;
}



