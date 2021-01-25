/*
   Welcome to Pack4U Project, This is a Travel Agency program that is not use any class in it.
   To properly use this code you need to download the .wav files and place them inside your folder where the .cpp of this code is located.
   If you not gonna make it the code will crash and ask you for audio files, so make sure you have download all 5 .wav files.
   This files located in out github and can be found here: https://github.com/SCE2020Team2/yesodot
   In folder: "Audio for us".
*/
#pragma comment(lib, "winmm.lib")
#define RED "\033[1;31m" //color red
#define GREEN "\033[1;32m" //color green
#define YELLOW "\033[1;33m" //color yellow
#define BLUE "\033[1;34m" //color blue
#define PINK "\033[1;35m" //color pink
#define MAGENTA "\033[1;36m" //color magenta
#define WHITE "\033[0m"    //color reset to white
#define BLOCKCOLOR "\033[1;100;30m" //block of color
#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#include <stdlib.h>
#include <ctime>
using namespace std;

void intro()
{
    srand((unsigned)time(0));
    if((rand() % 2)==1)
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

//Test Message box
int DisplayResourceNAMessageBox()
{
    int msgboxID = MessageBox(
        NULL,
        (LPCWSTR)L"Some shit here\nand some shit here",
        (LPCWSTR)L"Shit Title",
        MB_ICONASTERISK | MB_OKCANCEL | MB_DEFBUTTON2
    );

    switch (msgboxID)
    {
    case IDCANCEL:
        // TODO: add code
        break;
    case IDOK:
        // TODO: add code
        break;
    }

    return msgboxID;
}
int main()
{
    intro();
    Sleep(1000);
    cout << "Notification sound number 1"<<endl;
    PlaySound(TEXT("notification01.wav"), NULL, SND_FILENAME | SND_ASYNC);
    Sleep(1000);
    cout << "Notification sound number 2" << endl;
    PlaySound(TEXT("notification02.wav"), NULL, SND_FILENAME | SND_ASYNC);
    Sleep(1000);
    cout << "Notification sound number 3" << endl;
    PlaySound(TEXT("notification03.wav"), NULL, SND_FILENAME | SND_ASYNC);
    Sleep(1000);

    system("pause");

    DisplayResourceNAMessageBox();

    return 0;
}
