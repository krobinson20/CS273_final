#pragma once
#ifndef Person_H__
#define Person_H_
#include<string>
#include <iostream>
using namespace std;

class Person
{
protected:
	
public:
	string name;

	Person(){}

	Person(string n)
	{
		name = n;
	}



	virtual void Display()
	{
		cout << "Hello my name is " << name;
	}
};


#endif