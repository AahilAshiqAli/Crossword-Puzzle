#ifndef UNTITLED_H
#define UNTITLED_H
#include <vector>
#include <string>
using namespace std;
class Board {
		char data[15][15];
		int locations[20][2];
		string direction[20];
		int place;
	public:
		Board();
		~Board();
		char getSpot(int, int);
		int getRowLoc(int);
		int getColLoc(int);
		string getDir(int);
		void setSpot(char, int, int);
		void placeList(vector<string>&, vector<string>&);
		bool placeNextVer(string);
		bool placeNextHor(string);
		void printHidden();
		void convertboard(char **);
		bool checkboardsimple(char **);
		void congratulations(bool);
		void addcharacters(char **arr);
		void correctboard();
		void continuesolve(char **arr);
		bool complete(char **arr);
};

#endif
