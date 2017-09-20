#include <iostream>
#include "Customer.h"

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

int main()
{
	cout << "��ˢ���������������ַ�����ʾˢ����" << endl;
	getchar();
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