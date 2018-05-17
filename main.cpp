
#include<iostream>
#include "Hospital.h"
#include "Patient.h"
#include <string>
#include <fstream>	
#include<vector>
using namespace std;

void display_menu(Hospital& myhospital);
void emergency(Hospital &h, vector<string> r);

int main()
{
	string name;
	string first_name;
	string last_name;

	fstream firstname;
fstream lastname;

firstname.open("E://CS 273//Final project//CS273 Final project//residents_of_273ville.txt");
lastname.open("E://CS 273//Final project//CS273 Final project//surnames_of_273ville.txt");

if (!firstname) {
	cout << "Error: Can't open the file named residents.txt.\n";
	exit(1);
}
if (!lastname) {
	cout << "Error: Can't open the file named surnames.txt.\n";
	exit(1);
}

vector<string> residents;

while (!lastname.eof())
{
	firstname >> first_name;
	lastname >> last_name;

	name = first_name + " " + last_name;

	residents.push_back(name);
}

lastname.close();
lastname.open("E://CS 273//Final project//CS273 Final project//surnames_of_273ville.txt");

while (!firstname.eof())
{
	firstname >> first_name;
	lastname >> last_name;

	name = first_name + " " + last_name;

	residents.push_back(name);
}


cout << "__________________\nHOSPITAL SIMULATOR" << endl;

Hospital myhospital; //creates an Hospital object

myhospital.data(); //calls the function that allows the user to input data for the simulation

//10080
for (int clock = 0; clock < 10080; clock++)
{
	if (clock%myhospital.getArrival_rate() == 0) {
		emergency(myhospital, residents); //calls the emergency function that creates a new patient 
	}
	myhospital.Update(clock); //calls the update function that does all of the checking 
}

display_menu(myhospital); //displays the menu that the user can navagate

firstname.close();
lastname.close();

return 0;
}

void display_menu(Hospital& myhospital) // displays the menu to the user
{
	bool done = false;
	int response;
	int response2;
	do {
		//int response = 0;
		cout << "_______\nOPTIONS\n 0 - display a list of the names of all residents who were treated\n 1 - search for a specific resident" << endl;
		cin >> response;

		if (response == 0)
		{
			cout << "\nPatient's treated: " << myhospital.getRecord().size() << "\nServed by nurse: " << myhospital.getServed_by_nurse() << "\nServed by doctor: " << myhospital.getServed_by_doctor() << "\nAverage wait time: " << ((myhospital.getServed_by_nurse()*10)+(myhospital.getServed_by_doctor()*20))/ myhospital.getRecord().size() << " min" << endl;
			/*
			multimap<string, Patient*>::iterator it;
			for (it = myhospital.getRecord().begin(); it != myhospital.getRecord().end(); ++it)
			{
				cout << "\n";
				it->second->Display();
			}
			*/
		}
		else if (response == 1)
		{
			string f_name;
			string l_name;
			string name;
			cout << "Enter a FIRST name you would like to search: ";
			cin >> f_name;
			cout << "Now enter the LAST name: ";
			cin >> l_name;
			name = f_name + " " + l_name;
			if (myhospital.getRecord().count(name) == 0)
			{
				cout << "\n" << name << " never checked into the hospital or never finished treatment...";
			}
			else if (myhospital.getRecord().count(name) == 1)
			{
				myhospital.getRecord().find(name)->second->Display();
			}
			else
			{
				cout << "They entered more than once" << endl;
			}

		}
		cout << "\nWould you like to do something else? " << endl;
		cout << " 1 - yes\n 0 - no "<<endl;
		cin >> response2;
		if (response2 == 0)
			done = true;
		else 
		{
			response = NULL;
			response2 = NULL;
		}
	} while (!done);
}


void emergency(Hospital& h,vector<string> r) // is called when a a patienet is supposed to appear at the hospital and creates the patient
{
	//creates a patient object and assigns a random name from that list and gives it a priority, then sends to the queue
	int name_gen = rand() % r.size(); 
	cout << r[name_gen] << endl;
	Patient* p = new Patient(r[name_gen]);
	h.addPatient(p);
}