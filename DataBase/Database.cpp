#include "stdafx.h"
#include "Database.h"
//#include "Actor.h"
//#include "Person.h"
#include "sqlite3.h"




Database::Database(const char *name)
{
	database = NULL;
	Open(name);
}


Database::~Database(void)
{
}


bool Database::Open(const char *name)
{
	if(sqlite3_open(name, &database) == SQLITE_OK)
		return true;

	sqlite3_stmt* statement;
	const char* sql = "PRAGMA foreign_keys = ON";

	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
	{
		sqlite3_step(statement);
		sqlite3_finalize(statement);
	}

	return false;
}


void Database::Close(void)
{
	sqlite3_close(database);
}


vector<vector<string>> Database::Quary(const char *quary)
{
	vector<vector<string>> results;

	sqlite3_stmt *statement;

	if(sqlite3_prepare_v2(database, quary, -1, &statement, 0) == SQLITE_OK)
	{
		int cols = sqlite3_column_count(statement);
		int result = 0;
		while(true)
		{
			result = sqlite3_step(statement);

			if(result == SQLITE_ROW)
			{
				vector<string> values;
				for(int col=0; col < cols; col++)
				{
					values.push_back((char*)sqlite3_column_text(statement, col));
				}
				results.push_back(values);
			}
			else
				break;
		}
		sqlite3_finalize(statement);
	}
	return results;
}


int Database::Insert(vector<string> vec)
{
	////Insert VMA-element
	//const char *name = vec[0].c_str();
	//double dia = atof(vec[1].c_str());
	//double diaDist = atof(vec[2].c_str());
	//double cylHeight = atof(vec[3].c_str());
	//double nozzleDia = atof(vec[4].c_str());
	//double perforRate = atof(vec[5].c_str());

	//Insert ACTOR-element
	const char *name = vec[0].c_str();
	const char *nationality = vec[1].c_str();
	int yearStart = atoi(vec[2].c_str());
	int yearEnd = atoi(vec[3].c_str());
	int yearBorn = atoi(vec[4].c_str());

	sqlite3_stmt *statement;
	//const char *sql = "INSERT INTO VMAs(type, dia, distDiameter, cylindricalHeight, nozzleHoleDiameter, percentFlowArea) VALUES (?, ?, ?, ?, ?, ?)";
	const char *sql = "INSERT INTO ACTOR(name, nationality, yearStart, yearEnd, yearBorn) VALUES (?, ?, ?, ?, ?)";
	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
	{
		sqlite3_bind_text(statement, 1, name, strlen(name), 0);
		sqlite3_bind_text(statement, 2, nationality, strlen(nationality), 0);
		sqlite3_bind_int(statement, 3, yearStart);
		sqlite3_bind_int(statement, 4, yearEnd);
		sqlite3_bind_int(statement, 5, yearBorn);
		/*sqlite3_bind_double(statement, 2, dia);
		sqlite3_bind_double(statement, 3, diaDist);
		sqlite3_bind_double(statement, 4, cylHeight);
		sqlite3_bind_double(statement, 5, nozzleDia);
		sqlite3_bind_double(statement, 6, perforRate);*/
		sqlite3_step(statement);
	}
	else
		return -1;
	sqlite3_finalize(statement);

	//int v;
	////Insert Coil
	//double diaCoil = atof(vec[12].c_str());
	//double diaExternal = atof(vec[13].c_str());
	//double diaInternal = atof(vec[14].c_str());
	//double turns = atof(vec[15].c_str());
	////v = this->InsertCoil(name, diaCoil, diaExternal, diaInternal, turns);
	//if (v == -1)
	//	return v;
	//if (vec.size() > 16)
	//{
	//	diaCoil = atof(vec[16].c_str());
	//	diaExternal = atof(vec[17].c_str());
	//	diaInternal = atof(vec[18].c_str());
	//	turns = atof(vec[19].c_str());
	//	//v = this->InsertCoil(name, diaCoil, diaExternal, diaInternal, turns);
	//	if (v == -1)
	//		return v;
	//}
	return 0;
}








