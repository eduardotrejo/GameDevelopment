/* Name: Eduardo Trejo
*  Date: 11/17/13
*  File: battleship.cpp
*  Abstract: This program is battleship game. It features four boats, in two consecutive locations. It has a counter for
*  number of tries, functions to print the board, create boats, output requests, input guesses, and process guesses. Users
*  must hit all boats to win.
*/

#include <iostream>
#include <ctime> 
#include <iomanip>
using namespace std;

const int COLS = 10; // Constant for columns.
const int boats = 8; //Contstant boats.....4 boats with two locations

// Battleship function prototypes. 
void place_boats(char ocean[][COLS], int &rowRand, int &columnRand, int &rowRand2, int &columnRand2, int &rowRand3, int &columnRand3, int &rowRand4, int &columnRand4, int &rowRandb, int &columnRandb, int &rowRand2b, int &columnRand2b, int &rowRand3b, int &columnRand3b, int &rowRand4b, int &columnRand4b);
void print_board(char ocean[][COLS]);
int make_move(int &rowGuess, int &columnGuess);
void boat_hit(char ocean[][COLS], int rowGuess, int columnGuess, int rowRand, int columnRand, int &count, int rowRand2, int columnRand2, int &rowRand3, int &columnRand3, int &rowRand4, int &columnRand4, int &boathit, int &repeat, int &rowRandb, int &columnRandb, int &rowRand2b, int &columnRand2b, int &rowRand3b, int &columnRand3b, int &rowRand4b, int &columnRand4b);
void boat_miss(char ocean[][COLS], int rowGuess, int columnGuess, int rowRand, int columnRand, int &count, int &repeat, int rowRand2, int columnRand2, int &rowRand3, int &columnRand3, int &rowRand4, int &columnRand4, int &boathit, int &rowRandb, int &columnRandb, int &rowRand2b, int &columnRand2b, int &rowRand3b, int &columnRand3b, int &rowRand4b, int &columnRand4b);
void boat_gridbounds(char ocean[][COLS], int rowGuess, int columnGuess, int &count);
void boat_guessrepeat(char ocean[][COLS], int rowGuess, int columnGuess, int &count, int &repeat);

int main()
{
	srand((unsigned)time(NULL)); // Seeds Random Number Generater.

	// Constant for rows and columns. 
	const int ROWS = 10;
	const int COLS = 10;

	int rowGuess, columnGuess, count=0, repeat=0, boathit=0;
   //boat name variables init
	int rowRand=0, columnRand=0, rowRand2=0, columnRand2=0, rowRand3=0, columnRand3=0, rowRand4=0, columnRand4=0,
	rowRandb=0, columnRandb=0, rowRand2b=0, columnRand2b=0, rowRand3b=0, columnRand3b=0, rowRand4b=0, columnRand4b=0;


	char ocean[ROWS][COLS];
	cout << "Welcome to CST 231 BATTLESHIP!!!!\n" << endl;

	place_boats(ocean, rowRand, columnRand, rowRand2, columnRand2, rowRand3, columnRand3, rowRand4, columnRand4, rowRandb, columnRandb, rowRand2b, columnRand2b, rowRand3b, columnRand3b, rowRand4b, columnRand4b);
	print_board(ocean);
	// Repeat until the player guesses the correct location.
	do
	{
		while(boathit < boats)
		{
			make_move(rowGuess, columnGuess);
			boat_hit(ocean, rowGuess, columnGuess, rowRand, columnRand, count, rowRand2, columnRand2, rowRand3, columnRand3, rowRand4, columnRand4, boathit, repeat, rowRandb, columnRandb, rowRand2b,	 columnRand2b, rowRand3b, columnRand3b, rowRand4b, columnRand4b);
			boat_miss(ocean, rowGuess, columnGuess, rowRand, columnRand, count, repeat, rowRand2, columnRand2, rowRand3, columnRand3, rowRand4, columnRand4, boathit, rowRandb, columnRandb, rowRand2b,	 columnRand2b, rowRand3b, columnRand3b, rowRand4b, columnRand4b);
			boat_gridbounds(ocean, rowGuess, columnGuess, count);
			boat_guessrepeat(ocean, rowGuess, columnGuess, count, repeat);
		}
	}while(rowGuess != rowRand && columnGuess != columnRand && rowGuess != rowRand2 && columnGuess != columnRand2 && rowGuess != rowRand3 && columnGuess != columnRand3 && rowGuess != rowRand4 && columnGuess !=	 columnRand4 && rowGuess != rowRandb && columnGuess != columnRandb && rowGuess != rowRand2b && columnGuess != columnRand2b && rowGuess != rowRand3b && columnGuess != columnRand3b && rowGuess != rowRand4b	 && columnGuess != columnRand4b||
		rowGuess == rowRand && columnGuess != columnRand && rowGuess == rowRand2 && columnGuess != columnRand2 && rowGuess == rowRand3 && columnGuess != columnRand3 && rowGuess == rowRand4 &&	 columnGuess != columnRand4 && rowGuess == rowRandb && columnGuess != columnRandb && rowGuess == rowRand2b && columnGuess != columnRand2b && rowGuess == rowRand3b && columnGuess != columnRand3b &&	 rowGuess == rowRand4b && columnGuess != columnRand4b ||
		rowGuess != rowRand && columnGuess == columnRand && rowGuess != rowRand2 && columnGuess == columnRand2 && rowGuess != rowRand3 && columnGuess == columnRand3 && rowGuess != rowRand4 && columnGuess	 == columnRand4 && rowGuess != rowRandb && columnGuess == columnRandb && rowGuess != rowRand2b && columnGuess == columnRand2b && rowGuess != rowRand3b && columnGuess == columnRand3b && rowGuess !=	 rowRand4b && columnGuess == columnRand4b);	
		
		// Prints out the total of turns taken to hit the battleship.
		cout << "\nYou sank all my battleships in only " << count << " turns!\n" << endl;
		// Humanity
		cout << "Thanks for playing! Have a nice day!" << endl;

}

void place_boats(char ocean[][COLS], int &rowRand, int &columnRand, int &rowRand2, int &columnRand2, int &rowRand3, int &columnRand3, int &rowRand4, int &columnRand4, int &rowRandb, int &columnRandb, int &rowRand2b, int &columnRand2b, int &rowRand3b, int &columnRand3b, int &rowRand4b, int &columnRand4b)
{ 
	int position;
	do
	{
		rowRand = rand() % 10; columnRand = rand() % 10;    //boat 1
		rowRand2 = rand() % 10; columnRand2 = rand() % 10;  //boat 2
		rowRand3 = rand() % 10; columnRand3 = rand() % 10;  //boat 3
		rowRand4 = rand() % 10; columnRand4 = rand() % 10;  //boat 4
		
		//Sets up boat 1b, and assures it is within bounds.
		do
		{
			do
			{
				position = rand() % 3; //Position of boat (0=up,1=down, 2=left,3=right).
				switch(position)
				{
				case 0:
					rowRandb = rowRand-1;
					columnRandb = columnRand;
					break;
				case 1:
					rowRandb = rowRand+1;
					columnRandb = columnRand;
					break;
				case 2:
					rowRandb = rowRand;
					columnRandb = columnRand+1;
					break;
				case 3:
					rowRandb = rowRand;
					columnRandb = columnRand-1;
					break;
				}
			}while(rowRandb >= COLS && columnRandb >= COLS || rowRandb <= COLS && columnRandb >= COLS || rowRandb >= COLS && columnRandb <= COLS);
		}while(rowRandb < 0 || columnRandb < 0); //No negatives double check.

		//Sets up boat 2b, and assures it is within bounds.
		do
		{
			do
			{
				position = rand() % 3; //Position of boat (0=up,1=down, 2=left,3=right).
				switch(position)
				{
				case 0:
					rowRand2b = rowRand2-1;
					columnRand2b = columnRand2;
					break;
				case 1:
					rowRand2b = rowRand2+1;
					columnRand2b = columnRand2;
					break;
				case 2:
					rowRand2b = rowRand2;
					columnRand2b = columnRand2+1;
					break;
				case 3:
					rowRand2b = rowRand2;
					columnRand2b = columnRand2-1;
				break;
				}
			}while(rowRand2b >= COLS && columnRand2b >= COLS || rowRand2b <= COLS && columnRand2b >= COLS || rowRand2b >= COLS && columnRand2b <= COLS);
		}while(rowRand2b < 0 || columnRand2b < 0); //No negatives double check

		//Sets up boat 3b, and assures it is within bounds.
		do
		{
			do
			{
				position = rand() % 3; //Position of boat (0=up,1=down, 2=left,3=right).
				switch(position)
				{
				case 0:
					rowRand3b = rowRand3-1;
					columnRand3b = columnRand3;
					break;
				case 1:
					rowRand3b = rowRand3+1;
					columnRand3b = columnRand3;
					break;
				case 2:
					rowRand3b = rowRand3;
					columnRand3b = columnRand3+1;
					break;
				case 3:
					rowRand3b = rowRand3;
					columnRand3b = columnRand3-1;
					break;
				}
			}while(rowRand3b >= COLS && columnRand3b >= COLS || rowRand3b <= COLS && columnRand3b >= COLS || rowRand3b >= COLS && columnRand3b <= COLS);
		}while(rowRand3b < 0 || columnRand3b < 0); //No negatives double check.


		//Sets up boat 4b, and assures it is within bounds.
		do
		{
			do
			{
				position = rand() % 3; //Position of boat (0=up,1=down, 2=left,3=right).
				switch(position)
				{
				case 0:
					rowRand4b = rowRand4-1;
					columnRand4b = columnRand4;
					break;
				case 1:
					rowRand4b = rowRand4+1;
					columnRand4b = columnRand4;
					break;
				case 2:
					rowRand4b = rowRand4;
					columnRand4b = columnRand4+1;
					break;
				case 3:
					rowRand4b = rowRand4;
					columnRand4b = columnRand4-1;
					break;
				}
			}while(rowRand4b >= COLS && columnRand4b >= COLS || rowRand4b <= COLS && columnRand4b >= COLS || rowRand4b >= COLS && columnRand4b <= COLS);
		}while(rowRand4b < 0 || columnRand4b < 0); //NO negatives double check

	//Keeps looping until no two boats have same location, also assures no number is negative.
	}while(rowRand == rowRand2 && columnRand == columnRand2 &&
	   rowRand == rowRand3b && columnRand == columnRand3b &&
	   rowRand == rowRand4b && columnRand == columnRand4b &&
	   rowRandb == rowRand2 && columnRandb == columnRand2 &&
	   rowRand2 == rowRand3 && columnRand2 == columnRand3 &&
	   rowRand2 == rowRand3b && columnRand2 == columnRand3b &&
	   rowRand2b == rowRand3 && columnRand2b == columnRand3 &&
	   rowRand3 == rowRand4 && columnRand3 == columnRand4 &&
	   rowRand3 == rowRand2b && columnRand3 == columnRand2b &&
	   rowRand3b == rowRand4 && columnRand3b == columnRand4 &&
	   rowRand4 == rowRand2b && columnRand4 == columnRand2b &&
	   rowRand == rowRand4 && columnRand == columnRand4 &&
	   rowRand < 0 && rowRandb < 0 && rowRand2 < 0 && rowRand2b < 0 &&
	   rowRand3 < 0 && rowRand3b < 0 && rowRand4 < 0 && rowRand4b < 0); 

	////For debugging and testing purposes.
	cout << "For testing purposes: "<< endl; // Test.
	cout << "Boat 1: " << rowRand <<" " << columnRand << endl; 
	cout << "Boat 2: " << rowRand2 <<" " << columnRand2 << endl; 
	cout << "Boat 3: " << rowRand3 <<" " << columnRand3 << endl; 
	cout << "Boat 4: " << rowRand4 <<" " << columnRand4 << endl;
	cout << "Boat 1b: " << rowRandb <<" " << columnRandb << endl; 
	cout << "Boat 2b: " << rowRand2b <<" " << columnRand2b << endl;
	cout << "Boat 3b: " << rowRand3b <<" " << columnRand3b << endl; 
	cout << "Boat 4b: " << rowRand4b <<" " << columnRand4b << endl; 


}
void print_board(char ocean[][COLS])
{
	//Prints out created board.
	cout << " ";
	for(int a=0; a < COLS; a++)// Column labels.
	{
		cout << setw(2) << a;
    }
    cout << endl;
	for(int i=0; i < COLS; i++) 
	{
		cout << i << " "; // Row labels.
		for(int j=0; j < COLS; j++)
		{
			//Creates board with o's.
			ocean[i][j] = 'o';
			cout << ocean[i][j] << " ";
		}
		cout << "\n";
	}
}
int make_move(int &rowGuess, int &columnGuess)
{
	//outputs, takes in user data, processes and returns data
	cout << "\nWhich location would you like to guess? Enter row, then column: ";
	cin >> rowGuess >> columnGuess;

	return rowGuess, columnGuess;
}
void boat_hit(char ocean[][COLS], int rowGuess, int columnGuess, int rowRand, int columnRand, int &count, int rowRand2, int columnRand2, int &rowRand3, int &columnRand3, int &rowRand4, int &columnRand4, int &boathit, int &repeat, int &rowRandb, int &columnRandb, int &rowRand2b, int &columnRand2b, int &rowRand3b, int &columnRand3b, int &rowRand4b, int &columnRand4b)
{   
	// Checks if user already hit board for repeat output.
	if(ocean[rowGuess][columnGuess] == '*')
	{
		repeat++;
	}
	else if(rowGuess == rowRand && columnGuess == columnRand || 
			rowGuess == rowRand2 && columnGuess == columnRand2 ||
			rowGuess == rowRand3 && columnGuess == columnRand3 || 
			rowGuess == rowRand4 && columnGuess == columnRand4 ||
			rowGuess == rowRandb && columnGuess == columnRandb ||
			rowGuess == rowRand2b && columnGuess == columnRand2b ||
			rowGuess == rowRand3b && columnGuess == columnRand3b ||
			rowGuess == rowRand4b && columnGuess == columnRand4b)
		{
			//HIT a boat message
			cout << "HIT!\n" << endl;
			count++;
			boathit++;
			if(boathit < boats)
			{
				//prints out created board
				cout << " ";
				for(int a=0; a < COLS; a++)// Column labels.
				{
					cout << setw(2) << a;
				}
				cout << endl;
				for(int i=0; i < COLS; i++)
				{
					cout << i << " "; // Row labels.
					for(int j=0; j < COLS; j++)
					{			
						ocean[rowGuess][columnGuess] = '*';
						cout << ocean[i][j] << " ";		
					}
					cout << "\n";
				}
			}
		}	
}
void boat_miss(char ocean[][COLS], int rowGuess, int columnGuess, int rowRand, int columnRand, int &count, int &repeat, int rowRand2, int columnRand2, int &rowRand3, int &columnRand3, int &rowRand4, int &columnRand4, int &boathit, int &rowRandb, int &columnRandb, int &rowRand2b, int &columnRand2b, int &rowRand3b, int &columnRand3b, int &rowRand4b, int &columnRand4b)
{ 
	//Checks and makes sure boat has not been missed or if was hit.
	if(ocean[rowGuess][columnGuess] == 'x')
	{
		repeat++;
	}
	else if(ocean[rowGuess][columnGuess] == '*')
	{
		boathit;
	}
	else
	{
		//if none of above counts as miss.
		if( rowGuess != rowRand && columnGuess != columnRand && rowGuess < COLS && columnGuess < COLS || 
			rowGuess != rowRandb && columnGuess != columnRandb && rowGuess < COLS && columnGuess < COLS || 
			rowGuess != rowRand2 && columnGuess != columnRand2 && rowGuess < COLS && columnGuess < COLS || 
			rowGuess != rowRand2b && columnGuess != columnRand2b && rowGuess < COLS && columnGuess < COLS || 
			rowGuess != rowRand3 && columnGuess != columnRand3 && rowGuess < COLS && columnGuess < COLS ||
			rowGuess != rowRand3b && columnGuess != columnRand3b && rowGuess < COLS && columnGuess < COLS ||
			rowGuess != rowRand4 && columnGuess != columnRand4 && rowGuess < COLS && columnGuess < COLS ||
			rowGuess != rowRand4b && columnGuess != columnRand4b && rowGuess < COLS && columnGuess < COLS ||
			rowGuess == rowRand && columnGuess != columnRand && rowGuess < COLS && columnGuess < COLS || 
			rowGuess == rowRandb && columnGuess != columnRandb && rowGuess < COLS && columnGuess < COLS || 
			rowGuess == rowRand2 && columnGuess != columnRand2 && rowGuess < COLS && columnGuess < COLS || 
			rowGuess == rowRand2b && columnGuess != columnRand2b && rowGuess < COLS && columnGuess < COLS || 
			rowGuess == rowRand3 && columnGuess != columnRand3 && rowGuess < COLS && columnGuess < COLS || 
			rowGuess == rowRand3b && columnGuess != columnRand3b && rowGuess < COLS && columnGuess < COLS || 
			rowGuess == rowRand4 && columnGuess != columnRand4 && rowGuess < COLS && columnGuess < COLS || 
			rowGuess == rowRand4b && columnGuess != columnRand4b && rowGuess < COLS && columnGuess < COLS || 
			rowGuess != rowRand && columnGuess == columnRand && rowGuess < COLS && columnGuess < COLS || 
			rowGuess != rowRandb && columnGuess == columnRandb && rowGuess < COLS && columnGuess < COLS || 
			rowGuess != rowRand2 && columnGuess == columnRand2 && rowGuess < COLS && columnGuess < COLS ||
			rowGuess != rowRand2b && columnGuess == columnRand2b && rowGuess < COLS && columnGuess < COLS ||
			rowGuess != rowRand3 && columnGuess == columnRand3 && rowGuess < COLS && columnGuess < COLS || 
			rowGuess != rowRand3b && columnGuess == columnRand3b && rowGuess < COLS && columnGuess < COLS || 
			rowGuess != rowRand4 && columnGuess == columnRand4 && rowGuess < COLS && columnGuess < COLS ||
			rowGuess != rowRand4b && columnGuess == columnRand4b && rowGuess < COLS && columnGuess < COLS )
		{
			if(boathit != boats)
			{
				cout << "MISS!\n" << endl;
				count++;	
				
				cout << " ";
				for(int a=0; a < COLS; a++)// Column labels.
				{
					cout << setw(2) << a;
				}
				cout << endl;
				for(int i=0; i < COLS; i++)
				{
					cout << i << " "; // Row labels.
					for(int j=0; j < COLS; j++)
					{			
						ocean[rowGuess][columnGuess] = 'x';
						cout << ocean[i][j] << " ";		
					}
					cout << "\n";	
				}
			}	
		}
	}
}
void boat_gridbounds(char ocean[][COLS], int rowGuess, int columnGuess, int &count)
{
	//Assures user data is within boundary lines of our board.
	if(rowGuess >= COLS && columnGuess >= COLS || rowGuess <= COLS && columnGuess >= COLS || rowGuess >= COLS && columnGuess <= COLS)
	{
		cout << "That guess isn't even in the ocean!\n" << endl;
		count++;
	
		cout << " ";
		for(int a=0; a < COLS; a++)// Column labels.
		{
			cout << setw(2) << a;
		}
		cout << endl;
		for(int i=0; i < COLS; i++)
		{
			cout << i << " "; // Row labels.
			for(int j=0; j < COLS; j++)
			{			
				ocean[rowGuess][columnGuess] = 'o';
				cout << ocean[i][j] << " ";		
			}
			cout << "\n";
		}
	}
}
void boat_guessrepeat(char ocean[][COLS], int rowGuess, int columnGuess, int &count, int &repeat)
{
	//If input is repeated message oututs.
	if(ocean[rowGuess][columnGuess] == 'x' && repeat == 1)
	{
		cout << "You already guessed that location!\n" << endl;
		count++;
		repeat--;

		cout << " ";
		for(int a=0; a < COLS; a++)// Column labels.
		{
			cout << setw(2) << a;
		}
		cout << endl;
		for(int i=0; i < COLS; i++)
		{
			cout << i << " "; // Row labels.
			for(int j=0; j < COLS; j++)
			{			
				ocean[rowGuess][columnGuess] = 'x';
				cout << ocean[i][j] << " ";		
			}
			cout << "\n";
		}
	}
	//If user inputs already hit location outputs message.
	else if(ocean[rowGuess][columnGuess] == '*' && repeat == 1)
	{
		cout << "You already guessed that location!\n" << endl;
		count++;
		repeat--;

		cout << " ";
		for(int a=0; a < COLS; a++)// Column labels.
		{
			cout << setw(2) << a;
		}
		cout << endl;
		for(int i=0; i < COLS; i++)
		{
			cout << i << " "; // Row labels.
			for(int j=0; j < COLS; j++)
			{			
				ocean[rowGuess][columnGuess] = '*';
				cout << ocean[i][j] << " ";		
			}
			cout << "\n";
		}
	}
}