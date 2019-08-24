#include<bits/stdc++.h>
using namespace std;

struct node
{
    int board[8], heuristic;
    double probability;
};

int calc_heuristic(int board[])
{

    int count =0;

    for(int i=0; i<8; i++)
    {
        for(int j=i+1; j<8; j++)
        {
            if(board[i]==board[j])
                count++;
            else if(abs(board[i]-board[j])==abs(i-j))
                count++;
        }
    }
    return 28-count;
}

void print_board(int board[])
{
    for(int i = 0; i < 8; ++i)
        cout << board[i] << " ";
    cout << endl << endl;
}

void crossover(int board1[], int board2[])
{
    srand(time(NULL));
    int in = rand()%8;

    for(int i = in+1; i < 8; ++i)
        swap(board1[i], board2[i]);

    print_board(board1);
    print_board(board2);
}

void mutation(int board[])
{
    srand(time(NULL));
    int mutate=rand()%2;
    if(mutate)
    {
        int n = rand()%8;
        int val = rand()%8;
        board[n] = val;
    }
    print_board(board);
}

bool cmp(node a, node b)
{
    return a.probability > b.probability;
}

int main()
{
    srand(time(NULL));

    node arr[4];
    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 8; ++j)
            arr[i].board[j] = rand() % 8;

    cout << "Initial States" << endl;
    for(int i = 0; i < 4; ++i)
        print_board(arr[i].board);

    cout << "Crossover:" << endl;
    for(int i = 0; i < 4; i += 2)
        crossover(arr[i].board, arr[i+1].board);

    cout << "Mutation" << endl;
    for(int i = 0; i < 4; ++i)
        mutation(arr[i].board);

    double total_heuristic = 0;
    for(int i = 0; i < 4; ++i)
    {
        arr[i].heuristic = calc_heuristic(arr[i].board);
        total_heuristic += arr[i].heuristic;
    }

    for(int i = 0; i < 4; ++i)
        arr[i].probability = (arr[i].heuristic / total_heuristic) * 100;


    sort(arr, arr+4, cmp);
    cout << "After Sort" << endl;
    for(int i = 0; i < 4; ++i)
    {
        cout << "Probability: " << arr[i].probability << "% | Heuristic: " << arr[i].heuristic << " | Board: ";
        print_board(arr[i].board);
    }

    return 0;
}


