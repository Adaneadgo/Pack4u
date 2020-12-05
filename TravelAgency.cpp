#include<iostream>
#include<fstream>
#include<string>
using namespace std;


#define Separator " "
#define Size 20
typedef enum UserType { client, agent, manager } UserType;
typedef enum Status { Canceled, in_process, Confirmed } Status;

typedef struct User { string fullName; int id = 0; string email; string password; UserType type = client; } User;

typedef struct Date { int day = 0; int month = 0; int year = 0; }Date;
typedef struct Flight { string destanion = "none"; Date out; Date in; }Flight;
typedef struct Hotel { string name = "none"; string addres = "none"; }Hotel;
typedef struct Package { int id; Flight f; Hotel h; int rate; int numOfRates; int price; int quantity; } Package;

typedef struct Order { Date d; Package p; Status s = in_process; int clientId; int agentId = 0; } Order;

typedef struct Request { int senderId; int agentId; string content; } Request;
typedef struct Message { int senderId; int sentId; string content; }Message;
typedef struct Cupon { int cuponCode; int PackageId; float discount; int quantity; }Cupon;



ostream& operator<<(ostream& os, User* u);
ostream& operator<<(ofstream& os, User* u);
istream& operator>>(istream& f, User* u);
istream& operator>>(ifstream& f, User* u);

string strUserType(User* u);

bool userRegistration(UserType t);
bool login();

bool writeNewUserToFile(User* newClient);
User* readUserFromFile(ifstream& f);
void skipLine(ifstream& f, int n, char ch);
bool trackUser(ifstream& f, int id, string password);

// the global logged user
User* user = nullptr;


//Main
int main()
{
	userRegistration(client);
	userRegistration(client);
	userRegistration(agent);
	userRegistration(agent);
	cout << user << endl;


}


bool userRegistration(UserType t)
{
	// create the new user
	User* newClient = new User;
	cout << "put the following details:" << endl;
	cin >> newClient;
	newClient->type = t;

	// write the new cline to the DB
	writeNewUserToFile(newClient);

	//login
	user = newClient;

	//if everything went well
	return true;

}
bool login()
{

	// function looks bad need to be fixes!
	int id;
	string password;
	cout << "please put your id: ";
	cin >> id;
	cout << "please put you password: ";
	cin >> password;

	ifstream f;

	f.open("ClientsDB.txt");
	if (trackUser(f, id, password))
	{
		user = readUserFromFile(f);
		f.close();
		user->type = client;
		return true;
	}

	f.close();

	f.open("AgentsDB.txt");
	if (trackUser(f, id, password))
	{
		user = readUserFromFile(f);
		user->type = agent;
		f.close();
		return true;
	}
	f.close();
	cout << "Id, password or both Incorrect" << endl;
	return false;
}


User* readUserFromFile(ifstream& f)
{
	User* user = new User;
	f >> user;
	return user;
}
bool writeNewUserToFile(User* newClient)
{
	ofstream f;

	if ((newClient->type) == client)
		f.open("ClientsDB.txt", ios::app);
	else if ((newClient->type) == agent)
		f.open("AgentsDB.txt", ios::app);

	f << newClient;
	f.close();
	return 1;
}
void skipLine(ifstream& f, int n, char ch)
{
	for (int i = 0; i < n; i++)
		f.ignore(numeric_limits<streamsize>::max(), ch);
}
bool trackUser(ifstream& f, int id, string password)
{
	string input;
	streampos pos = f.tellg();

	while (f >> input)
	{
		if (input == to_string(id))
		{
			f >> input;
			if (input == password)
			{
				f.seekg(pos);
				return true;
			}
		}
		skipLine(f, 1, '\n');
		pos = f.tellg();
	}
	return false;
}


string strUserType(User* u)
{
	switch (u->type)
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

ostream& operator<<(ostream& os, User* u)
{
	os << endl << strUserType(u);
	os << " Name: " << u->fullName << endl;
	os << "Id: " << u->id << endl;
	os << "Email: " << u->email << endl;

	return os;
}
ostream& operator<<(ofstream& f, User* u)
{
	f << u->id << Separator;
	f << u->password << Separator;
	f << u->fullName << Separator;
	f << u->email << endl;
	return f;
}
istream& operator>>(istream& is, User* u)
{
	// getting the new user client details
	cout << "put your id please: ";
	is >> u->id;
	cout << "please put you new password ";
	is >> u->password;
	cout << "put your full name please: ";
	is >> u->fullName;
	cout << "put your email please ";
	is >> u->email;
	return is;
}
istream& operator>>(ifstream& f, User* u)
{
	f >> u->id;
	f >> u->password;
	f >> u->fullName;
	f >> u->email;
	return f;
}
