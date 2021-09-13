/*
	Let's use Abstract Factory Pattern now.

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

// Abstract Factory
//////////////////////////////////////////
/////////////////////  DbFactory.h
//////////////////////////////////////////
// #pragma once
#include <string>
class DbFactory {
public:
	virtual Connection* CreateConnection() = 0;
	virtual Command* CreateCommand() = 0;
};

//////////////////////////////////////////
/////////////////////  SqlFactory.h
//////////////////////////////////////////
// #pragma once
#include <string>
class SqlFactory : public DbFactory {
public:
	Connection* CreateConnection() override {
		return new SqlConnection();
	}
	Command* CreateCommand() override {
		return new SqlCommand();
	}
};


//////////////////////////////////////////
/////////////////////  MySqlFactory.h
//////////////////////////////////////////
// #pragma once
#include <string>
class MySqlFactory : public DbFactory {
public:
	Connection* CreateConnection() override {
		return new MySqlConnection();
	}
	Command* CreateCommand() override {
		return new MySqlCommand();
	}
};


///////////////////////////////////////////////////
///////////////////////////////////////////////////
///////////////////////   Client code
///////////////////////////////////////////////////
///////////////////////////////////////////////////

void UsingAbstractFactory(DbFactory *pFactory) {
	Connection *pCon = pFactory->CreateConnection();
	pCon->SetConnectionString("uid=ajay;db=movies;table=actors");
	pCon->Open();

	Command *pCmd = pFactory->CreateCommand();


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


	UsingAbstractFactory(new MySqlFactory());

	delete pCon;
	delete pCmd;
	delete pRec;

	return 0;
}



