#pragma once
#include <string>
#include "Customer.h"
#include "SQLiteHelper.h"
#include "Transcode.h"
using namespace std;

class Operation
{
public:
	Operation();
	~Operation();

public:
	Customer* customer;
	SQLiteHelper* sqliteHelper;
	Transcode* transcode;

public:
	void customerRegister();
	void modifyInformation();
	void useCard();
	void customerDelete();
	
};