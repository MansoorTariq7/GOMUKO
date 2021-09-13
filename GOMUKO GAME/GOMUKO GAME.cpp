#include <iostream>
#include <fstream>
#include <time.h>
#include <conio.h>
#include <windows.h>

using namespace std;

void gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}
void allocation(char**& B, int& row, int& coloum, int& nop, char Ns[][50], char*& si, int& wc, int& pid);
void displaygrid(char** B, int row, int coloum);
void displayplayerid(char* name);
void taketurn(int& pr, int& pc, int row, int col);
bool illigalmove(char** B, int pr, int pc, int row, int coloum, int nop, char* si);
void placeonbox(char**& B, int pr, int pc, char symbol);
void turnchange(int& pid, int nop);
bool checkrowcol(int pr, int pc, int row, int col);
bool sumwinner(char** B, int row, int coloum, int wc, char* si, int nop);
bool col(char** B, int row, int coloum, int wc, char* si, int nop);
bool sumcol(int ri, int  ci, char** B, int wc, char* si, int nop);
bool rowcheck(char ** B,int row,int coloum,int wc,char* si,int nop);
bool sumrow(int row ,int ri, int  ci, char** B, int wc, char* si, int nop);
bool digcheckright(char** B, int row, int coloum, int wc, char* si, int nop);
bool sumdigright(int row, int ri, int  ci, char** B, int wc, char* si, int nop);
bool digcheckleft(char** B, int row, int coloum, int wc, char* si, int nop);
bool sumdigleft(int row, int ri, int  ci, char** B, int wc, char* si, int nop);
void winner(char name [] [50] , int pid);


int main()
{
	char ** B = nullptr;
	int row = 0;
	int coloum = 0; 

	int nop = 0;
	char Ns[10][50];
	char* si = 0;
	int wc = 0;
	int pr, pc;
	int pid = 0 ;

	srand(time(0));
	cout << " WELCOME TO GOMUKO " << endl ;
	cout << " THIS VERSION OF GOMUKO IS MADE BY MANSOOR TARIQ " << endl;
	cout << endl;
	allocation(B, row, coloum, nop, Ns , si, wc , pid);
	do
	{
		displaygrid(B, row, coloum);
		displayplayerid(Ns[pid]);
		do
		{
			taketurn(pr, pc,row,coloum);

		} while (!(illigalmove(B, pr, pc, row, coloum, nop, si)));
		placeonbox(B, pr, pc, si[pid]);
		turnchange(pid, nop);

	} while (sumwinner(B, row, coloum, wc, si, nop));
	
	system("CLS");
	displaygrid(B, row, coloum);
	turnchange(pid, nop);
	winner(Ns,pid);
	
}


void allocation(char**& B, int& row, int& coloum, int& nop, char Ns[][50], char * & si,int & wc , int & pid )
{
	ifstream fin("gomuko.txt");

	cout << "ENTER THE HIGHT OF THE GRID YOU WANT TO PLAY IN :: = ";
	cin >> row;
	cout << endl;
	cout << "ENTER THE WRITH OF THE GRID YOU WANT TO PLAY IN :: = ";
	cin >> coloum;
	cout << endl;

	B = new char * [row];
	for (int r = 0; r < row; r++)
	{
		B[r] = new char[coloum];
	}

	for (int ri = 0; ri < row; ri++)
	{
		for (int ci = 0; ci < coloum; ci++)
		{
			B[ri][ci] = '_';
		}
	}

	cout << " ENTER THE NUMBERS OF PLAYERS :: = ";
	cin >> nop;
	cout << endl;
	
	si = new char[nop];
	for (int id = 0; id < nop; id++)
	{
		cout << " ENTER THE SYMBOL OF THE PLAYER " << id+1 << " :: =  ";
		cin >> si [id]; 
		cout << endl;
		cout << " ENTER THE NAME OF THE PLAYER " << id+1 << " :: =  ";
		cin >> Ns[id];
		cout << endl;
	}

	cout << " ENTER THE POINTS ON WHICH GAME SHOULD DECLARE A WINNER :: =  ";
	cin >> wc;
	cout << endl;
	
	pid = rand() % nop;

	system("CLS");
}
void displaygrid (char **  B,int row,int coloum)
{
	system("CLS");
	cout << "\t" ;
 	for (int ci = 0; ci < coloum; ci++)
	{
		cout << ci+1 << "\t";
	}
	cout << endl;
	cout << endl;
	for (int ri = 0; ri < row; ri++)
	{
		cout << ri+1 << "\t";
		
		for (int ci = 0; ci < coloum; ci++)
		{
			cout << B[ri][ci] << "\t" ;
		}
		cout << endl;
		cout << endl;
	}
	cout << endl;
}
void displayplayerid(char * name)
{	
	cout << endl;
	cout << "\t\t\t\t\t\t\t\t";
	cout << " THIS IS PLAYER '' " << name << "  '' 's TURN " << endl;
}
void taketurn(int & pr , int & pc , int row , int col)
{
	do
	{
		cout << endl;
		cout << "\t\t\t\t\t\t\t\t";
		cout << " ENTER THE LINE NUMBER :: ";
		cin >> pr;
		pr--;
		
		cout << endl;
		cout << "\t\t\t\t\t\t\t\t";
		cout << " ENTER THE BOX NUMBER ::  ";
		cin >> pc;
		pc--;
	} while (!checkrowcol(pr,pc,row,col));
}
bool checkrowcol(int pr, int pc, int row, int col)
{
	bool condition = true;

	if (pr > row)
	{
		cout << " INVALID MOVE ...... ENTER THE ROW AGAIN " << endl;
		condition = false;
		return condition;
	}
	else if (pc > col)
	{
		cout << " INVALID MOVE ...... ENTER THE BOX AGAIN " << endl;
		condition = false;
		return condition;
	}
	return condition;

}
bool illigalmove(char** B, int pr, int pc, int row, int coloum, int nop , char * si)
{	
	bool condition = true;

	/*for (int ri = 0; ri < row; ri++)
	{
		for (int ci = 0; ci < coloum; ci++)
		{
			if (B[ri][ci] == 
		}
		cout << endl;
	}*/

	for (int i = 0 ; i < nop; i++)
	{
		if (B[pr][pc] == si[i])
		{
			condition = false;
			cout << " YOU HAVE ENTERED AN INVALID ENTRY  ............. ENTER AGAIN " << endl;
			return condition;
		}
	}
	condition = true;
	return condition;

}
void placeonbox(char ** & B, int pr , int pc , char symbol)
{

	B[pr][pc] = symbol;

}
void turnchange(int & pid  , int nop)
{
	pid = (pid + 1) % nop;
}
bool sumwinner(char ** B , int row, int coloum , int wc , char* si , int nop)
{	
	if (!col(B, row, coloum, wc, si, nop))
	{
		return false;
	}
	else if (!rowcheck(B, row, coloum, wc, si, nop))
	{
		return false;
	}
	else if (!digcheckright(B, row, coloum, wc, si, nop))
	{
		return false;
	}
	else if (!digcheckleft(B, row, coloum, wc, si, nop))
	{
		return false;
	}
}
bool rowcheck(char ** B, int row, int coloum, int wc, char* si, int nop)
{
	bool condition = true;
	for (int ci = 0; ci < coloum; ci++)
	{
		for (int ri = 0; ri < row; ri++)
		{
			if (sumrow(row,ri, ci, B, wc, si, nop))
			{
				condition = false;
				return condition;
			}
		}
	}
	return condition;
}
bool sumrow(int row ,int ri, int  ci, char** B, int wc, char* si, int nop)
{
	bool condition = false;
	int sum = 0;
	char ai = 0;
	for (int a = 0; a < nop; a++)
	{
		ai = a;
		for (int r = ri; r < ri + wc; r++)
		{
			if (r < row)
			if (B[r][ci] == si[a])
			{
				sum++;
			}
			if (sum == wc)
			{
				condition = true;
				return condition;
			}

		}
		sum = 0;
	}
	return condition;
}
bool col(char** B, int row, int coloum, int wc, char* si, int nop)
{
	bool condition = true;
	for (int ri = 0; ri < row; ri++)
	{
		for (int ci = 0; ci < coloum; ci++)
		{
			if (sumcol(ri, ci, B, wc, si, nop))
			{
				condition = false;
				return condition;
			}
		}
	}
	return condition;
}
bool sumcol(int ri, int  ci, char** B , int wc, char* si,int nop)
{
	bool condition = false;
	int sum = 0;
	char ai = 0; 
	for (int a = 0 ; a < nop ; a++)
	{
		ai = a;
		for (int c = ci; c < ci + wc; c++)
		{
			if (B[ri][c] == si[a])
			{
				sum++;
			}
			if (sum == wc)
			{
				condition = true;
				return condition;
			}

		}
		sum = 0;
	}
	return condition;

}
void winner(char name [] [50] ,int pid)
{
	cout << "\t\t\t\t\t\t\t\t\t THE PLAYER [ " << name[pid] << " ] IS THE WINNER " << endl;
	cout << "\t\t\t\t\t\t\t\t CONGRATULATION'S   " << name[pid] << "   ON WINNING THE GAME " << endl << endl ;
	cout << "\t\t\t\t\t\t\t" << name[pid] << " YOU ARE THE WINNER OF GOMUKO VERSION MADE BY MANSOOR TARIQ " << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
}
bool digcheckright(char** B, int row, int coloum, int wc, char* si, int nop)
{
	bool condition = true;
	for (int ci = 0; ci < coloum; ci++)
	{
		for (int ri = 0; ri < row; ri++)
		{
			if (sumdigright(row, ri, ci, B, wc, si, nop))
			{
				condition = false;
				return condition;
			}
		}
	}
	return condition;
}
bool sumdigright(int row, int ri, int  ci, char** B, int wc, char* si, int nop)
{
	bool condition = false;
	int sum = 0;
	char ai = 0;
	for (int a = 0; a < nop; a++)
	{
		ai = a;
		for (int r = ri; r < ri + wc; r++)
		{
			if (r < row)
				if (B[r][r] == si[a])
				{
					sum++;
				}
			if (sum == wc)
			{
				condition = true;
				return condition;
			}

		}
		sum = 0;
	}
	return condition;
}
bool digcheckleft(char** B, int row, int coloum, int wc, char* si, int nop)
{
	bool condition = true;
	for (int ci = 0; ci < coloum; ci++)
	{
		for (int ri = 0; ri < row; ri++)
		{
			if (sumdigleft(row, ri, ci, B, wc, si, nop))
			{
				condition = false;
				return condition;
			}
		}
	}
	return condition;
}
bool sumdigleft(int row, int ri, int  ci, char** B, int wc, char* si, int nop)
{
	bool condition = false;
	int sum = 0;
	char ai = 0;
	int w = 0;
	int temp = ri;
	for (int a = 0; a < nop; a++)
	{
		ai = a;
		
		for (int r = ri ; r < ri + wc; r++)
		{
			if (r < row )
			if (B[r][temp] == si[a])
			{
				sum++;
				temp--;
			}
			if (sum == wc)
			{
				condition = true;
				return condition;
			}
			
		}
		sum = 0;
	}
	return condition;
}


















