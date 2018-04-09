//requires employees.txt and timesheet.txt as input files

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

class EmployeeData
{
public:
	//EmployeeData();
	EmployeeData(int the_ID, double the_payrate, string the_name, int the_hours, EmployeeData* the_link);
	int getID() const;
	double getRate() const;
	string getName() const;
	void setData(int the_ID, double the_payrate, string the_name);
	void setHours(int the_hours);
	int getHours() const;
	EmployeeData* getLink() const;
	double getPay(double the_payrate, int the_hours);
	
private:
	int ID;
	double payrate;
	string name;
	int hours;
	EmployeeData* link;


};
//EmployeeData::EmployeeData():ID(0),payrate(0),name(""),link(NULL)
//{

//}
EmployeeData::EmployeeData(int the_ID, double the_payrate, string the_name, int the_hours, EmployeeData* the_link):ID(the_ID),payrate(the_payrate),name(the_name),hours(the_hours),link(the_link)
{


}
int EmployeeData::getID() const
{
	return ID;
}
double EmployeeData::getRate() const
{
	return payrate;
}
string EmployeeData::getName() const
{
	return name;
}
int EmployeeData::getHours() const
{
	return hours;
}

void EmployeeData::setData(int the_ID, double the_payrate, string the_name)
{
	ID = the_ID;
	payrate = the_payrate;
	name = the_name;

}
void EmployeeData::setHours(int the_hours)
{
	

	hours += the_hours;


}
EmployeeData* EmployeeData::getLink() const
 {
	return link;
	}
void head_insert(EmployeeData*& head, int the_ID, double the_payrate, string the_name, int the_hours)
{
	EmployeeData* temp_ptr;
		temp_ptr = new EmployeeData(the_ID, the_payrate, the_name, the_hours, head);
	head = temp_ptr;
}
double EmployeeData::getPay(double the_payrate, int the_hours)
{
	double pay;
	pay = the_payrate*the_hours;
	return pay;


}

int main()
{
	EmployeeData* head;
	EmployeeData* tmp;
	head = new EmployeeData(0, 0, "", 0, NULL);
	string filename;
	cout << "Please enter the filename containing the employee list (ex: employees.txt):";
	cin >> filename;
	ifstream employeeList;
	employeeList.open(filename);
	if (employeeList.fail())
	{
		cout << "File failed to open!";
		exit(1);
	}
	
	int tempID;
	double temprate;
	string tempname;
	int IDtemp, temphours;
	cout << "Please enter the filename containing the employee timesheet (ex:timesheet.txt):";
	cin >> filename;
	ifstream timeSheet;
	timeSheet.open(filename);
	if (timeSheet.fail())
	{
		cout << "File failed to open!";
		exit(1);
	}
	timeSheet >> IDtemp >> temphours;
	employeeList >> tempID;
	employeeList >> temprate;
	getline(employeeList, tempname);
	head_insert(head, tempID, temprate, tempname, temphours);
	
	
	while (employeeList >> tempID)
	{
		timeSheet >> IDtemp >> temphours;
		employeeList >> temprate;
		getline(employeeList, tempname);
		head_insert(head, tempID, temprate, tempname, temphours);
		EmployeeData *iter;
		for (iter = head; iter != nullptr; iter = iter->getLink()) {
			if (iter->getID() == IDtemp)
				iter->setHours(temphours);
		}
		
	}

	
	tmp = head;

	cout << "*********Payroll Information********" << endl;
	while (tmp->getLink()!= NULL)
	{
		

		//cout << "ID:" << tmp->getID() << endl;
		//cout << "Rate:" << tmp->getRate() << endl;
		cout << tmp->getName() << ",";
		//cout << "Hours:" << tmp->getHours() << endl;
		cout << " $" << tmp->getPay(tmp->getRate(), tmp->getHours()) << endl;
		
		tmp = tmp->getLink();
	}
	cout << "*********End payroll**************";
	tmp = head;
	while (tmp != NULL)
	{
		EmployeeData* nodeToDelete = tmp;
		tmp = tmp->getLink();
		delete nodeToDelete;
	}

	employeeList.close();
	timeSheet.close();
	
	return 0;
}