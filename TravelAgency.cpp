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

//Structs: user defention
typedef struct User { int id = 0; string password; string userName; UserType type = client; } User;
//package and order defention
typedef struct Date { int day = 0; int month = 0; int year = 0; }Date; // date libary **
typedef struct Flight { string destination = "none"; }Flight;
typedef struct Hotel { string name = "none"; string address = "none"; }Hotel;
typedef struct Package { Date out; Date in; string id="NONE00"; Flight f; Hotel h; float rate = 0 ; int numOfRates = 0; float price = 0; int quantity = 0; } Package;
typedef struct Order { int id =999;  Date date; string packageId = "NONE00"; Status status = in_process; int clientId = 0; int agentId = 0; } Order;
// other structs
typedef struct Message { Date d; string sender; UserType to = client; string message; }Message;
typedef struct Cupon { int cuponCode; float discount; Date expiry; }Cupon;

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
ostream& operator<<(ostream& os, Cupon& c);
istream& operator>>(istream& is, Cupon& c);
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
bool writeNewMessageFromManegerToFile(Message& newMessage, UserType t);
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




//others
string strUserType(UserType& u);
string strStatus(Status& s);
Date today();
void skipLines(ifstream& f, int n);


User* user = nullptr; // The global logged user


//Main
int main()
{
	
	agentMenu();


	
		
}


bool userRegistration(UserType t)
{
	// allocate and creat the new user
	User* newClient = new User;
	cout << "put the following details:" << endl;
	cin >> *newClient;
	newClient->type = t; // asaing the type

	// write the new cline to the DB
	writeNewUserToFile(*newClient);

	//if no user been logged- login the new user
	if (!user)
		user = newClient;

	//if everything went well
	return true;

}
bool login()
{
	
	int id; // details needed to singed in
	string password;
	cout << "please put your id: ";
	cin >> id;
	cout << "please put you password: ";
	cin >> password;

	// creat the new login to the system
	user = new User;

	// open the users DB to find a match
	ifstream f("UsersDB.txt");
	while (f >> *user)
	{
		if (user->id == id && user->password == password)
		{f.close(); return true; }
	}

	// if no math been founded delete the allocation and close
	f.close();
	delete user;
	return false;
}
bool logOrRegist()
{
	// if no user is looged and and login is needed!
	// user going to have to select login or regigst
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

	// return true if the log been succeful
	return user != nullptr;

}
bool makeAnOrder(Package& p)
{

	Order o;
	int i = 0;
	ifstream of("OrdersDB.txt");
	while (of >> o)
	{
		i++;
	}
	of.close();
	

	// put the the need deatils automatcly
	Order order = { 1000 + i,today(), p.id, in_process, user->id, 0 };
	cout << endl << "Summary" << endl << order << endl << p << endl;

	// send user to pay
	paymentSystem(p.price);

	// put the new order in the orders DB
	ofstream f("OrdersDB.txt", ios::app);
	f << order;
	f.close();

	return 1;
}
bool paymentSystem(float price)
{
	int cupon;
	string card;
	cout << "Payment" << endl;
	cout << "put your coupon code if you have" << endl;
	cin >> cupon;
	// if coupon is valid // lower pric

	cout << "please put you credit card details:" << endl << "xxxxxxx mm/yy cvx" << endl;
	cin >> card;

	cout << "THANK YOU AND FUCK YOU" << endl;
	return 1;

}

bool addPackage()
{
	/*if (user->type == agent ) return false;*/

	Package newPackage;
	cout << "put the following details: " << endl;
	cin >> newPackage;

	writeNewPackageToFile(newPackage);

	//if everything went well
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

	while (f >> p)
	{ arr.push_back(p); }


	f.close();

	////////////////////////////////////////////////////

	cout << "Press 1 to order a package" << endl;

	if (user && (user->type==agent || user->type==manager)) ///// agent/manager only
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

		cout << " Enter choice: ";

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
				if (ch1 == 2 && (user->type == agent|| user->type == manager))
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

	cout << "Press 1 to sort by destination" << endl;
	cout << "Press 2 to sort by price range" << endl;
	cout << "Press 3 to sort by departure date" << endl;
	cout << "Press 4 for Popular Packages" << endl << endl;
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

	}
	
	return 1;
}

bool trackOrder()
{
	vector<Order> arr;
	Order temp;
	ifstream f("OrdersDB.txt");

	Date d;
	string p;
	Status s;

	while(f>>temp)
	{ arr.push_back(temp); }


	cout << "View Orders By:" << endl;
	cout << "1.by Order Date" << endl << "2.by Package" << endl << "3.by status" << endl;
	cout << "0. to exit" << endl;
	int userChoise;
	cin >> userChoise;
	do {

		switch (userChoise)
		{
		case 1:
			cout << "Put the date:" << endl;
			cin >> d;
			for (int i = 0; i < arr.size(); i++)
			{
				if (arr[i].date == d)
					cout << arr[i] << endl << endl;
			}
			break;
		case 2:

			// SHIT!!!






			break;
		case 3:

			cout << "what status: " << endl;
			cout << "(1)canceld" <<endl <<"(2)in proccess " <<endl<< "(3)confimed" << endl;
			cin >> userChoise;
			s = Status(userChoise - 1);
			for (int i = 0; i < arr.size(); i++)
			{
				if (arr[i].status == s)
					cout << arr[i] << endl << endl;
			}

			break;
		case 0:
			break;
		default:
			cout << "Worng key!" << endl;
			break;
		}

	} while (!userChoise);

	return 1;
}
bool viewClientOrders(int userId)
{
	Order temp;
	vector<Order> arr; 
	ifstream f("OrdersDB.txt");
	while (f >> temp)
	{ arr.push_back(temp); }

	for (int i = 0; i < arr.size(); i++)
	{
		if (arr[i].clientId == userId)
			cout << arr[i] << endl;
	}
	return 0;
}
bool cancelAnOrder(vector<Order>& arr,int orderId)
{
	for (int i = 0; i < arr.size(); i++)
	{
		if (arr[i].id == orderId)
		{
			arr[i].status = Canceled;
			return true;
		}
	}
	return false;
}
bool approveOrder(vector<Order>& arr,int orderId)
{

	for (int i = 0; i < arr.size(); i++)
	{
		if (arr[i].id == orderId)
		{
			arr[i].status = Confirmed;
		}
	}
	return false;
}
bool rateByOrder(vector<Order>& o_arr,int orderId)
{
	int packageId;

	// load packages from file
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
					rateApackage(p_arr[j]); // rate
					ofstream wpf("PackagesDB.txt"); //rewrite package file
					for (int i = 0; i < p_arr.size(); i++)
						wpf << p_arr[i];
				}
			}
		}
	}
	return false;

}
bool rateApackage(Package& p)
{
	cout << "Enter your rate for this package: ";
	float temp;
	cin >> temp;
	p.rate = (p.rate * p.numOfRates + temp) / (p.numOfRates + 1);
	p.numOfRates ++;
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
	while (f>>m)
	{
		if (m.to == t)
			cout << m << endl;
	}
	f.close();
}

bool writeNewUserToFile(User& newClient)
{
	// write New User To File
	ofstream f("UsersDB.txt", ios::app);
	f << newClient;
	f.close();
	return 1;
}
bool writeNewMessageFromClientToFile(Message& newMessage)
{
	ofstream f("MessageFromClientDB.txt", ios::app);
	if (!f) return false;
	f << newMessage;
	f.close();
	return 1;
}
bool writeNewMessageFromManegerToFile(Message& newMessage, UserType t)
{
	newMessage.to = t;
	ofstream f("MessageFromManegerDB.txt", ios::app);
	if (!f) return false;
	f << newMessage;
	f.close();
	return 1;
}
bool writeNewPackageToFile(Package& newPackage)
{
	ofstream f("PackagesDB.txt", ios::app);
	if (!f) return false;
	f << newPackage;
	f.close();
	return 1;
}

bool clientMessageBox()
{
	// cupon
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

	char ch;
	for (int i = 0; i < arr.size(); i++)
	{
		cout << arr[i] << endl;
		cout << endl << "(" << arr.size() - i << ") messages remain" << endl;
		cout << "Countinue ? Y/N: " << endl;
		cin >> ch;

		if (ch == 'Y')
			continue;

		if (ch == 'N')
			break;
	}
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
		return "The Manager";
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
void skipLines(ifstream& f, int n)
{
	// skip to the wanted line in text file
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
	if ((d1.year == d2.year) && (d1.month == d2.month) && (d1.day == d2.day))
		return true;
	else
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
ostream& operator<<(ostream& os, User& u)
{
	os << strUserType(u.type);
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
istream& operator>>(ifstream& f, Status& u)
{
	int i;
	f >> i;
	u = Status(i);
	return f;
}

ostream& operator<<(ostream& os, Order& o)
{
	os << "Date: " <<o.date << endl;
	os << "Client Id: " << o.clientId << endl;
	os << "Order Id: " << o.id << endl;
	os <<"Package Id: "<< o.packageId << endl;
	os << "Order status: " << strStatus(o.status);
	return os;
		
}
ostream& operator<<(ofstream& f, Order& o)
{

	f << o.date << endl;
	f << o.clientId << endl;
	f << o.id << endl;
	f << o.packageId << endl;
	f << o.status << endl;
	f << o.agentId << endl;
	return f;
}
istream& operator>>(ifstream& f, Order& o)
{
	f >> o.date;
	f >> o.clientId;
	f >> o.id;
	f >> o.packageId;
	f >> o.status;
	f >> o.agentId;

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
	cout << "day: ";
	is >> d.day;
	cout << "month: ";
	is >> d.month;
	cout << "year: ";
	is >> d.year;
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

	cout << "Enter package id: ";
	is >> p.id;

	updatePack(p);

	return is;
}
ifstream& operator>>(ifstream& f, Package& p)
{
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
{
	f << m.d << endl;
	f << m.sender << endl;
	f  << m.to << endl;
	f << m.message << endl;
	return f;
}
istream& operator>>(ifstream& f, Message& m)
{
	f >> m.d;
	f >> m.sender;
	f >> m.to;
	f >> m.message;
	return f;
}
ostream& operator<<(ostream& os, Message& m)
{
	os << "Sent at : " << m.d << endl;
	os << "From: " << m.sender << endl;
	os << "Body message: " << m.message;
	return os;
}
istream& operator>>(istream& is, Message& m)
{
	m.d = today();
	m.sender = user->userName;
	cout << "Body message: ";
	is >> m.message;
	return is;
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
//Agent menu
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
		case 3:
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
//Manger menu
void managerMenu()
{
	int choice;
	do {
		cout << "\n\n\t1.View Agent Options";
		cout << "\n\n\t2.Add an agent";
		cout << "\n\n\t3.Remove an agent";
		cout << "\n\n\t4.Creat discaunt cupon and send to client";
		cout << "\n\n\t5.Send message to agents";
		cout << "\n\n\t6.Exit" << endl;
		cin >> choice;
		Message m;
		switch (choice)
		{
		case 1: agentMenu();
			break;
		case 2: userRegistration(agent);
			break;
		case 3: //removeAgentFromFile();
			break;
		case 4:
			//
			break;
		case 5:
			cin >> m;
			writeNewMessageFromManegerToFile(m, agent);
			break;
		default:
			cout << "\n\n\tTRY AGAIN";
			break;
		}
	} while (choice != 6);
}


