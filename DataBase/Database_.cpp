#include "stdafx.h"
#include "Database.h"
//#include "Excep.h"

//
//Database::Database(char *name)
//{
//	database = NULL;
//	bool open = Open(name);
//	if(!open)
//		throw Excep("Database didn't open");
//}
//
//
//Database::~Database(void)
//{
//}
//
//
//bool Database::Open(char *name)
//{
//	if(sqlite3_open(name, &database) == SQLITE_OK)
//		return true;
//
//	return false;
//}
//
//
//void Database::Close(void)
//{
//	sqlite3_close(database);
//}
//
//
//vector<vector<string>> Database::Quary(const char *quary)
//{
//	vector<vector<string>> results;
//
//	sqlite3_stmt *statement;
//
//	if(sqlite3_prepare_v2(database, quary, -1, &statement, 0) == SQLITE_OK)
//	{
//		int cols = sqlite3_column_count(statement);
//		int result = 0;
//		while(true)
//		{
//			result = sqlite3_step(statement);
//
//			if(result == SQLITE_ROW)
//			{
//				vector<string> values;
//				for(int col=0; col < cols; col++)
//				{
//					values.push_back((char*)sqlite3_column_text(statement, col));
//				}
//				results.push_back(values);
//			}
//			else
//				break;
//		}
//		sqlite3_finalize(statement);
//	}
//	return results;
//}
//
//
//int Database::Insert(vector<string> vec)
//{
//	//Insert VMA-element
//	const char *name = vec[0].c_str();
//	double dia = atof(vec[1].c_str());
//	double diaDist = atof(vec[2].c_str());
//	double cylHeight = atof(vec[3].c_str());
//	double nozzleDia = atof(vec[4].c_str());
//	double perforRate  = atof(vec[5].c_str());
//	
//	sqlite3_stmt *statement;
//	const char *sql = "INSERT INTO VMAs(type, dia, distDiameter, cylindricalHeight, nozzleHoleDiameter, percentFlowArea) VALUES (?, ?, ?, ?, ?, ?)";
//	if(sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
//	{
//		sqlite3_bind_text(statement, 1, name, strlen(name), 0);		
//		sqlite3_bind_double(statement, 2, dia);
//		sqlite3_bind_double(statement, 3, diaDist);
//		sqlite3_bind_double(statement, 4, cylHeight);
//		sqlite3_bind_double(statement, 5, nozzleDia);
//		sqlite3_bind_double(statement, 6, perforRate);
//		sqlite3_step(statement);
//	}
//	else
//		return -1;
//	sqlite3_finalize(statement);
//
//	int v;
//	//Insert Coil
//	double diaCoil = atof(vec[12].c_str());
//	double diaExternal = atof(vec[13].c_str());
//	double diaInternal = atof(vec[14].c_str());
//	double turns = atof(vec[15].c_str());
//	v = this->InsertCoil(name, diaCoil, diaExternal, diaInternal, turns);
//	if(v==-1)
//		return v;
//	if(vec.size() > 16)
//	{
//		diaCoil = atof(vec[16].c_str());
//		diaExternal = atof(vec[17].c_str());
//		diaInternal = atof(vec[18].c_str());
//		turns = atof(vec[19].c_str());
//		v = this->InsertCoil(name, diaCoil, diaExternal, diaInternal, turns);
//		if(v==-1)
//			return v;
//	}
//	
//	//Insert into COMMONs
//	const char *function = vec[6].c_str();
//	const char *nozzle = vec[7].c_str();
//	v = this->InsertNoz(name, function, nozzle);
//	if(v==-1)
//		return v;
//	function = vec[8].c_str();
//	nozzle = vec[9].c_str();
//	v = this->InsertNoz(name, function, nozzle);
//	if(v==-1)
//		return v;
//	function = vec[10].c_str();
//	nozzle = vec[11].c_str();
//	v = this->InsertNoz(name, function, nozzle);
//	if(v==-1)
//		return v;
//
//	return 0;
//}
//
//
//int Database::InsertCoil(const char *name, double diaCoil, double diaExternal, double diaInternal, double turns)
//{
//	const char *sql = "INSERT INTO COILs(diaCoil,diaExternal,diaInternal,turns,type) VALUES(?, ?, ?, ?, ?)";
//	sqlite3_stmt *statement;
//	if(sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
//	{		
//		sqlite3_bind_double(statement, 1, diaCoil);
//		sqlite3_bind_double(statement, 2, diaExternal);
//		sqlite3_bind_double(statement, 3, diaInternal);
//		sqlite3_bind_double(statement, 4, turns);
//		sqlite3_bind_text(statement, 5, name, strlen(name), 0);	
//		sqlite3_step(statement);
//	}
//	else
//		return -1;
//	sqlite3_finalize(statement);
//
//	//Primary Key no skal findes for coilen, der netop er overført til databasen. 	
//	const char *selectCommand = "SELECT last_insert_rowid()";
//	vector<vector<string>> result = this->Quary(selectCommand);
//	int no = atoi(result[0][0].c_str());
//
//	return no;
//}
//
//
//int Database::InsertNoz(const char* type, const char* function, const char* nozzle)
//{
//	const char *sql = "INSERT INTO COMMONs(type,function,nozzle) VALUES(?, ?, ?)";
//	sqlite3_stmt *statement;
//	if(sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
//	{
//		sqlite3_bind_text(statement, 1, type, strlen(type), 0);	
//		sqlite3_bind_text(statement, 2, function, strlen(function), 0);
//		sqlite3_bind_text(statement, 3, nozzle, strlen(nozzle), 0);
//		sqlite3_step(statement);
//	}
//	else
//		return -1;
//	sqlite3_finalize(statement);
//	return 0;
//}
//
//
//int Database::Delete(string type)
//{
//	const char *name = type.c_str();
//	sqlite3_stmt *statement;
//	//Delete Coils
//	const char *sql1 = "DELETE FROM COILs WHERE type=?";
//	if(sqlite3_prepare_v2(database, sql1, -1, &statement, 0) == SQLITE_OK)
//	{
//		sqlite3_bind_text(statement, 1, name, strlen(name), 0);	
//		
//		sqlite3_step(statement);
//	}
//	else
//		return -1;
//
//	//Delete COMMONs
//	const char *sql2 = "DELETE FROM COMMONs WHERE type=?";
//	if(sqlite3_prepare_v2(database, sql2, -1, &statement, 0) == SQLITE_OK)
//	{
//		sqlite3_bind_text(statement, 1, name, strlen(name), 0);	
//		
//		sqlite3_step(statement);
//	}
//	else
//		return -1;
//
//	//Delete VMAs
//	const char *sql = "DELETE FROM VMAs WHERE type=?";
//	if(sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
//	{
//		sqlite3_bind_text(statement, 1, name, strlen(name), 0);	
//		
//		sqlite3_step(statement);
//	}
//	else
//		return -1;
//	sqlite3_finalize(statement);
//	return 0;
//}
//
//
//void Database::GetVMA(shared_ptr<Cooler> cooler, int i)
//{
//	string selectCommand; 
//	if(i==0)
//		selectCommand = "SELECT * FROM VMA WHERE type='" + cooler->type + "';";
//	else
//		selectCommand = "SELECT * FROM VMAs WHERE type='" + cooler->type + "';";
//	vector<vector<string>> result = this->Quary(selectCommand.c_str());
//	vector<vector<string>>::iterator itera;
//	for(itera=result.begin(); itera < result.end(); itera++)
//	{
//		vector<string> row = *itera;
//		cooler->diameter = atof(row.at(1).c_str())/1000.0;		
//		cooler->distDiameter = atof(row.at(2).c_str())/1000.0;
//		cooler->cylindricalHeight = atof(row.at(3).c_str())/1000.0;
//		cooler->nozzleHoleDiameter = atof(row.at(4).c_str())/1000.0;
//		cooler->percentFlowArea = atof(row.at(5).c_str());
//	}
//	if(i==0)
//		selectCommand = "SELECT * FROM COIL WHERE type='" + cooler->type + "';";
//	else
//		selectCommand = "SELECT * FROM COILs WHERE type='" + cooler->type + "';";
//	result = this->Quary(selectCommand.c_str());
//
//	shared_ptr<Coil> coil;
//	for(itera=result.begin(); itera < result.end(); itera++)
//	{
//		vector<string> row = *itera;
//		coil = std::make_shared<Coil>();
//		coil->diaCoil = atof(row.at(1).c_str())/1000.0;
//		coil->diaExternal = atof(row.at(2).c_str())/1000.0;
//		coil->diaInternal = atof(row.at(3).c_str())/1000.0;
//		coil->turns = atof(row.at(4).c_str());
//		cooler->coils.push_back(coil);
//	}
//	//Fælles tabel mellem mellekøler- og studstabel
//	if(i==0)
//		selectCommand = "SELECT * FROM COMMON WHERE type='" + cooler->type + "';";
//	else
//		selectCommand = "SELECT * FROM COMMONs WHERE type='" + cooler->type + "';";
//	result = this->Quary(selectCommand.c_str());
//
//	for(itera=result.begin(); itera < result.end(); itera++)
//	{
//		vector<string> row = *itera;
//		//Studsstørrelse hørende til fællestabellen opsøges i studstabellen
//		selectCommand = "SELECT * FROM NOZZLE WHERE nozzle ='" + row.at(2) + "';";
//		vector<vector<string>> nozzle = this->Quary(selectCommand.c_str());
//
//		if(row.at(1).compare("Discharge")==0){
//			cooler->DischNoz = std::make_shared<Nozzle>(nozzle[0].at(0), atof(nozzle[0].at(1).c_str()), atof(nozzle[0].at(2).c_str()));
//			continue;
//		}
//		if(row.at(1).compare("Suction")==0){
//			cooler->SuctionNoz = std::make_shared<Nozzle>(nozzle[0].at(0), atof(nozzle[0].at(1).c_str()), atof(nozzle[0].at(2).c_str()));
//			continue;
//		}	
//		if(row.at(1).compare("Flash")==0){
//			cooler->FlashNoz = std::make_shared<Nozzle>(nozzle[0].at(0), atof(nozzle[0].at(1).c_str()), atof(nozzle[0].at(2).c_str()));
//		}	
//		
//	}
//	
//
//}
//
//
//
//vector<string> Database::GetVMAspec(string type, int i)
//{
//	string selectCommand;
//	if(i==0)
//		selectCommand = "SELECT * FROM VMA WHERE type='" + type + "';";
//	else
//		selectCommand = "SELECT * FROM VMAs WHERE type='" + type + "';";
//	vector<vector<string>> result = this->Quary(selectCommand.c_str());		
//
//	vector<string> vma = result[0];
//	//Tre pladser til studse lægges til vektoren (Discharge, Suction, Flash)
//	vma.push_back("");
//	vma.push_back("");
//	vma.push_back("");
//	//Fælles tabel mellem mellekøler- og studstabel
//	if(i==0)
//		selectCommand = "SELECT * FROM COMMON WHERE type='" + type + "';";
//	else
//		selectCommand = "SELECT * FROM COMMONs WHERE type='" + type + "';";
//	vector<vector<string>> resultNoz = this->Quary(selectCommand.c_str());
//
//	vector<vector<string>>::iterator itera;
//	for(itera = resultNoz.begin(); itera < resultNoz.end(); itera++)
//	{
//		vector<string> vec = *itera;
//		if(vec.at(1).compare("Discharge")==0){
//			vma[vma.size()-3] = vec.at(2);
//			continue;
//		}
//		if(vec.at(1).compare("Suction")==0){
//			vma[vma.size()-2] = vec.at(2);
//			continue;
//		}
//		if(vec.at(1).compare("Flash")==0)
//			vma[vma.size()-1] = vec.at(2);
//
//	}
//	if(i==0)
//		selectCommand = "SELECT * FROM COIL WHERE type='" + type + "';";
//	else
//		selectCommand = "SELECT * FROM COILs WHERE type='" + type + "';";
//	result = this->Quary(selectCommand.c_str());
//
//	for(itera=result.begin(); itera < result.end(); itera++)
//	{
//		vector<string> row = *itera;
//		vma.push_back(row.at(0));
//		vma.push_back(row.at(1));
//		vma.push_back(row.at(2));
//		vma.push_back(row.at(3));
//		vma.push_back(row.at(4));
//		vma.push_back(row.at(5));		
//	}	
//
//	return vma;
//}
//
//
//vector<string> Database::GetVMAtypes(int i)
//{
//	string selectCommand;
//	if(i==0)
//		selectCommand = "SELECT * FROM VMA;";
//	else
//		selectCommand = "SELECT * FROM VMAs;";
//	vector<vector<string>> result = this->Quary(selectCommand.c_str());
//	vector<vector<string>>::iterator itera;
//	vector<string> types;
//	for(itera=result.begin(); itera < result.end(); itera++)
//	{
//		vector<string> vec = *itera;
//		types.push_back(vec.at(0));
//	}
//	return types;
//}
//
//
//vector<string> Database::GetNozzleList(void)
//{
//	string selectCommand = "SELECT * FROM NOZZLE;";
//	vector<vector<string>> result = this->Quary(selectCommand.c_str());
//	vector<vector<string>>::iterator itera;
//	vector<string> types;
//	for(itera=result.begin(); itera < result.end(); itera++)
//	{
//		vector<string> vec = *itera;
//		types.push_back(vec.at(0));
//	}
//	return types;
//}
//
//
//
//int Database::Update(vector<string> vec)
//{
//	//Opdater VMA-element
//	const char *type = vec[0].c_str();
//	double dia = atof(vec[1].c_str());
//	double diaDist = atof(vec[2].c_str());
//	double cylHeight = atof(vec[3].c_str());
//	double nozzleDia = atof(vec[4].c_str());
//	double perforRate  = atof(vec[5].c_str());
//	
//	sqlite3_stmt *statement;
//	const char *sql = "UPDATE VMAs SET dia=?, distDiameter=?, cylindricalHeight=?, nozzleHoleDiameter=?, percentFlowArea=? WHERE type=?";
//	if(sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
//	{
//		sqlite3_bind_text(statement, 6, type, strlen(type), 0);		
//		sqlite3_bind_double(statement, 1, dia);
//		sqlite3_bind_double(statement, 2, diaDist);
//		sqlite3_bind_double(statement, 3, cylHeight);
//		sqlite3_bind_double(statement, 4, nozzleDia);
//		sqlite3_bind_double(statement, 5, perforRate);
//		sqlite3_step(statement);
//	}
//	else
//		return -1;
//	sqlite3_finalize(statement);
//
//	int v;
//	//Update Coil
//	int a = atoi(vec[12].c_str());
//	double diaCoil = atof(vec[13].c_str());
//	double diaExternal = atof(vec[14].c_str());
//	double diaInternal = atof(vec[15].c_str());
//	double turns = atof(vec[16].c_str());
//	v = this->UpdateCoil(a,diaCoil,diaExternal,diaInternal,turns);
//	if(v==-1)
//		return v;
//	if(vec.size() > 18)
//	{
//		int a = atoi(vec[17].c_str());
//		diaCoil = atof(vec[18].c_str());
//		diaExternal = atof(vec[19].c_str());
//		diaInternal = atof(vec[20].c_str());
//		turns = atof(vec[21].c_str());
//		v = this->UpdateCoil(a,diaCoil,diaExternal,diaInternal,turns);
//		if(v==-1)
//			return v;
//	}
//	
//	//Update COMMONs
//	const char *function = vec[6].c_str();
//	const char *nozzle = vec[7].c_str();
//	v = this->UpdateNoz(type, function, nozzle);
//	if(v==-1)
//		return v;
//	function = vec[8].c_str();
//	nozzle = vec[9].c_str();
//	v = this->UpdateNoz(type, function, nozzle);
//	if(v==-1)
//		return v;
//	function = vec[10].c_str();
//	nozzle = vec[11].c_str();
//	v = this->UpdateNoz(type, function, nozzle);
//	if(v==-1)
//		return v;
//
//	return 0;
//}
//
//
//int Database::UpdateCoil(int a, double diaCoil, double diaExternal, double diaInternal, double turns)
//{
//	const char *sql = "UPDATE Coils SET diaCoil=?, diaExternal=?, diaInternal=?, turns=? WHERE a=?";
//	sqlite3_stmt *statement;
//	if(sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
//	{			
//		sqlite3_bind_int(statement, 5, a);
//		sqlite3_bind_double(statement, 1, diaCoil);
//		sqlite3_bind_double(statement, 2, diaExternal);
//		sqlite3_bind_double(statement, 3, diaInternal);
//		sqlite3_bind_double(statement, 4, turns);
//		sqlite3_step(statement);
//	}
//	else
//		return -1;
//	sqlite3_finalize(statement);
//	return 0;
//}
//
//
//
//int Database::UpdateNoz(const char* type, const char* function, const char* nozzle)
//{
//	const char *sql = "UPDATE COMMONs SET nozzle=? WHERE type=? AND function=?";
//
//	sqlite3_stmt *statement;
//	if(sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
//	{
//		sqlite3_bind_text(statement, 2, type, strlen(type), 0);	
//		sqlite3_bind_text(statement, 3, function, strlen(function), 0);
//		sqlite3_bind_text(statement, 1, nozzle, strlen(nozzle), 0);
//		sqlite3_step(statement);
//	}
//	else
//		return -1;
//	sqlite3_finalize(statement);
//	return 0;
//}
//
