#include <iostream>
#include "Customer.h"

using namespace std;

int main()
{
	Customer cus("xm", 18, 452.36);
	cout << cus.getName() << cus.getBalance();
	cus.cost(52);
	cout << cus.getName() << cus.getBalance();
	
	system("pause");
	return 0;
}