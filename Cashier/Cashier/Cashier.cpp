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
//utf-8转换到GB3212  
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
//GB2312到UTF-8的转换  
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
	cout << "请选择要修改的内容：" << endl;
	cout << "0：退出修改" << endl;
	cout << "1：姓名" << endl;
	cout << "2：年龄" << endl;
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
			cout << "请输入更正后的姓名：";
			string name;
			cin >> name;
			customer->setName(name);
			break;
		}
		case 2:
			cout << "请输入更正后的年龄：";
			int age;
			cin >> age;
			customer->setAge(age);
			break;
		default:
			cout << "您的操作有误，请重新输入！" << endl;
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
	cout << "请输入新用户姓名：";
	cin >> name;
	cout << "请输入新用户年龄：";
	cin >> age;
	cout << "请输入新用户初始金额：";
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
		cout << "新用户注册成功！" << endl;
	}
	cout << "新用户编号为：" << sqliteHelper->getLastID() << endl << endl;
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
	cout << "请刷卡！（输入ID，表示从卡中读取的数据）" << endl;
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
		cout << "对不起，没有该ID对应的顾客。请确认您的输入！";
		return;
	}
	cout << endl << nRow << nCol;
	char* rrr = U2G(pResult[5]);
	cout << rrr;*/
	//string strOut;
	//int index = nCol;
	//for (int i = 0; i < nRow; i++)
	//{
	//	printf("第 %d 条记录\n", i);
	//	for (int j = 0; j < nCol; j++)
	//	{
	//		printf("字段名:%s ? > 字段值:%s\n", pResult[5], pResult[5]);
	//		index++;
	//		// dbResult 的字段值是连续的，从第0索引到第 nColumn - 1索引都是字段名称，从第 nColumn 索引开始，后面都是字段值，它把一个二维的表（传统的行列表示法）用一个扁平的形式来表示
	//	}
	//}



	Customer customer(name, age, balance);
	cout << endl << "成功读取卡内信息：" << endl;
	cout << "*************************" << endl;
	cout << "  姓名：" << customer.getName() << endl;
	cout << "  年龄：" << customer.getAge() << endl;
	cout << "  余额：" << customer.getBalance() << endl;
	cout << "*************************" << endl << endl;
	while (true)
	{
		cout << "请选择您要进行的操作：" << endl;
		cout << "0：退出" << endl;
		cout << "1：消费" << endl;
		cout << "2：充值" << endl;
		cout << "3：修改基本信息" << endl << endl;
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
				cout << "请输入消费金额：";
				double cost;
				cin >> cost;
				customer.cost(cost);
				break;
			case 2:
				cout << "请输入充值金额：";
				double deposit;
				cin >> deposit;
				customer.deposit(deposit);
				break;
			case 3:
				modifyInformation(&customer);
				break;
			default:
				cout << "您的操作有误，请重新输入！" << endl;
				inputAgain = true;
				break;
			}
		} while (inputAgain);

		if (choice == 0)
			break;

		cout << endl << "更新后信息：" << endl;
		cout << "*************************" << endl;
		cout << "  姓名：" << customer.getName() << endl;
		cout << "  年龄：" << customer.getAge() << endl;
		cout << "  余额：" << customer.getBalance() << endl;
		cout << "*************************" << endl << endl;
	}
}

int operate(SQLiteHelper *sqliteHelper)
{
	cout << "请选择要执行的操作：" << endl;
	cout << "0：退出" << endl;
	cout << "1：注册新用户" << endl;
	cout << "2：用户刷卡" << endl;

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
			cout << "您的操作有误，请重新输入！" << endl;
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
		cout << "数据库打开失败！" << endl;
	}
	sqliteHelper->closeDB();
	getchar();
}