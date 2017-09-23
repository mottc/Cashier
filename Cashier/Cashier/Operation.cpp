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
		cout << "���û�ע��ɹ���" << endl;
		cout << "���û����Ϊ��" << sqliteHelper->getLastID() << endl << endl;
	}
	
}

void Operation::modifyInformation()
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

void Operation::useCard()
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
	string name = transcode->U2G(re[3]);
	int age = atoi(re[4]);
	double balance = atof(re[5]);

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
				modifyInformation();
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

void Operation::customerDelete()
{

}