#include "StdAfx.h"
#include "Create.h"
#include <iostream>
#include <sstream>

using namespace std;

Create::Create(void)
{	
}

Create::Create(int vv)
{
	std::shared_ptr<Database> db = std::make_shared<Database>("Pic.db");

	db->Quary("CREATE TABLE PICS (name TEXT PRIMARY KEY, size INTEGER, pict BLOB)");
	//db->Quary("CREATE TABLE PICS (index INTEGER PRIMARY KEY, actMov TEXT, pic BLOB)");
	cout << "Finish" << endl;
}


Create::Create(int vv, int xx)
{
	Database db("WPD_2024_.db");
	db.Quary("CREATE TABLE DIRECTOR (name TEXT PRIMARY KEY, nationality TEXT, yearStart INTEGER, yearEnd INTEGER)");

	db.Quary("CREATE TABLE ACTOR (name TEXT PRIMARY KEY, nationality TEXT, yearStart INTEGER, yearEnd INTEGER, yearBorn INTEGER)");

	db.Quary("CREATE TABLE COMMON (nameMovie TEXT NOT NULL REFERENCES MOVIE(nameMovie), name TEXT NOT NULL REFERENCES ACTOR(name), PRIMARY KEY(nameMovie,name))");//Havde fejl

	db.Quary("CREATE TABLE MOVIEaka (a INTEGER AUTO_INCREMENT PRIMARY KEY, aka TEXT NOT NULL, nameMovie TEXT NOT NULL REFERENCES MOVIE(nameMovie))");

	db.Quary("CREATE TABLE ACTORaka (a INTEGER AUTO_INCREMENT PRIMARY KEY, aka TEXT NOT NULL, name TEXT NOT NULL REFERENCES ACTOR(name))");

	db.Quary("CREATE TABLE DIRECTORaka (a INTEGER AUTO_INCREMENT PRIMARY KEY, aka TEXT NOT NULL, name TEXT NOT NULL REFERENCES DIRECTOR(name))");
		
	db.Quary("CREATE TABLE PRODUCERS (name TEXT PRIMARY KEY)");

	db.Quary("CREATE TABLE DISTRIBUTORS (name TEXT PRIMARY KEY)");

	db.Quary("CREATE TABLE MOVIE (nameMovie TEXT PRIMARY KEY, director TEXT NOT NULL REFERENCES DIRECTOR(name), producer TEXT REFERENCES PRODUCERS(name), distributor TEXT REFERENCES DISTRIBUTORS(name), year INTEGER, status INTEGER, inCollection INTEGER, type INTEGER, MP4 INTEGER, size INTEGER)");



	db.Quary("CREATE TABLE LABELS (name TEXT PRIMARY KEY)");		
	
	db.Quary("CREATE TABLE MOLABEL (nameMovie TEXT NOT NULL REFERENCES MOVIE(nameMovie), name TEXT NOT NULL REFERENCES LABELS(name), PRIMARY KEY(nameMovie, name))"); //Havde fejl

	db.Quary("CREATE TABLE SUS (a INTEGER, year INTEGER, month INTEGER, incollection INTEGER, format INTEGER)");

	db.Quary("CREATE TABLE SUScom (noSUS INTEGER NOT NULL REFERENCES SUS(a), name TEXT NOT NULL REFERENCES ACTOR(name), PRIMARY KEY(noSUS,name))"); //Havde fejl

	db.Quary("CREATE TABLE COLOR (a INTEGER, year INTEGER, month INTEGER, incollection INTEGER, format INTEGER)");

	db.Quary("CREATE TABLE COLORcom (noCOLOR INTEGER NOT NULL REFERENCES COLOR(a), name TEXT NOT NULL REFERENCES ACTOR(name), PRIMARY KEY(noCOLOR,name))"); //Havde fejl

	db.Quary("CREATE TABLE ActPic (a INTEGER AUTO_INCREMENT PRIMARY KEY, name TEXT  NOT NULL REFERENCES ACTOR(name), size INTEGER, pict BLOB)");

	db.Quary("CREATE TABLE MoviePic (a INTEGER AUTO_INCREMENT PRIMARY KEY, name TEXT  NOT NULL REFERENCES MOVIE(nameMovie), size INTEGER, pict BLOB)");

	db.Quary("CREATE TABLE DirPic (a INTEGER AUTO_INCREMENT PRIMARY KEY, name TEXT  NOT NULL REFERENCES DIRECTOR(name), size INTEGER, pict BLOB)");

	db.Quary("CREATE TABLE SusPic (a INTEGER AUTO_INCREMENT PRIMARY KEY, name TEXT  NOT NULL REFERENCES SUS(a), size INTEGER, pict BLOB)");

	db.Quary("CREATE TABLE ColorPic (a INTEGER AUTO_INCREMENT PRIMARY KEY, name TEXT  NOT NULL REFERENCES COLOR(a), size INTEGER, pict BLOB)");

	
}


Create::~Create(void)
{
}




void Create::BioDB2()
{
	Database db = "BioDB.db";
	db.Quary("CREATE TABLE Project (name TEXT PRIMARY KEY)");

	db.Quary("CREATE TABLE PipeRun (name TEXT PRIMARY KEY, project TEXT NOT NULL REFERENCES Project(name), InletHead REAL, OutletHead REAL)");

	db.Quary("CREATE TABLE Ror (pk TEXT PRIMARY KEY, type TEXT NOT NULL, Dim INTEGER NOT NULL, Dia REAL, s REAL)");
	
	db.Quary("CREATE TABLE BioComponent (pk TEXT PRIMARY KEY, tag TEXT, function TEXT NOT NULL, description TEXT, pipeRun TEXT NOT NULL REFERENCES PipeRun(name), inlet TEXT REFERENCES BioComponent(pk), outlet TEXT REFERENCES BioComponent(pk), length REAL, elbow90 INTEGER, elbow45 INTEGER, ror TEXT NOT NULL REFERENCES Ror(pk))");



	
}

void Create::AddTable()
{
	Database db = "BioDB.db";
	db.Quary("CREATE TABLE Test5 (pk TEXT PRIMARY KEY, tag TEXT,  type TEXT, pipeRun TEXT NOT NULL REFERENCES PipeRun(name), inlet TEXT REFERENCES Test5(pk), outlet TEXT REFERENCES Test5(pk), length REAL, elbow90 INTEGER, elbow45 INTEGER, ror TEXT NOT NULL REFERENCES Ror(pk))");

}


void Create::PicDB()
{
	Database db = "Utilities.db";
	db.Quary("CREATE TABLE IconPic (name TEXT PRIMARY KEY, size INTEGER, pict BLOB)");
}






