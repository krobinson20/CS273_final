#pragma once
#ifndef Doctor_H__
#define Doctor_H_
#include <string>
#include"Person.h"
using namespace std; 
class Doctor: public Person 
{
private:
	
	int max_treat_time;
	bool available;
	int start_treatment;
	Patient* current_patient;

public: 
	
	Doctor()
	{
		max_treat_time = 20;
		available = true;
		start_treatment = 0;
	}
	
	// function that is supposed to check weather or not the doctor is done treating the patient
	void service(Patient* p)
	{

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