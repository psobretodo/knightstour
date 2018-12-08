//
//  main.cpp
//  KnightsTour
//
//  Created by Phillip Sobretodo on 9/22/18.
//  Copyright © 2018 Phillip Sobretodo. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

bool inBounds(int a, int b)
{
    if(a >= 0 && a <= 7 && b >= 0 && b <= 7)
        return true;
    else
        return false;
}

int  nextMove(int square, int move)
{
    return square+move;
}

void print(int BOARD[8][8])
{
    for (int i = 0; i <= 7; i++)
    {
        for (int j = 0; j <= 7; j++)
        {
            cout << setw(5) << right << BOARD[i][j] << setw(5) << right;
        }
        cout << endl;
    }
    return;
}

int main()
{
    int BOARD[8][8];
    int i = 0; //rows
    int j = 0; //columns
    
    int KTMOVI[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
    int KTMOVJ[8] = {1, 2, 2, 1, -1, -2, -2, -1};
    
    for(int row = 0; row <= 7; row++)
    {
        for(int col = 0; col <= 7; col++)
        {
            BOARD[row][col] = 0;
        }
    }
    
    cout << "Input your starting point (row, col)" << endl;
    cin >> i >> j;
    cout << "Your starting point is: " << "(" << i << "," << j << ")" << endl;
    i--; //decrements to fit 0-7
    j--; //decrements to fit 0-7
    
    BOARD[i][j] = 1; //assigns initial point as 1
    
    if(inBounds(i, j)) //if initial point is on board
    {
        for(int m = 2; m <= 64; m++) //while board is not filled
        {
            int NPOS = 0; //set number of possibilities to 0
            int K[7]; //K[] holds the position of ktmov array
            int b = 0; //keeps track of K
            for(int a = 0; a <= 7; a++)
            {
                int iMove = KTMOVI[a];
                int jMove = KTMOVJ[a];
                int iNext = nextMove(i, iMove);
                int jNext = nextMove(j, jMove);
                
                if(BOARD[iNext][jNext] == 0 && inBounds(iNext, jNext))
                {
                    NPOS++;
                    K[b] = a;
                    b++;
                }
            }
            
            if(NPOS > 0)
            {
                if(NPOS == 1)
                {
                    i += KTMOVI[K[0]];
                    j += KTMOVJ[K[0]];
                    BOARD[i][j] = m;
                }
                else
                {
                    int EXITS[NPOS];
            
                    for(int l = 0; l < NPOS; l++)
                    {
                        int counter = 0;
                        //EXITS[l] = 0;
                        for(int n = 0; n <= 7; n++)
                        {
                            int iMove = nextMove(i, KTMOVI[K[l]]);
                            int jMove = nextMove(j, KTMOVJ[K[l]]);
                            int iNext = nextMove(iMove, KTMOVI[n]);
                            int jNext = nextMove(jMove, KTMOVJ[n]);
                            
                            if(BOARD[iNext][jNext] == 0 && inBounds(iNext, jNext))
                            {
                                counter++;
                            }
                        }
                        EXITS[l] = counter;
                    }
                    
                    int MIN = 0;
                    int smallest = EXITS[0];
                    for(int find = 1; find < NPOS; find++)
                    {
                        if(EXITS[find] < smallest)
                        {
                            smallest = EXITS[find];
                            MIN = find;
                        }
                    }
                    
                    i += KTMOVI[K[MIN]];
                    j += KTMOVJ[K[MIN]];
                    BOARD[i][j] = m;
                    
                }
            }
            else
            {
                cout << "Error, Knight movement ended prematurely." << endl;
                m = 64;
            }
        }
        
        print(BOARD);
    }
    else
    {
        cout << "Error, invalid initial points" << endl;
    }
    

    return 0;
}
 


