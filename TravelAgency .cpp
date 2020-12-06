#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<string>
#include<ctime>


using namespace std;

// Enums: states/type of objects
typedef enum  UserType { client, agent, manager } UserType;
typedef enum  Status { Canceled, in_process, Confirmed } Status;

//Structs: user defention
typedef struct User { int id = 0; string password; string userName; UserType type = client; } User;
//package and order defention
typedef struct Date { int day = 0; int month = 0; int year = 0; }Date; // date libary **
typedef struct Flight { string destanion = "none"; Date out; Date in; }Flight;
typedef struct Hotel { string name = "none"; string addres = "none"; }Hotel;
typedef struct Package { int id=0; Flight f; Hotel h; float rate = 0 ; int numOfRates = 0; float price = 0; int quantity = 0; } Package;
typedef struct Order { Date date; int packageId; Status status = in_process; int clientId; int agentId = 0; } Order; // redfine dfd - order approved only if agent accept
// other structs
typedef struct Request { int senderId; int agentId = 0; string content; } Request;
typedef struct Message { int senderId; int sentId; string content; }Message;
typedef struct Cupon { int cuponCode; int PackageId; float discount; int quantity; }Cupon; /// date or quantity 

// Operators: read/write to/from file
ostream& operator<<(ofstream& os, User& u);
istream& operator>>(ifstream& f, User& u);
istream& operator>>(ifstream& f, UserType& u);
//read/write to/from console
ostream& operator<<(ostream& os, User& u);
istream& operator>>(istream& f, User& u);
// Order
ostream& operator<<(ostream& os, Order& o);

// Features: 1.
bool logOrRegist();
bool userRegistration(UserType t);
bool login();
//2.
bool makeAnOrder(Package p);
//3.
bool search();

// Asisnt function: files
bool writeNewUserToFile(User& newClient);
void skipLines(ifstream& f, int n);
//others
string strUserType(UserType& u);
string strStatus(Status& s);
Date today();


User* user = nullptr; // The global logged user


//Main
int main()
{
	search();


}



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
	else if(d.day < dn.day)
		return false;

	return true;
}

bool writeNewUserToFile(User& newClient)
{
	ofstream f("UsersDB.txt",ios::app);
	f << newClient;
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
	User* newClient = new User;
	cout << "put the following details:" << endl;
	cin >> *newClient;
	newClient->type = t;

	// write the new cline to the DB
	writeNewUserToFile(*newClient);

	//login
	if (!user)
		user = newClient;

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
		{f.close(); return true; }
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
	{ cout << "not logged" << endl; logOrRegist(); }
	
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
	os << " Name: " << u.userName << endl;
	os << "Id: " << u.id << endl;
	return os;
}
istream& operator>>(istream& is, User& u)
{
	// getting the new user client details
	cout << "Id: ";
	is >> u.id;
	cout << "Password ";
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
	os << "Date: " << "dd.mm.yyyy"<< endl;
	os << "Client Id: " << o.clientId << endl;
	os << o.packageId << endl;
	os << "Order status: " << strStatus(o.status) << endl;
	return os;
		
}
ostream& operator<<(ofstream& f, Order& o)
{
	f << "dd.mm.yyyy" << endl;
	f << o.clientId << endl;
	f << "package details" << endl;
	f << o.status << endl;
	f << o.agentId << endl;
	return f;
}



