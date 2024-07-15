#pragma once
#include <string>
#include <vector>
#include <memory>


using namespace std;

class sqlite3;

class Database
{
	static std::shared_ptr<Database> instance;
public:
	Database(const char *);
	~Database(void);
public:
	bool Open(const char *);
	vector<vector<string>> Quary(const char *); 
	void Close(void);
	int Insert(vector<string>);
	

private:
	sqlite3 *database;

};






