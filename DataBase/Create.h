#pragma once
#include "Database.h"

class Create
{
public:
	Create(void);
	void BioDB2();
	void AddTable();

	/*Used to create database for pictures*/
	Create(int vv);

	/*Used to create new database 2024*/
	Create(int vv, int xx);

	/*Used 20 11 2024 To create picture db*/
	void PicDB();

	/*Used to test constraints*/
	Create(int vv, int xx, int rr);

	~Create(void);

	
};


