#include <iostream>
#include "Customer.h"

using namespace std;

int main()
{
	cout << "请刷卡！" << endl;
	getchar();
	Customer customer("王某某", 18, 452.36);
	cout << "*************************" << endl;
	cout << "  姓名：" << customer.getName() << endl;
	cout << "  年龄：" << customer.getAge() << endl;
	cout << "  余额：" << customer.getBalance() << endl;
	cout << "*************************" << endl << endl;

	cout << "请选择您要进行的操作：" << endl;
	cout << "1：消费" << endl;
	cout << "2：充值" << endl << endl;

	bool inputAgain = false;
	do
	{
		int choice;
		cin >> choice;
		switch (choice)
		{
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
		default:
			cout << "您的操作有误，请重新输入！" << endl;
			inputAgain = true;
			break;
		}
	} while (inputAgain);
	

	cout << endl << "更新后信息：" << endl;
	cout << "*************************" << endl;
	cout << "  姓名：" << customer.getName() << endl;
	cout << "  年龄：" << customer.getAge() << endl;
	cout << "  余额：" << customer.getBalance() << endl;
	cout << "*************************" << endl << endl;

	system("pause");
	return 0;
}