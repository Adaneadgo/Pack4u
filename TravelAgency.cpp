#include<iostream>
#include<fstream>
#include<string>
using namespace std;


#define Separator " "
#define Size 20
typedef enum class UserType { client, agent, manager } UserType;
typedef enum class Status { Canceled, in_process, Confirmed } Status;

typedef struct User { int id = 0; string password; string userName; UserType type = UserType::client; } User;

typedef struct Date { int day = 0; int month = 0; int year = 0; }Date;
typedef struct Flight { string destanion = "none"; Date out; Date in; }Flight;
typedef struct Hotel { string name = "none"; string addres = "none"; }Hotel;
typedef struct Package { int id; Flight f; Hotel h; int rate; int numOfRates; int price; int quantity; } Package;

typedef struct Order { Date d; Package p; Status s = Status::in_process; int clientId; int agentId = 0; } Order;

typedef struct Request { int senderId; int agentId; string content; } Request;
typedef struct Message { int senderId; int sentId; string content; }Message;
typedef struct Cupon { int cuponCode; int PackageId; float discount; int quantity; }Cupon;



ostream& operator<<(ostream& os, User& u);
ostream& operator<<(ofstream& os, User& u);
istream& operator>>(istream& f, User& u);
istream& operator>>(ifstream& f, User& u);
istream& operator>>(ifstream& f, UserType& u);

string strUserType(User& u);

bool userRegistration(UserType t);
bool login();

bool writeNewUserToFile(User& newClient);
User* readUserFromFile(ifstream& f);
void skipLines(ifstream& f, int n);


// the global logged user
User* user = new User;


//Main
int main()
{
	//EXAMPLE

	// register and auto log in if no user is loged
	userRegistration(UserType::client);
	userRegistration(UserType::agent);
	
	//login auto recognize user type
	login();


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

	ifstream f("UsersDB.txt");
	while (f >> *user)
	{
		if (user->id == id && user->password == password);
		{f.close(); return true; }
	}
	f.close();
	return false;
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

string strUserType(User& u)
{
	switch (u.type)
	{
	case UserType::client:
		return "Client";
	case UserType::agent:
		return "Agent";
	case UserType::manager:
		return "Manager";
	default:
		return "";
	}
}

ostream& operator<<(ostream& os, User& u)
{
	os << endl << strUserType(u);
	os << " Name: " << u.userName << endl;
	os << "Id: " << u.id << endl;
	return os;
}
ostream& operator<<(ofstream& f, User& u)
{
	f << u.id << endl;
	f << u.password << endl;
	f << u.userName << endl;
	f << int(u.type) << endl;
	return f;
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


