#include "Employee.h" // Defines class Employee
#include "Map.h"	  // Defines template Map<Key, Value>
#include "BookCard.h"
#include <iostream>

typedef unsigned int ID;			// Identification number of employee
typedef Map<ID, Employee> Database; // Database of employees
typedef Map<string, BookCard> Library;

using namespace std;

void testEmployeeExample();
void testLibraryExample();
void addEmployees(Database &database);
void modifyEmployees(Database &database);
void addBooks(Library &library);
void modifyBooks(Library &library);
void testExceptions(Library &library);

int main()
{
	testEmployeeExample();
	testLibraryExample();
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
	cout << "Modified database: (size = " << newDatabase.getSize() << ")" << endl
		 << newDatabase << endl;

	database = newDatabase; // Update original database

	cout << "Database after the assignment: (size = " << database.getSize() << ")" << endl
		 << database << endl;
}

void testLibraryExample()
{
	cout << "Library example" << endl;
	Library library;
	addBooks(library);

	Library newLibrary = library;
	BookCard book("Harry Potter", "J. K. Rowling", "Fantasy", 420, false);
	newLibrary.add(book.name, book);
	modifyBooks(newLibrary);

	cout << "Original library: (size = " << library.getSize() << ")" << endl
		 << library << endl;
	cout << "Modified library: (size = " << newLibrary.getSize() << ")" << endl
		 << newLibrary << endl;

	library = newLibrary;

	cout << "Library after the assignment: (size = " << library.getSize() << ")" << endl
		 << library << endl;

	testExceptions(library);
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

void addBooks(Library &library)
{
	BookCard book1("Mistborn", "Brandon Sanderson", "Fantasy", 520, false);
	library.add(book1.name, book1);
	BookCard book2("Lord of the rings", "Tolkien", "Fantasy", 650, true);
	library.add(book2.name, book2);
	BookCard book3("Disc World", "Terry Pratchet", "Sci-fi", 460, true);
	library.add(book3.name, book3);
	BookCard book4("Game of thrones", "George R. R. Martin", "Fantasy", 890, false);
	library.add(book4.name, book4);
}

void modifyBooks(Library &library)
{
	BookCard *bookPtr;
	bookPtr = library.find("Lord of the rings");
	bookPtr->author = "J. R. R. Tolkien";

	bookPtr = library.find("Disc World");
	bookPtr->category = "fantasy";
}

void testExceptions(Library &library)
{
	try
	{
		cout << "Test KeyNotFoundException" << endl;
		BookCard *bookPtr;
		bookPtr = library.find("Star Wars");
		bookPtr->borrowed = true;
		cout << "Test failed" << endl;
	}
	catch (Library::KeyNotFoundException &knfe)
	{
		cerr << knfe.what() << endl;
		cout << "Test succeded" << endl;
	}

	try
	{
		cout << "Test KeyAlreadyExists" << endl;
		BookCard book("Mistborn", "Brandon Sanderson", "Fantasy", 520, false);
		library.add(book.name, book);
		cout << "Test failed" << endl;
	}
	catch (Library::KeyAlreadyExistsException &kaee)
	{
		cerr << kaee.what() << endl;
		cout << "Test succeded" << endl;
	}
}