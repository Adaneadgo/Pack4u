#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<string>
#include<ctime>
#include<vector>

#define goodRate 4

using namespace std;

// Enums: states and types of objects
typedef enum  UserType { client, agent, manager } UserType;
typedef enum  Status { Canceled, in_process, Confirmed } Status;

// Structs: user defention
typedef struct User { int id = 0; string password; string userName; UserType type = client; } User;

// package and order defention
typedef struct Date { int day = 0; int month = 0; int year = 0; }Date; // date libary **
typedef struct Flight { string destination = "none"; }Flight;
typedef struct Hotel { string name = "none"; string address = "none"; }Hotel;
<<<<<<< HEAD
typedef struct Package { Date out; Date in; string id="NONE00"; Flight f; Hotel h; float rate = 0 ; int numOfRates = 0; float price = 0; int quantity = 0; } Package;
typedef struct Order { int id =999;  Date date; string packageId = "NONE00"; Status status = in_process; int clientId = 0; int agentId = 0; } Order;

=======
typedef struct Package { Date out; Date in; string id = "NONE00"; Flight f; Hotel h; float rate = 0; int numOfRates = 0; float price = 0; int quantity = 0; } Package;
typedef struct Order { int id = 999;  Date date; string packageId = "NONE00"; Status status = in_process; int clientId = 0; int agentId = 0; } Order;
>>>>>>> e99706affba472f052152c7f13efe02cf1101fd0
// other structs
typedef struct Message { Date d; string sender; UserType to = client; string message; }Message;
typedef struct Coupon { int couponCode; float discount; Date expiry; }Cupon;

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

bool trackOrder();
bool viewClientOrders(int userId);
bool cancelAnOrder(vector<Order>& o_arr, int orderId);
bool approveOrder(vector<Order>& o_arr, int orderId);
bool rateByOrder(vector<Order>& o_arr, int orderId);
bool rateApackage(Package& r);

bool addPackage();
bool updatePack(Package& p);
void editPackage(vector<Package>& arr, int index);
bool viewPackages();
bool sortPackages(vector<Package>& arr);

void showMessagesFromClient();
void showMessagesFromManeger(UserType t);

bool clientMessageBox();
bool agentMessageBox();
bool requestsFromClient();

bool creatCoupon();
float readCoupon(int code);

// Others
string strUserType(UserType& u);
string strStatus(Status& s);
Date today();
void skipLines(ifstream& f, int n);
User* user = nullptr; // The global logged user

// Main
int main()
{
	
		
}

// Functions
//Main
int main()
{
	








}


void agentMenu()
{
	int choice;
	do {
		cout << "\n\n\t1.View packages";
		cout << "\n\n\t2.View client";
		cout << "\n\n\t3.Add a package";
		cout << "\n\n\t4.Remove a package";
		cout << "\n\n\t5.Message box";
		cout << "\n\n\t6.Exit";

		cin >> choice;
		switch (choice)
		{
		case 1:
			//view package
			break;
		case 2:
			//view client
			break;
		case 3: addPackage();
			break;
		case 4:
			cout << "\n\n\tEmail: pack4u@mail.com\n\tPhone: 1-700-800-800";
			break;
		case 5:
			//call login register func
			break;
		default:
			cout << "\n\n\tTRY AGAIN";
			break;
		}
	} while (choice != 6);
}
void managerMenu()
{
	int choice;
	Message m;

	do {
		cout << "\n\n\t1.View Agent Options";
		cout << "\n\n\t2.Add an agent";
		cout << "\n\n\t3.Remove an agent";
		cout << "\n\n\t4.Creat discaunt cupon and send to clients";
		cout << "\n\n\t5.Send a genral message to all agents";
		cout << "\n\n\t6.Exit" << endl;
		cin >> choice;

		switch (choice)
		{
		case 1: agentMenu();
			break;

		case 2:
			cout << "Please add the new agent details" << endl;
			userRegistration(agent);
			break;

		case 3: // remove agent
			break;

		case 4: creatCoupon();
			break;

		case 5:
			cin >> m;
			m.to = agent;
			writeNewMessageFromManegerToFile(m);
			break;

		default:
			cout << "\n\n\tTRY AGAIN";
			break;
		}
	} while (choice != 6);
}
bool userRegistration(UserType t)
{
	// Allocate and creat the new user
	User* newClient = new User;
	cout << "put the following details:" << endl;
	cin >> *newClient;
	newClient->type = t; // Asaing the type
	// Write the new cline to the DB
	writeNewUserToFile(*newClient);
	// If no user been logged- login the new user
	if (!user)
		user = newClient;
	// If everything went well
	return true;
}
bool login()
{
	int id; // Details needed to singed in
	int id; // details needed to singed in
	string password;
	cout << "please put your id: ";
	cin >> id;
	cout << "please put you password: ";
	cin >> password;
	// Creat the new login to the system
	user = new User;
	// Open the users DB to find a match
	ifstream f("UsersDB.txt"); // Read user file
	while (f >> *user)
	{
		if (user->id == id && user->password == password)
		{
			f.close(); return true;
		}
	}
	// If no math been founded delete the allocation and close
	f.close();
	delete user;
	//If everything was not right
	return false;
}
bool logOrRegist()
{
	// If no user is looged and and login is needed!
	// User going to have to select login or regigst
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
	// Return true if the log been succeful
	return user != nullptr;
}
bool makeAnOrder(Package& p)
{
	// Allocate and creat the new order
	Order o;
	int i = 0;
	ifstream of("OrdersDB.txt"); // Read order file
	while (of >> o)
	{
		i++;
	}
	of.close();

	// put the the need deatils automatcly
	Order order = { 1000 + i,today(), p.id, in_process, user->id, 0 };
	cout << endl << "Summary" << endl << order << endl << p << endl;
	// Send user to pay
	paymentSystem(p.price);
	// Put the new order in the orders DB
	ofstream f("OrdersDB.txt", ios::app);
	f << order;
	f.close();
	return 1;
}
bool paymentSystem(float price)
{
	int code;
	string card;
	float discount = 1;

	cout << "Payment" << endl;
	cout << "put your coupon code if you have" << endl;
	cin >> cupon;
	// If coupon is valid // lower pric
	cout << "please put you credit card details:" << endl << "xxxxxxx mm/yy cvx" << endl;
	cin >> card;
	cout << "THANK YOU AND FUCK YOU" << endl;
	return 1;
	cout << "put your coupon code if you have one" << endl;
	cin >> code;
	discount = readCoupon(code);
	cout << "please put you credit card details:" << endl << "xxxxxxxx  mm/yy  cvc" << endl;
	cin >> card;
	cout << "Total price: " << price * discount << "$" << endl;
	return 1;
}
bool addPackage()
{
	/*if (user->type == agent ) return false;*/
	// Allocate and creat the new package
	Package newPackage;
	cout << "put the following details: " << endl;
	cin >> newPackage;
	writeNewPackageToFile(newPackage);
	// If everything went well
	return true;
}
bool updatePack(Package& p)
{
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
			cout << "Enter flight return date:" << endl;
			cin >> p.in;
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
	// If everything went well
	return true;
}
void editPackage(vector<Package>& arr, int index)
{
	updatePack(arr[index]);
	ofstream f;
	f.open("Package.txt");
	for (int i = 0; i < arr.size(); ++i)
		f << arr[i];
	f.close();
}
bool viewPackages()
{
	int ch1, ch2;
	Package p;
	vector<Package> arr;
	ifstream f;
	f.open("PackagesDB.txt");
	while (f >> p) { arr.push_back(p); }
	f.close();
	cout << "Press [1] to order a package" << endl;
	if (user && (user->type==agent || user->type==manager)) // Agent/manager only
		cout << "Press [2] to edit packages" << endl;
	cout << "Press [3] to sort" << endl;
	while (f >> p)
	{
		arr.push_back(p);
	}

	f.close();
	cout << "Press 1 to order a package" << endl;
	if (user && (user->type == agent || user->type == manager)) ///// agent/manager only
		cout << "Press 2 to edit packages" << endl;
	cout << "Press 3 to sort" << endl;
	cout << endl << endl;
	for (int i = 0; i < arr.size(); ++i)
		cout << arr[i] << endl;
	cin >> ch1;
	if (ch1 == 1 || ch1 == 2)
	{
		for (int i = 0; i < arr.size(); ++i)
			cout << i + 1 << arr[i] << endl;
		cout << endl << endl;
		cout << "Press choice: ";
		cin >> ch2;
		--ch2;
		for (int i = 0; i < arr.size(); ++i)
			if (arr[i].id == arr[ch2].id)
			{
				if (ch1 == 1)
				{
					makeAnOrder(arr[ch2]);
					break;
				}
				if (ch1 == 2 && (user->type == agent || user->type == manager))
				{
					editPackage(arr, ch2);
					break;
				}
			}
	}
	if (ch1 == 3)
		sortPackages(arr);
	return 1;
}
bool sortPackages(vector<Package>& arr)
{
	int ch;
	cout << "Press [1] to sort by destination" << endl;
	cout << "Press [2] to sort by price range" << endl;
	cout << "Press [3] to sort by departure date" << endl;
	cout << "Press [4] for Popular Packages" << endl;
	cout << "Press [0] for back to last page" << endl << endl;
	cin >> ch;

	Package p;
	string dest;
	int min, max;
	Date d;

	int r, index = 0;

	switch (ch)
	{
	case 1:

		cout << "Enter destination: ";
		cin >> dest;

		for (int i = 1, j = 0; i < arr.size(); ++i)
		{
			if (arr[i].f.destination == dest)
				cout << arr[i] << endl;
		}
		break;
	case 2:
		cout << "Enter minimum price: ";
		cin >> min;
		cout << "Enter max price: ";
		cin >> max;
		for (int i = 1, j = 0; i < arr.size(); ++i)
		{
			if ((arr[i].price > min) && (arr[i].price < max))
				cout << arr[i] << endl;
		}
		break;
	case 3:
		cout << "Enter requested departure date: ";
		cin >> d;
		for (int i = 1, j = 0; i < arr.size(); ++i)
			if (arr[i].out == d)
				cout << arr[i] << endl;
		break;
	case 4:
		for (int i = 0; i < arr.size(); ++i)
		{
			if (arr[i].rate >= goodRate)
				cout << arr[i] << endl;
		}
	default:
		cout << "\n\n\tTRY AGAIN"; // Wrong choice
		break;

	} while (choice != 0);
	return 1;
}
bool trackOrder()
{
	vector<Order> arr;
	Order temp;
	ifstream f("OrdersDB.txt"); // Read order file
	Date d;
	string id;
	Status s;
	while(f>>temp) { arr.push_back(temp); }
	while (f >> temp)
	{
		arr.push_back(temp);
	}
	cout << "View Orders By:" << endl;
	cout << "Press [1] to sort by Order Date" << endl << "Press [2] to sort by Package" << endl << "Press [3] to sort by status" << endl;
	cout << "Press [0] to return to the last page" << endl;
	int userChoise;
	cin >> userChoise;
	do {

		switch (userChoise)
		{
		case 1:
			// Sort by date
			cout << "Put the date:" << endl;
			cin >> d;
			for (int i = 0; i < arr.size(); i++)
			{
				if (arr[i].date == d)
					cout << arr[i] << endl << endl;
			}
			break;
		case 2:
			// Sort by package
			cout << "Put the Package id" << endl;
			cin >> id;

			for (int i = 0; i < arr.size(); i++)
			{
				if (arr[i].packageId == id)
					cout << arr[i] << endl << endl;
			}
			break;
		case 3:
			// Sort by status
			cout << "what status: " << endl;
			cout << "(1)canceld" << endl << "(2)in proccess " << endl << "(3)confimed" << endl;
			cin >> userChoise;
			s = Status(userChoise - 1);
			for (int i = 0; i < arr.size(); i++)
			{
				if (arr[i].status == s)
					cout << arr[i] << endl << endl;
			}
			break;
		default:
			cout << "TRY AGAIN" << endl; // Wrong choice
			break;
		}
	} while (userChoise != 0); // If the user chooses to return to the previous menu
	return 1;
}
bool viewClientOrders(int userId)
{
	Order temp;
	vector<Order> arr; 
	ifstream f("OrdersDB.txt"); // // Read order file
	while (f >> temp) { arr.push_back(temp); }
	vector<Order> arr;
	ifstream f("OrdersDB.txt");
	while (f >> temp)
	{
		arr.push_back(temp);
	}
	for (int i = 0; i < arr.size(); i++)
	{
		if (arr[i].clientId == userId)
			cout << arr[i] << endl;
	}
	return 0;
}
bool cancelAnOrder(vector<Order>& arr, int orderId)
{
	for (int i = 0; i < arr.size(); i++)
	{
		if (arr[i].id == orderId)
		{
			arr[i].status = Canceled;
			// If everything went well
			return true;
		}
	}
	//If everything was not right
	return false;
}
bool approveOrder(vector<Order>& arr, int orderId)
{

	for (int i = 0; i < arr.size(); i++)
	{
		if (arr[i].id == orderId)
		{
			arr[i].status = Confirmed;
		}
	}
	//If everything was not right
	return false;
}
bool rateByOrder(vector<Order>& o_arr, int orderId)
{
	int packageId;
	// Load packages from file
	Package tempPackage;
	vector<Package> p_arr;
	ifstream rpf("PackagesDB.txt"); // Read package file
	while (rpf >> tempPackage) { p_arr.push_back(tempPackage); }
	rpf.close();
	// Track the order
	for (int i = 0; i < o_arr.size(); i++)
	{
		if (o_arr[i].id == orderId)
		{

			// Track the package
			for (int j = 0; j < p_arr.size(); j++)
			{
				if (p_arr[j].id == o_arr[i].packageId)
				{
					rateApackage(p_arr[j]); // Rate
					ofstream wpf("PackagesDB.txt"); //Rewrite package file
					for (int i = 0; i < p_arr.size(); i++)
						wpf << p_arr[i];
				}
			}
		}
	}
	//If everything was not right
	return false;
}
bool rateApackage(Package& p)
{
	// The client has the option to rate a package after its return flight date has passed
	cout << "Enter your rate for this package: ";
	float temp;
	cin >> temp;
	p.rate = (p.rate * p.numOfRates + temp) / (p.numOfRates + 1);
	p.numOfRates++;
	return 1;
}
void showMessagesFromClient()
{
	// The client has the ability to leave a request to contact the agent
	Message m;
	ifstream f("MessageFromClientDB.txt");// Read message file
	while (f >> m)
	{
		cout << m << endl;;
	}
	f.close();
}
void showMessagesFromManeger(UserType t)
{
	// Agents and customers will be able to view the mailings they receive from the manager
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
	// Write new user to file
	ofstream f("UsersDB.txt", ios::app);
	f << newClient;
	f.close();
	return 1;
}
bool writeNewMessageFromClientToFile(Message& newMessage)
{
	// Write new message from client to file
	ofstream f("MessageFromClientDB.txt", ios::app);
	if (!f) return false;
	f << newMessage;
	f.close();
	return 1;
}
bool writeNewMessageFromManegerToFile(Message& newMessage)
{
	// Write new message from maneger to file
	newMessage.to = t;
	ofstream f("MessageFromManegerDB.txt", ios::app);
	if (!f) return false;
	f << newMessage;
	f.close();
	return 1;
}
bool writeNewPackageToFile(Package& newPackage)
{
	// Write new package to file
	ofstream f("PackagesDB.txt", ios::app);
	if (!f) return false;
	f << newPackage;
	f.close();
	return 1;
}

bool clientMessageBox()
{
	// A client will be able to view mailings received from a manager
	Message m;
	ifstream f("MessageFromManegerDB.txt"); // Read message file
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
	// An agent will be able to view mailings received from a manager
	Message m;
	cout << "Messages from the Manger" << endl << endl;
	ifstream f("MessageFromManegerDB.txt"); // Read message file
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
	// An agent will be able to view contact messages left by customers
	Message m;
	vector<Message> arr;
	ifstream f("MessageFromClientDB.txt"); // Read message file
	while (f >> m)
		arr.push_back(m);
	f.close();
	char ch;

	if (arr.size() == 0)
	{
		cout << "no new messages" << endl;
		return false;
	}
	char ch = 'A';
	for (int i = 0; i < arr.size(); i++)
	{
		system("cls");
		cout << arr[i] << endl;
		cout << endl << "(" << arr.size() - i << ") messages remain" << endl;
		cout << "Countinue ? Y/N: " << endl;
		cin >> ch;
		if (arr.size() - 1 - i != 0)
		{
			cout << endl << "(" << arr.size() - i - 1 << ") messages remain" << endl;
			cout << "Countinue ? Y/N: " << endl;
			cin >> ch;
		}
		if (ch == 'Y')
			continue;
		if (ch == 'N')
			break;
	}
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
	m.to == client;
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
			return c.discount;
	}
	
	cout << "Vaild code" << endl;
	return 1;

}
string strUserType(UserType& t)
{
	// Convert user type to string
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
	// Convert status to string
	switch (s)
	{
	case Canceled:
		return "Canceled!";
	case in_process:
		return "in process!";
	case Confirmed:
		return "Confirmed!";
	default:
		return "";
	}
}
Date today()
{
	time_t t = time(NULL); // Set the current time
	tm time = *localtime(&t); // Convert to dd.mm.yyyy format
	Date d = { time.tm_mday,time.tm_mon + 1,time.tm_year + 1900 };
	return d;
}
void skipLines(ifstream& f, int n)
{
	// Skip to the wanted line in text file
	for (int i = 0; i < n; i++)
		f.ignore(numeric_limits<streamsize>::max(), '\n');
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
	// Comparison between two dates
	if ((d1.year == d2.year) && (d1.month == d2.month) && (d1.day == d2.day))
		// If everything went well
		return true;
	else
		//If everything was not right
		return false;
}
// Operator
ostream& operator<<(ofstream& f, User& u)
{	// Read user from file
	f << u.id << endl;
	f << u.password << endl;
	f << u.userName << endl;
	f << int(u.type) << endl;
	return f;
}
istream& operator>>(ifstream& f, User& u)
{	// Write the new user to file
	f >> u.id;
	f >> u.password;
	f >> u.userName;
	f >> u.type;
	return f;
}
ostream& operator<<(ostream& os, User& u)
{	// Read user from console
	os << strUserType(u.type);
	os << " Name: " << u.userName << endl;
	os << "Id: " << u.id << endl;
	return os;
}
istream& operator>>(istream& is, User& u)
{	// Write the new user details
	cout << "Id: ";
	is >> u.id;
	cout << "Password ";
	is >> u.password;
	cout << "UserName: ";
	is >> u.userName;
	return is;
}
istream& operator>>(ifstream& f, UserType& u)
{	// Read user type from file
	int i;
	f >> i;
	u = UserType(i);
	return f;
}
istream& operator>>(ifstream& f, Status& u)
{	// Read status from file
	int i;
	f >> i;
	u = Status(i);
	return f;
}
ostream& operator<<(ostream& os, Order& o)
{	// Write new order to console

	os << "Date: " << o.date << endl;
	os << "Client Id: " << o.clientId << endl;
	os << "Order Id: " << o.id << endl;
	os << "Package Id: " << o.packageId << endl;
	os << "Order status: " << strStatus(o.status);
	return os;
}
ostream& operator<<(ofstream& f, Order& o)
{	// Read order from file	
	f << o.date << endl;
	f << o.clientId << endl;
	f << o.id << endl;
	f << o.packageId << endl;
	f << o.status << endl;
	f << o.agentId << endl;
	return f;
}
istream& operator>>(ifstream& f, Order& o)
{	// Weite new order from file
	f >> o.date;
	f >> o.clientId;
	f >> o.id;
	f >> o.packageId;
	f >> o.status;
	f >> o.agentId;
	return f;
}
ostream& operator<<(ofstream& f, Date& d)
{	// Read date from file
	f << d.day << ".";
	f << d.month << ".";
	f << d.year;
	return f;
}
istream& operator>>(ifstream& f, Date& d)
{	// Write new date to file
	char dot;//for save dot
	f >> d.day;
	f >> dot;
	f >> d.month;
	f >> dot;
	f >> d.year;
	return f;
}
ostream& operator<<(ostream& os, Date& d)
{	// Read date from console
	os << d.day << ".";
	os << d.month << ".";
	os << d.year;
	return os;
}
istream& operator>>(istream& is, Date& d)
{
	// Write new date to console
	cout << "day: ";
	is >> d.day;
	cout << "month: ";
	is >> d.month;
	cout << "year: ";
	is >> d.year;
	return is;
}
ostream& operator<<(ostream& os, Package& p)
{	// Read package from cosole
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
{	// Read package from file
	f << p.id << endl;
	f << p.f.destination << endl;
	f << p.out << endl;
	f << p.in << endl;
	f << p.h.name << endl;
	f << p.h.address << endl;
	f << p.rate << endl;
	f << p.numOfRates << endl;
	f << p.price << endl;
	f << p.quantity << endl;
	return f;
}
istream& operator>>(istream& is, Package& p)
{
	// Write new package to console
	cout << "Enter package id: ";
	is >> p.id;
	updatePack(p);
	return is;
}
ifstream& operator>>(ifstream& f, Package& p)
{	// Write package from file
	f >> p.id;
	f >> p.f.destination;
	f >> p.out;
	f >> p.in;
	f >> p.h.name;
	f >> p.h.address;
	f >> p.rate;
	f >> p.numOfRates;
	f >> p.price;
	f >> p.quantity;
	return f;
}
ostream& operator<<(ofstream& f, Message& m)
{	// Read message from file	
	f << m.d << endl;
	f << m.sender << endl;
	f << m.to << endl;
	f << m.message << endl;
	return f;
}
istream& operator>>(ifstream& f, Message& m)
{	// Write new message to file
	f >> m.d;
	f >> m.sender;
	f >> m.to;
	getline(f, m.message);
	getline(f, m.message);
	return f;
}
ostream& operator<<(ostream& os, Message& m)
<<<<<<< HEAD
{	// Read message from console 
	os << "Sent at: " << m.d << endl;
	os << "From: " << m.sender << endl;
	os << "Body message: " << m.message;
	return os;
}
istream& operator>>(istream& is, Message& m)
{
	// Write new message to console
	m.d = today();
	m.sender = user->userName;
	cout << "Body message: ";
	cin.ignore();
	getline(is, m.message);
	return is;
}
<<<<<<< HEAD
	ostream & operator<<(ostream & os, Cupon & c)
{	// Read cupon from console
	os << "Cupon code: " << c.cuponCode << endl;
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
	// Write new cupon to console
	cout << "Hello manager, please enter code for discount (4 digits): " << endl;
	is >> c.cuponCode;
	cout << "Enter discount amount: " << endl;
	is >> c.couponCode;
	cout << "Please enter discount amount: " << endl;
	is >> c.discount;
	cout << "Enter day, month and year for expiry date: " << endl;
	is >> c.expiry;
	return is;
}
// Agent menu
void agentMenu()
{
	int choice;
	do {
		cout << "\n\n\tPress [1] to view packages";
		cout << "\n\n\tPress [2] to view client";
		cout << "\n\n\tPress [3] to add a package";
		cout << "\n\n\tPress [4] to remove a package from data base";
		cout << "\n\n\tPress [5] for a mailbox";
		cout << "\n\n\tPress [0] to exit";
		cin >> choice;
		switch (choice)
		{
		case 1:
			//view package
			break;
		case 2:
			//view client // If the agent wants to view a client list
			break;
		case 3: addPackage(); // If the agent wants to add a package
			break;
		case 4: removePackage(); // If the agent wants to remove a package
			break;
		case 5: requestsFromClient(); // If the agent wants to view messages from a manager or customer
			break;
		default:
			cout << "\n\n\tTRY AGAIN"; // Wrong choice
			break;
		}
	} while (choice != 0); // If the user chooses to return to the previous menu
}
// Manger menu
void managerMenu()
{
	int choice;
	do {
		cout << "\n\n\tPress [1] to view Agent Options";
		cout << "\n\n\tPress [2] to add an agent";
		cout << "\n\n\tPress [3] to remove an agent";
		cout << "\n\n\tPress [4] to creat discaunt";
		cout << "\n\n\tPress [5] to send message to agents";
		cout << "\n\n\tPress [0] to exit" << endl;
		cin >> choice;
		Message m;
		switch (choice)
		{
		case 1: agentMenu(); // If the manager wants to access the agents menu
			break;
		case 2: userRegistration(agent); // If the manager wants to add a new agent
			break;
		case 3: //removeAgentFromFile(); // If the manager wants to remove an agent
			break;
		case 4:  // If the manager wants to generate a coupon code
			//make a cupon
			break;
		case 5:  // If the administrator wants to send a message
			cin >> m;
			writeNewMessageFromManegerToFile(m, agent);
			break;
		default:
			cout << "\n\n\tTRY AGAIN"; // Wrong choice
			break;
		}
	} while (choice != 0); // If the user chooses to return to the previous menu
}
ostream& operator<<(ofstream& f, Coupon& c)
{
	f << c.couponCode << endl;
	f <<  c.discount << endl;
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


