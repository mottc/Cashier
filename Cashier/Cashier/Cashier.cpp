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
	cout << "请选择要执行的操作：" << endl;
	cout << "0：退出" << endl;
	cout << "1：注册新用户" << endl;
	cout << "2：用户刷卡" << endl;
}

void display1()
{
	cout << "请选择您要进行的操作：" << endl;
	cout << "0：退出" << endl;
	cout << "1：消费" << endl;
	cout << "2：充值" << endl;
	cout << "3：修改姓名" << endl;
	cout << "4：修改年龄" << endl;
	cout << "5：删除顾客" << endl << endl;
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
						cout << "您的操作有误，请重新输入！" << endl;
						break;
					}
				} while (inputAgain);
			}
			again = true;
			display0();
			break;
		default:
			cout << "您的操作有误，请重新输入！" << endl;
			again = true;
			break;
		}
	} while (again);
}