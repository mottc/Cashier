#include <iostream>
#include <sstream>
#include "Customer.h"
#include "sqlite3.h" 
#include "SQLiteHelper.h"
#include "Operation.h"
#pragma comment(lib, "sqlite3.lib") 

using namespace std;

string name;
int age;
double balance;

void display0()
{
	cout << "��ѡ��Ҫִ�еĲ�����" << endl;
	cout << "0���˳�" << endl;
	cout << "1��ע�����û�" << endl;
	cout << "2���û�ˢ��" << endl;
}

void display1()
{
	cout << "��ѡ����Ҫ���еĲ�����" << endl;
	cout << "0���˳�" << endl;
	cout << "1������" << endl;
	cout << "2����ֵ" << endl;
	cout << "3���޸�����" << endl;
	cout << "4���޸�����" << endl;
	cout << "5��ɾ���˿�" << endl << endl;
}
void main()
{
	Operation* operation = new Operation();
	string ID;
	display0();

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
			again = false;
		break;
	    case 1:
		{
			operation->customerRegister();
			again = true;
			display0();
			break;
		}
		case 2:
			ID = operation->useCard();
			if (ID != "")
			{
				display1();
				int choice;
				
				bool inputAgain = true;
				do
				{
					cin >> choice;
					switch (choice)
					{
					case 0:
						inputAgain = false;
						break;
					case 1:
						inputAgain = true;
						operation->cost(ID);
						operation->infoDisplay();
						display1();
						break;
					case 2:
						inputAgain = true;
						operation->deposit(ID);
						operation->infoDisplay();
						display1();
						break;
					case 3:
						inputAgain = true;
						operation->setName(ID);
						operation->infoDisplay();
						display1();
						break;
					case 4:
						inputAgain = true;
						operation->setAge(ID);
						operation->infoDisplay();
						display1();
						break;
					case 5:
						inputAgain = false;
						operation->customerDelete(ID);
						break;
					default:
						inputAgain = true;
						cout << "���Ĳ����������������룡" << endl;
						break;
					}
				} while (inputAgain);
			}
			again = true;
			display0();
			break;
		default:
			cout << "���Ĳ����������������룡" << endl;
			again = true;
			break;
		}
	} while (again);
}