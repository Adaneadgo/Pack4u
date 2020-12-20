/*
   Welcome to Pack4U Project, This is a Travel Agency program that is not use any class in it.
   To properly use this code you need to download the .wav files and place them inside your folder where the .cpp of this code is located.
   If you not gonna make it the code will crash and ask you for audio files, so make sure you have download all 5 .wav files.
   This files located in out github and can be found here: https://github.com/SCE2020Team2/yesodot
   In folder: "Audio for us".
*/
#pragma comment(lib, "winmm.lib")
#define _CRT_SECURE_NO_WARNINGS
#define RED "\033[1;31m" //color red
#define GREEN "\033[1;32m" //color green
#define YELLOW "\033[1;33m" //color yellow
#define BLUE "\033[1;34m" //color blue
#define PINK "\033[1;35m" //color pink
#define MAGENTA "\033[1;36m" //color magenta
#define WHITE "\033[0m"    //color reset to white
#define BLOCKCOLOR "\033[1;100;30m" //block of color
#include<iostream>
#include<fstream>
#include<string>
#include<ctime>
#include<vector>
#include <windows.h>
#include <mmsystem.h>
#include <stdlib.h>

#define goodRate 4

using namespace std;

// Enums: states and types of objects
typedef enum  UserType { client, agent, manager } UserType;
typedef enum  Status { Canceled, in_process, Confirmed } Status;

//Structs: user defention
typedef struct User { int id = 0; string password; string userName; UserType type = client; } User;
//package and order defention
typedef struct Date { int day = 0; int month = 0; int year = 0; }Date; // date libary **
typedef struct Flight { string destination = "none"; }Flight;
typedef struct Hotel { string name = "none"; string address = "none"; }Hotel;
typedef struct Package { Date out; Date in; string id = "NONE00"; Flight f; Hotel h; float rate = 0; int numOfRates = 0; float price = 0; int quantity = 0; } Package;
typedef struct Order { int id = 999;  Date date; string packageId = "NONE00"; Status status = in_process; int clientId = 0; int agentId = 0; bool rated = false; } Order;
// other structs
typedef struct Message { Date d; string sender;; UserType to = client; string message = "none"; }Message;
typedef struct Coupon { int couponCode = 0; float discount = 1; Date expiry; }Cupon;

// Operators: I/O stream - user
ostream& operator<<(ofstream& os, User& u);
istream& operator>>(ifstream& f, User& u);
ostream& operator<<(ostream& os, User& u);
istream& operator>>(istream& f, User& u);
// Order
ostream& operator<<(ostream& os, Order& o);
ostream& operator<<(ofstream& f, Order& o);
istream& operator>>(ifstream& f, Order& o);
//date
ostream& operator<<(ofstream& f, Date& d);
istream& operator>>(ifstream& f, Date& d);
ostream& operator<<(ostream& os, Date& d);
istream& operator>>(istream& is, Date& d);
//package
ostream& operator<<(ostream& os, Package& p);
ofstream& operator<<(ofstream& f, Package& p);
istream& operator>>(istream& is, Package& p);
ifstream& operator>>(ifstream& f, Package& p);
//cupon
ostream& operator<<(ostream& os, Coupon& c);
istream& operator>>(istream& is, Coupon& c);
ostream& operator<<(ofstream& f, Coupon& c);
istream& operator>>(ifstream& f, Coupon& c);


//message
ostream& operator<<(ostream& os, Message& p);
istream& operator>>(istream& is, Message& p);
ostream& operator<<(ofstream& f, Message& m);
istream& operator>>(ifstream& f, Message& m);
//others
istream& operator>>(ifstream& f, UserType& u);
istream& operator>>(ifstream& f, Status& u);


//other operators
bool operator<(Date& d1, Date& d2);
bool operator==(Date& d1, Date& d2);


// Data base
bool writeNewUserToFile(User& newClient);
bool writeNewMessageFromClientToFile(Message& newMessage);
bool writeNewMessageFromManegerToFile(Message& newMessage);
bool writeNewPackageToFile(Package& newPackage);

// Features: 
bool logOrRegist();
bool userRegistration(UserType t);
bool login();
bool makeAnOrder(Package& p);
bool paymentSystem(float price);

bool trackOrder(vector<Order>& arr);
bool viewClientOrders();
bool cancelAnOrder(vector<Order>& o_arr, int orderId);
bool approveOrder(vector<Order>& o_arr, int orderId);
bool rateByOrder(vector<Order>& o_arr, int orderId);
bool rateApackage(Package& r);


bool addPackage(vector<Package>& arr);
bool updatePackage(Package& p);
bool removePackage(vector<Package>& arr, string id);
bool trackPackages(vector<Package>& arr);
bool selectPackageByClient();


void showMessagesFromClient();
void showMessagesFromManeger(UserType t);

bool clientMessageBox();
bool agentMessageBox();
bool requestsFromClient();


bool removeUser(UserType t);

bool manageClientsDB();
bool manageOrdersDB();
bool managePackagesDB();


bool creatCoupon();
float readCoupon(int code);


//others
string strUserType(UserType& u);
string strStatus(Status& s);
Date today();

User* user = nullptr; // The global logged user

void managerMenu();
void agentMenu();
void clientMenu();
void mainMenu();
void aboutus();
void intro();
void logo();


string enc(string s);
string dec(string s);

//Main
int main()
{
	intro();
	mainMenu();

}

string enc(string s)
{
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == '\n')
			continue;
		s[i] += 1;
	}
	return s;
}
string dec(string s)
{
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == '\n')
			continue;
		s[i] -= 1;
	}
	return s;
}


void aboutus()
{
	//about us info

	cout << "\n\n\tPack4U has been committed to bringing our clients the best in value and quality travel arrangements.";
	cout << "\n\tWe are passionate about travel and sharing the world's wonders on the leisure travel side.";
	cout << "\n\tWe hope you have a great time with out software.";

	int choice;
	do {
		cout << "\n\n\tfor more options:\n\t[1] See contact information\n\t[0] Back to the main menu\n\n\t";
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "\n\n\tEmail: pack4u@mail.com\n\tPhone: 1-700-800-800";
			break;

		case 0:
			break;

		default:
			cout << "\n\n\tTRY AGAIN";
			break;
		}
	} while (choice != 0);

}
void mainMenu()
{

	////Menu for visitors and unregistered users

	int num, ch;
	do
	{
		system("cls");
		logo();
		cout << "\n\n\t[1] View packages";
		cout << "\n\n\t[2] Login/Register";
		cout << "\n\n\t[3] About Us";
		cout << "\n\n\t[0] EXIT";
		cout << "\n\n\tSelect Your Option [0-3] " << endl;;
		cin >> ch;
		system("cls");
		switch (ch)
		{
		case 1:
			selectPackageByClient();
			break;
		case 2:
			logOrRegist();

			if (user)
			{
				switch (user->type)
				{
				case client:
					clientMenu();
					break;

				case agent:
					agentMenu();
					break;

				case manager:
					managerMenu();
					break;
				}
			}
			break;
		case 3:
			aboutus();
			break;
		case 0:
			cout << "\n\n\tThanks for using our system";
			break;
		default:
			cout << "Bad input! Try again" << endl << endl;
		}
	} while (ch != 0);


}
void clientMenu()
{
	///menu for registered clients

	Message m;
	int choice;
	do {
		cout << "\n\n\tPress [1] to view packages";
		cout << "\n\n\tPress [2] to contact us";
		cout << "\n\n\tPress [3] to my order and rate";
		cout << "\n\n\tPress [4] to my Message box";
		cout << "\n\n\tPress [0] to exit" << endl;
		cin >> choice;
		system("cls");
		switch (choice)
		{
		case 0:
			break;
		case 1:
			selectPackageByClient();
			break;
		case 2:
			cout << "\n\n\tPlease start your message with phone number" << endl;
			cin >> m;
			writeNewMessageFromClientToFile(m);
			break;
		case 3:
			viewClientOrders();
			break;
		case 4:
			showMessagesFromManeger(client);
			break;
		default:
			cout << "\n\n\tTRY AGAIN";
			break;
		}
	} while (choice != 0);

}
void agentMenu()
{
	/// Menu for registered agents

	int choice;
	do {
		cout << "\n\n\tPress [1] to Manage clients DB";
		cout << "\n\n\tPress [2] to Manage orders DB";
		cout << "\n\n\tPress [3] to Mangae packages DB";
		cout << "\n\n\tPress [4] to Message box";
		cout << "\n\n\tPress [5] to Clients requests";
		cout << "\n\n\tPress [0] to Exit";
		cin >> choice;
		system("cls");
		switch (choice)
		{
		case 1:
			manageClientsDB();
			break;
		case 2:
			manageOrdersDB();
			break;
		case 3:
			managePackagesDB();
			break;
		case 4:
			showMessagesFromManeger(agent);
			break;
		case 5:
			requestsFromClient();
			break;
		default:
			cout << "\n\n\tTRY AGAIN";
			break;
		}
	} while (choice != 0);
}
void managerMenu()
{

	/// Menu for managers

	int choice;
	Message m;

	do {
		cout << "\n\n\tPress [1] to View Agent Options";
		cout << "\n\n\tPress [2] to Add an agent";
		cout << "\n\n\tPress [3] to Remove an agent";
		cout << "\n\n\tPress [4] to Create discount coupon and send to clients";
		cout << "\n\n\tPress [5] to Send a general message to all agents";
		cout << "\n\n\tPress [6] Load the system Administrator only!";
		cout << "\n\n\tPress [0] to Exit" << endl;
		cin >> choice;
		system("cls");
		switch (choice)
		{
		case 0:
			break;
		case 1: agentMenu();
			break;

		case 2:
			cout << "Please add the new agent details" << endl;
			userRegistration(agent);
			break;

		case 3: removeUser(agent);
			break;

		case 4: creatCoupon();
			break;

		case 5:
			cin >> m;
			m.to = agent;
			writeNewMessageFromManegerToFile(m);
			break;

		case 6:

			//////////
			break;
		default:
			cout << "\n\n\tTRY AGAIN";
			break;
		}
	} while (choice != 0);
}

bool userRegistration(UserType t)
{
	// Allocate and create the new user
	User* newUser = new User;
	cout << "put the following details:" << endl;
	cin >> *newUser;
	newUser->type = t; // asaing the type


	// Write the new user to the DB
	if (!writeNewUserToFile(*newUser))
	{
		cout << "\n\tUser already exists! Registeration failed\n";

		return false;
	}

	//If no user been logged- login the new user
	if (!user)
		user = newUser;

	//If everything went well
	return true;

}
bool login()
{

	int id; // User's details needed to signed in
	string password;
	cout << "please put your id: ";
	cin >> id;
	cout << "please put you password: ";
	cin >> password;

	// Create the new login to the system
	user = new User;

	// Open the users DB to find a match
	ifstream f("UsersDB.txt");
	while (f >> *user)
	{
		if (user->id == id && user->password == password)
		{
			cout << endl << "Hello " << strUserType(user->type) << ": " << user->userName << endl;
			f.close();
			return true;
		}
	}

	// If no match been found, delete the allocation and close
	f.close();
	delete user;

	cout << "\n\tUser not found! login failed.\n";

	return false;
}
bool logOrRegist()
{
	// If no user is logged and login or register is needed!
	// User will have to select login or register to proceed
	int input;
	do {
		cout << "\n\n\tplease select:" << endl;
		cout << "\n\n\t[1] Login" << "\n\n\t[2] Register" << endl;
		cin >> input;

		if (input == 1)
			login();
		if (input == 2)
			userRegistration(client);

	} while (input != 1 && input != 2);

	// Return true if the log has been successful
	return user != nullptr;

}
bool makeAnOrder(Package& p)
{
	// If user is not logged in, they are asked to either create a new account or login to an existing one
	while (!user)
	{
		cout << "\n\tPlease register or login to an existing account:\n";

		if (logOrRegist())
			return false;


	}

	//// Counting number of orders to create a new order id

	Order o;
	int i = 0;
	ifstream of("OrdersDB.txt");
	while (of >> o)
	{
		i++;
	}
	of.close();



	// Details are entered automatically
	Order order = { 1000 + i,today(), p.id, in_process, user->id, 0 };
	cout << endl << "Summary" << endl << order << endl << p << endl;

	// Send user to payment
	paymentSystem(p.price);

	ifstream fa("PackagesDB.txt");
	Package pa;

	vector<Package> arr;
	while (fa >> pa)
	{
		if (pa.id == p.id)
			pa.quantity--;

		arr.push_back(pa);

	}
	fa.close();

	ofstream ff("PackagesDB.txt");

	for (int i = 0; i < arr.size(); ++i)
		ff << arr[i];


	ff.close();

	--p.quantity;   //Package quantity reduced

	// Enter the new order to the orders DB
	ofstream f("OrdersDB.txt", ios::app);
	f << order;
	f.close();

	PlaySound(TEXT("notification03.wav"), NULL, SND_FILENAME | SND_ASYNC);

	return 1;
}
bool paymentSystem(float price)
{

	//Here a payment is made and discount is calculated in final price

	int code;
	string card;
	float discount = 1;

	cout << "Payment system" << endl;
	cout << "put your coupon code if you have one" << endl;
	cin >> code;

	discount = readCoupon(code);

	cout << "please put you credit card details:" << endl << "[xxxxxxxx]  [mm/yy]  [cvc]" << endl;
	cin >> card;
	cout << "Total price: " << price * discount << "$" << endl;
	return 1;


}

bool addPackage(vector<Package>& arr)
{

	/// Adding package to package DB

	if (!user || user->type == client)
		return false;

	Package newPackage;
	cout << "put the following details: " << endl;
	cin >> newPackage;

	arr.push_back(newPackage);

	//if everything went well
	return true;
}
bool updatePackage(Package& p)
{


	// Editing an existing package in the package DB


	cout << "Put the new details to the package" << endl;

	char ch;
	do
	{
		cout << "Include flight? Y/N" << endl;
		cin >> ch;
		if (ch == 'Y')
		{
			cout << "Enter flight destination: ";
			cin >> p.f.destination;

			cout << "Enter flight departure date:" << endl;
			cin >> p.out;
			do {
				cout << "Enter flight return date:" << endl;
				cin >> p.in;
				if (p.in < p.out)
					cout << endl << "Return date is before departure date, try again!" << endl << endl;
			} while (p.in < p.out);

		}
		else if (ch == 'N')
		{
			p.f.destination = "none";

			p.out = { 0,0,0 };

			p.in = { 0,0,0 };
			break;
		}
		else
			cout << "Bad input! Try again." << endl;
	} while (ch != 'Y');

	do
	{
		cout << "Include hotel? Y/N" << endl;
		cin >> ch;
		if (ch == 'Y')
		{
			cout << "Hotel name: ";
			cin >> p.h.name;

			cout << "Hotel address: ";
			cin >> p.h.address;

		}
		else if (ch == 'N')
		{
			p.h.name = "none";
			p.h.address = "none";

			break;
		}
		else
			cout << "Bad input! Try again." << endl;

	} while (ch != 'Y');

	cout << "Enter package price: ";
	cin >> p.price;

	cout << "Enter package quantity: ";
	cin >> p.quantity;

	return true;
}
bool removePackage(vector<Package>& arr, string id)
{

	// Removing an existing package in package DB

	for (int i = 0; i < arr.size(); i++)
	{
		if (arr[i].id == id)
			arr.erase(arr.begin() + i, arr.begin() + i + 1);
	}
	return 1;
}
bool trackPackages(vector<Package>& arr)
{

	// Here the user sorts packages to view by presented categories

	int ch;
	Package p;
	string dest;
	int min, max;
	Date date;

	do
	{

		cout << "\n\tPress [1] to sort by destination" << endl;
		cout << "\n\tPress [2] to sort by price range" << endl;
		cout << "\n\tPress [3] to sort by departure date" << endl;
		cout << "\n\tPress [4] to Popular Packages" << endl;
		cout << "\n\tPress [0] to Exit" << endl << endl;
		cin >> ch;

		switch (ch)
		{

		case 1:
			cout << "Enter destination: ";
			cin >> dest;

			for (int i = 0; i < arr.size(); i++)
			{
				if (arr[i].f.destination == dest)
					cout << arr[i] << endl;
			}
			break;

		case 2:
			cout << "Enter the minimum price: ";
			cin >> min;
			cout << "Enter the max price: ";
			cin >> max;

			for (int i = 1; i < arr.size(); i++)
			{
				if ((arr[i].price > min) && (arr[i].price < max))
					cout << arr[i] << endl;
			}
			break;

		case 3:
			cout << "Enter requested departure date: ";
			cin >> date;

			for (int i = 1; i < arr.size(); ++i)
				if (arr[i].out == date)
					cout << arr[i] << endl;
			break;


		case 4:
			for (int i = 0; i < arr.size(); ++i)
			{
				if (arr[i].rate >= goodRate)
					cout << arr[i] << endl;
			}
			break;

		case 0:
			break;

		default:
			cout << "Wrong key!" << endl;
			break;
		}

	} while (ch);

	return 1;
}
bool selectPackageByClient()
{

	// Here the user can view packages and order them


	vector<Package> arr;
	Package p;
	string packId;
	int ch;


	ifstream f("PackagesDB.txt");
	while (f >> p)
	{

		if (p.quantity > 0)
		{
			arr.push_back(p);
			cout << endl << p << endl;
		}
	}
	f.close();

	do
	{


		cout << "\n\tPress [1] to make an order" << endl;
		cout << "\n\tPress [2] to sort the packages" << endl;
		cout << "\n\tpress [0] to return" << endl;
		cin >> ch;



		switch (ch)
		{



		case 1:
			cout << "Put the package id" << endl;
			cin >> packId;

			for (int i = 0; i < arr.size(); i++)
			{
				if (arr[i].id == packId)
				{
					makeAnOrder(arr[i]);
					return 1;

				}
			}
			break;

		case 2:
			trackPackages(arr);
			break;

		case 0:
			break;

		default:
			cout << "Wrong key!" << endl;
			break;
		}



	} while (ch != 0);

	return 1;
}

bool trackOrder(vector<Order>& arr)
{

	// Here the user can sort existing orders

	Date d;
	string packId;
	Status s;


	int userChoise;

	do {
		cout << "\n\tView Orders By:" << endl;
		cout << "\n\tPress [1] to sort by date" << endl << "\n\tPress [2] to sort by package" << endl;
		cout << "\n\tPress [3] to sort by status" << endl << "\n\tPress [0] to return" << endl;
		cin >> userChoise;

		switch (userChoise)
		{
		case 1:
			cout << "Enter the date:" << endl;
			cin >> d;
			for (int i = 0; i < arr.size(); i++)
			{
				if ((arr[i].date == d) && (arr[i].agentId == user->id))
					cout << arr[i] << endl << endl;
			}
			break;
		case 2:
			cout << "Enter the Package id" << endl;
			cin >> packId;

			for (int i = 0; i < arr.size(); i++)
			{
				if ((arr[i].packageId == packId) && (arr[i].agentId == user->id))
					cout << arr[i] << endl << endl;
			}

			break;
		case 3:

			cout << "\n\tSelect the status: ";
			cout << "\n\tPress [1] to 'Canceld'" << "\n\tPress [2] to 'In Processes'" << "\n\tPress [3] to 'Approved'" << endl;
			cin >> userChoise;
			s = Status(userChoise - 1);
			for (int i = 0; i < arr.size(); i++)
			{
				if ((arr[i].status == s) && (arr[i].agentId == user->id))
					cout << arr[i] << endl << endl;
			}
			break;

		case 0:
			break;

		default:
			cout << "Wrong key!" << endl;
			break;
		}

	} while (userChoise != 0);

	return 1;
}
bool viewClientOrders()
{


	// Here the user can watch their orders and rate it, after being approved, only once!

	int pId;
	char ch;


	Order temp;
	vector<Order> arr;
	ifstream f("OrdersDB.txt");
	while (f >> temp)
	{
		arr.push_back(temp);
	}

	for (int i = 0; i < arr.size(); i++)
	{
		if (arr[i].clientId == user->id)
			cout << endl << arr[i] << endl;
	}



	do {

		cout << "Rate an package Y/N" << endl;
		cin >> ch;

		switch (ch)
		{

		case 'Y':
			cout << "Your approved orders: " << endl;

			int i;

			for (i = 0; i < arr.size(); i++)
			{
				if (arr[i].clientId == user->id && arr[i].status == Confirmed)
					cout << arr[i] << endl;
			}

			if (i)
			{
				cout << "Enter the order id" << endl;
				cin >> pId;

				rateByOrder(arr, pId);
			}
			else
				cout << "No approved orders to rate!" << endl;

		}
		break;


	} while (ch != 'Y' && ch != 'N');

	return 1;

}
bool cancelAnOrder(vector<Order>& arr, int orderId)
{
	// Here the user can cancel an existing order, it cannot be approved after being cancelled!
	// A new order will be required

	string packId = "NONE00";
	Package p;

	for (int i = 0; i < arr.size(); i++)
	{
		if (arr[i].id == orderId && (user->id == arr[i].agentId || user->type == manager))
		{
			arr[i].status = Canceled;
			packId = arr[i].packageId;
		}
	}



	if (packId != "NONE00")
	{
		ifstream f("PackagesDB.txt");
		vector<Package> p_arr;
		while (f >> p)
		{
			if (p.id == packId)
				p.quantity++;

			p_arr.push_back(p);
		}
		f.close();

		ofstream fa("PackagesDB.txt");
		for (int i = 0; i < arr.size(); i++)
			fa << arr[i];
		fa.close();

	}

	return 1;

}
bool approveOrder(vector<Order>& arr, int orderId)
{
	// Here the user will approve in proccess orders

	for (int i = 0; i < arr.size(); i++)
	{

		if (arr[i].id == orderId && arr[i].status == Canceled)
		{
			cout << "This order been canceld can not be aprrove" << endl;
			return false;
		}

		if (arr[i].id == orderId && (user->id == arr[i].agentId || user->type == manager))
		{
			arr[i].status = Confirmed;
		}
	}
	return false;
}
bool rateByOrder(vector<Order>& o_arr, int orderId)
{
	int packageId;

	// Load packages from file
	Package tempPackage;
	vector<Package> p_arr;
	ifstream rpf("PackagesDB.txt"); // read package file
	while (rpf >> tempPackage)
	{
		p_arr.push_back(tempPackage);
	}
	rpf.close();





	// track the order
	for (int i = 0; i < o_arr.size(); i++)
	{
		if (o_arr[i].id == orderId)
		{

			// track the package
			for (int j = 0; j < p_arr.size(); j++)
			{
				if (p_arr[j].id == o_arr[i].packageId)
				{
					if (o_arr[i].rated == true || o_arr[i].status == Canceled || o_arr[i].status == in_process)
					{
						cout << "Package has already been rated or the order is not approved!" << endl;
						return false;

					}

					o_arr[i].rated = true;

					rateApackage(p_arr[j]); // rate
					ofstream wpf("PackagesDB.txt"); //rewrite package file
					for (int i = 0; i < p_arr.size(); i++)
						wpf << p_arr[i];
					wpf.close();
				}
			}
		}
	}
	return true;

}
bool rateApackage(Package& p)
{
	int temp;
	do {
		cout << "Enter your rate for this package [1-5]: ";
		
		cin >> temp;
	} while (temp < 1 || temp>5);
		p.rate = (p.rate * p.numOfRates + (float)temp) / (p.numOfRates + 1);
	p.numOfRates++;
	return 1;
}

bool removeUser(UserType t)
{
	// Remove existing user

	int input;
	User u;
	vector<User> arr;
	ifstream f("UsersDB.txt");
	while (f >> u)
	{
		arr.push_back(u);
	}
	f.close();


	for (int i = 0; i < arr.size(); i++)
	{
		if (arr[i].type == t)
			cout << arr[i] << endl;
	}

	cout << "add the " << strUserType(t) << " id:" << endl;
	cin >> input;

	for (int i = 0; i < arr.size(); i++)
	{
		if (arr[i].id == input)
		{
			arr.erase(arr.begin() + i, arr.begin() + i + 1);
		}
	}

	ofstream fa("UsersDB.txt");
	for (int i = 0; i < arr.size(); i++)
		fa << arr[i];
	f.close();

	return 1;

}
bool manageClientsDB()
{

	// Here the user can manage client DB

	if ((!user) || (user->type == client))
		return false;

	int ch;
	User u;
	vector<User> arr;
	ifstream f;

	do {
		f.open("UsersDB.txt");
		while (f >> u)
		{
			if (u.type == client)
				cout << u << endl;
		}
		f.close();

		cout << "\n\n\tSelect: " << "\n\t[1] Add client";
		cout << "\n\t[2] Remove client" << endl << "\n\t[0] Return" << endl;
		cin >> ch;

		switch (ch)
		{
		case 1:
			userRegistration(client);
			break;

		case 2:
			removeUser(client);
			break;
		case 0:
			break;

		default:
			cout << "\n\tBad input! Try again" << endl;
			break;


		}

	} while (ch);

	return true;
}
bool manageOrdersDB()
{
	// Here the user can manage order DB

	if ((!user) || (user->type == client))
		return false;

	vector<Order> arr;
	Order o;
	int orderId;
	int ch;

	ifstream f("OrdersDB.txt");
	while (f >> o)
		arr.push_back(o);


	f.close();

	do {

		for (int i = 0; i < arr.size(); i++)
		{
			if (arr[i].agentId == user->id || user->type == manager)
				cout << endl << arr[i] << endl << endl;
		}

		cout << "\n\tPress [1] to sort Orders" << "\n\tPress [2] to approve orders";
		cout << "\n\tPress [3] to cancel Orders" << "\n\tPress [4] add new orders";
		cout << "\n\tPress [0] to return to last page" << endl;
		cin >> ch;

		switch (ch)
		{

		case 1:
			trackOrder(arr);
			break;

		case 2:
			cout << "Enter the order id you want to confirm" << endl;
			cin >> orderId;
			approveOrder(arr, orderId);
			break;

		case 3:
			cout << "Enter the order id you want to cancel" << endl;
			cin >> orderId;
			cancelAnOrder(arr, orderId);
			break;

		case 4:

			cout << "Order that that not been taken" << endl;
			for (int i = 0; i < arr.size(); i++)
			{
				if (arr[i].agentId == 0)
					cout << endl << arr[i] << endl;
			}

			cout << "Enter the Order id you would like to take" << endl;
			cin >> ch;

			for (int i = 0; i < arr.size(); i++)
			{
				if (arr[i].id == ch)
					arr[i].agentId = user->id;
			}
			break;

		case 0:
			break;

		default:
			cout << "Wrong key!" << endl;

		}

	} while (ch);


	ofstream of("OrdersDB.txt");
	for (int i = 0; i < arr.size(); i++)
		of << arr[i];
	of.close();

	return 1;
}
bool managePackagesDB()
{
	if ((!user) || (user->type == client))
		return false;

	vector<Package> arr;
	Package o;
	string packId;
	int ch;

	ifstream f("PackagesDB.txt");
	while (f >> o)
	{
		cout << o << endl;

		arr.push_back(o);
	}
	f.close();

	do {
		cout << "\n\tPress [1] to sort packages" << "\n\tPress [2] to add package";
		cout << "\n\tPress [3] to update package" << "\n\tPress [4] to remove package";
		cout << "\n\tPress [0] to Return" << endl;
		cin >> ch;

		switch (ch)
		{

		case 1:
			trackPackages(arr);
			break;

		case 2:
			addPackage(arr);
			break;

		case 3:
			cout << "Enter the package id you want to update" << endl;
			cin >> packId;
			for (int i = 0; i < arr.size(); i++)
			{
				if (arr[i].id == packId)
					updatePackage(arr[i]);
			}

			break;

		case 4:
			cout << "Enter the package id you want to remove" << endl;
			cin >> packId;
			for (int i = 0; i < arr.size(); i++)
			{
				if (arr[i].id == packId)
					removePackage(arr, packId);
			}
			break;

		default:
			cout << "Wrong key!" << endl;

		}

	} while (!ch);


	ofstream of("PackagesDB.txt");
	for (int i = 0; i < arr.size(); i++)
		of << arr[i];
	of.close();

	return 1;

}


void showMessagesFromClient()
{
	Message m;
	ifstream f("MessageFromClientDB.txt");
	while (f >> m)
	{
		cout << m << endl;;
	}

	f.close();
}
void showMessagesFromManeger(UserType t)
{
	Message m;
	ifstream f("MessageFromManegerDB.txt");
	while (f >> m)
	{
		if (m.to == t)
			cout << m << endl;
	}
	f.close();
}

bool writeNewUserToFile(User& newClient)
{
	ifstream e("UsersDB.txt");
	User u;

	while (e >> u)
		if (u.id == newClient.id)
		{
			e.close();

			return false;
		}

	e.close();

	// write New User To File
	ofstream f("UsersDB.txt", ios::app);
	f << newClient;
	f.close();
	return true;
}
bool writeNewMessageFromClientToFile(Message& newMessage)
{
	ofstream f("MessageFromClientDB.txt", ios::app);
	if (!f) return false;
	f << newMessage;
	f.close();
	return true;
}
bool writeNewMessageFromManegerToFile(Message& newMessage)
{
	ofstream f("MessageFromManegerDB.txt", ios::app);
	if (!f) return false;
	f << newMessage;
	f.close();
	return 1;
}
bool writeNewPackageToFile(Package& newPackage)
{
	ofstream f;
	f.open("PackagesDB.txt", ios::app);
	f << newPackage;
	f.close();
	return 1;
}

bool clientMessageBox()
{
	Message m;
	ifstream f("MessageFromManegerDB.txt");
	while (f >> m)
	{
		if (m.to == client)
			cout << m;
	}
	f.close();
	return 1;
}
bool agentMessageBox()
{
	Message m;
	cout << "Messages from the Manger" << endl << endl;
	ifstream f("MessageFromManegerDB.txt");
	while (f >> m)
	{
		if (m.to == agent)
			cout << m;
	}
	f.close();
	return 1;
}
bool requestsFromClient()
{
	Message m;
	vector<Message> arr;
	ifstream f("MessageFromClientDB.txt");
	while (f >> m)
		arr.push_back(m);
	f.close();

	if (arr.size() == 0)
	{
		cout << endl << "No new messages" << endl;
		return false;
	}

	char ch = 'A';
	for (int i = 0; i < arr.size(); i++)
	{

		cout << arr[i] << endl;

		if (arr.size() - 1 - i != 0)
		{
			cout << endl << "(" << arr.size() - i - 1 << ") messages remain" << endl;
			cout << "Countinue ? Y/N: " << endl;
			cin >> ch;
		}


		if (ch == 'Y')
		{
			system("cls");
			continue;
		}

		if (ch == 'N')
		{
			arr.erase(arr.begin(), arr.begin() + 1 + i);
			break;
		}
	}


	ofstream of("MessageFromClientDB.txt");
	for (int i = 0; i < arr.size(); i++)
		of << arr[i];
	of.close();

	return 1;
}

bool creatCoupon()
{
	Coupon c;
	cin >> c;
	ofstream f("CouponDB.txt");
	f << c;
	f.close();

	cout << "good, let you clients know there is new coupon" << endl;
	Message m;
	cin >> m;
	m.to = client;
	writeNewMessageFromManegerToFile(m);
	return 1;
}
float readCoupon(int code)
{
	Coupon c;
	Date d = today();
	ifstream f("CouponDB.txt");
	while (f >> c)
	{
		if ((c.couponCode == code) && (d < c.expiry || d == c.expiry))
		{
			cout << "Code vailid! Price reduced" << endl;
			return c.discount;
		}
	}

	cout << "Invaild code!" << endl;
	return 1;

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
		return "Manager";
	default:
		return "";
	}
}
string strStatus(Status& s)
{
	// convert status to string
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
	time_t t = time(NULL); // set the current time
	tm time = *localtime(&t); // convert to dd.mm.yyyy format
	Date d = { time.tm_mday,time.tm_mon + 1,time.tm_year + 1900 };
	return d;
}

bool operator<(Date& d1, Date& d2)
{
	if (d1.year > d2.year)
		return false;
	else if (d1.year < d2.year)
		return true;
	else if (d1.month > d2.month)
		return false;
	else if (d1.month < d2.month)
		return true;
	else if (d1.day >= d2.day)
		return false;
	else if (d1.day < d2.day)
		return true;



}
bool operator==(Date& d1, Date& d2)
{
	if ((d1.year == d2.year) && (d1.month == d2.month) && (d1.day == d2.day))
		return true;
	else
		return false;


}

ostream& operator<<(ofstream& f, User& u)
{
	f << u.id << endl;
	f << enc(u.password) << endl;
	f << enc(u.userName) << endl;
	f << int(u.type) << endl;
	return f;
}
istream& operator>>(ifstream& f, User& u)
{
	f >> u.id;
	f >> u.password;
	u.password = dec(u.password);
	f >> u.userName;
	u.userName = dec(u.userName);
	f >> u.type;
	return f;
}
ostream& operator<<(ostream& os, User& u)
{
	os << strUserType(u.type);
	os << " Name: " << u.userName << endl;
	os << "Id: " << u.id << endl;
	return os;
}
istream& operator>>(istream& is, User& u)
{
	// getting the new user  details
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
istream& operator>>(ifstream& f, Status& u)
{
	int i;
	f >> i;
	u = Status(i);
	return f;
}

ostream& operator<<(ostream& os, Order& o)
{
	os << "Date: " << o.date << endl;
	os << "Client Id: " << o.clientId << endl;
	os << "Agent id: " << o.agentId << endl;
	os << "Order Id: " << o.id << endl;
	os << "Package Id: " << o.packageId << endl;
	os << "Order status: " << strStatus(o.status);
	return os;

}
ostream& operator<<(ofstream& f, Order& o)
{

	f << o.date << endl;
	f << o.clientId << endl;
	f << o.id << endl;
	f << enc(o.packageId) << endl;
	f << o.status << endl;
	f << o.agentId << endl;
	f << o.rated << endl;

	return f;
}
istream& operator>>(ifstream& f, Order& o)
{
	f >> o.date;
	f >> o.clientId;
	f >> o.id;
	f >> o.packageId;
	o.packageId = dec(o.packageId);
	f >> o.status;
	f >> o.agentId;
	f >> o.rated;

	return f;
}

ostream& operator<<(ofstream& f, Date& d)
{
	f << d.day << ".";
	f << d.month << ".";
	f << d.year;
	return f;
}
istream& operator>>(ifstream& f, Date& d)
{

	char dot;//for save dot

	f >> d.day;
	f >> dot;
	f >> d.month;
	f >> dot;
	f >> d.year;
	return f;
}
ostream& operator<<(ostream& os, Date& d)
{
	os << d.day << ".";
	os << d.month << ".";
	os << d.year;
	return os;
}
istream& operator>>(istream& is, Date& d)
{
	Date t = today();
	bool flag = true;

	do
	{
		flag = true;
		cout << "day: ";
		is >> d.day;
		cout << "month: ";
		is >> d.month;
		cout << "year: ";
		is >> d.year;

		if (d < t || d.day>31 || d.day < 1 || d.month < 1 || d.month>12 || d.year < t.year)
		{
			cout << "\n\n\tInvalid date! Try again\n\n";
			flag = false;
		}
	} while (!flag);

	return is;
}

ostream& operator<<(ostream& os, Package& p)
{
	os << "Package id: " << p.id << endl;
	os << "Package price: " << p.price << endl;
	os << "Package quantity: " << p.quantity << endl;
	os << "Flight destination: " << p.f.destination << endl;
	os << "Flight departure: " << p.out << endl;
	os << "Flight return " << p.in << endl;
	os << "Hotel name: " << p.h.name << endl;
	os << "Hotel Address: " << p.h.address << endl;
	os << "Package rating: " << p.rate << " out of: " << p.numOfRates << " Ratings." << endl;
	return os;
}
ofstream& operator<<(ofstream& f, Package& p)
{
	f << enc(p.id) << endl;
	f << enc(p.f.destination) << endl;
	f << p.out << endl;
	f << p.in << endl;
	f << enc(p.h.name) << endl;
	f << enc(p.h.address) << endl;
	f << p.rate << endl;
	f << p.numOfRates << endl;
	f << p.price << endl;
	f << p.quantity << endl;
	return f;
}
istream& operator>>(istream& is, Package& p)
{
	bool flag = true;

	Package pa;
	vector<Package> arr;
	ifstream f("PackagesDB.txt");

	while (f >> pa)
		arr.push_back(pa);

	f.close();

	do
	{
		flag = true;
		cout << "\n\tEnter package id: ";
		is >> p.id;

		for (int i = 0; i < arr.size(); ++i)
			if (p.id == arr[i].id || !flag)
			{
				cout << "\n\t Package ID already exists! Try again\n";
				flag = false;
			}
	} while (!flag);

	updatePackage(p);

	return is;
}
ifstream& operator>>(ifstream& f, Package& p)
{
	f >> p.id;
	p.id = dec(p.id);
	f >> p.f.destination;
	p.f.destination = dec(p.f.destination);
	f >> p.out;
	f >> p.in;
	f >> p.h.name;
	p.h.name = dec(p.h.name);
	f >> p.h.address;
	p.h.address = dec(p.h.address);
	f >> p.rate;
	f >> p.numOfRates;
	f >> p.price;
	f >> p.quantity;
	return f;
}

ostream& operator<<(ofstream& f, Message& m)
{
	f << m.d << endl;
	f << enc(m.sender) << endl;
	f << m.to << endl;
	f << enc(m.message) << endl;

	PlaySound(TEXT("notification02.wav"), NULL, SND_FILENAME | SND_ASYNC);

	return f;
}
istream& operator>>(ifstream& f, Message& m)
{
	f >> m.d;
	f >> m.sender;
	m.sender = dec(m.sender);
	f >> m.to;
	getline(f, m.message);
	getline(f, m.message);
	m.message = dec(m.message);
	return f;
}
ostream& operator<<(ostream& os, Message& m)
{
	os << "Sent at: " << m.d << endl;
	os << "From: " << m.sender << endl;
	os << "Body message: " << m.message;
	return os;
}
istream& operator>>(istream& is, Message& m)
{
	m.d = today();
	m.sender = user->userName;
	cout << "Body message: ";
	cin.ignore();
	getline(is, m.message);
	return is;
}

ostream& operator<<(ostream& os, Coupon& c)
{
	os << "Cupon code: " << c.couponCode << endl;
	os << "Discount amount: " << c.discount << endl;
	os << "Expiry date: " << c.expiry << endl;
	return os;
}
istream& operator>>(istream& is, Coupon& c)
{
	cout << "Hello manager, please enter code for discount (4 digits): " << endl;
	is >> c.couponCode;
	cout << "Please enter discount amount: " << endl;
	is >> c.discount;
	cout << "Enter day, month and year for expiry date: " << endl;
	is >> c.expiry;
	return is;
}
ostream& operator<<(ofstream& f, Coupon& c)
{
	f << c.couponCode << endl;
	f << c.discount << endl;
	f << c.expiry << endl;
	return f;
}
istream& operator>>(ifstream& f, Coupon& c)
{
	f >> c.couponCode;
	f >> c.discount;
	f >> c.expiry;
	return f;
}


void intro()
{
	srand((unsigned)time(0));
	if ((rand() % 2) == 1)
		PlaySound(TEXT("startup01.wav"), NULL, SND_FILENAME | SND_ASYNC);
	else
		PlaySound(TEXT("startup02.wav"), NULL, SND_FILENAME | SND_ASYNC);
	cout << PINK << "HHHH "; Sleep(35); cout << MAGENTA << "     HH     "; Sleep(35); cout << YELLOW << "   HHHH "; Sleep(35); cout << GREEN << "  H    H"; Sleep(35); cout << RED << " H   H"; Sleep(35); cout << BLUE << "  H     H" << endl; Sleep(35);
	cout << PINK << "H   H"; Sleep(35); cout << MAGENTA << "    H  H    "; Sleep(35); cout << YELLOW << "  H    H"; Sleep(35); cout << GREEN << "  H  H  "; Sleep(35); cout << RED << " H   H"; Sleep(35); cout << BLUE << "  H     H" << endl; Sleep(35);
	cout << PINK << "HHHH "; Sleep(35); cout << MAGENTA << "   H    H   "; Sleep(35); cout << YELLOW << " H      "; Sleep(35); cout << GREEN << "  HH    "; Sleep(35); cout << RED << " HHHHH"; Sleep(35); cout << BLUE << "  H     H" << endl; Sleep(35);
	cout << PINK << "H    "; Sleep(35); cout << MAGENTA << "  HHHHHHHH  "; Sleep(35); cout << YELLOW << " H      "; Sleep(35); cout << GREEN << "  HH    "; Sleep(35); cout << RED << "     H"; Sleep(35); cout << BLUE << "  H     H" << endl; Sleep(35);
	cout << PINK << "H    "; Sleep(35); cout << MAGENTA << " H        H "; Sleep(35); cout << YELLOW << "  H    H"; Sleep(35); cout << GREEN << "  H  H  "; Sleep(35); cout << RED << "     H"; Sleep(35); cout << BLUE << "  H     H" << endl; Sleep(35);
	cout << PINK << "H    "; Sleep(35); cout << MAGENTA << "H          H"; Sleep(35); cout << YELLOW << "   HHHH "; Sleep(35); cout << GREEN << "  H    H"; Sleep(35); cout << RED << "     H"; Sleep(35); cout << BLUE << "   HHHHH " << endl; Sleep(35);
	for (int i = 0; i < 48; i++)
	{
		cout << BLOCKCOLOR << " ";
		Sleep(13);
	}
	cout << WHITE << endl;
	system("pause");
}
void logo()
{
	cout << PINK << "HHHH " << MAGENTA << "     HH     " << YELLOW << "   HHHH " << GREEN << "  H    H" << RED << " H   H" << BLUE << "  H     H" << endl;
	cout << PINK << "H   H" << MAGENTA << "    H  H    " << YELLOW << "  H    H" << GREEN << "  H  H  " << RED << " H   H" << BLUE << "  H     H" << endl;
	cout << PINK << "HHHH " << MAGENTA << "   H    H   " << YELLOW << " H      " << GREEN << "  HH    " << RED << " HHHHH" << BLUE << "  H     H" << endl;
	cout << PINK << "H    " << MAGENTA << "  HHHHHHHH  " << YELLOW << " H      " << GREEN << "  HH    " << RED << "     H" << BLUE << "  H     H" << endl;
	cout << PINK << "H    " << MAGENTA << " H        H " << YELLOW << "  H    H" << GREEN << "  H  H  " << RED << "     H" << BLUE << "  H     H" << endl;
	cout << PINK << "H    " << MAGENTA << "H          H" << YELLOW << "   HHHH " << GREEN << "  H    H" << RED << "     H" << BLUE << "   HHHHH " << endl;
	cout << BLOCKCOLOR << "                                                " << WHITE;
}