#include "Untitled3.h"
#include<iostream>
using namespace std;
#include <vector>
#include <string>
#include<windows.h>
#include<conio.h>
Board::Board(){

	for(int i=0; i<15; i++){
		for(int j=0; j<15; j++){
			data[i][j] = '_';
		}
	}

	for(int row=0; row<20; row++){
		for(int col=0; col<2; col++){
			locations[row][col] = 0;
		}
	}
	// "place" keeps track of which word in list goes to which location
	// start at 1 because first (longest) word will be placed before the
	// method is called that places the next word on the board
	place = 1;

	// direction keeps track of the orientation of the words placed
	for(int i=0; i<20; i++){
		direction[i] = " ";
	}
}

Board::~Board() {}

void Board::printHidden(){
	cout<<"   1 2 3 4 5 6 7 8 9 0 1 2 3 4 5"<<endl;
	for(int i=0; i<15; i++){
		if((i+1)/10 == 0)
			cout<<i+1<<"  ";
		else
			cout<<i+1<<" ";

		for(int j=0; j<15; j++){
			if(data[i][j]=='_')
				cout << '+';
			else
				cout << '_';
			cout << " ";
		}
		cout << endl;
	}
}
void Board::correctboard(){
	cout<<"   1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6"<<endl;
	for(int i=0; i<15; i++){
		if((i+1)/10 == 0)
			cout<<i+1<<"  ";
		else
			cout<<i+1<<" ";

		for(int j=0; j<15; j++){
			if(data[i][j]=='_')
				cout << ' ';
			else
				cout << data[i][j];
			cout << " ";
		}
		cout << endl;
	}
}

void Board::setSpot(char c, int row, int col) {
	data[row][col] = c;
}

int Board::getRowLoc(int x){
	return locations[x][0]+1; // add 1 so the coordinates go from 1-15, not 0-14
}

int Board::getColLoc(int y){
	return locations[y][1]+1; // add 1 so the coordinates go from 1-15, not 0-14
}

void Board::placeList(vector<string>& list, vector<string>& hints){

	int hold;

	for(int i=0; i<list.size(); i++){
		if(i==0){
			for(int j=0; j<list[0].size(); j++)
				setSpot((list[0])[j], 7, (15-list[0].size())/2 + j);

			direction[0] = "ACROSS";
			locations[0][0] = 7;
			locations[0][1] = (15-list[0].size())/2;
		}

		if(i!=0 && i%2==0){
			if(placeNextVer(list[i])){
				direction[i] = "DOWN";
			}
			else if(placeNextHor(list[i])){
				direction[i] = "ACROSS";
			}
			else{
				cout << "Could not place word: " << list[i] << endl;
				list[i] = hints[i] = " ";
				place++;
				direction[i] = " ";
			}
		}
		else if(i!=0 && i%2!=0){
			if(placeNextHor(list[i])){
				direction[i] = "ACROSS";
			}
			else if(placeNextVer(list[i])){
				direction[i] = "DOWN";
			}
			else{
				cout << "Could not place word: " << list[i] << endl;
				list[i] = " ";
				place++;
				direction[i] = " ";
			}
		}
	}
}

char Board::getSpot(int i, int j) {
	return data[i][j];
}

string Board::getDir(int x){
	return direction[x];
}


bool Board::placeNextVer(string word){
	int match = 0;
	bool isPlaced = 0, key = 0;
		for(int j=0; j<15; j++){
			for(int i=0; i<15+1-word.size(); i++){
				for(int k=0; k<word.size(); k++){
					if(getSpot(i+k,j)=='_' || getSpot(i+k,j)==word[k]){
						match++;
					}
					if(getSpot(i+k,j)==word[k]){
						if(getSpot(i+k+1,j)=='_' && getSpot(i+k-1,j)=='_'){
							match += 2;
							key = 1;
						}
					}
					if(getSpot(i+k,j+1)=='_' && getSpot(i+k,j-1)=='_'){
						match += 2;
					}
					if(getSpot(i-1,j)=='_' && getSpot((i+word.size()),j)=='_'){
						if(k==0)
							match += 2;
					}
				} // end of "k" for loop
				if(match == 3*word.size()+2 && key == 1 && isPlaced == 0){
					// place word
					for(int p=0; p<word.size(); p++){
						setSpot(word[p], i+p, j);
					}
					// set isPlaced to true
					isPlaced = 1;
					// assign coordinates to the newly-placed word
					locations[place][0] = i;
					locations[place][1] = j;
					place++;
					return true;

				}
				match = 0;
				key = 0;
			}
		}
	return false;
}


bool Board::placeNextHor(string word){
	int match = 0;
	bool isPlaced = 0, key = 0;
		for(int j=0; j<15; j++){
			for(int i=0; i<15+1-word.size(); i++){
				for(int k=0; k<word.size(); k++){
					if(getSpot(j,i+k)=='_' || getSpot(j,i+k)==word[k]){
						match++;
					}
					if(getSpot(j,i+k)==word[k]){
						if(getSpot(j,i+k+1)=='_' && getSpot(j,i+k-1)=='_'){
							match = match+2;
							key = 1;
						}
					}
					if(getSpot(j+1,i+k)=='_'&&getSpot(j-1,i+k)=='_'){
						match = match + 2;
					}
					if(getSpot(j,i-1)=='_' && getSpot(j,i+word.size())=='_'){
						if(k==0) match = match + 2;
					}
				} // end of "k" for loop
				if(match == 3*word.size()+2 && key == 1 && isPlaced == 0){
					// place word
					for(int p=0; p<word.size(); p++){
						setSpot(word[p], j,i+p);
					}
					locations[place][0] = j;
					locations[place][1] = i;
					place++;

					// set isPlaced to true
					isPlaced = 1;
					return 1;

				}
				match = 0;
				key = 0;
			}
		}
	return 0;
}

void Board::convertboard(char **arr){

	for(int i=0; i<15; i++){
		for(int j=0; j<15; j++){
			if(data[i][j]=='_')
				arr[i][j] = '+';
			else
				arr[i][j] = '-';
		}
	}
}

bool Board::checkboardsimple(char **arr){
	for(int i=0;i<15;i++){
		for(int j=0;j<15;j++){
			if(arr[i][j] != data[i][j] && arr[i][j] != '+')
				return 1;
		}
	}
	return 0;
}

void Board::congratulations(bool flag){

	system("CLS");
	if(flag == 1){
		COORD coord;

		for(int j=50 ;j>=10;j--){
			int i=20;
	  	coord.X = i;
	  	coord.Y = j;
	  	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	 	system("Color 0D");
	 	cout<<"!    !    !    !    !    !    !    !    !    !    !    !    !    !    !    !"<<endl;
	 	system("Color 0A");
	 	cout<<"\t\t\t\t\t\tC O N G R A T U L A T I O N S"<<endl;
	 		int k=25;
	 	coord.X = k;
	  	coord.Y = j;
	  	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		system("Color 0C");
	 	cout<<"!    !    !    !    !    !    !    !    !    !    !    !    !    !    !    !"<<endl;
	 	system("cls");
	 	}
	 	 	system("Color 9");
	     static CONSOLE_FONT_INFOEX  fontex;
	     fontex.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	     HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	     GetCurrentConsoleFontEx(hOut, 0, &fontex);
	     fontex.FontWeight = 700;
	     fontex.dwFontSize.X = 36;
	     fontex.dwFontSize.Y = 36;
	     SetCurrentConsoleFontEx(hOut, NULL, &fontex);
	 		cout<<endl;
	 	 	cout<<"\t\t\t ****************************"<<endl;
	 	 	cout<<"\t\t\t        CONGRATULATION  "<<endl;
	 	 	cout<<"\t\t\t ****************************"<<endl;
	 	 }

	else{
			cout<<endl;
	 	 	cout<<"\t\t\t ****************************"<<endl;
	 	 	cout<<"\t\t\t            YOU LOST  "<<endl;
	 	 	cout<<"\t\t\t ****************************"<<endl;
	 	 	getch();
	 	 	system("CLS");
	 	 	cout<<"\n\n\n\t\t\t ****************************"<<endl;
	 	 	cout<<"\t\t\t CORRECT BOARD  "<<endl;
	 	 	cout<<"\t\t\t ****************************"<<endl;
	 	 	correctboard();
	}
}

void Board::continuesolve(char **arr){
	for(int i=0;i<15;i++){
		for(int j=0;j<15;j++){
			if(arr[i][j] != data[i][j] && arr[i][j] != '+')
				arr[i][j] = '-';
		}
	}
}

bool Board::complete(char **arr){
	for(int i=0;i<15;i++){
		for(int j=0;j<15;j++){
			if(arr[i][j] == '-')
				return 0;
		}
	}
	return 1;
}
