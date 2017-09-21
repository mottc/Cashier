#include <iostream>
#include <sstream>
#include "Customer.h"
#include "sqlite3.h"  
#pragma comment(lib, "sqlite3.lib") 

using namespace std;

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

int customerRegister(sqlite3 *db)
{
	int rc;
	
	char *zErrMsg = 0;
	string name;
	int age;
	double balance;
	cout << "���������û�������";
	cin >> name;
	cout << "���������û����䣺";
	cin >> age;
	cout << "���������û���ʼ��";
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
		fprintf(stdout, "���û�ע��ɹ���\n");
	}
	cout << "���û����Ϊ��" << sqlite3_last_insert_rowid(db) << endl << endl;
	return 0;
}

int useCard()
{
	cout << "��ˢ���������������ַ�����ʾˢ����" << endl;
	char ch;
	cin >> ch;
	Customer customer("��ĳĳ", 18, 452.36);
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
	return 0;
}

void main()
{
	sqlite3 * db;
	int res = sqlite3_open("customer.db", &db);
	if (res != SQLITE_OK) 
	{
		cout << "���ݿ��ʧ�ܣ�" << sqlite3_errmsg(db) << endl;
	}
	else 
	{
		while (true)
		{
			cout << "��ѡ��Ҫִ�еĲ�����" << endl;
			cout << "0���˳�" << endl;
			cout << "1��ע�����û�" << endl;
			cout << "2���û�ˢ��" << endl;
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
					cout << "���Ĳ����������������룡" << endl;
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