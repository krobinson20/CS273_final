#pragma once
#ifndef Nurse_H__
#define Nurse_H_

#include <string>
#include "Person.h"
#include"Patient.h"
using namespace std;

class Nurse : public Person 
{
private:
	
	int max_treat_time;
	bool available;
	int start_treatment;
	Patient* current_patient;

public: 

	Nurse()
	{
		max_treat_time = 10;
		available = true;
		start_treatment = 0;
	}

	void service(Patient* p)
	{
		current_patient = p;
		available = false;
	}
	bool checkAvailable() {
		return available;
	}
	int get_start_treatment()
	{
		return start_treatment;
	}
	int get_max_treatment_time()
	{
		return max_treat_time;
	}
	void incrament() {
		start_treatment++;
	}
	void reset() {
		start_treatment = 0;
		available = true;
	}
	Patient* getPatient() {
		return current_patient;
	}
};

#endif