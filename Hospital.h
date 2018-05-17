#pragma once
#ifndef Hospital_H__
#define Hospital_H_
#include "Nurse.h"
#include "Doctor.h"
#include "Patient.h"
#include <queue>
#include <map>
#include <vector>

class Hospital {
private:
	int nurse_number;
	int doctor_number;
	int served_by_nurse = 0;
	int served_by_doctor = 0;
	vector<Nurse*> nurses;
	vector<Doctor*> doctors;
	int arrival_rate;
	priority_queue<Patient *> waiting_room; //holds patients waiting to see a doctor or nurse
	priority_queue<Patient *> doctor_patients; //holds the patients that are going to be seen by the doctors
	priority_queue<Patient *> nurse_patients;//holds teh patients that are going to be seen by the nurses
	multimap<string, Patient *> patients_served; //holds the info about the patients that have been served

public:
	Hospital(){}

	void addPatient(Patient* p) {
		if (p->getPriority() <= 10)
		{
			nurse_patients.push(p);
			//cout << "added to nurses" << endl;
			//cout << "Nurse patients: " << nurse_patients.size() << endl;
		}
		else if (p->getPriority() > 10)
		{
			doctor_patients.push(p);
			//cout << "added to doctors" << endl;
			//cout << "Doctor patients: " << doctor_patients.size() << endl;
		}
	}
	void data() // prompts the user to add data about the simulation
	{
		do 
		{
			cout << "Enter the Average patient arrival rate (one patient every X min): ";
			cin >> arrival_rate;
		} while (arrival_rate > 60 || arrival_rate <= 0);
		cout << "Enter the number of Doctors working: ";
		cin >> doctor_number;
		cout << "Enter the number of Nurses working: ";
		cin >> nurse_number;

		for (int i = 0; i < nurse_number; i++) {
			Nurse* n = new Nurse();
			nurses.push_back(n);
		}
		for (int i = 0; i < doctor_number; i++) {
			Doctor* d = new Doctor();
			doctors.push_back(d);
		}

	}
	void Update(int clock)
	{
		for (int i = 0; i < nurses.size(); i++)
		{
			if (nurses[i]->checkAvailable())
			{
				//cout << "Nurse patients: " << nurse_patients.size() << endl;
				if (!nurse_patients.empty()) 
				{
					nurses[i]->service(nurse_patients.top());
					nurse_patients.pop();
					//cout << "SERVICED" << endl;
				}
				else
				{
					//cout << "nurse queue empty" << endl;
				}
			}
			else
			{
				if (nurses[i]->get_start_treatment() == nurses[i]->get_max_treatment_time()) 
				{
					// sets visit number based on how many times the patient's name comes up in patients_served
					int vn = patients_served.count(nurses[i]->getPatient()->getName()) + 1;
					nurses[i]->getPatient()->set_visit_number(vn);
					patients_served.insert(make_pair(nurses[i]->getPatient()->getName(), nurses[i]->getPatient()));
					nurses[i]->reset();
					served_by_nurse++;
					//cout << "ALL THE WAAAAAAAAAAAAAAAAAAAAY" << endl;
					
				}
				else
					nurses[i]->incrament();
			}
		}
		for (int i = 0; i < doctors.size(); i++) 
		{
			if (doctors[i]->checkAvailable()) 
			{
				//cout << "Doctor patients: " << doctor_patients.size() << endl;
				if (!doctor_patients.empty())
				{
					doctors[i]->service(doctor_patients.top());
					doctor_patients.pop();
					//cout << "SERVICED" << endl;
				}
				else
				{
					//cout << "doctor queue empty" << endl;
				}
			}
			else
			{
				if (doctors[i]->get_start_treatment() == doctors[i]->get_max_treatment_time()) 
				{
					// sets visit number based on how many times the patient's name comes up in patients_served
					int vn = patients_served.count(doctors[i]->getPatient()->getName()) + 1;
					doctors[i]->getPatient()->set_visit_number(vn);
					patients_served.insert(make_pair(doctors[i]->getPatient()->getName(), doctors[i]->getPatient()));
					doctors[i]->reset();
					served_by_doctor++;
					//cout << "ALL THE WAAAAAAAAAAAAAAAAAAY" << endl;
					
				}
				else
					doctors[i]->incrament();
			}
		}
	}

	int getArrival_rate()
	{
		return arrival_rate;
	}
	multimap<string, Patient*> getRecord() 
	{
		return patients_served;
	}
	int getServed_by_nurse() {
		return served_by_nurse;
	}
	int getServed_by_doctor() {
		return served_by_doctor;
	}
};
#endif