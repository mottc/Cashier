#include <iostream>
#include "Customer.h"

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

int main()
{
	cout << "请刷卡！（按下任意字符键表示刷卡）" << endl;
	getchar();
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