#include "Operation.h"
#include <iostream>

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
	cout << "请输入新用户姓名：";
	cin >> name;
	cout << "请输入新用户年龄：";
	cin >> age;
	cout << "请输入新用户初始金额：";
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
		cout << "新用户注册成功！" << endl;
		cout << "新用户编号为：" << sqliteHelper->getLastID() << endl << endl;
	}
	
}

void Operation::modifyInformation()
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

void Operation::useCard()
{
	cout << "请刷卡！（输入ID，表示从卡中读取的数据）" << endl;
	string ID;
	cin >> ID;
	/* Create SQL statement */
	string sql_string = "SELECT NAME,AGE,BALANCE FROM CUSTOMERS WHERE ID=" + ID;
	const char* sql = sql_string.c_str();

	int row, col;
	char *Initialization = "Init";
	char **result = &Initialization;
	char **re = sqliteHelper->rawQuery(sql, &row, &col, result);
	string name = transcode->U2G(re[3]);
	int age = atoi(re[4]);
	double balance = atof(re[5]);

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
				modifyInformation();
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

void Operation::customerDelete()
{

}