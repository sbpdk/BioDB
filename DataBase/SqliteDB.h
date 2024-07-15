#pragma once
#include <memory>
#include <string>
#include <sstream>
#include <vector>


using namespace std;

//class Actor;
//class Movie;
//class Director;
//class SUS;
//class Interface;
//class Distributor;
//class Producer;
class sqlite3;

namespace PLANT
{
	class BiomassPipeRun;
}


namespace CIRCUIT
{
	class BioHex;
	class BioPump;
	class BioFlowMeter;
	class PipeRunBiomass;
	class BiomassCmp;
}


namespace DATABASE
{
	class SqliteDB
	{
	public:		
		SqliteDB(const char* name);
		~SqliteDB();

		int InsertProject(string name) const;

		int InsertPipeRun(std::string projectName, shared_ptr<PLANT::BiomassPipeRun> bioPR) const;
		vector<shared_ptr<PLANT::BiomassPipeRun>> GetBiomassPipeRuns(string project) const;
		vector<pair<string, string>> GetPipeRunNames(string projectName);
		vector<string> GetRuns();


		int InsertRor(string pk, string type, int Dim, double Dia, double s) const;
		pair<string, int> GetRor(string pk) const;
		pair<int, double> GetPK_Ror(string type, int Dim) const;
		pair<int, double> GetPK_Ror_(int pk) const;
		
		//int InsertBioComponent(string pk, string tag, string type, string function, string PipeRun, string inletPipe, string outletPipe, double length, int elbow90, int elbow45, string ror) const; //Virker ikke
		//int InsertBioComponent(shared_ptr<CIRCUIT::BiomassCmp> cmp, string project, string pipeRun); //Virker ikke
		int InsertBioCmp(shared_ptr<CIRCUIT::BiomassCmp> cmp, string project, string pipeRun);
		shared_ptr<CIRCUIT::BiomassCmp> GetBioCmps(string bioPipeRun) const;
		vector<shared_ptr<CIRCUIT::BiomassCmp>> GetBioCmps2(string bioPipeRun) const;
		int UpdateBioCmpRef(string project, shared_ptr<CIRCUIT::BiomassCmp> pipe, shared_ptr<CIRCUIT::BiomassCmp> inlet, shared_ptr<CIRCUIT::BiomassCmp> outlet) const;


		/*shared_ptr<PLANT::BiomassPipeRun> GetPipeRunComponents(int key);
		vector<shared_ptr<CIRCUIT::BiomassCmp>> GetBiomassCmp(int biomassPipeRunID);*/

		//vector<string> GetActorList() const;		
		//vector<string> GetMovieList() const;
		//vector<string> GetDirectorList() const;

		//shared_ptr<Actor> GetActor(string name, bool deep = false);
		//int InsertActor(shared_ptr<Actor> actor);
		//int UpdateActor(shared_ptr<Actor> actor);
		//int DeleteActor(shared_ptr<Actor> actor);

		//shared_ptr<Director> GetDirector(string name, bool deep = false);		
		//int InsertDirector(shared_ptr<Director> director);
		//vector<string> GetDirectorAKA(string name);
		//int InsertDirectorAKA(string name, string aka);

		///*vector<string> GetActorsMovies(string name);*/
		//vector<shared_ptr<Movie>> GetMovies(bool deep = false);
		//shared_ptr<Movie> GetMovie(string name, bool deep = false);
		//int InsertMovie(shared_ptr<Movie> movie);
		//int UpdateMovie(shared_ptr<Movie> movie);
		//int UpdateMovie2(shared_ptr<Movie> movie);
		//int UpdateMovie3(shared_ptr<Movie> movie);
		//int DeleteMovie(shared_ptr<Movie> movie);

		////vector<string> SelectFromCommonTable(string selectCommand, int col);
		//vector<shared_ptr<Movie>> ActMovies(string name);
		//vector<shared_ptr<Actor>> MovieActs(string name);
		//vector<shared_ptr<Actor>> SUS_Acts(int no);
		//vector<shared_ptr<SUS>> ActorSUS(string name);

		//vector<shared_ptr<Movie>> DirectorMovies(string name);
		//
		//vector<string> GetMovieAKA(string name);
		//int InsertMovieAKA(string name, string aka);
		//int DeleteMovieAKA(string name);

		//vector<string> GetActorAKA(string name);
		//int InsertActorAKA(string name, string aka);
		//int DeleteActorAKA(string name);

		//int InsertCommon(string nameMovie, string nameActor);
		//int DeleteCommon(string nameMovie);

		//shared_ptr<SUS> GetSUS(int susNo, bool deep = false);
		//int InsertSUS(shared_ptr<SUS> sus);
		//int InsertActToSUS(string actName, int susNo);
	
		////int InsertCOLOR(shared_ptr<COLOR> sus);

		//void InsertPicture(int index, string name, char* bytes, unsigned int size);
		//void InsertPicture(int index, string sqls, string name, char* bytes, unsigned int size);
		//void InsertPicture(string sqls, string name, char* bytes, unsigned int size);
		//vector<char> GetPicture(string name);
		//pair<char*, int> GetPicture2(string name);

		//vector<char> GetActPicture(string name);
		//vector<vector<char>> GetActPictures(string name);
		//vector<vector<char>> GetMoviePictures(string name);
		//int DeleteMoviePicture(string movieName);
		//
		//int InsertMoviePicture(string movieName, string path);
		//int InsertActorPicture(string actorName, string path);
		//int InsertSUS_Pircture(string susName, string path);
		//int DeleteActorPicture(string actorName);

		//shared_ptr<Producer> GetProducer(string name);
		//int InsertProducer(shared_ptr<Producer> prod);
		//shared_ptr<Distributor> GetDistributor(string name);
		//int InsertDistributor(shared_ptr<Distributor> dist);

	private:
		bool Open(const char* name);
		void Close();
		//vector<shared_ptr<Interface>> DATABASE::SqliteDB::Quary(const char* quary);

		sqlite3* database;
	};
}

