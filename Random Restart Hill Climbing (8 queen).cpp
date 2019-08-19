#include<bits/stdc++.h>
using namespace std;

const int N = 8;

int calcEvaluationFunction(int (&board)[N])
{
	int cnt = 0;
	for(int i = 0; i < 8; ++i)
	{
		for(int j = i+1; j < 8; ++j)
		{
			if(board[i] == board[j])
				++cnt;
			else if(abs(i-j) == abs(board[i]-board[j]))
				++cnt;
		}
	}
	return 28-cnt;			
}

void printBoard(int (&board)[N])
{
	int grid[10][10];
	memset(grid, 0, sizeof grid);
	for(int i = 0; i < 8; ++i)
		grid[ board[i] ][i] = 1;
	for(int i = 0; i < 8; ++i)
	{
		for(int j = 0; j < 8; ++j)
			cout << grid[i][j] << " ";
		cout << endl;
	}
	return;
}

void copyBoard(int (&board1)[N], int (&board2)[N])
{
	for(int i = 0; i < 8; ++i)
		board1[i] = board2[i];
}
	
bool hillClimbing(int (&board)[N])
{
	int bestBoard[N], bestValue, boardValue;
	copyBoard(bestBoard, board);
	
	int cnt = 0;
	while(1)
	{
		int currBoard[N], currValue;
		copyBoard(currBoard, board);
		boardValue = bestValue = calcEvaluationFunction(board);
		
		if(bestValue == 28)
		{
			cout << "Reached Global Maxima after " << cnt << " moves" << endl;
			printBoard(bestBoard);
			return 1;
		}
		
		++cnt;		
		for(int i = 0; i < 8; ++i)
		{
			int temp = currBoard[i];
			for(int j = 0; j < 8; ++j)
			{
				if(j == board[i])
					continue;
				currBoard[i] = j;
				currValue = calcEvaluationFunction(currBoard);
				if(currValue > bestValue)
				{
					bestValue = currValue;
					copyBoard(bestBoard, currBoard);
				}
			}
			currBoard[i] = temp;
		}
		if(bestValue <= boardValue)
		{
			cout << "Stucked in Local Maxima after " << cnt << " moves" << endl;
			printBoard(bestBoard);
			return 0;
		}
		copyBoard(board, bestBoard);
	}
}

int main()
{
	//~ freopen("output.txt", "w", stdout);
	srand(time(NULL));
	bool success = 0;
	int cnt = 1, board[N];
	while(1)
	{
		for(int i = 0; i < 8; ++i)
			board[i] = rand()%8;			
	
		cout << "======================== Iteration : " << cnt << endl;
		cout << "Initial Board" << endl;
		printBoard(board);
		success = hillClimbing(board);
		++cnt;
		
		if(success)
			break;
	}
	
	
	return 0;
}
