#include "stdafx.h"
#include <iostream>
#include <string>
#include <tuple>
#include <fstream>
#include "SqliteDB.h"
#include "sqlite3.h"
//#include "Person.h"
//#include "Actor.h"
//#include "Movie.h"
//#include "Director.h"
//#include "Distributor.h"
//#include "Producer.h"
//#include "SUS.h"
#include "BiomassPipeRun.h"

#include "sqlite3.h"

DATABASE::SqliteDB::SqliteDB(const char* name)
{
	database = NULL;
	bool open = Open(name);
	if(!open)
		throw std::exception("Database didn't open");

	
}


DATABASE::SqliteDB::~SqliteDB(void)
{
	if (database != nullptr)
		Close();
}




bool DATABASE::SqliteDB::Open(const char *name)
{
	bool error = true;
	if (sqlite3_open(name, &database) == SQLITE_OK)
	{
		int vv = 0;
		//return true;

	/*	error = false;
	else
		return false;*/

		//int fkeyConstraintsEnabled;
		//int i = 1; /* either 0 or 1 to disable/enable constraints */
		//int err = sqlite3_db_config(database, SQLITE_DBCONFIG_ENABLE_FKEY, i, &fkeyConstraintsEnabled);
		//if (err != SQLITE_OK) /* die */

		//PRAGMA foreign_keys = ON


		sqlite3_stmt* statement;
		const char* sql = "PRAGMA foreign_keys = ON";

		if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
		{
			sqlite3_step(statement);
			sqlite3_finalize(statement);
		}

		return true;
	}

	return false;
}


void DATABASE::SqliteDB::Close()
{
	sqlite3_close(database);
}


int DATABASE::SqliteDB::InsertProject(string name) const
{
	sqlite3_stmt* statement;	

	const char* sql = "INSERT INTO Project(name) VALUES(?)";

	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
	{
		sqlite3_bind_text(statement, 1, name.c_str(), strlen(name.c_str()), 0);
		sqlite3_step(statement);			
	}
	else
		return -1;
	sqlite3_finalize(statement);

	return 0;
}


int DATABASE::SqliteDB::InsertRor(string pk, string type, int Dim, double Dia, double s) const
{
	sqlite3_stmt* statement;

	const char* sql = "INSERT INTO Ror(pk, type, Dim, Dia, s) VALUES(?, ?, ?, ?, ?)";

	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
	{
		sqlite3_bind_text(statement, 1, pk.c_str(), strlen(pk.c_str()), 0);
		sqlite3_bind_text(statement, 2, type.c_str(), strlen(type.c_str()), 0);
		sqlite3_bind_int(statement, 3, Dim);
		sqlite3_bind_double(statement, 4, Dia);
		sqlite3_bind_double(statement, 5, s);

		sqlite3_step(statement);
	}
	else
		return -1;
	sqlite3_finalize(statement);

	return 0;
}


pair<string, int> DATABASE::SqliteDB::GetRor(string pk) const
{
	sqlite3_stmt* statement;

	string pipeType;
	int dim = 0;
	
	const char* sql = "SELECT * FROM Ror WHERE pk = ?";

	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
	{
		sqlite3_bind_text(statement, 1, pk.c_str(), strlen(pk.c_str()), 0);
		
		int cols = sqlite3_column_count(statement);
		int result = 0;
		while (true)
		{
			result = sqlite3_step(statement);

			if (result == SQLITE_ROW)
			{
				pipeType = (char*)sqlite3_column_text(statement, 1);
				dim = sqlite3_column_int(statement, 2);				
			}
			else
				break;
		}
		sqlite3_finalize(statement);
	}

	return make_pair(pipeType, dim);
	
}


pair<int, double> DATABASE::SqliteDB::GetPK_Ror(string type, int Dim) const
{
	int pk = 0;
	double dia = 0;
	
	sqlite3_stmt* statement;
	const char* sql = "SELECT * FROM Ror WHERE type = ? AND dim = ?";
	
		if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
		{
			sqlite3_bind_text(statement, 1, type.c_str(), strlen(type.c_str()), 0);
			sqlite3_bind_int(statement, 2, Dim);
			int cols = sqlite3_column_count(statement);
			int result = 0;
			while(true)
			{
				result = sqlite3_step(statement);
			
				if(result == SQLITE_ROW)
				{								
					pk =  sqlite3_column_int(statement, 0);	
					dia = sqlite3_column_double(statement, 3);
				}
				else
					break;
			}
			sqlite3_finalize(statement);
		}		
	 	
		return make_pair(pk, dia);
}



pair<int, double> DATABASE::SqliteDB::GetPK_Ror_(int pk) const
{
	double dia = 0;

	sqlite3_stmt* statement;
	const char* sql = "SELECT * FROM Ror WHERE a = ?";

	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
	{
		
		sqlite3_bind_int(statement, 0, pk);
		int cols = sqlite3_column_count(statement);
		int result = 0;
		while (true)
		{
			result = sqlite3_step(statement);

			if (result == SQLITE_ROW)
			{
				pk = sqlite3_column_int(statement, 0);
				dia = sqlite3_column_double(statement, 3);
			}
			else
				break;
		}
		sqlite3_finalize(statement);
	}

	return make_pair(pk, dia);
}



int DATABASE::SqliteDB::InsertPipeRun(string projectName, shared_ptr<PLANT::BiomassPipeRun> bioPR) const
{
	sqlite3_stmt* statement;

	const char* sql = "INSERT INTO PipeRun(name, project, InletHead, OutletHead) VALUES(?, ?, ?, ?)";

	string name = bioPR->GetName();

	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
	{
		sqlite3_bind_text(statement, 1, name.c_str(), strlen(name.c_str()), 0);
		sqlite3_bind_text(statement, 2, projectName.c_str(), strlen(projectName.c_str()), 0);
		sqlite3_bind_double(statement, 3, bioPR->GetInletHead_m());
		sqlite3_bind_double(statement, 4, bioPR->GetOutletHead_m());
		sqlite3_step(statement);
	}
	else
		return -1;
	sqlite3_finalize(statement);

	return 0;
}


vector<shared_ptr<PLANT::BiomassPipeRun>> DATABASE::SqliteDB::GetBiomassPipeRuns(string projectName) const
{
	vector<shared_ptr<PLANT::BiomassPipeRun>> vec;
	shared_ptr<CIRCUIT::BiomassCmp> bioCmps;
	string namePipeRun;
	double inletHead_m = 0;
	double outletHead_m = 0;

	sqlite3_stmt* statement;
	const char* sql = "SELECT * FROM PipeRun WHERE project = ? ";	

	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
	{
		sqlite3_bind_text(statement, 1, projectName.c_str(), strlen(projectName.c_str()), 0);
				
		int result = 0;
		while (true)
		{
			result = sqlite3_step(statement);

			if (result == SQLITE_ROW)
			{				
				namePipeRun = (char*)sqlite3_column_text(statement, 0);
				inletHead_m = sqlite3_column_double(statement, 2);
				outletHead_m = sqlite3_column_double(statement, 3);
				bioCmps = GetBioCmps(namePipeRun);
				
				vec.push_back(make_shared<PLANT::BiomassPipeRun>(namePipeRun, bioCmps, inletHead_m, outletHead_m));
			}
			else
				break;
		}
		sqlite3_finalize(statement);
	}

	return vec;
}




int DATABASE::SqliteDB::InsertBioCmp(shared_ptr<CIRCUIT::BiomassCmp> cmp, string project, string pipeRun)
{
	string tag = cmp->GetTag();
	string pk = project + "_" + tag;
	double length = 0;
	int elbow90 = 0;
	int elbow45 = 0;

	string ror = "";
	string function;

	switch (cmp->GetFunctionType())
	{
	case CIRCUIT::BiomassCmpType::pipe:
	{
		function = "Pipe";
		shared_ptr<CIRCUIT::PipeRunBiomass> pipe_ = dynamic_pointer_cast<CIRCUIT::PipeRunBiomass>(cmp);
		length = pipe_->GetLength();
		elbow90 = pipe_->GetElbow90();
		elbow45 = pipe_->GetElbow45();
		ror = pipe_->GetType() + "_" + to_string(pipe_->GetDimension());
		break;
	}
	case CIRCUIT::BiomassCmpType::flowmeter:
		function = "Flow meter";
		ror = "C2_100";
		break;
	case CIRCUIT::BiomassCmpType::hex:
		function = "HEX";
		ror = "C2_100";
		break;
	case CIRCUIT::BiomassCmpType::macerator:
		function = "Macerator";
		ror = "C1_100";
		break;
	case CIRCUIT::BiomassCmpType::mixer:
		function = "Mixer";
		ror = "C1_100";
		break;
	case CIRCUIT::BiomassCmpType::pump:
		function = "Pump";
		ror = "C1_100";
		break;
	case CIRCUIT::BiomassCmpType::screwpress:
		function = "Screwpress";
		ror = "C1_100";
		break;
	default:
		break;
	}
		
	string inletPipe = pk;
	string outletPipe = pk;
	string description = cmp->GetType();


	sqlite3_stmt* statement;
	const char* sql = "INSERT INTO BioComponent(pk, tag, function, description, pipeRun, inlet, outlet, length, elbow90, elbow45, ror) VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
	
	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
	{
		sqlite3_bind_text(statement, 1, pk.c_str(), strlen(pk.c_str()), 0);
		sqlite3_bind_text(statement, 2, tag.c_str(), strlen(tag.c_str()), 0);
		sqlite3_bind_text(statement, 3, function.c_str(), strlen(function.c_str()), 0);
		sqlite3_bind_text(statement, 4, description.c_str(), strlen(description.c_str()), 0);
		sqlite3_bind_text(statement, 5, pipeRun.c_str(), strlen(pipeRun.c_str()), 0);
		sqlite3_bind_text(statement, 6, inletPipe.c_str(), strlen(inletPipe.c_str()), 0);
		sqlite3_bind_text(statement, 7, outletPipe.c_str(), strlen(outletPipe.c_str()), 0);
		sqlite3_bind_double(statement, 8, length);
		sqlite3_bind_int(statement, 9, elbow90);
		sqlite3_bind_int(statement, 10, elbow45);
		sqlite3_bind_text(statement, 11, ror.c_str(), strlen(ror.c_str()), 0);
		sqlite3_step(statement);
	}
	else
		return -1;
	sqlite3_finalize(statement);

	return 0;
}


struct Ref
{
	Ref(string tag, string tagUpStream, string tagDownStream) : tag(tag), tagUpStream(tagUpStream), tagDownStream(tagDownStream)
	{
	}

	string tag;
	string tagUpStream;
	string tagDownStream;
};



shared_ptr<CIRCUIT::BiomassCmp> DATABASE::SqliteDB::GetBioCmps(string bioPipeRun) const
{
	vector<shared_ptr<CIRCUIT::BiomassCmp>> vec;
	vector<Ref> refs;	

	sqlite3_stmt* statement;	
	const char* sql = "SELECT * FROM BioComponent WHERE pipeRun = ?";	
	
	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
	{
		string pk;
		string tag;
		string function;
		string description;
		string pipeRun;
		string inlet;
		string outlet;
		double length = 0;
		int elbow90 = 0;
		int elbow45 = 0;
		string ror;
		
		sqlite3_bind_text(statement, 1, bioPipeRun.c_str(), strlen(bioPipeRun.c_str()), 0);

		int result = 0;
		while (true)
		{
			result = sqlite3_step(statement);

			if (result == SQLITE_ROW)
			{
				pk = (char*)sqlite3_column_text(statement, 0);	
				tag = (char*)sqlite3_column_text(statement, 1);
				function = (char*)sqlite3_column_text(statement, 2);
				description = (char*)sqlite3_column_text(statement, 3);
				bioPipeRun = (char*)sqlite3_column_text(statement, 4);
				inlet = (char*)sqlite3_column_text(statement, 5);
				outlet = (char*)sqlite3_column_text(statement, 6);
				length = sqlite3_column_double(statement, 7);
				elbow90 = sqlite3_column_int(statement, 8);
				elbow45 = sqlite3_column_int(statement, 9);
				ror = (char*)sqlite3_column_text(statement, 10);

				if (function.compare("Pipe") == 0)
				{
					pair<string, int> pipeDim = GetRor(ror);
					vec.push_back(make_shared<CIRCUIT::PipeRunBiomass>(tag, pipeDim.first, pipeDim.second, 0.05e-3, length, elbow45, elbow90, 0, 0, nullptr));
				}
				else if (function.compare("Flow meter") == 0)
					vec.push_back(make_shared<CIRCUIT::BioFlowMeter>(tag, description, nullptr));
				else if (function.compare("HEX") == 0)
					vec.push_back(make_shared<CIRCUIT::BioHEX>(tag, description, nullptr));
				else if (function.compare("Macerator") == 0)
					vec.push_back(make_shared<CIRCUIT::Macerator>(tag, description, nullptr));
				else if (function.compare("Mixer") == 0)
					vec.push_back(make_shared<CIRCUIT::BioMixer>(tag, description, nullptr));
				else if (function.compare("Pump") == 0)
					vec.push_back(make_shared<CIRCUIT::BioPump>(tag, description, nullptr));
				else if (function.compare("Screwpress") == 0)
					vec.push_back(make_shared<CIRCUIT::BioPump>(tag, description, nullptr));
								
				refs.push_back(Ref(pk, inlet, outlet));
			}
			else
				break;

		}
		sqlite3_finalize(statement);
	}

	shared_ptr<CIRCUIT::BiomassCmp> current = nullptr;
	shared_ptr<CIRCUIT::BiomassCmp> inletOutlet = nullptr;
	for (unsigned int ii = 0; ii < refs.size(); ii++)
	{
		current = vec.at(ii);
		string pk = refs.at(ii).tag;
		string upSt = refs.at(ii).tagUpStream;
		string downSt = refs.at(ii).tagDownStream;

		for (unsigned jj = 0; jj < refs.size(); jj++)
		{
			if (upSt.compare(refs.at(jj).tag) == 0)
				current->SetUpStream(vec.at(jj));
			if (downSt.compare(refs.at(jj).tag) == 0)
				current->SetDownStream(vec.at(jj));
		}
	}	

	if (vec.size() > 0)
		return vec.at(0);
	else
		return nullptr;
}



vector<shared_ptr<CIRCUIT::BiomassCmp>> DATABASE::SqliteDB::GetBioCmps2(string bioPipeRun) const
{
	vector<shared_ptr<CIRCUIT::BiomassCmp>> vec;	
	vector<Ref> refs;

	sqlite3_stmt* statement;
	const char* sql = "SELECT * FROM BioComponent WHERE pipeRun = ?";

	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
	{
		string pk;
		string tag;
		string function;
		string description;
		string pipeRun;
		string inlet;
		string outlet;
		double length = 0;
		int elbow90 = 0;
		int elbow45 = 0;
		string ror;

		sqlite3_bind_text(statement, 1, bioPipeRun.c_str(), strlen(bioPipeRun.c_str()), 0);

		int result = 0;
		while (true)
		{
			result = sqlite3_step(statement);

			if (result == SQLITE_ROW)
			{
				pk = (char*)sqlite3_column_text(statement, 0);
				tag = (char*)sqlite3_column_text(statement, 1);
				function = (char*)sqlite3_column_text(statement, 2);
				description = (char*)sqlite3_column_text(statement, 3);
				bioPipeRun = (char*)sqlite3_column_text(statement, 4);
				inlet = (char*)sqlite3_column_text(statement, 5);
				outlet = (char*)sqlite3_column_text(statement, 6);
				length = sqlite3_column_double(statement, 7);
				elbow90 = sqlite3_column_int(statement, 8);
				elbow45 = sqlite3_column_int(statement, 9);
				ror = (char*)sqlite3_column_text(statement, 10);

				if (function.compare("Pipe") == 0)
				{
					pair<string, int> pipeDim = GetRor(ror);
					vec.push_back(make_shared<CIRCUIT::PipeRunBiomass>(tag, pipeDim.first, pipeDim.second, 0.05e-3, length, elbow45, elbow90, 0, 0, nullptr));
				}
				else if (function.compare("Flow meter") == 0)
					vec.push_back(make_shared<CIRCUIT::BioFlowMeter>(tag, description, nullptr));
				else if (function.compare("HEX") == 0)
					vec.push_back(make_shared<CIRCUIT::BioHEX>(tag, description, nullptr));
				else if (function.compare("Macerator") == 0)
					vec.push_back(make_shared<CIRCUIT::Macerator>(tag, description, nullptr));
				else if (function.compare("Mixer") == 0)
					vec.push_back(make_shared<CIRCUIT::BioMixer>(tag, description, nullptr));
				else if (function.compare("Pump") == 0)
					vec.push_back(make_shared<CIRCUIT::BioPump>(tag, description, nullptr));
				else if (function.compare("Screwpress") == 0)
					vec.push_back(make_shared<CIRCUIT::BioPump>(tag, description, nullptr));
				
				refs.push_back(Ref(pk, inlet, outlet));
			}
			else
				break;

		}
		sqlite3_finalize(statement);
	}


	shared_ptr<CIRCUIT::BiomassCmp> current = nullptr;
	shared_ptr<CIRCUIT::BiomassCmp> inletOutlet = nullptr;
	for (unsigned int ii = 0; ii < refs.size(); ii++)
	{
		current = vec.at(ii);
		string pk = refs.at(ii).tag;
		string upSt = refs.at(ii).tagUpStream;
		string downSt = refs.at(ii).tagDownStream;

		for (unsigned jj = 0; jj < refs.size(); jj++)
		{
			if (upSt.compare(refs.at(jj).tag) == 0)
				current->SetUpStream(vec.at(jj));
			if (downSt.compare(refs.at(jj).tag) == 0)
				current->SetDownStream(vec.at(jj));
		}
	}	

	return vec;;

}






int DATABASE::SqliteDB::UpdateBioCmpRef(string project, shared_ptr<CIRCUIT::BiomassCmp> pipe, shared_ptr<CIRCUIT::BiomassCmp> inlet, shared_ptr<CIRCUIT::BiomassCmp> outlet) const
{
	sqlite3_stmt* statement;

	if (inlet == nullptr)
	{
		const char* sql = "UPDATE BioComponent SET  outlet = ? WHERE pk = ?";
				
		if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
		{
			string pk = project + "_" + pipe->GetTag();
			
			string pk_outlet = project + "_" + outlet->GetTag();
			sqlite3_bind_text(statement, 2, pk.c_str(), strlen(pk.c_str()), 0);
			sqlite3_bind_text(statement, 1, pk_outlet.c_str(), strlen(pk_outlet.c_str()), 0);

			sqlite3_step(statement);
		}
		else
			return -1;

		sqlite3_finalize(statement);
	}
	else if (outlet == nullptr)
	{
		const char* sql = "UPDATE BioComponent SET  inlet = ? WHERE pk = ?";

		
		if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
		{
			string pk = project + "_" + pipe->GetTag();
			string pk_inlet = project + "_" + inlet->GetTag();
			sqlite3_bind_text(statement, 2, pk.c_str(), strlen(pk.c_str()), 0);
			sqlite3_bind_text(statement, 1, pk_inlet.c_str(), strlen(pk_inlet.c_str()), 0);

			sqlite3_step(statement);
		}
		else
			return -1;

		sqlite3_finalize(statement);
	}
	else
	{
		const char* sql = "UPDATE BioComponent SET inlet = ?, outlet = ? WHERE pk = ?";

		if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
		{
			string pk = project + "_" + pipe->GetTag();
			string pk_inlet = project + "_" + inlet->GetTag();
			string pk_outlet = project + "_" + outlet->GetTag();
			sqlite3_bind_text(statement, 3, pk.c_str(), strlen(pk.c_str()), 0);
			sqlite3_bind_text(statement, 1, pk_inlet.c_str(), strlen(pk_inlet.c_str()), 0);
			sqlite3_bind_text(statement, 2, pk_outlet.c_str(), strlen(pk_outlet.c_str()), 0);

			sqlite3_step(statement);
		}
		else
			return -1;

		sqlite3_finalize(statement);
	}
	
}














vector<pair<string, string>> DATABASE::SqliteDB::GetPipeRunNames(string projectName)
{
	vector<pair<string, string>> keysToRuns;

	sqlite3_stmt* statement;
	const char* sql = "SELECT * FROM PipeRun WHERE project = ? ";
	
	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
	{
		sqlite3_bind_text(statement, 1, projectName.c_str(), strlen(projectName.c_str()), 0);
		
		//int cols = sqlite3_column_count(statement);
		int result = 0;
		while(true)
		{
			result = sqlite3_step(statement);
			
			if(result == SQLITE_ROW)
			{							
				string key = (char*)sqlite3_column_text(statement, 0);
				string name = (char*)sqlite3_column_text(statement, 1);
						
				keysToRuns.push_back(make_pair(key, name));
						
			}
			else
				break;
		}
		sqlite3_finalize(statement);
	}
			 	
	return keysToRuns;
}


vector<string> DATABASE::SqliteDB::GetRuns()
{
	vector<string> res;

	sqlite3_stmt* statement;
	const char* sql = "SELECT * FROM PipeRun";

	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
	{
		//sqlite3_bind_text(statement, 3, projectName.c_str(), strlen(projectName.c_str()), 0);

		int cols = sqlite3_column_count(statement);
		int result = 0;
		while (true)
		{
			result = sqlite3_step(statement);

			if (result == SQLITE_ROW)
			{
				/*int key = sqlite3_column_int(statement, 0);
				res.push_back(to_string(key));*/
				string name = (char*)sqlite3_column_text(statement, 1);
				res.push_back(name);
				/*keysToRuns.push_back(make_pair(key, name));
				res.push_back((char*)sqlite3_column_text(statement, 0));*/

			}
			else
				break;
		}
		sqlite3_finalize(statement);
	}

	return res;
}
	




//
//vector<shared_ptr<CIRCUIT::BiomassCmp>> DATABASE::SqliteDB::GetBioMassCmp(int bioMassPipeRunID)
//{
//	vector<shared_ptr<CIRCUIT::BiomassCmp>> vec;
//
//	return vec;
//}




//vector<shared_ptr<Interface>> DATABASE::SqliteDB::Quary(const char *quary)
//{
//	vector<Interface> results;
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
//				//vector<string> values;
//				for(int col=0; col < cols; col++)
//				{
//					//values.push_back((char*)sqlite3_column_text(statement, col));
//				
//				}
//				//results.push_back(values);
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
//shared_ptr<Actor> DATABASE::SqliteDB::GetActor(string name, bool deep)
//{
//	shared_ptr<Actor> actor = nullptr;
//
//	auto natio = [](string na) {
//
//		if (na.compare("Belgian") == 0)
//			return Nationality::Belgian;
//		if (na.compare("Danish") == 0)
//			return Nationality::Danish;
//		if (na.compare("French") == 0)
//			return Nationality::French;
//		if (na.compare("German") == 0)
//			return Nationality::German;
//		if (na.compare("Italian") == 0)
//			return Nationality::Italian;
//		if (na.compare("Spanish") == 0)
//			return Nationality::Spanish;
//		if (na.compare("USA") == 0)
//			return Nationality::USA;
//		if (na.compare("Not knowen") == 0)
//			return Nationality::NotKnown;
//	};
//	
//	
//	sqlite3_stmt* statement;
//	const char* sql = "SELECT * FROM ACTOR WHERE name = ?";
//
//	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
//	{
//		sqlite3_bind_text(statement, 1, name.c_str(), strlen(name.c_str()), 0);
//		int cols = sqlite3_column_count(statement);
//		int result = 0;
//		while(true)
//		{
//			result = sqlite3_step(statement);
//		
//			if(result == SQLITE_ROW)
//			{		
//				string nati = (char*)sqlite3_column_text(statement, 1);				
//				int yearStart = sqlite3_column_int(statement, 2);
//				int yearEnd = sqlite3_column_int(statement, 3);
//				int yearBorn = sqlite3_column_int(statement, 4);
//
//				actor = make_shared<Actor>(name, yearBorn, yearStart, yearEnd, natio(nati));						
//					
//			}
//			else
//				break;
//		}
//		sqlite3_finalize(statement);
//	}
//	actor->aka = GetActorAKA(name);
//
//	if (deep)
//	{
//		actor->movies_ = ActMovies(name);
//	}
// 	
//	return actor;
//}
//
//
//int DATABASE::SqliteDB::InsertActor(shared_ptr<Actor> actor)
//{
//	string natio;
//	switch (actor->nationality)
//	{
//	case Nationality::Belgian:
//		natio = "Belgian";
//		break;
//	case Nationality::Danish:
//		natio = "Danish";
//		break;
//	case Nationality::French:
//		natio = "French";
//		break;
//	case Nationality::German:
//		natio = "German";
//		break;
//	case Nationality::Italian:
//		natio = "Italian";
//		break;
//	case Nationality::Spanish:
//		natio = "Spanish";
//		break;
//	case Nationality::USA:
//		natio = "USA";
//		break;
//	case Nationality::NotKnown:
//		natio = "Not known";
//		break;
//	}
//
//	sqlite3_stmt* statement;	
//
//	const char* sql = "INSERT INTO ACTOR(name, nationality, yearStart, yearEnd, yearBorn) VALUES(?, ?, ?, ?, ?)";
//
//	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
//	{
//		sqlite3_bind_text(statement, 1, actor->name.c_str(), strlen(actor->name.c_str()), 0);
//		sqlite3_bind_text(statement, 2, natio.c_str(), strlen(natio.c_str()), 0);
//		sqlite3_bind_int(statement, 3, actor->yearStart);
//		sqlite3_bind_int(statement, 4, actor->yearEnd);
//		sqlite3_bind_int(statement, 5, actor->yearBorn);
//		sqlite3_step(statement);			
//	}
//	else
//		return -1;
//	sqlite3_finalize(statement);
//}
//
//
//
//
//int DATABASE::SqliteDB::UpdateActor(shared_ptr<Actor> actor)
//{
//	sqlite3_stmt* statement;
//	
//	const char* sql = "UPDATE ACTOR SET nationality = ?, yearStart = ?, yearEnd = ?, yearBorn = ? WHERE name = ?";
//
//	string natio;
//	switch (actor->nationality)
//	{
//	case Nationality::Belgian:
//		natio = "Belgian";
//		break;
//	case Nationality::Danish:
//		natio = "Danish";
//		break;
//	case Nationality::French:
//		natio = "French";
//		break;
//	case Nationality::German:
//		natio = "German";
//		break;
//	case Nationality::Italian:
//		natio = "Italian";
//		break;
//	case Nationality::Spanish:
//		natio = "Spanish";
//		break;
//	case Nationality::USA:
//		natio = "USA";
//		break;
//	case Nationality::NotKnown:
//		natio = "Not known";
//		break;
//	}
//	string non = "";
//	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
//	{
//		sqlite3_bind_text(statement, 5, actor->name.c_str(), strlen(actor->name.c_str()), 0);
//		sqlite3_bind_text(statement, 1, natio.c_str(), strlen(natio.c_str()), 0);
//		sqlite3_bind_int(statement, 2, actor->yearStart);
//		sqlite3_bind_int(statement, 3, actor->yearEnd);
//		sqlite3_bind_int(statement, 4, actor->yearBorn);
//
//		sqlite3_step(statement);
//	}
//	else
//		return -1;
//	sqlite3_finalize(statement);
//
//	DeleteActorAKA(actor->name);
//	for (string aka : actor->aka)
//		InsertActorAKA(actor->name, aka);
//}
//
//
//int DATABASE::SqliteDB::DeleteActor(shared_ptr<Actor> actor)
//{
//	DeleteActorPicture(actor->name);
//	DeleteActorAKA(actor->name);
//
//	sqlite3_stmt* statement;
//	const char* sql = "DELETE FROM ACTOR WHERE name = ?";
//
//	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
//	{
//		sqlite3_bind_text(statement, 1, actor->name.c_str(), strlen(actor->name.c_str()), 0);
//		int cols = sqlite3_column_count(statement);
//		int result = 0;
//		result = sqlite3_step(statement);
//				
//		sqlite3_finalize(statement);
//	}
//	else
//		return -1;
//
//	return 0;
//}
//	
//
//vector<string> DATABASE::SqliteDB::GetActorList() const
//{
//	vector<string> list;
//
//	sqlite3_stmt* statement;
//	const char* sql = "SELECT * FROM ACTOR";
//
//	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
//	{
//		//sqlite3_bind_text(statement, 1, name.c_str(), strlen(name.c_str()), 0);
//		int cols = sqlite3_column_count(statement);
//		int result = 0;
//		while (true)
//		{
//			result = sqlite3_step(statement);
//
//			if (result == SQLITE_ROW)
//			{
//				list.push_back((char*)sqlite3_column_text(statement, 0));
//			}
//			else
//				break;
//		}
//		sqlite3_finalize(statement);
//	}
//	return list;
//}
//
//
//
//
//
//vector<string> DATABASE::SqliteDB::GetMovieList() const
//{
//	vector<string> list;
//
//	sqlite3_stmt* statement;
//	const char* sql = "SELECT * FROM MOVIE";
//
//	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
//	{
//		//sqlite3_bind_text(statement, 1, name.c_str(), strlen(name.c_str()), 0);
//		int cols = sqlite3_column_count(statement);
//		int result = 0;
//		while (true)
//		{
//			result = sqlite3_step(statement);
//
//			if (result == SQLITE_ROW)
//			{
//				list.push_back((char*)sqlite3_column_text(statement, 0));
//			}
//			else
//				break;
//		}
//		sqlite3_finalize(statement);
//	}
//	return list;
//}
//
//
//vector<string> DATABASE::SqliteDB::GetDirectorList() const
//{
//	vector<string> list;
//
//	sqlite3_stmt* statement;
//	const char* sql = "SELECT * FROM DIRECTOR";
//
//	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
//	{
//		//sqlite3_bind_text(statement, 1, name.c_str(), strlen(name.c_str()), 0);
//		int cols = sqlite3_column_count(statement);
//		int result = 0;
//		while (true)
//		{
//			result = sqlite3_step(statement);
//
//			if (result == SQLITE_ROW)
//			{
//				list.push_back((char*)sqlite3_column_text(statement, 0));
//			}
//			else
//				break;
//		}
//		sqlite3_finalize(statement);
//	}
//	return list;
//}
//
//
//shared_ptr<Director> DATABASE::SqliteDB::GetDirector(string name, bool deep)
//{
//	shared_ptr<Director> director = nullptr;
//
//	auto natio = [](string na) {
//
//		if (na.compare("Belgian") == 0)
//			return Nationality::Belgian;
//		if (na.compare("Danish") == 0)
//			return Nationality::Danish;
//		if (na.compare("French") == 0)
//			return Nationality::French;
//		if (na.compare("German") == 0)
//			return Nationality::German;
//		if (na.compare("Italian") == 0)
//			return Nationality::Italian;
//		if (na.compare("Spanish") == 0)
//			return Nationality::Spanish;
//		if (na.compare("USA") == 0)
//			return Nationality::USA;
//		if (na.compare("Not knowen") == 0)
//			return Nationality::NotKnown;
//	};
//
//
//	sqlite3_stmt* statement;
//	const char* sql = "SELECT * FROM DIRECTOR WHERE name = ?";
//
//	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
//	{
//		sqlite3_bind_text(statement, 1, name.c_str(), strlen(name.c_str()), 0);
//		int cols = sqlite3_column_count(statement);
//		int result = 0;
//		while (true)
//		{
//			result = sqlite3_step(statement);
//
//			if (result == SQLITE_ROW)
//			{
//				string nati = (char*)sqlite3_column_text(statement, 1);
//				int yearStart = sqlite3_column_int(statement, 2);
//				int yearEnd = sqlite3_column_int(statement, 3);				
//
//				director = make_shared<Director>(name, yearStart, yearEnd, natio(nati));
//
//			}
//			else
//				break;
//		}
//		sqlite3_finalize(statement);
//	}
//	if(deep)
//		director->movies_ = DirectorMovies(name);
//
//	return director;
//
//}
//
//
//
//int DATABASE::SqliteDB::InsertDirector(shared_ptr<Director> director)
//{
//	string natio;
//	switch (director->nationality)
//	{
//	case Nationality::Belgian:
//		natio = "Belgian";
//		break;
//	case Nationality::Danish:
//		natio = "Danish";
//		break;
//	case Nationality::French:
//		natio = "French";
//		break;
//	case Nationality::German:
//		natio = "German";
//		break;
//	case Nationality::Italian:
//		natio = "Italian";
//		break;
//	case Nationality::Spanish:
//		natio = "Spanish";
//		break;
//	case Nationality::USA:
//		natio = "USA";
//		break;
//	case Nationality::NotKnown:
//		natio = "Not known";
//		break;
//	} 
//	
//	sqlite3_stmt* statement;
//	const char* sql = "INSERT INTO DIRECTOR(name, nationality, yearStart, yearEnd) VALUES(?, ?, ?, ?)";
//
//	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
//	{
//		sqlite3_bind_text(statement, 1, director->name.c_str(), strlen(director->name.c_str()), 0);
//		sqlite3_bind_text(statement, 2, natio.c_str(), strlen(natio.c_str()), 0);
//		sqlite3_bind_int(statement, 3, director->yearStart);
//		sqlite3_bind_int(statement, 4, director->yearEnd);
//		sqlite3_step(statement);
//	}
//	else
//		return -1;
//	sqlite3_finalize(statement);
//}
//
//
//
//
//shared_ptr<Movie> DATABASE::SqliteDB::GetMovie(string name, bool deep)
//{
//	shared_ptr<Movie> movie = nullptr;
//
//	sqlite3_stmt* statement;
//	const char* sql = "SELECT * FROM MOVIE WHERE nameMovie = ?";
//
//	
//	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
//	{
//		sqlite3_bind_text(statement, 1, name.c_str(), strlen(name.c_str()), 0);
//		int cols = sqlite3_column_count(statement);
//		int result = 0;
//		while (true)
//		{
//			result = sqlite3_step(statement);
//
//		
//			if (result == SQLITE_ROW)
//			{						
//				vector<shared_ptr<Actor>> acts;
//				vector<shared_ptr<Label>> labels;
//				string director = (char*)sqlite3_column_text(statement, 1);
//				string producer = (char*)sqlite3_column_text(statement, 2);
//				string distributor = (char*)sqlite3_column_text(statement, 3);
//				int year = sqlite3_column_int(statement, 4);
//				int status = sqlite3_column_int(statement, 5);
//				int inCollection = sqlite3_column_int(statement, 6);
//				int type = sqlite3_column_int(statement, 7);				
//				int mp4 = sqlite3_column_int(statement, 8);
//				int mp4_size = sqlite3_column_int(statement, 9);
//				InCollection inCol = InCollection::NotInCollection;
//				Type type_ = Type::Film;
//
//				switch (inCollection)
//				{
//				case 0:
//					inCol = InCollection::DVD;
//					break;
//				case 1:
//					inCol = InCollection::Download;
//					break;
//				case 2:
//					inCol = InCollection::NotInCollection;
//					break;
//				}
//
//				if (type == 1)
//					type_ = Type::Compilation;
//
//				bool MP4 = false;
//				if (mp4 == 1)
//					MP4 = true;
//				else
//					mp4_size = 0;				
//				movie = make_shared<Movie>(name, nullptr, nullptr, labels, year, type_, inCol, MP4, mp4_size);
//				movie->director_ = GetDirector(director);
//				movie->producer_ = GetProducer(producer);
//				movie->distributor_ = GetDistributor(distributor);
//			}
//			else
//				break;
//
//			if(deep)
//				movie->actors_ = this->MovieActs(name); //ActMovies(name);
//		}
//		sqlite3_finalize(statement);
//
//		movie->aka = GetMovieAKA(name);
//		
//
//	}
//
//	return movie;
//
//}
//
//vector<shared_ptr<Movie>> DATABASE::SqliteDB::GetMovies(bool deep)
//{
//	vector<shared_ptr<Movie>> mos;
//	sqlite3_stmt* statement;
//	const char* sql = "SELECT * FROM MOVIE";
//
//	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
//	{
//		int cols = sqlite3_column_count(statement);
//		int result = 0;
//		while (true)
//		{
//			result = sqlite3_step(statement);
//
//			if (result == SQLITE_ROW)
//			{
//				vector<shared_ptr<Actor>> acts;
//				vector<shared_ptr<Label>> labels;
//				string name = (char*)sqlite3_column_text(statement, 0);
//				string director = (char*)sqlite3_column_text(statement, 1);
//				string producer = (char*)sqlite3_column_text(statement, 2);
//				string distributor = (char*)sqlite3_column_text(statement, 3);
//				int year = sqlite3_column_int(statement, 4);
//				int status = sqlite3_column_int(statement, 5);
//				int inCollection = sqlite3_column_int(statement, 6);
//				int type = sqlite3_column_int(statement, 7);
//				int mp4 = sqlite3_column_int(statement, 8);
//				int mp4_size = sqlite3_column_int(statement, 9);
//				InCollection inCol = InCollection::NotInCollection;
//				
//
//				switch (inCollection)
//				{
//				case 0:
//					inCol = InCollection::DVD;
//					break;
//				case 1:
//					inCol = InCollection::Download;
//					break;
//				case 2:
//					inCol = InCollection::NotInCollection;
//					break;
//				}
//
//				bool MP4 = false;
//				if (mp4 == 1)
//					MP4 = true;
//				else
//					mp4_size = 0;
//				shared_ptr<Director> dir = GetDirector(director);//GetDirector(director);
//			
//
//				mos.push_back(make_shared<Movie>(name, dir, nullptr, labels, year, Type::Film, inCol, MP4, mp4_size));
//				if (deep)
//					mos.back()->actors_ = this->MovieActs(name); //ActMovies(name);
//
//				mos.back()->distributor_ = GetDistributor(distributor);
//				mos.back()->producer_ = GetProducer(producer);
//				mos.back()->aka = GetMovieAKA(name);
//			}
//			else
//				break;
//		}
//		sqlite3_finalize(statement);
//	}
//	
//
//	return mos;
//}
//
//
//int DATABASE::SqliteDB::InsertMovie(shared_ptr<Movie> movie)
//{
//	sqlite3_stmt* statement;	
//
//	const char* sql = "INSERT INTO MOVIE(nameMovie, director, producer, distributor, year, status, inCollection, type, MP4, size) VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
//	string non = "";
//	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
//	{
//		sqlite3_bind_text(statement, 1, movie->name.c_str(), strlen(movie->name.c_str()), 0);
//		sqlite3_bind_text(statement, 2, movie->director_->name.c_str(), strlen(movie->director_->name.c_str()), 0);
//		if(movie->producer_ != nullptr)
//			sqlite3_bind_text(statement, 3, movie->producer_->name.c_str(), strlen(movie->producer_->name.c_str()), 0);
//		else
//			sqlite3_bind_text(statement, 3, non.c_str(), strlen(non.c_str()), 0);
//		if(movie->distributor_ != nullptr)
//			sqlite3_bind_text(statement, 4, movie->distributor_->name.c_str(), strlen(movie->distributor_->name.c_str()), 0);
//		else
//			sqlite3_bind_text(statement, 4, non.c_str(), strlen(non.c_str()), 0);
//		sqlite3_bind_int(statement, 5, movie->year);
//		sqlite3_bind_int(statement, 6, 0); //Todo find value
//		sqlite3_bind_int(statement, 7, movie->inCollection);
//		sqlite3_bind_int(statement, 8, movie->type);
//		if (movie->MP4)
//		{
//			sqlite3_bind_int(statement, 9, 1);
//			sqlite3_bind_int(statement, 10, movie->MP4_size);
//		}
//		else
//		{
//			sqlite3_bind_int(statement, 9, 0);
//			sqlite3_bind_int(statement, 10, 0);
//		}
//		
//		sqlite3_step(statement);
//	}
//	else
//		return -1;
//	sqlite3_finalize(statement);
//
//	for (string aka : movie->aka)
//		InsertMovieAKA(movie->name, aka);
//	for (shared_ptr<Actor> act : movie->actors_)
//		InsertCommon(movie->name, act->name);
//}
//
//int DATABASE::SqliteDB::UpdateMovie(shared_ptr<Movie> movie)
//{
//	sqlite3_stmt* statement;
//
//	
//	const char* sql = "UPDATE MOVIE SET MP4 = ?, size = ? WHERE nameMovie = ?";
//	
//	
//	string non = "";
//	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
//	{
//		sqlite3_bind_text(statement, 3, movie->name.c_str(), strlen(movie->name.c_str()), 0);
//		if (movie->MP4)
//		{
//			sqlite3_bind_int(statement, 1, 1);
//			sqlite3_bind_int(statement, 2, movie->MP4_size);
//		}
//		else
//		{
//			sqlite3_bind_int(statement, 1, 0);
//			sqlite3_bind_int(statement, 2, 0);
//		}
//
//
//
//		//sqlite3_bind_text(statement, 10, movie->name.c_str(), strlen(movie->name.c_str()), 0);
//		//sqlite3_bind_text(statement, 1, movie->director_->name.c_str(), strlen(movie->director_->name.c_str()), 0);
//		//if (movie->producer_ != nullptr)
//		//	sqlite3_bind_text(statement, 2, movie->producer_->name.c_str(), strlen(movie->producer_->name.c_str()), 0);
//		//else
//		//	sqlite3_bind_text(statement, 2, non.c_str(), strlen(non.c_str()), 0);
//		//if (movie->distributor_ != nullptr)
//		//	sqlite3_bind_text(statement, 3, movie->distributor_->name.c_str(), strlen(movie->distributor_->name.c_str()), 0);
//		//else
//		//	sqlite3_bind_text(statement, 3, non.c_str(), strlen(non.c_str()), 0);
//		//sqlite3_bind_int(statement, 4, movie->year);
//		//sqlite3_bind_int(statement, 5, 0); //Todo find value
//		//sqlite3_bind_int(statement, 6, movie->inCollection);
//		//sqlite3_bind_int(statement, 7, movie->type);
//		//if (movie->MP4)
//		//{
//		//	sqlite3_bind_int(statement, 8, 1);
//		//	sqlite3_bind_int(statement, 9, movie->MP4_size);
//		//}
//		//else
//		//{
//		//	sqlite3_bind_int(statement, 8, 0);
//		//	sqlite3_bind_int(statement, 9, 0);
//		//}
//		
//		sqlite3_step(statement);
//	}
//	else
//		return -1;
//	sqlite3_finalize(statement);
//}
//
//
//
//int DATABASE::SqliteDB::UpdateMovie2(shared_ptr<Movie> movie)
//{
//	sqlite3_stmt* statement;
//	
//	const char* sql = "UPDATE MOVIE SET director = ?, producer = ?, distributor = ?, year = ?, status = ?, inCollection = ?, type = ?, MP4 = ?, size = ? WHERE nameMovie = ?";
//	   
//	int inCol = 2;
//	switch (movie->inCollection)
//	{
//	case InCollection::NotInCollection:
//		inCol = 2;
//		break;
//	case InCollection::DVD:
//		inCol = 0;
//		break;
//	case InCollection::Download:
//		inCol = 1;
//		break;
//	default:
//		break;
//	}
//	
//	string non = "";
//	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
//	{
//		sqlite3_bind_text(statement, 10, movie->name.c_str(), strlen(movie->name.c_str()), 0);
//		
//		sqlite3_bind_text(statement, 1, movie->director_->name.c_str(), strlen(movie->director_->name.c_str()), 0);
//
//		if (movie->producer_ != nullptr)
//			sqlite3_bind_text(statement, 2, movie->producer_->name.c_str(), strlen(movie->producer_->name.c_str()), 0);
//		else
//			sqlite3_bind_text(statement, 2, non.c_str(), strlen(non.c_str()), 0);
//
//		if (movie->distributor_ != nullptr)
//			sqlite3_bind_text(statement, 3, movie->distributor_->name.c_str(), strlen(movie->distributor_->name.c_str()), 0);
//		else
//			sqlite3_bind_text(statement, 3, non.c_str(), strlen(non.c_str()), 0);
//
//		sqlite3_bind_int(statement, 4, movie->year);
//		sqlite3_bind_int(statement, 5, 0); //Todo find value
//
//		sqlite3_bind_int(statement, 6, inCol);
//		sqlite3_bind_int(statement, 7, movie->type);
//		if (movie->MP4)
//		{
//			sqlite3_bind_int(statement, 8, 1);
//			sqlite3_bind_int(statement, 9, movie->MP4_size);
//		}
//		else
//		{
//			sqlite3_bind_int(statement, 8, 0);
//			sqlite3_bind_int(statement, 9, 0);
//		}
//
//		sqlite3_step(statement);
//	}
//	else
//		return -1;
//	sqlite3_finalize(statement);
//
//	DeleteMovieAKA(movie->name);
//	for (string aka : movie->aka)
//		InsertMovieAKA(movie->name, aka);
//	DeleteCommon(movie->name);
//	for (shared_ptr<Actor> act : movie->actors_)
//		InsertCommon(movie->name, act->name);
//	
//}
//
//
//
//int DATABASE::SqliteDB::UpdateMovie3(shared_ptr<Movie> movie)
//{
//	sqlite3_stmt* statement;
//
//	const char* sql = "UPDATE MOVIE SET director = ?, year = ? WHERE nameMovie = ?";
//	//const char* sql = "UPDATE MOVIE SET director = ?, producer = ?, distributor = ?, year = ? WHERE nameMovie = ?";
//
//	string non = "";
//	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
//	{
//		sqlite3_bind_text(statement, 3, movie->name.c_str(), strlen(movie->name.c_str()), 0);
//		sqlite3_bind_text(statement, 1, movie->director_->name.c_str(), strlen(movie->director_->name.c_str()), 0);
//		/*sqlite3_bind_text(statement, 2, prod.c_str(), strlen(prod.c_str()), 0);
//		sqlite3_bind_text(statement, 3, dist.c_str(), strlen(dist.c_str()), 0);*/
//		sqlite3_bind_int(statement, 2, movie->year);
//
//		sqlite3_step(statement);
//	}
//	else
//		return -1;
//	sqlite3_finalize(statement);
//}
//
//
//
//int DATABASE::SqliteDB::DeleteMovie(shared_ptr<Movie> movie)
//{
//	DeleteCommon(movie->name);
//	DeleteMoviePicture(movie->name);
//	DeleteMovieAKA(movie->name);
//
//	sqlite3_stmt* statement;
//	const char* sql = "DELETE FROM Movie WHERE nameMovie = ?";
//
//	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
//	{
//		sqlite3_bind_text(statement, 1, movie->name.c_str(), strlen(movie->name.c_str()), 0);
//		int cols = sqlite3_column_count(statement);
//		int result = 0;
//		result = sqlite3_step(statement);
//
//		sqlite3_finalize(statement);
//	}
//	else
//		return -1;
//
//	return 0;
//}
//
//
////
////vector<string> DATABASE::SqliteDB::SelectFromCommonTable(string name, int col)
////{
////	vector<string> results;
////	
////	sqlite3_stmt* statement;
////
////	const char* sql = "SELECT * FROM COMMON WHERE name = ?";
////	
////
////	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
////	{
////		sqlite3_bind_text(statement, 1, name.c_str(), strlen(name.c_str()), 0);
////
////		int cols = sqlite3_column_count(statement);
////		int result = 0;
////		while (true)
////		{
////			result = sqlite3_step(statement);
////
////			if (result == SQLITE_ROW)
////			{
////				results.push_back((char*)sqlite3_column_text(statement, col));
////			}
////			else
////				break;
////		}
////		sqlite3_finalize(statement);
////	}
////
////
////	return results;
////}
//
//
//vector<shared_ptr<Movie>> DATABASE::SqliteDB::ActMovies(string name)
//{
//	vector<shared_ptr<Movie>> movies;
//	vector<string> results;
//
//	sqlite3_stmt* statement;
//	const char* sql = "SELECT * FROM COMMON WHERE name = ?";
//
//
//	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
//	{
//		sqlite3_bind_text(statement, 1, name.c_str(), strlen(name.c_str()), 0);
//
//		int cols = sqlite3_column_count(statement);
//		int result = 0;
//		while (true)
//		{
//			result = sqlite3_step(statement);
//
//			if (result == SQLITE_ROW)
//			{
//				results.push_back((char*)sqlite3_column_text(statement, 0));
//			}
//			else
//				break;
//		}
//		sqlite3_finalize(statement);
//	}
//		
//
//	for (string& moName : results)
//		movies.push_back(GetMovie(moName));
//
//	return movies;
//}
//
//
//vector<shared_ptr<Movie>> DATABASE::SqliteDB::DirectorMovies(string name)
//{
//	vector<shared_ptr<Movie>> movies;
//	vector<string> results;
//
//	sqlite3_stmt* statement;
//	const char* sql = "SELECT * FROM MOVIE WHERE director = ?";
//
//
//	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
//	{
//		sqlite3_bind_text(statement, 1, name.c_str(), strlen(name.c_str()), 0);
//
//		int cols = sqlite3_column_count(statement);
//		int result = 0;
//		while (true)
//		{
//			result = sqlite3_step(statement);
//
//			if (result == SQLITE_ROW)
//			{
//				results.push_back((char*)sqlite3_column_text(statement, 0));
//			}
//			else
//				break;
//		}
//		sqlite3_finalize(statement);
//	}
//
//
//	for (string& moName : results)
//		movies.push_back(GetMovie(moName));
//
//	return movies;
//}
//
//
//vector<string> DATABASE::SqliteDB::GetActorAKA(string name)
//{
//	vector<string> results;
//
//	sqlite3_stmt* statement;
//	const char* sql = "SELECT * FROM ACTORaka WHERE name = ?";
//
//	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
//	{
//		sqlite3_bind_text(statement, 1, name.c_str(), strlen(name.c_str()), 0);
//
//		int cols = sqlite3_column_count(statement);
//		int result = 0;
//		while (true)
//		{
//			result = sqlite3_step(statement);
//
//			if (result == SQLITE_ROW)
//			{
//				results.push_back((char*)sqlite3_column_text(statement, 1));
//			}
//			else
//				break;
//		}
//		sqlite3_finalize(statement);
//	}
//
//	return results;
//}
//
//
//
//vector<string> DATABASE::SqliteDB::GetDirectorAKA(string name)
//{
//	vector<string> results;
//
//	sqlite3_stmt* statement;
//	const char* sql = "SELECT * FROM DIRECTORaka WHERE name = ?";
//
//	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
//	{
//		sqlite3_bind_text(statement, 1, name.c_str(), strlen(name.c_str()), 0);
//
//		int cols = sqlite3_column_count(statement);
//		int result = 0;
//		while (true)
//		{
//			result = sqlite3_step(statement);
//
//			if (result == SQLITE_ROW)
//			{
//				results.push_back((char*)sqlite3_column_text(statement, 1));
//			}
//			else
//				break;
//		}
//		sqlite3_finalize(statement);
//	}
//
//	return results;
//}
//
//
//vector<string> DATABASE::SqliteDB::GetMovieAKA(string name)
//{
//	vector<string> results;
//
//	sqlite3_stmt* statement;
//	const char* sql = "SELECT * FROM MOVIEaka WHERE nameMovie = ?";
//
//
//	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
//	{
//		sqlite3_bind_text(statement, 1, name.c_str(), strlen(name.c_str()), 0);
//
//		int cols = sqlite3_column_count(statement);
//		int result = 0;
//		while (true)
//		{
//			result = sqlite3_step(statement);
//
//			if (result == SQLITE_ROW)
//			{
//				results.push_back((char*)sqlite3_column_text(statement, 1));
//			}
//			else
//				break;
//		}
//		sqlite3_finalize(statement);
//	}
//
//	return results;
//}
//
//
//int DATABASE::SqliteDB::InsertActorAKA(string name, string aka)
//{
//	sqlite3_stmt* statement;
//	const char* sql = "INSERT INTO ACTORaka(aka, name) VALUES(?, ?)";
//
//	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
//	{
//		sqlite3_bind_text(statement, 1, aka.c_str(), strlen(aka.c_str()), 0);
//		sqlite3_bind_text(statement, 2, name.c_str(), strlen(name.c_str()), 0);
//		sqlite3_step(statement);
//	}
//	else
//		return -1;
//	sqlite3_finalize(statement);
//}
//
//
//int DATABASE::SqliteDB::InsertMovieAKA(string nameMovie, string aka)
//{
//	sqlite3_stmt* statement;
//	const char* sql = "INSERT INTO MOVIEaka(aka, nameMovie) VALUES(?, ?)";
//
//	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
//	{
//		sqlite3_bind_text(statement, 1, aka.c_str(), strlen(aka.c_str()), 0);
//		sqlite3_bind_text(statement, 2, nameMovie.c_str(), strlen(nameMovie.c_str()), 0);		
//		sqlite3_step(statement);
//	}
//	else
//		return -1;
//	sqlite3_finalize(statement);
//}
//
//
//int DATABASE::SqliteDB::DeleteMovieAKA(string name)
//{
//	sqlite3_stmt* statement;
//	
//	const char* sql = "DELETE FROM MOVIEaka WHERE nameMovie = ?";	
//
//	string non = "";
//	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
//	{
//		sqlite3_bind_text(statement, 1, name.c_str(), strlen(name.c_str()), 0);		
//
//		sqlite3_step(statement);
//	}
//	else
//
//		return -1;
//	sqlite3_finalize(statement);
//}
//
//
//
//int DATABASE::SqliteDB::DeleteActorAKA(string name)
//{
//	sqlite3_stmt* statement;
//
//	const char* sql = "DELETE FROM ACTORaka WHERE name = ?";
//
//	string non = "";
//	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
//	{
//		sqlite3_bind_text(statement, 1, name.c_str(), strlen(name.c_str()), 0);
//
//		sqlite3_step(statement);
//	}
//	else
//
//		return -1;
//	sqlite3_finalize(statement);
//}
//
//
//int DATABASE::SqliteDB::InsertDirectorAKA(string name, string aka)
//{
//	sqlite3_stmt* statement;
//	const char* sql = "INSERT INTO DIRECTORaka(aka, name) VALUES(?, ?)";
//
//	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
//	{
//		sqlite3_bind_text(statement, 1, aka.c_str(), strlen(aka.c_str()), 0);
//		sqlite3_bind_text(statement, 2, name.c_str(), strlen(name.c_str()), 0);
//		sqlite3_step(statement);
//	}
//	else
//		return -1;
//	sqlite3_finalize(statement);
//}
//
//
//int DATABASE::SqliteDB::InsertCommon(string nameMovie, string nameActor)
//{
//	sqlite3_stmt* statement;
//	const char* sql = "INSERT INTO COMMON(nameMovie, name) VALUES(?, ?)";
//	
//	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
//	{
//		sqlite3_bind_text(statement, 1, nameMovie.c_str(), strlen(nameMovie.c_str()), 0);
//		sqlite3_bind_text(statement, 2, nameActor.c_str(), strlen(nameActor.c_str()), 0);
//		sqlite3_step(statement);
//	}
//	else
//		return -1;
//	sqlite3_finalize(statement);
//}
//
//
//
//
//vector<shared_ptr<Actor>> DATABASE::SqliteDB::MovieActs(string name)
//{
//	vector<shared_ptr<Actor>> actors;
//	vector<string> results;
//
//	sqlite3_stmt* statement;
//	const char* sql = "SELECT * FROM COMMON WHERE nameMovie = ?";
//
//
//	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
//	{
//		sqlite3_bind_text(statement, 1, name.c_str(), strlen(name.c_str()), 0);
//
//		int cols = sqlite3_column_count(statement);
//		int result = 0;
//		while (true)
//		{
//			result = sqlite3_step(statement);
//
//			if (result == SQLITE_ROW)
//			{
//				results.push_back((char*)sqlite3_column_text(statement, 1));
//			}
//			else
//				break;
//		}
//		sqlite3_finalize(statement);
//	}
//
//	for (string& actName : results)
//		actors.push_back(GetActor(actName));
//
//	return actors;
//}
//
//
//
//
//int DATABASE::SqliteDB::DeleteCommon(string name)
//{
//	sqlite3_stmt* statement;
//
//	const char* sql = "DELETE FROM COMMON WHERE nameMovie = ?";
//
//	string non = "";
//	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
//	{
//		sqlite3_bind_text(statement, 1, name.c_str(), strlen(name.c_str()), 0);
//
//		sqlite3_step(statement);
//	}
//	else
//
//		return -1;
//	sqlite3_finalize(statement);
//}
//
//
//vector<shared_ptr<Actor>> DATABASE::SqliteDB::SUS_Acts(int no)
//{
//	vector<shared_ptr<Actor>> actors;
//	vector<string> results;
//
//	sqlite3_stmt* statement;
//	const char* sql = "SELECT * FROM COMMON WHERE noSUS = ?";
//	string No = to_string(no);
//
//	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
//	{
//		sqlite3_bind_text(statement, 1, No.c_str(), strlen(No.c_str()), 0);
//
//		int cols = sqlite3_column_count(statement);
//		int result = 0;
//		while (true)
//		{
//			result = sqlite3_step(statement);
//
//			if (result == SQLITE_ROW)
//			{
//				results.push_back((char*)sqlite3_column_text(statement, 2));
//			}
//			else
//				break;
//		}
//		sqlite3_finalize(statement);
//	}
//
//	for (string& actName : results)
//		actors.push_back(GetActor(actName));
//
//	return actors;
//}
//
//
//vector<shared_ptr<SUS>> DATABASE::SqliteDB::ActorSUS(string name)
//{
//	vector<shared_ptr<SUS>> suss;
//	vector<int> results;
//
//	sqlite3_stmt* statement;
//	const char* sql = "SELECT * FROM SUScom WHERE name = ?";	
//
//	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
//	{
//		sqlite3_bind_text(statement, 1, name.c_str(), strlen(name.c_str()), 0);
//
//		int cols = sqlite3_column_count(statement);
//		int result = 0;
//		while (true)
//		{
//			result = sqlite3_step(statement);
//
//			if (result == SQLITE_ROW)
//			{
//				results.push_back(sqlite3_column_int(statement, 1));				
//			}
//			else
//				break;
//		}
//		sqlite3_finalize(statement);
//	}
//
//	for (int& susNo : results)
//		suss.push_back(GetSUS(susNo));
//
//	return suss;
//}
//
//void DATABASE::SqliteDB::InsertPicture(int index, string name, char* bytes, unsigned int size)
//{
//	sqlite3_stmt* statement;
//	const char* sql = "INSERT INTO PICS(name, size, pict) VALUES(?, ?, ?)";
//
//
//	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
//	{
//		sqlite3_bind_text(statement, 1, name.c_str(), strlen(name.c_str()), 0);
//		sqlite3_bind_int(statement, 2, size);
//		sqlite3_bind_blob(statement, 3, bytes, size, SQLITE_STATIC);
//
//		sqlite3_step(statement);		
//		sqlite3_finalize(statement);
//	}
//}
//
////db.Quary("CREATE TABLE ActPic (a INTEGER AUTO_INCREMENT PRIMARY KEY, name TEXT  NOT NULL REFERENCES ACTOR(name), size INTEGER, pict BLOB)");
//void DATABASE::SqliteDB::InsertPicture(int index, string sqls, string name, char* bytes, unsigned int size)
//{
//	sqlite3_stmt* statement;
//	//const char* sql = nullptr;// "INSERT INTO PICS(name, size, pict) VALUES(?, ?, ?)";
//	//"INSERT INTO ActPic(name, size, pict) VALUES(?, ?, ?)";
//	const char* sql = sqls.c_str();
//	//delete sql;
//
//	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
//	{
//		sqlite3_bind_int(statement, 1, index);
//		sqlite3_bind_text(statement, 2, name.c_str(), strlen(name.c_str()), 0);
//		sqlite3_bind_int(statement, 3, size);
//		sqlite3_bind_blob(statement, 4, bytes, size, SQLITE_STATIC);
//		sqlite3_step(statement);
//		sqlite3_finalize(statement);
//	}
//	/*else
//		return -1;*/
//}
//
////db.Quary("CREATE TABLE ActPic (a INTEGER AUTO_INCREMENT PRIMARY KEY, name TEXT  NOT NULL REFERENCES ACTOR(name), size INTEGER, pict BLOB)");
//void DATABASE::SqliteDB::InsertPicture(string sqls, string name, char* bytes, unsigned int size)
//{
//	sqlite3_stmt* statement;
//	//const char* sql = nullptr;// "INSERT INTO PICS(name, size, pict) VALUES(?, ?, ?)";
//	//"INSERT INTO ActPic(name, size, pict) VALUES(?, ?, ?)";
//	const char* sql = sqls.c_str();
//	//delete sql;
//
//	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
//	{
//		//sqlite3_bind_int(statement, 1, index);
//		sqlite3_bind_text(statement, 1, name.c_str(), strlen(name.c_str()), 0);
//		sqlite3_bind_int(statement, 2, size);
//		sqlite3_bind_blob(statement, 3, bytes, size, SQLITE_STATIC);
//		sqlite3_step(statement);
//		sqlite3_finalize(statement);
//	}
//	/*else
//		return -1;*/
//}
//
//
//
//
//vector<char> DATABASE::SqliteDB::GetPicture(string name)
//{
//	//char* bytes = nullptr;
//	vector<char> resO;
//
//	sqlite3_stmt* statement;
//	const char* sql = "SELECT * FROM PICS WHERE name = ?";
//
//	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
//	{
//		sqlite3_bind_text(statement, 1, name.c_str(), strlen(name.c_str()), 0);
//
//		int cols = sqlite3_column_count(statement);
//		int result = 0;
//		while (true)
//		{
//			result = sqlite3_step(statement);
//
//			if (result == SQLITE_ROW)
//			{
//				//bytes = (char*)sqlite3_column_text(statement, 1);
//				int size = sqlite3_column_int(statement, 1);
//				char* p = (char*)sqlite3_column_blob(statement, 2);
//				vector<char> res(p, p + size);
//				resO = res;
//			}
//			else
//				break;
//		}
//		sqlite3_finalize(statement);
//	}
//
//
//	return resO;
//}
//
//
//pair<char*, int> DATABASE::SqliteDB::GetPicture2(string name)
//{
//	char* bytes = nullptr;
//	pair<char*, int> resO;
//	//vector<char> resO;
//
//	sqlite3_stmt* statement;
//	const char* sql = "SELECT * FROM PICS WHERE name = ?";
//
//	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
//	{
//		sqlite3_bind_text(statement, 1, name.c_str(), strlen(name.c_str()), 0);
//
//		int cols = sqlite3_column_count(statement);
//		int result = 0;
//		while (true)
//		{
//			result = sqlite3_step(statement);
//
//			if (result == SQLITE_ROW)
//			{
//				//bytes = (char*)sqlite3_column_text(statement, 1);
//				int size = sqlite3_column_int(statement, 1);
//				char* p = (char*)sqlite3_column_blob(statement, 2);
//				//vector<char> res(p, p + size);
//				//resO = res;
//				resO = make_pair(p, size);
//			}
//			else
//				break;
//		}
//		sqlite3_finalize(statement);
//	}
//
//
//	return resO;
//}
//
//
//vector<char> DATABASE::SqliteDB::GetActPicture(string name)
//{
//	vector<char> res;
//
//	sqlite3_stmt* statement;
//	const char* sql = "SELECT * FROM ActPic WHERE name = ?";
//
//	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
//	{
//		sqlite3_bind_text(statement, 1, name.c_str(), strlen(name.c_str()), 0);
//
//		int cols = sqlite3_column_count(statement);
//		int result = 0;
//		while (true)
//		{
//			result = sqlite3_step(statement);
//
//			if (result == SQLITE_ROW)
//			{
//				//bytes = (char*)sqlite3_column_text(statement, 1);
//				int size = sqlite3_column_int(statement, 2);
//				char* p = (char*)sqlite3_column_blob(statement, 3);
//				vector<char> res1(p, p + size);
//				res = res1;
//			}
//			else
//				break;
//			break;//Fetch only first picture
//		}
//		sqlite3_finalize(statement);
//	}
//
//	return res;
//}
//
//
//
//vector<vector<char>> DATABASE::SqliteDB::GetActPictures(string name)
//{
//	vector<vector<char>> res;
//
//	sqlite3_stmt* statement;
//	const char* sql = "SELECT * FROM ActPic WHERE name = ?";
//
//	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
//	{
//		sqlite3_bind_text(statement, 1, name.c_str(), strlen(name.c_str()), 0);
//
//		int cols = sqlite3_column_count(statement);
//		int result = 0;
//		while (true)
//		{
//			result = sqlite3_step(statement);
//
//			if (result == SQLITE_ROW)
//			{
//				//bytes = (char*)sqlite3_column_text(statement, 1);
//				int size = sqlite3_column_int(statement, 2);
//				char* p = (char*)sqlite3_column_blob(statement, 3);
//				vector<char> res1(p, p + size);
//				res.push_back(res1);
//			}
//			else
//				break;
//		}
//		sqlite3_finalize(statement);
//	}
//
//	return res;
//}
//
//
//int DATABASE::SqliteDB::DeleteActorPicture(string name)
//{
//	sqlite3_stmt* statement;
//	const char* sql = "DELETE FROM ActPic WHERE name = ?";	
//	
//	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
//	{
//		sqlite3_bind_text(statement, 1, name.c_str(), strlen(name.c_str()), 0);
//		int cols = sqlite3_column_count(statement);
//		int result = 0;
//		/*while (true)
//		{*/
//			result = sqlite3_step(statement);
//
//		/*	if (result == SQLITE_ROW)
//			{				
//			}
//			else
//				break;
//		}*/
//		sqlite3_finalize(statement);
//	}
//	else
//		return -1;
//
//	return 0;
//}
//
//
//
//vector<vector<char>> DATABASE::SqliteDB::GetMoviePictures(string name)
//{
//	//char* bytes = nullptr;
//	vector<vector<char>> res;
//
//	sqlite3_stmt* statement;
//	const char* sql = "SELECT * FROM MoviePic WHERE name = ?";
//
//	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
//	{
//		sqlite3_bind_text(statement, 1, name.c_str(), strlen(name.c_str()), 0);
//
//		int cols = sqlite3_column_count(statement);
//		int result = 0;
//		while (true)
//		{
//			result = sqlite3_step(statement);
//
//			if (result == SQLITE_ROW)
//			{
//				//bytes = (char*)sqlite3_column_text(statement, 1);
//				int size = sqlite3_column_int(statement, 2);
//				char* p = (char*)sqlite3_column_blob(statement, 3);
//				vector<char> res1(p, p + size);
//				res.push_back(res1);
//			}
//			else
//				break;
//		}
//		sqlite3_finalize(statement);
//	}
//
//	return res;
//}
//
//int DATABASE::SqliteDB::InsertMoviePicture(string name, string path)
//{
//	FILE* fp = fopen(path.c_str(), "rb");
//	if (fp)
//	{
//		char* buffer;
//
//		fseek(fp, 0, SEEK_END);
//		unsigned int imageLen = ftell(fp);
//		fseek(fp, 0, SEEK_SET);
//
//		buffer = new char[imageLen + 1];
//
//		fread(buffer, 1, imageLen, fp);
//
//		fclose(fp);
//
//		/*const char* sql = "INSERT INTO MoviePic(a, name, size, pict) VALUES(?, ?, ?, ?)";
//		InsertPicture(1000, sql, name, buffer, imageLen + 1);*/
//		const char* sql = "INSERT INTO MoviePic(name, size, pict) VALUES(?, ?, ?)";
//		InsertPicture(sql, name, buffer, imageLen + 1);
//
//
//		delete[] buffer;
//
//		return 0;
//	}
//	else
//		return -1;
//	
//}
//
//
//int DATABASE::SqliteDB::DeleteMoviePicture(string name)
//{
//	sqlite3_stmt* statement;
//	const char* sql = "DELETE FROM MoviePic WHERE name = ?";
//
//	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
//	{
//		sqlite3_bind_text(statement, 1, name.c_str(), strlen(name.c_str()), 0);
//		int cols = sqlite3_column_count(statement);
//		
//		sqlite3_step(statement);
//
//		
//		sqlite3_finalize(statement);
//	}
//	else
//		return -1;
//
//	return 0;
//}
//
//
//int DATABASE::SqliteDB::InsertActorPicture(string name, string path)
//{
//	FILE* fp = fopen(path.c_str(), "rb");
//	if (fp)
//	{
//		char* buffer;
//
//		fseek(fp, 0, SEEK_END);
//		unsigned int imageLen = ftell(fp);
//		fseek(fp, 0, SEEK_SET);
//
//		buffer = new char[imageLen + 1];
//
//		fread(buffer, 1, imageLen, fp);
//
//		fclose(fp);
//
//		const char* sql = "INSERT INTO ActPic(name, size, pict) VALUES(?, ?, ?)";
//		InsertPicture(sql, name, buffer, imageLen + 1);
//
//		delete[] buffer;
//
//		return 0;
//	}
//	else
//		return -1;
//
//}
//
//
//int DATABASE::SqliteDB::InsertSUS_Pircture(string susName, string path)
//{
//	FILE* fp = fopen(path.c_str(), "rb");
//	if (fp)
//	{
//		char* buffer;
//
//		fseek(fp, 0, SEEK_END);
//		unsigned int imageLen = ftell(fp);
//		fseek(fp, 0, SEEK_SET);
//
//		buffer = new char[imageLen + 1];
//
//		fread(buffer, 1, imageLen, fp);
//
//		fclose(fp);
//
//		const char* sql = "INSERT INTO SUSPic(name, size, pict) VALUES(?, ?, ?)";
//		InsertPicture(sql, susName, buffer, imageLen + 1);
//
//		delete[] buffer;
//
//		return 0;
//	}
//	else
//		return -1;
//}
//
//
//shared_ptr<SUS> DATABASE::SqliteDB::GetSUS(int susNo, bool deep)
//{
//	shared_ptr<SUS> sus = nullptr;
//	string susNo_ = to_string(susNo);
//
//	sqlite3_stmt* statement;
//	const char* sql = "SELECT * FROM SUS WHERE a = ?";
//	
//
//	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
//	{
//		sqlite3_bind_text(statement, 1, susNo_.c_str(), strlen(susNo_.c_str()), 0);
//		int cols = sqlite3_column_count(statement);
//		int result = 0;
//		while (true)
//		{
//			result = sqlite3_step(statement);
//
//			if (result == SQLITE_ROW)
//			{		
//				sus = make_shared<SUS>();
//				sus->no = sqlite3_column_int(statement, 1);
//				sus->year = sqlite3_column_int(statement, 2);
//				sus->month = sqlite3_column_int(statement, 3);
//				sus->inCollection = sqlite3_column_int(statement, 4);	
//				sus->format = sqlite3_column_int(statement, 5);
//			}
//			else
//				break;
//
//			if (deep)
//				sus->actors = SUS_Acts(susNo);				
//		}
//		sqlite3_finalize(statement);
//		
//	}
//
//	return sus;
//}
//
//int DATABASE::SqliteDB::InsertSUS(shared_ptr<SUS> sus)
//{
//	sqlite3_stmt* statement;
//	const char* sql = "INSERT INTO SUS(a, year, month, incollection, format) VALUES(?, ?, ?, ?, ?)";
//	
//	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
//	{
//		sqlite3_bind_int(statement, 1, sus->no);
//		sqlite3_bind_int(statement, 2, sus->year);
//		sqlite3_bind_int(statement, 3, sus->month);
//		sqlite3_bind_int(statement, 4, sus->inCollection);
//		sqlite3_bind_int(statement, 5, sus->format);
//
//		sqlite3_step(statement);
//	}
//	else
//		return -1;
//	sqlite3_finalize(statement);
//
//	return 0;
//}
//
//
//int DATABASE::SqliteDB::InsertActToSUS(string actName, int susNo)
//{
//	sqlite3_stmt* statement;
//	const char* sql = "INSERT INTO SUScom(a, name) VALUES(?, ?)";
//
//	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
//	{
//		sqlite3_bind_int(statement, 1, susNo);
//		sqlite3_bind_text(statement, 2, actName.c_str(), strlen(actName.c_str()), 0);		
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
//int DATABASE::SqliteDB::InsertProducer(shared_ptr<Producer> prod)
//{
//	sqlite3_stmt* statement;
//	const char* sql = "INSERT INTO PRODUCERS(name) VALUES(?)";
//
//	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
//	{
//		sqlite3_bind_text(statement, 1, prod->name.c_str(), strlen(prod->name.c_str()), 0);
//		sqlite3_step(statement);
//	}
//	else
//		return -1;
//	sqlite3_finalize(statement);
//}
//
//
//shared_ptr<Producer> DATABASE::SqliteDB::GetProducer(string name)
//{
//	shared_ptr<Producer> producer = nullptr;
//	sqlite3_stmt* statement;
//	const char* sql = "SELECT * FROM PRODUCERS WHERE name = ?";
//
//	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
//	{
//		sqlite3_bind_text(statement, 1, name.c_str(), strlen(name.c_str()), 0);
//		int cols = sqlite3_column_count(statement);
//		int result = 0;
//		while (true)
//		{
//			result = sqlite3_step(statement);
//
//			if (result == SQLITE_ROW)
//			{
//				producer = make_shared<Producer>(name);
//			}
//			else
//				break;
//		}
//		sqlite3_finalize(statement);
//	}
//	
//	return producer;
//}
//
//
//
//int DATABASE::SqliteDB::InsertDistributor(shared_ptr<Distributor> dist)
//{
//	sqlite3_stmt* statement;
//	const char* sql = "INSERT INTO DISTRIBUTORS(name) VALUES(?)";
//
//	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
//	{
//		sqlite3_bind_text(statement, 1, dist->name.c_str(), strlen(dist->name.c_str()), 0);
//		sqlite3_step(statement);
//	}
//	else
//		return -1;
//	sqlite3_finalize(statement);
//}
//
//
//shared_ptr<Distributor> DATABASE::SqliteDB::GetDistributor(string name)
//{
//	shared_ptr<Distributor> distributor = nullptr;
//	sqlite3_stmt* statement;
//	const char* sql = "SELECT * FROM DISTRIBUTORS WHERE name = ?";
//
//	if (sqlite3_prepare_v2(database, sql, -1, &statement, 0) == SQLITE_OK)
//	{
//		sqlite3_bind_text(statement, 1, name.c_str(), strlen(name.c_str()), 0);
//		int cols = sqlite3_column_count(statement);
//		int result = 0;
//		while (true)
//		{
//			result = sqlite3_step(statement);
//
//			if (result == SQLITE_ROW)
//			{
//				distributor = make_shared<Distributor>(name);
//			}
//			else
//				break;
//		}
//		sqlite3_finalize(statement);
//	}
//
//	return distributor;
//}