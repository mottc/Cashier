#include <iostream>
#include "Customer.h"

using namespace std;

int main()
{
	cout << "��ˢ����" << endl;
	getchar();
	Customer customer("��ĳĳ", 18, 452.36);
	cout << "*************************" << endl;
	cout << "  ������" << customer.getName() << endl;
	cout << "  ���䣺" << customer.getAge() << endl;
	cout << "  ��" << customer.getBalance() << endl;
	cout << "*************************" << endl << endl;

	cout << "��ѡ����Ҫ���еĲ�����" << endl;
	cout << "1������" << endl;
	cout << "2����ֵ" << endl << endl;

	bool inputAgain = false;
	do
	{
		int choice;
		cin >> choice;
		switch (choice)
		{
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
		default:
			cout << "���Ĳ����������������룡" << endl;
			inputAgain = true;
			break;
		}
	} while (inputAgain);
	

	cout << endl << "���º���Ϣ��" << endl;
	cout << "*************************" << endl;
	cout << "  ������" << customer.getName() << endl;
	cout << "  ���䣺" << customer.getAge() << endl;
	cout << "  ��" << customer.getBalance() << endl;
	cout << "*************************" << endl << endl;

	system("pause");
	return 0;
}