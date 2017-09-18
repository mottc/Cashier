#pragma once

#include <string>

using namespace std;

class Customer
{
public:
	Customer();
	Customer(string name, int age, double balance);
	~Customer();

private:
	string name;
	int age;
	double balance;

public:
	string getName();
	void setName(string name);
	int getAge();
	void setAge(int age);
	double getBalance();
	void setBalance(double balance);
	void cost(double cost);
	void deposit(double deposit);
};