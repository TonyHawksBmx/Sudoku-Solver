#include<stdio.h>
#include<stdlib.h>

#define N 9

void enterSudoku(int (*A)[N]);
void printSudoku(int (*A)[N]);
int solveSudoku(int (*A)[N], int row , int col);
int checkLegal(int (*A)[N], int row, int col, int num);

int main(){
	int exit_status = system("gnome-terminal");
	int A[N][N]={
		{0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0},
		{0,0,2,0,0,5,1,0,0},
		{0,0,0,0,0,0,0,0,0},
		{0,0,3,0,0,8,0,0,0},
		{0,0,0,7,4,3,0,0,0},
		{0,0,7,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0}};
	//enterSudoku(A);
	printSudoku(A);
	printf("\n\n");
	if (solveSudoku(A,0,0) == 1)
		printSudoku(A);
	else
		printf("\nNo solution.");
	return 0;
}

	
void enterSudoku (int (*A)[N]){
	for(int i=0;i<N;i++){
		for (int j=0;j<N;j++){
			char c = 'A';
			int Num = 10;
			while (Num>N || N<0){
				c=getchar();
				Num=c-'0';
			}
			A[i][j]=N;
			printf ("\t");
		}
	}
}

void printSudoku (int (*A)[N]){
	for (int i =0; i<N ; i++){
		for (int j =0; j<N; j++){
			if (A[i][j] == 0)
				printf(" \t");
			else
				printf("%d\t",A[i][j]);
		}
		printf("\n\n");
	}
}

int solveSudoku (int (*A)[N], int row, int col){
	if (row == N - 1 && col == N)
		return 1;
	if (col == N){
		row ++;
		col = 0;
	}
	if (A[row][col] > 0)
		return solveSudoku(A, row, col+1);
	for (int num =1; num <=N; num ++){
		if (checkLegal(A,row,col,num)){
			A[row][col]=num;
			if (solveSudoku(A,row,col+1) == 1)
				return 1;
		}
		A[row][col] = 0;
	}
	return 0;
}

int checkLegal (int (*A)[N],int row,int col,int num){
	for (int x =0; x<N ; x++)
		if (A[row][x] == num)
			return 0;
	for (int x =0; x<N ; x++)
		if( A[x][col] == num)
			return 0;
	int startRow = row - row%3; 
	int startCol = col - col%3;
	for (int i= 0; i<3; i++)
		for ( int j =0; j<3; j++)
			if(A[i + startRow][j+startCol]==num)
				return 0;
	return 1;
}
