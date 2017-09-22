#include <iostream>
#include <sstream>
#include "Customer.h"
#include "sqlite3.h" 
#include "SQLiteHelper.h"
#pragma comment(lib, "sqlite3.lib") 

using namespace std;

string name;
int age;
double balance;
//utf-8ת����GB3212  
char* U2G(const char* utf8)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
	len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
	if (wstr) delete[] wstr;
	return str;
}
//GB2312��UTF-8��ת��  
char* G2U(const char* gb2312)
{
	int len = MultiByteToWideChar(CP_ACP, 0, gb2312, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_ACP, 0, gb2312, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	if (wstr) delete[] wstr;
	return str;
}

void modifyInformation(Customer* customer)
{
	cout << "��ѡ��Ҫ�޸ĵ����ݣ�" << endl;
	cout << "0���˳��޸�" << endl;
	cout << "1������" << endl;
	cout << "2������" << endl;
	bool chooseAgain = false;
	do
	{
		int index;
		cin >> index;
		switch (index)
		{
		case 0:
			break;
		case 1:
		{
			cout << "������������������";
			string name;
			cin >> name;
			customer->setName(name);
			break;
		}
		case 2:
			cout << "���������������䣺";
			int age;
			cin >> age;
			customer->setAge(age);
			break;
		default:
			cout << "���Ĳ����������������룡" << endl;
			chooseAgain = true;
			break;
		}
	} while (chooseAgain);
}

void customerRegister(SQLiteHelper *sqliteHelper)
{
	int rc;
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
	char* sql = G2U(sql1);
	/* Execute SQL statement */
	rc = sqliteHelper->execSQL(sql);
	if (rc != SQLITE_OK) {
		cout << "SQL error!" << endl;
	}
	else {
		cout << "���û�ע��ɹ���" << endl;
	}
	cout << "���û����Ϊ��" << sqliteHelper->getLastID() << endl << endl;
}

static int callback(void *data, int argc, char **argv, char **azColName) {
	int i;
	//fprintf(stderr, "%s: ", (const char*)data);
	for (i = 0; i<argc; i++) {
		switch (i)
		{
		case 0:
			name = U2G(argv[i]);
			break;
		case 1:
			age = atoi(argv[i]);
			break;
		case 2:
			balance = atof(argv[i]);
			break;
		default:
			break;
		}
	}
	printf("\n");
	return 0;
}

void useCard(SQLiteHelper *sqliteHelper)
{
	cout << "��ˢ����������ID����ʾ�ӿ��ж�ȡ�����ݣ�" << endl;
	string ID;
	cin >> ID;
	string sql_string = "SELECT NAME,AGE,BALANCE FROM CUSTOMERS WHERE ID=" + ID;
	cout << sql_string;
	const char* sql = sql_string.c_str();
	//char *Initialization = "Init";
	//char** pResult = &Initialization;
	//int nRow;
	//int nCol;
	//int nResult;
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	//char *sql;
	const char* data = "Callback function called";

	/* Open database */
	rc = sqlite3_open("customer.db", &db);
	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		exit(0);
	}
	else {
		fprintf(stderr, "Opened database successfully\n");
	}

	/* Create SQL statement */
	//sql = "SELECT * from COMPANY";

	rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "Operation done successfully\n");
	}

	//sqlite3_close(db);
	//nResult = sqliteHelper->rawQuery(sql, &nRow, &nCol, pResult);
	//nResult = sqlite3_get_table(db, strSql.c_str(), &pResult, &nRow, &nCol, &errmsg);
	/*if (nResult != SQLITE_OK)
	{
		cout << "�Բ���û�и�ID��Ӧ�Ĺ˿͡���ȷ���������룡";
		return;
	}
	cout << endl << nRow << nCol;
	char* rrr = U2G(pResult[5]);
	cout << rrr;*/
	//string strOut;
	//int index = nCol;
	//for (int i = 0; i < nRow; i++)
	//{
	//	printf("�� %d ����¼\n", i);
	//	for (int j = 0; j < nCol; j++)
	//	{
	//		printf("�ֶ���:%s ? > �ֶ�ֵ:%s\n", pResult[5], pResult[5]);
	//		index++;
	//		// dbResult ���ֶ�ֵ�������ģ��ӵ�0�������� nColumn - 1���������ֶ����ƣ��ӵ� nColumn ������ʼ�����涼���ֶ�ֵ������һ����ά�ı���ͳ�����б�ʾ������һ����ƽ����ʽ����ʾ
	//	}
	//}



	Customer customer(name, age, balance);
	cout << endl << "�ɹ���ȡ������Ϣ��" << endl;
	cout << "*************************" << endl;
	cout << "  ������" << customer.getName() << endl;
	cout << "  ���䣺" << customer.getAge() << endl;
	cout << "  ��" << customer.getBalance() << endl;
	cout << "*************************" << endl << endl;
	while (true)
	{
		cout << "��ѡ����Ҫ���еĲ�����" << endl;
		cout << "0���˳�" << endl;
		cout << "1������" << endl;
		cout << "2����ֵ" << endl;
		cout << "3���޸Ļ�����Ϣ" << endl << endl;
		int choice;
		cin >> choice;
		bool inputAgain = false;
		do
		{
			switch (choice)
			{
			case 0:
				break;
			case 1:
				cout << "���������ѽ�";
				double cost;
				cin >> cost;
				customer.cost(cost);
				break;
			case 2:
				cout << "�������ֵ��";
				double deposit;
				cin >> deposit;
				customer.deposit(deposit);
				break;
			case 3:
				modifyInformation(&customer);
				break;
			default:
				cout << "���Ĳ����������������룡" << endl;
				inputAgain = true;
				break;
			}
		} while (inputAgain);

		if (choice == 0)
			break;

		cout << endl << "���º���Ϣ��" << endl;
		cout << "*************************" << endl;
		cout << "  ������" << customer.getName() << endl;
		cout << "  ���䣺" << customer.getAge() << endl;
		cout << "  ��" << customer.getBalance() << endl;
		cout << "*************************" << endl << endl;
	}
}

int operate(SQLiteHelper *sqliteHelper)
{
	cout << "��ѡ��Ҫִ�еĲ�����" << endl;
	cout << "0���˳�" << endl;
	cout << "1��ע�����û�" << endl;
	cout << "2���û�ˢ��" << endl;

	/*sqlite3 *db;
	char *sql;

	sqlite3_open("customer.db", &db);*/
	bool again = false;
	int index;
	do
	{
		cin >> index;
		switch (index)
		{
		case 0:
			/*sql = "CREATE TABLE CUSTOMERS("  \
			"ID INTEGER PRIMARY KEY AUTOINCREMENT," \
			"NAME TEXT NOT NULL," \
			"AGE INT NOT NULL," \
			"BALANCE REAL);";
			sqlite3_exec(db, sql, 0, 0, 0);*/
			break;
		case 1:
		{
			customerRegister(sqliteHelper);
			break;
		}
		case 2:
			useCard(sqliteHelper);
			break;
		default:
			cout << "���Ĳ����������������룡" << endl;
			again = true;
			break;
		}
	} while (again);
	return index;
}

void main()
{
	SQLiteHelper *sqliteHelper = new SQLiteHelper();
	int res = sqliteHelper->openDB("customer.db");
	if (res == SQLITE_OK) 
	{
		while (true)
		{
			int result = operate(sqliteHelper);
			if (result == 0)
			{
				break;
			}
		}
	}
	else
	{
		cout << "���ݿ��ʧ�ܣ�" << endl;
	}
	sqliteHelper->closeDB();
	getchar();
}