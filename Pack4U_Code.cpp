#include <iostream>
using namespace std;

//Functions
void search();
void loginregister();

typedef struct Date { int day, month, year; }Date;
typedef struct Packege { string destination; Date takeoff; Date landing; int price; char status; }Packege;
typedef struct Client { string name; string username; string email; string password; int phone; }Client;
typedef struct Agent { Client agent; Client* my_clients; }Agent;
typedef struct Manager { Agent manager; Agent* workers; }Manager;

void aboutus()
{
	int choice;
	do {
		cout << "\n\n\tPack4U has been committed to bringing our clients the best in value and quality travel arrangements.";
	    cout<<"\n\tWe are passionate about travel and sharing the world's wonders on the leisure travel side";
		cout << "\n\n\tfor more options:\n\t1.See contact information\n\t2.Sign up to receive our exclusive travel offers\n\t3.Back to the main menu\n\n\t";
		cin>>choice;
		switch (choice)
		{
		case 1:
			cout << "\n\n\tEmail: pack4u@mail.com\n\tPhone: 1-700-800-800";
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
int main()
{
	int num,ch;
	do
	{
		//User** username;
		system("cls");
		cout << "\n\n\n\tTravel Agency - Pack4U";
		cout << "\n\n\t01. Search";
		cout << "\n\n\t02. Login/Register";
		cout << "\n\n\t03. About Us";
		cout << "\n\n\t04. EXIT";
		cout << "\n\n\tSelect Your Option (1-4) ";
		cin >> ch;
		system("cls");
		switch (ch)
		{
		case '1':
			cout << "\n\n\t "; cin >> num;
			break;
		case '2':
			cout << "\n\n\t "; cin >> num;
			break;
		case '3':
			aboutus();
			break;
		case '4':
			cout << "\n\n\tThanks for using our system";
			break;
		default:
			cout << "\a";
		}
		cin.ignore();
		cin.get();
	} while (ch != '4');
	return 0;

    

	
}