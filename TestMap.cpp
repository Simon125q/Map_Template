#include "Employee.h" // Defines class Employee
#include "Map.h"	  // Defines template Map<Key, Value>
#include <iostream>

typedef unsigned int ID;			// Identification number of employee
typedef Map<ID, Employee> Database; // Database of employees

using namespace std;

void testEmployeeExample();
void testLibraryExample();
void addEmployees(Database &database);
void modifyEmployees(Database &database);

int main()
{
	testEmployeeExample();
	return 0;
};

void testEmployeeExample()
{
	cout << "Employee example" << endl;

	Database database;
	addEmployees(database);

	Database newDatabase = database;									// Make a copy of database
	newDatabase.add(830505432, Employee("Ewa Nowak", "charwoman", 43)); // Add fourth employee
	modifyEmployees(newDatabase);

	cout << "Original database: (size = " << database.getSize() << ")" << endl
		 << database << endl;
	cout << "Modified database: (size = " << newDatabase.getSize() << ")" << endl << newDatabase << endl;

	database = newDatabase; // Update original database

	cout << "Database after the assignment: (size = " << database.getSize() << ")" << endl << database << endl;
}
void addEmployees(Database &database)
{
	database.add(761028073, Employee("Jan Kowalski", "salesman", 28));	// Add first employee: name: Jan Kowalski, position: salseman, age: 28,
	database.add(510212881, Employee("Adam Nowak", "storekeeper", 54)); // Add second employee
	database.add(730505129, Employee("Anna Zaradna", "secretary", 32)); // Add third employee
}

void modifyEmployees(Database &database)
{
	Employee *employeePtr;

	employeePtr = database.find(510212881); // Find employee using its ID
	employeePtr->position = "salesman";		// Modify the position of employee

	employeePtr = database.find(761028073); // Find employee using its ID
	employeePtr->age = 29;					// Modify the age of employee
}
