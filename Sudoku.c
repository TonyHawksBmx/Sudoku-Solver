#include<stdio.h>
#include<stdlib.h>
#include<ncurses.h>
#define N 9

void enterSudoku(int (*A)[N], WINDOW *W);
void printSudoku(int (*A)[N], WINDOW *W);
void resetSudoku(int (*A)[N], WINDOW *W);
int solveSudoku(int (*A)[N], int row , int col, WINDOW *W);
int checkLegal(int (*A)[N], int row, int col, int num);

int main(){
	int A[N][N]={
		{0,0,0,0,1,0,0,0,0},
		{0,0,0,0,2,0,0,0,0},
		{0,0,0,0,3,0,0,0,0},
		{0,0,0,0,4,0,0,0,0},
		{0,0,0,0,5,0,0,0,0},
		{0,0,0,0,6,0,0,0,0},
		{0,0,0,0,7,0,0,0,0},
		{0,0,0,0,8,0,0,0,0},
		{0,0,0,0,9,0,0,0,0}};
		
	WINDOW *w , *w1;
	
	char list[5][16] = {
		"Enter Sudoku ->",
		"Print Sudoku ->",
		"Solve Sudoku ->",
		"Reset Sudoku.",
		"Exit!"};
	
	char item[16];
	
	int ch, i=0, j=0, width = 16;
	
	initscr();
	
	w = newwin( 8, 20, 3, 1 );
	w1 = newwin (11, 28, 3, 30);
	box( w, '|', '-' );
	box( w1, '|', '-');
	mvwprintw(stdscr,2,1,"%s","MENU");
	mvwprintw(stdscr,2,30,"%s","SUDOKU");
	for( i=0; i<5; i++ ){
		if( i == 0 ) 
			wattron( w, A_STANDOUT );
		else
			wattroff( w, A_STANDOUT );
		sprintf(item, "%-15s",  list[i]);
		mvwprintw( w, i+1, 2, "%s", item );
	}
	wrefresh( w );
	
	printSudoku(A,w1);

	noecho();
	keypad( w, TRUE );
	curs_set( 0 );
	
	while(( ch = wgetch(w)) != 'q'){
		sprintf(item, "%-15s",  list[i]); 			
		mvwprintw( w, i+1, 2, "%s", item ); 
		switch( ch ) {
			case KEY_UP:
				i--;
				i = ( i<0 ) ? 4 : i;
				break;
			case KEY_DOWN:
				i++;
				i = ( i>4 ) ? 0 : i;
				break;
			case 10:
				switch(i){
					case 0:
						enterSudoku(A,w1);
						break;
					case 1:
						printSudoku(A,w1);
						break;
					case 2:
						solveSudoku(A,0,0,w1);
						break;
					case 3:
						resetSudoku(A,w1);
						break;
					case 4:
						delwin(w);
						delwin(w1);
						endwin();
						return 0;
				}
		}
		wattron( w, A_STANDOUT );
		sprintf(item, "%-15s",  list[i]);
		mvwprintw( w, i+1, 2, "%s", item);
		wattroff( w, A_STANDOUT );
	}
	delwin( w );
	delwin( w1 );
	endwin();
	return 0;
}

void enterSudoku (int (*A)[N],WINDOW *w){
	for(int i=0;i<N;i++){
		for (int j=0;j<N;j++){
			char c = 'A';
			int Num = 10;
			wattron(w, A_STANDOUT);
			mvwprintw(w, i+1, 3*j+1, "%d", A[i][j]);
			while (Num>N || Num<0){
				c=wgetch(w);
				Num=c-'0';
			}
			A[i][j]=Num;
			mvwprintw(w, i+1, 3*j+1, "%d", A[i][j]);
			wattroff(w, A_STANDOUT);
			mvwprintw(w, i+1, 3*j+1, "%d", A[i][j]);
		}
	}
	wrefresh(w);
}

void printSudoku (int (*A)[N], WINDOW *w){
	for (int i =0; i<N ; i++)
		for (int j =0; j<N; j++)
			mvwprintw( w, i+1, 3*j+1, "%d", A[i][j]);
	wrefresh(w);
}

void resetSudoku(int (*A)[N], WINDOW *w){
	for (int i =0; i<N ; i++)
		for (int j =0; j<N; j++)
			A[i][j]=0;
	printSudoku(A,w);		
}

int solveSudoku (int (*A)[N], int row, int col, WINDOW *w){
	if (row == N - 1 && col == N)
		return 1;
	if (col == N){
		row ++;
		col = 0;
	}
	if (A[row][col] > 0)
		return solveSudoku(A, row, col+1,w);
	for (int num =1; num <=N; num ++){
		if (checkLegal(A,row,col,num)){
			A[row][col]=num;
			if (solveSudoku(A,row,col+1,w) == 1)
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
