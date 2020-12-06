#include<iostream>
#include<fstream>
#include<string>
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
typedef struct Package { int id; Flight f; Hotel h; float rate; int numOfRates; float price; int quantity; } Package;
typedef struct Order { Date d; int packageId; Status s = in_process; int clientId; int agentId = 0; } Order; // redfine dfd - order approved only if agent accept
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

// Features: 1.
bool userRegistration(UserType t);
bool login();
//2.
bool makeAnOrder();

// Asisnt function: files
bool writeNewUserToFile(User& newClient);
User* readUserFromFile(ifstream& f);
void skipLines(ifstream& f, int n);
//others
string strUserType(User& u);


User* user = nullptr; // The global logged user


//Main
int main()
{
	
	login();
	cout << *user;
	
}



string strUserType(User& u)
{
	switch (u.type)
	{
	case client:
		return "Client";
	case agent:
		return "Agent";
	case manager:
		return "Manager";
	default:
		return "";
	}
}

User* readUserFromFile(ifstream& f)
{
	User* user = new User;
	f >> *user;
	return user;
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

bool makeAnOrder()
{
	// here we need to call the search function that will return the desierd package id
    // int packageId = searchPackage()
	int packId = 9999; // example...

	
	Order order = { Date(), packId, Status::in_process, user->id, 0 };
	return 1;
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
	if (user)
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
istream& operator>>(ifstream& f, UserType& u)
{
	int i;
	f >> i;
	u = UserType(i);
	return f;
}
ostream& operator<<(ostream& os, User& u)
{
	os << endl << strUserType(u);
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



