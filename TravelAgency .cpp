#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<string>
#include<ctime>


using namespace std;

//Enums: states/type of objects
typedef enum  UserType { client, agent, manager } UserType;
typedef enum  Status { Canceled, in_process, Confirmed } Status;

//Structs: user defention
typedef struct User { int id = 0; string password; string userName; UserType type = client; } User;
//Package and order defention
typedef struct Date { int day = 0; int month = 0; int year = 0; }Date; // date libary **
typedef struct Flight { string destanion = "none"; Date out; Date in; }Flight;
typedef struct Hotel { string name = "none"; string addres = "none"; }Hotel;
typedef struct Package { int id = 0; Flight f; Hotel h; float rate = 0; int numOfRates = 0; float price = 0; int quantity = 0; } Package;
typedef struct Order { Date date; int packageId; Status status = in_process; int clientId; int agentId = 0; } Order; // redfine dfd - order approved only if agent accept
//Other structs
typedef struct Request { int senderId; int agentId = 0; string content; } Request;
typedef struct Message { int senderId; int sentId; string content; }Message;
typedef struct Cupon { int cuponCode; float discount; Date expiry; }Cupon; /// date or quantity 

// Operators: read/write to/from file
//User
ostream& operator<<(ofstream& os, User& u);
istream& operator>>(ifstream& f, User& u);
istream& operator>>(ifstream& f, UserType& u);
//Date
ostream& operator<<(ofstream& f, Date& d);
istream& operator<<(ifstream& f, Date& d);

//Read/write to/from console
//User
ostream& operator<<(ostream& os, User& u);
istream& operator>>(istream& is, User& u);
// Order
ostream& operator<<(ostream& os, Order& o);
//Date
ostream& operator<<(ostream& os, Date& d);
istream& operator>>(istream& is, Date& d);
//Features: 1.
bool logOrRegist();
bool userRegistration(UserType t);
bool login();
//2.
bool makeAnOrder(Package p);
//3.
bool search();
//Asisnt function: files
bool writeNewUserToFile(User& newUser);
void skipLines(ifstream& f, int n);
//Others
string strUserType(UserType& u);
string strStatus(Status& s);
Date today();
void agentMenu();


User* user = nullptr; // The global logged user

string strUserType(UserType& t)
{
	switch (t)
	{
	case client:
		return "Client";
	case agent:
		return "Agent";
	case manager:
		return "The Manager";
	default:
		return "";
	}
}
string strStatus(Status& s)
{
	switch (s)
	{
	case Canceled:
		return "Canceled";
	case in_process:
		return "in process";
	case Confirmed:
		return "Confirmed";
	default:
		return "";
	}
}
Date today()
{
	time_t t = time(NULL);
	tm time = *localtime(&t);
	Date d = { time.tm_mday,time.tm_mon + 1,time.tm_year + 1900 };
	return d;
}
bool isDateVaild(Date d)
{
	Date dn = today();
	if (d.year < dn.year)
		return false;
	else if (d.month < dn.month)
		return false;
	else if (d.day < dn.day)
		return false;

	return true;
}
bool writeNewUserToFile(User& newUser)
{
	ofstream f("UsersDB.txt", ios::app);
	f << newUser;
	f.close();
	return 1;
}
void skipLines(ifstream& f, int n)
{
	for (int i = 0; i < n; i++)
		f.ignore(numeric_limits<streamsize>::max(), '\n');
}
bool logOrRegist()
{

	int input;
	do {
		cout << "please select:" << endl;
		cout << "1. Login" << endl << "2. Regist" << endl;
		cin >> input;

		if (input == 1)
			login();
		if (input == 2)
			userRegistration(client);

	} while (input != 1 && input != 2);

	return user != nullptr;

}
bool userRegistration(UserType t)
{
	// create the new user
	User* newUser = new User;
	cout << "put the following details:" << endl;
	cin >> *newUser;
	newUser->type = t;

	// write the new cline to the DB
	writeNewUserToFile(*newUser);

	//login
	if (!user)
		user = newUser;

	//if everything went well
	return true;

}
bool login()
{
	int id;
	string password;
	cout << "please put your id: ";
	cin >> id;
	cout << "please put you password: ";
	cin >> password;

	user = new User;

	ifstream f("UsersDB.txt");
	while (f >> *user)
	{
		if (user->id == id && user->password == password)
		{
			f.close(); return true;
		}
	}

	f.close();
	delete user;
	return false;
}
bool search()
{
	// search package need to writen.

	Package p;
	makeAnOrder(p);
	return true;

}
bool makeAnOrder(Package p)
{
	if (!user)
	{
		cout << "not logged" << endl; logOrRegist();
	}
	Order order = { today(), p.id, in_process, user->id, 0 };
	cout << endl << "Summary: " << order << endl << "{package details}" << endl;
	ofstream f("Orders");
	return 1;
}
ostream& operator<<(ofstream& f, User& u)
{
	f << u.id << endl;
	f << u.password << endl;
	f << u.userName << endl;
	f << int(u.type) << endl;
	return f;
}
istream& operator>>(ifstream& f, User& u)
{
	f >> u.id;
	f >> u.password;
	f >> u.userName;
	f >> u.type;
	return f;
}
ostream& operator<<(ostream& os, User& u)
{
	os << endl << strUserType(u.type);
	os << "Name: " << u.userName << endl;
	os << "Id: " << u.id << endl;
	return os;
}
istream& operator>>(istream& is, User& u)
{
	// getting the new user client details
	cout << "Id: ";
	is >> u.id;
	cout << "Password: ";
	is >> u.password;
	cout << "UserName: ";
	is >> u.userName;
	return is;
}
istream& operator>>(ifstream& f, UserType& u)
{
	int i;
	f >> i;
	u = UserType(i);
	return f;
}
ostream& operator<<(ostream& os, Order& o)
{
	os << "Date: " << o.date << endl;
	os << "Client Id: " << o.clientId << endl;
	os << o.packageId << endl;
	os << "Order status: " << strStatus(o.status) << endl;
	return os;

}
ostream& operator<<(ofstream& f, Order& o)
{
	f << o.date << endl;
	f << o.clientId << endl;
	f << "Package details: " << endl;
	f << o.status << endl;
	f << o.agentId << endl;
	return f;
}
ostream& operator<<(ostream& os, Date& d)
{
	os << d.day << ".";
	os << d.month << ".";
	os << d.year << endl;
	return os;
}
istream& operator>>(istream& is, Date& d)
{
	is >> d.day;
	is >> d.month;
	is >> d.year;
	return is;
}
ostream& operator<<(ofstream& f, Date& d)
{
	f << d.day << ".";
	f << d.month << ".";
	f << d.year << endl;
	return f;
}
istream& operator<<(ifstream& f, Date& d)
{
	char dot;//for save dot
	f >> d.day;
	f >> dot;
	f >> d.month;
	f >> dot;
	f >> d.year;
	return f;
}
ostream& operator<<(ostream& os, Cupon& c)
{
	os << "Cupon code: " << c.cuponCode << endl;
	os << "Discount amount: " << c.discount << endl;
	os << "Expiry date: " << c.expiry << endl;
	return os;
}
istream& operator>>(istream& is, Cupon& c)
{
	cout << "Hello manager, please enter code for discount (4 digits): " << endl;
	is >> c.cuponCode;
	cout << "Please enter discount amount: " << endl;
	is >> c.discount;
	cout << "Enter day, month and year for expiry date: " << endl;
	is >> c.expiry;
	return is;
}
// write the new cline to the DB
//writeNewUserToFile(&newUser);
//Agent menu
void agentMenu()
{
	int choice;
	do {
		cout << "\n\n\t1.View packages";
		cout << "\n\n\t2.View client";
		cout << "\n\n\t3.Message box";
		cout << "\n\n\t4.Exit";

		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "\n\n\tEmail: pack4u@mail.com\n\tPhone: 1-700-800-800";
			break;

		case 2:
			//call login register func
			break;
		case 3:
			break;

		default:
			cout << "\n\n\tTRY AGAIN";
			break;
		}
	} while (choice != 4);
}
//Manger menu
void managerMenu()
{
	int choice;
	do {
		cout << "\n\n\t1.View Agent Options";
		cout << "\n\n\t2.View agents";
		cout << "\n\n\t3.Add an agent";
		cout << "\n\n\t4.Remove an agent";
		cout << "\n\n\t5.Creat discount";
		cout << "\n\n\t6.Exit" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1: agentMenu();
			break;

		case 2:
			//call login register func
			break;

		default:
			cout << "\n\n\tTRY AGAIN";
			break;
		}
	} while (choice != 3);
}
void addAgent()
{

}


//Main
int main()
{
	managerMenu();

}


