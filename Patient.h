#pragma once
#ifndef Patient_H__
#define Patient_H_
#include<fstream>
#include<iostream>
#include"Person.h"
#include<string>
#include<time.h>

class Patient: public Person 
{
private:

	int visit_number;
	int priority;

public: 
	

	Patient(string n)
	{
		name = n; 

		int priority_generator = rand() % 10 + 1;
		
		if (priority_generator <= 7)
		{
			priority = rand() % 10 + 1;
		}
		else if (priority_generator == 8 || priority_generator == 9)
		{
			priority = rand() % 5 + 11;
		}
		else
		{
			priority = rand() % 5 + 16;
		}
	}
	
	bool operator<(const Patient &other) const {
		if (priority < other.priority) {
			return true;
		}
		else {
			return false;
		}
	}

	void Display()
	{
		cout << "\nName: " << name << " \nVisit Number: " << visit_number << " \nPriority: " << priority << endl;
	}

	int getPriority() {
		return priority;
	}
	string getName() {
		return name;
	}
	void set_visit_number(int n) {
		visit_number = n;
	}
};

#endif