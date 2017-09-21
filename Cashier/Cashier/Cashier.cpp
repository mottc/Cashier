#include <iostream>
#include <sstream>
#include "Customer.h"
#include "sqlite3.h"  
#pragma comment(lib, "sqlite3.lib") 

using namespace std;

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

int customerRegister(sqlite3 *db)
{
	int rc;
	
	char *zErrMsg = 0;
	string name;
	int age;
	double balance;
	cout << "请输入新用户姓名：";
	cin >> name;
	cout << "请输入新用户年龄：";
	cin >> age;
	cout << "请输入新用户初始金额：";
	cin >> balance;

	stringstream age_stream;
	age_stream << age;
	string age_string = age_stream.str();
	stringstream balance_stream;
	balance_stream << balance;
	string balance_string = balance_stream.str();


	/* Create SQL statement */
	string sql_string = "INSERT INTO CUSTOMERS (ID,NAME,AGE,BALANCE) VALUES (null, \"" + name + "\", " + age_string + ", " + balance_string + ");";
	cout << sql_string;
	const char* sql = sql_string.c_str();
	/*sprintf(sql, "INSERT INTO CUSTOMERS (ID,NAME,AGE,BALANCE)" \
		"VALUES (null, '%s', %d, %f );", name, age, balance);*/
	
	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "新用户注册成功！\n");
	}
	cout << "新用户编号为：" << sqlite3_last_insert_rowid(db) << endl << endl;
	return 0;
}

int useCard()
{
	cout << "请刷卡！（按下任意字符键表示刷卡）" << endl;
	char ch;
	cin >> ch;
	Customer customer("王某某", 18, 452.36);
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
	return 0;
}

void main()
{
	sqlite3 * db;
	int res = sqlite3_open("customer.db", &db);
	if (res != SQLITE_OK) 
	{
		cout << "数据库打开失败！" << sqlite3_errmsg(db) << endl;
	}
	else 
	{
		while (true)
		{
			cout << "请选择要执行的操作：" << endl;
			cout << "0：退出" << endl;
			cout << "1：注册新用户" << endl;
			cout << "2：用户刷卡" << endl;
			bool again = false;
			int index;
			do
			{
				cin >> index;
				switch (index)
				{
				case 0:
					/*sql = "CREATE TABLE CUSTOMERS("  \
						"ID INT PRIMARY KEY," \
						"NAME           TEXT    NOT NULL," \
						"AGE            INT     NOT NULL," \
						"BALANCE         REAL );";
					sqlite3_exec(db, sql, 0, 0, &zErrMsg);*/
					break;
				case 1:
				{
					customerRegister(db);
					break;
				}
				case 2:
					useCard();
					break;
				default:
					cout << "您的操作有误，请重新输入！" << endl;
					again = true;
					break;
				}
			} while (again);
			if (index == 0)
			{
				break;
			}
		}
	}
	sqlite3_close(db);
}