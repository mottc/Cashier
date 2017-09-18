#include "Customer.h"
#include "string"

Customer::Customer()
{
}

Customer::Customer(string name, int age, double balance)
{
	this->name = name;
	this->age = age;
	this->balance = balance;
}

Customer::~Customer()
{
}

string Customer::getName()
{
	return name;
}

void Customer::setName(string name)
{
	this->name = name;
}

int Customer::getAge()
{
	return age;
}

void Customer::setAge(int age)
{
	this->age = age;
}

double Customer::getBalance()
{
	return balance;
}

void Customer::setBalance(double balance)
{
	this->balance = balance;
}

void Customer::cost(double cost)
{
	this->balance = this->balance - cost;
}

void Customer::deposit(double deposit)
{
	this->balance = this->balance + deposit;
}
