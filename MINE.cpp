#include <iostream>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>
using namespace std;

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Color(int ForgC)
{
	WORD wColor;

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		SetConsoleTextAttribute(hStdOut, (0 + (ForgC * 16)));
	}
	return;
}

void minesweeper_layout(int a[][8], int p[][8]);
void minesweeper_pointer(int a[8][8]);
void arrayinput(int a[][8]);
void chance1(int a[][8], int p[][8]);
void gameover(int a[][8]);

int main()
{
	for (int i = 1; i <= 6; i++)
	{
		Color(i);
		system("CLS");

		gotoxy(47, 14);
		cout << "-----------------";
		gotoxy(46, 15);
		cout << "|   MINESWEEPER   |";
		gotoxy(47, 16);
		cout << "-----------------";

		Sleep(300);
	}

	system("CLS");
	int arr[8][8] = {0}, p[8][8] = {0};
	minesweeper_layout(arr, p);
	arrayinput(arr);
	minesweeper_pointer(arr);
	return 0;
}

void minesweeper_layout(int a[][8], int p[][8])
{
	int i, j;
	gotoxy(47, 2);
	cout << "-----------------";
	gotoxy(46, 3);
	cout << "|   MINESWEEPER   |";
	gotoxy(47, 4);
	cout << "-----------------";
	gotoxy(10, 9);

	for (j = 0; j < 8; j++)
		cout << " _";

	for (int i = 0; i < 8; i++)
	{
		gotoxy(10, 10 + i);
		for (j = 0; j < 9; j++)
			cout << "|_";
		cout << "\b \n";
	}

	for (i = 0; i < 8; i++)
		for (j = 0; j < 8; j++)
			if (p[j][i] != 0 && p[j][i] != 9)
			{
				gotoxy((2 * i) + 11, j + 10);
				cout << a[i][j];
			}
			else if (p[j][i] == 9)
			{
				gotoxy(2 * i + 11, j + 10);
				cout << "F";
			}
}

void minesweeper_pointer(int a[][8])
{
	char ch;
	int x = 11, i = 0, j, y = 10, Exit = 0, chance = 1, arr[8][8], p[8][8] = {0};
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			arr[i][j] = a[i][j];

	gotoxy(x, y);
	cout << "+";

	do
	{
		ch = getch();
		i = y - 10;
		j = (x - 11) / 2;
		switch (ch)
		{
		case 77:
			if (x >= 11 && x < 25)
				for (j = (x - 11) / 2; j < 7; j++)
				{
					if (p[i][j + 1] == 0 || p[i][j + 1] == 9)
					{
						x = (j + 1) * 2 + 11;
						break;
					}
				}
			else
				x = 11;
			break;

		case 75:
			if (x > 11 && x <= 25)
				for (j = (x - 11) / 2; j > 0; j--)
				{
					if (p[i][j - 1] == 0 || p[i][j - 1] == 9)
					{
						x = (j - 1) * 2 + 11;
						break;
					}
				}
			else
				x = 25;
			break;

		case 80:
			if (y >= 10 && y < 17)
				for (i = y - 10; i < 7; i++)
				{
					if (p[i + 1][j] == 0 || p[i + 1][j] == 9)
					{
						y = (i + 1) + 10;
						break;
					}
				}
			else
				y = 10;
			break;

		case 72:
			if (y > 10 && y <= 17)
				for (i = y - 10; i > 0; i--)
				{
					if (p[i - 1][j] == 0 || p[i - 1][j] == 9)
					{
						y = (i - 1) + 10;
						;
						break;
					}
				}
			else
				y = 17;
			break;

		case 13:
			if (chance == 1)
			{
				cout << "\b" << a[(x - 11) / 2][y - 10];
				p[y - 10][(x - 11) / 2] = 1;
				if (a[(x - 11) / 2][y - 10] != 8)
					chance1(arr, p);
				else
					gameover(a);
				chance++;
			}
			else
			{
				p[y - 10][(x - 11) / 2] = 1;
				;
				cout << "\b" << a[(x - 11) / 2][y - 10];
				if (a[(x - 11) / 2][y - 10] == 8)
				{
					gameover(a);
					Exit = 1;
				}
			}

			getch();
			break;

		case 36:
			p[y - 10][(x - 11) / 2] = 9;
			cout << "\bF";
			getch();
			break;

		case 27:
			Exit++;
			break;
		}

		minesweeper_layout(a, p);
		gotoxy(x, y);
		cout << "+";
	} while (Exit == 0);

	for (i = 0; i < 8; i++)
		for (j = 0; j < 8; j++)
			if (p[i][j] == 0)
				break;

	if (i == 9)
	{
		gotoxy(35, 35);
		cout << "CONGRATULATIONS! YOU WON!!";
	}
	gotoxy(0, 26);
}

void arrayinput(int a[][8])
{
	srand(time(0));
	int rand1, rand2, i, j;
	for (i = 0; i < 12; i++)
	{
		rand1 = rand() % 8;
		rand2 = rand() % 8;
		if (a[rand1][rand2] != 8)
			a[rand1][rand2] = 8;
		else
			i--;
	}

	for (i = 0; i < 8; i++)
		for (j = 0; j < 8; j++)
			if (a[i][j] >= 8)
			{
				a[i - 1][j - 1]++;
				a[i - 1][j]++;
				a[i - 1][j + 1]++;
				a[i][j - 1]++;
				a[i][j + 1]++;
				a[i + 1][j - 1]++;
				a[i + 1][j]++;
				a[i + 1][j + 1]++;
			}

	for (i = 0; i < 8; i++)
		for (j = 0; j < 8; j++)
			if (a[i][j] > 8)
				a[i][j] = 8;
}

void chance1(int a[][8], int p[][8])
{
	int i, j;
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			if (a[i][j] == 0)
			{
				p[j][i] = 1;
				gotoxy(2 * i + 11, j + 10);
				cout << a[i][j];
			}
			if (a[i][j - 1] == 0 && a[i][j] != 8)
			{
				p[j][i] = 1;
				gotoxy(2 * i + 11, j + 10);
				cout << a[i][j];
			}
			if (a[i - 1][j] == 0 && a[i][j] != 8)
			{
				p[j][i] = 1;
				gotoxy(2 * i + 11, j + 10);
				cout << a[i][j];
			}
			if (a[i + 1][j] == 0 && a[i][j] != 8)
			{
				p[j][i] = 1;
				gotoxy(2 * i + 11, j + 10);
				cout << a[i][j];
			}
			if (a[i][j + 1] == 0 && a[i][j] != 8)
			{
				p[j][i] = 1;
				gotoxy(2 * i + 11, j + 10);
				cout << a[i][j];
			}
			if (a[i + 1][j + 1] == 0 && a[i][j] != 8)
			{
				p[j][i] = 1;
				gotoxy(2 * i + 11, j + 10);
				cout << a[i][j];
			}
			if (a[i - 1][j - 1] == 0 && a[i][j] != 8)
			{
				p[j][i] = 1;
				gotoxy(2 * i + 11, j + 10);
				cout << a[i][j];
			}
		}
	}
}

void gameover(int a[][8])
{
	int i, j;
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			if (a[i][j] == 8)
			{
				gotoxy(2 * i + 11, j + 10);
				cout << "*";
			}
		}
	}
	gotoxy(25, 25);
	cout << "Sorry! Better Luck Next Time!!";
	gotoxy(30, 26);
	cout << "Game Over!!";
}
