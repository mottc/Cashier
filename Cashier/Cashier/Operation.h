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
	string useCard();
	void customerDelete(string ID);
	void setName(string ID);
	void setAge(string ID);
	void cost(string ID);
	void deposit(string ID);
	void infoDisplay();
};