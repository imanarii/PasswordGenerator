#include <iostream>
#include <process.h>
#include <string>
#include <vector>

#define NOMINMAX
#include <Windows.h>
int count = 0;
bool hist = false;
std::vector<std::string> passwords{};

// Display all passwords in the vector 
void history()
{
	if (count > 0)
	{
		system("cls");
		std::cout << "password history:  \n";
		for (int i = 0; i < passwords.size(); ++i)
			std::cout << i + 1 << ". " << passwords[i] << std::endl;
		std::cout << "Warning: History will be deleted When programme closes\n";
	}
	else
		std::cout << "You havent generated any passwords yet! \n";
	hist = true;
}

// Copy password to clipboard 
void toClipboard(const std::string& s)
{
	OpenClipboard(0);
	EmptyClipboard();
	HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, s.size() + 1);
	if (!hg)
	{
		CloseClipboard();
		return;
	}
	memcpy(GlobalLock(hg), s.c_str(), s.size() + 1);
	GlobalUnlock(hg);
	SetClipboardData(CF_TEXT, hg);
	CloseClipboard();
	GlobalFree(hg);
}


// generate a password with Proccess id as seed the first time the function is called and tickCount(amount of milliseconds since system started) every other time
void gen(std::string arry)
{
	static int first = 0;
	if (first == 0)
		srand(_getpid());
	else
		srand(GetTickCount64());

	std::string pass, q;
	int n, len = arry.size();
	std::cout << "Password length: ";
	std::cin >> n;
	system("cls");
	for (int i = 0; i < n; i++)
		pass += arry[rand() % len];
		
	++count;
	passwords.push_back(pass);
	std::cout << passwords[count - 1] << std::endl;
	std::cout << "\nWould you like to copy the password(y or n)?: ";
	std::cin >> q;
	if (q == "y")
	{
		toClipboard(passwords[count - 1]);
		system("cls");
		std::cout << "Password copied!";
		Sleep(800);
	}
	system("cls");
	first = 1;
}


int main()
{
	std::string alphaNum = "0123456789!@#$%^&*abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	std::string noSym =  "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ" ;
	std::string q;
	
	while (true)
	{
		if (count == 1 && !hist)
		std::cout << "TIP: To view past passwords type 'h' \n";
		std::cout << "Would you like symbols? y or n: ";

		if (std::cin >> q && q.size() == 1)
		{
			system("cls");
			q[0] = tolower(q[0]);

			if (q == "h")
				history();

			else if (q == "y")
			{
				gen(alphaNum);
			}
			if (q == "n")
			{
				gen(noSym);
			}
		}
		else
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}

	return 0;
}