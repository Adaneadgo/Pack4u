#include <iostream>
using namespace std;

//Functions
void search();
void loginregister();

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
			cout << "\n\n\t "; cin >> num;
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