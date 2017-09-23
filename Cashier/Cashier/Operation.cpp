#include "Operation.h"
#include <iostream>
using namespace std;

Operation::Operation()
{
	customer = new Customer();
	sqliteHelper = new SQLiteHelper();
	transcode = new Transcode();
	sqliteHelper->openDB("customer.db");
}

Operation::~Operation()
{
	delete customer;
	delete sqliteHelper;
	delete transcode;
}

void Operation::customerRegister()
{
	int registerResult;
	string name;
	string age;
	string balance;
	cout << "���������û�������";
	cin >> name;
	cout << "���������û����䣺";
	cin >> age;
	cout << "���������û���ʼ��";
	cin >> balance;

	/* Create SQL statement */
	string sql_string = "INSERT INTO CUSTOMERS (ID,NAME,AGE,BALANCE) VALUES (null, \"" + name + "\", " + age + ", " + balance + ");";
	const char* sql1 = sql_string.c_str();
	char* sql = transcode->G2U(sql1);

	/* Execute SQL statement */
	registerResult = sqliteHelper->execSQL(sql);
	if (registerResult != SQLITE_OK) {
		cout << "SQL error!" << endl;
	}
	else {
		cout << "���û�ע��ɹ������IDΪ��" << sqliteHelper->getLastID() << endl << endl;
	}
}


string Operation::useCard()
{
	cout << "��ˢ����������ID����ʾ�ӿ��ж�ȡ�����ݣ�" << endl;
	string ID;
	cin >> ID;
	/* Create SQL statement */
	string sql_string = "SELECT NAME,AGE,BALANCE FROM CUSTOMERS WHERE ID=" + ID;
	const char* sql = sql_string.c_str();
	int row, col;
	char *Initialization = "Init";
	char **result = &Initialization;
	char **re = sqliteHelper->rawQuery(sql, &row, &col, result);
	if (row == 1)
	{
		string name = transcode->U2G(re[3]);
		int age = atoi(re[4]);
		double balance = atof(re[5]);
		customer->setName(name);
		customer->setAge(age);
		customer->setBalance(balance);
		cout << endl << "�ɹ���ȡ������Ϣ��" << endl;
		infoDisplay();
		return ID;
	}
	else
	{
		cout << "û�иñ��ID��Ӧ�Ĺ˿ͣ�" << endl;
		return "";
	}
}

void Operation::customerDelete(string ID)
{
	string sql_string = "DELETE from CUSTOMERS WHERE ID=" + ID;
	const char* sql1 = sql_string.c_str();
	char* sql = transcode->G2U(sql1);
	sqliteHelper->execSQL(sql);
}

void Operation::infoDisplay()
{
	cout << "*************************" << endl;
	cout << "  ������" << customer->getName() << endl;
	cout << "  ���䣺" << customer->getAge() << endl;
	cout << "  ��" << customer->getBalance() << endl;
	cout << "*************************" << endl << endl;
}

void Operation::setName(string ID)
{
	cout << "������������������";
	string name;
	cin >> name;
	customer->setName(name);
	/* Create SQL statement */
	string sql_string = "UPDATE CUSTOMERS SET NAME = '"+ name +"' WHERE ID=" + ID;
	const char* sql1 = sql_string.c_str();
	char* sql = transcode->G2U(sql1);
	sqliteHelper->execSQL(sql);
}

void Operation::setAge(string ID)
{
	cout << "���������������䣺";
	string age;
	cin >> age;
	const char* age1 = age.c_str();
	customer->setAge(atoi(age1));
	/* Create SQL statement */
	string sql_string = "UPDATE CUSTOMERS SET AGE = '" + age + "' WHERE ID=" + ID;
	const char* sql = sql_string.c_str();
	sqliteHelper->execSQL(sql);
}

void Operation::cost(string ID)
{
	cout << "���������ѽ�";
	double cost;
	cin >> cost;
	customer->cost(cost);
	char str[256];
	sprintf(str, "%lf", customer->getBalance());
	string balance = str;
	/* Create SQL statement */
	string sql_string = "UPDATE CUSTOMERS SET BALANCE = '" + balance + "' WHERE ID=" + ID;
	const char* sql = sql_string.c_str();
	sqliteHelper->execSQL(sql);
}

void Operation::deposit(string ID)
{
	cout << "�������ֵ��";
	double deposit;
	cin >> deposit;
	customer->deposit(deposit);
	char str[256];
	sprintf(str, "%lf", customer->getBalance());
	string balance = str;
	/* Create SQL statement */
	string sql_string = "UPDATE CUSTOMERS SET BALANCE = '" + balance + "' WHERE ID=" + ID;
	const char* sql = sql_string.c_str();
	sqliteHelper->execSQL(sql);
}