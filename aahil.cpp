#include<iostream>
using namespace std;
#include "Untitled3.h"
#define N 15
#define L 26
#include <vector>
#include <string>
#include <fstream>
#include<cstring>
#include<conio.h>
//#include<unistd.h>






//.......................................TRIE DATA-STRUCTURE..............................................................


class TrieNode{
public:
   char data;
   TrieNode* children[L];
   bool isTerminal;

   TrieNode(char ch){
       data = ch;
       for(int i=0;i<L;i++){
           children[i]=NULL;
       }
       isTerminal=false;
   }
};


class Trie_Tree {
TrieNode* root;
public:
   Trie_Tree() {
       root = new TrieNode('\0');
   }
   void insertUtil(TrieNode* root,string word){

       if(word.length() == 0){
           root->isTerminal=true;
           return;
       }

       int idx = word[0]-'a';
       TrieNode*child;

       if(root->children[idx] != NULL){
           child = root->children[idx];
       }

       else{
           child = new TrieNode(word[0]);
           root->children[idx]=child;
       }

       insertUtil(child,word.substr(1));
   }

   void insert(string word) {
     insertUtil(root,word);
   }
   bool searchUtil(TrieNode*root,string word){
       if(word.length()==0){
           return root->isTerminal;
       }
       int idx = word[0]-'a';
       TrieNode*child;

       if(root->children[idx]!=NULL){
           child = root->children[idx];
       }
       else{

           return false;
       }

       return searchUtil(child,word.substr(1));
   }

   bool search(string word) {
       return searchUtil(root,word);
   }
};



//...............................................function DECLARATION..................................................................................

Trie_Tree*t = new Trie_Tree();
Board board;
char xam;
int man;

bool horizontally(char **arr, string word, int i, int j);

bool* placehorizontally(char **arr, string word, int i, int j);

void unplacehorizontally(char **arr, bool* we, int i, int j);

bool vertically(char **arr, string word, int i, int j);

bool* placevertically(char **arr, string word, int i, int j);

void unplacevertically(char **arr, bool* we, int i, int j);

void print(char **arr, int size, vector<string>& hints);

void sortHighLow(vector<string>&,vector<string>&);

void makeCaps(vector<string>&);

bool checkForLetters(string);

string convertcap(string word);

//...............................................LOGIC FOR FIRST TWO CASES..................................................................................

void solution(char **arr, string words[], int idx, vector<string>hints, int T){
	system("CLS");
	if(board.complete(arr) == true){
		bool flag = board.checkboardsimple(arr);
		if(flag == false){
			board.congratulations(1);
			exit(1);
		}
		else {
			if(xam == '2'){

				man = 30;
				return;
			}
			board.congratulations(0);

		}
	}
		string word = words[idx];
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				if(arr[i][j] == '-' || arr[i][j] == word[0]){
					if(horizontally(arr,word,i,j)){
						bool *we = placehorizontally(arr,word,i,j);
						T1:
						print(arr,T,hints);
						cout<<"Write next word..if done write quit"<<endl;
						cin>>words[idx+1];
						words[idx+1] = convertcap(words[idx+1]);
						if(words[idx+1] == "B"){
							unplacehorizontally(arr,we,i,j);
							if(idx == 0){
								goto S1;
							}
							return;
						}
						solution(arr,words,idx+1,hints,T);
						if(man == 30){

							return;
						}
						goto T1;
					}
					if(vertically(arr,word,i,j)){
						bool *we = placevertically(arr,word,i,j);
						P1:
						print(arr,T,hints);
						cout<<"Write next word..if done write quit"<<endl;
						cin>>words[idx+1];
						words[idx+1] = convertcap(words[idx+1]);
						if(words[idx+1] == "B"){
							unplacevertically(arr,we,i,j);
							if(idx == 0){
								goto S1;
							}
							return;
						}
						solution(arr,words,idx+1,hints,T);
						if(man == 30){

							return;
						}
						goto P1;
					}

				}
			}
		}
		{
			cout<<"The letter couldnot be placed."<<endl;
			cout<<"Enter word"<<endl;
			cin>>words[idx];
			words[idx] = convertcap(words[idx]);
			if(words[idx] == "B")
				return;
			solution(arr,words,idx,hints,T);
			if(man == 30){

							return;
						}
		}
		if(idx == 0){
		S1:
		//for(int i=0;i<)
		print(arr,T,hints);
		cout<<"Enter word"<<endl;
		cin>>words[idx];
		words[idx] = convertcap(words[idx]);
		solution(arr,words,0,hints,T);
		if(man == 30){

							return;
						}
		goto S1;
	}
}




//...............................................SOLUTION FOR THIRD CASE....................................................................................

void solution_third(char **arr, string words[], int idx, vector<string>hints, int T){
	system("CLS");
	if(board.complete(arr) == true){
			board.congratulations(1);
			exit(1);
	}
		string word = words[idx];
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				if(arr[i][j] == '-' || arr[i][j] == word[0]){
					if(horizontally(arr,word,i,j)){
						placehorizontally(arr,word,i,j);
						print(arr,T,hints);
						cout<<"Write next word..if done write quit"<<endl;
						G1:
						cin>>words[idx+1];
							//trie
							if(t->search(words[idx+1]) == false){
								cout<<"WRONG. RE_ENTER "<<endl;
								goto G1;
							}
						words[idx+1] = convertcap(words[idx+1]);
						solution_third(arr,words,idx+1,hints,T);
					}
					if(vertically(arr,word,i,j)){
						placevertically(arr,word,i,j);
						print(arr,T,hints);
						cout<<"Write next word..if done write quit"<<endl;
						G2:
						cin>>words[idx+1];
						//trie
							if(t->search(words[idx+1]) == false){
									cout<<"WRONG. RE_ENTER "<<endl;
									goto G2;
								}
						words[idx+1] = convertcap(words[idx+1]);
						solution_third(arr,words,idx+1,hints,T);
					}

				}
			}
		}
}





//....................................................... MAIN FUNCTION ...................................................................................


int main(int argc, char *argv[]){

	cout << "\n\n------------------------------------------------" << endl;
	cout << "Welcome to the Crossword Anagram Puzzle Program" << endl;
	cout << "------------------------------------------------\n\n" << endl;

	vector<string> list;
	vector<string>hints;
	string temp;
	string tempc;
//.....................................................Checking files..................................................................
	if(argc==3) {

		ifstream ifs;
		ifstream ifclue;
		string file = argv[1];
		string clue = argv[2];
		ifs.open(file.c_str());
		ifclue.open(clue.c_str());


		if(!ifs){
			cout << "\nInvalid file name for names. Exiting program "<<endl;
			exit(1);
		}

		while(ifs.peek() != '.'){
			if(list.size()==20){
				cout << "--------------------------------------------" << endl;
				cout << "20 words have been placed - Maximum Reached" << endl;
				cout << "--------------------------------------------" << endl;
				cout << "\n" << endl;
				break;
			}
			getline(ifs, temp);
			getline(ifclue,tempc);
			if(checkForLetters(temp)){
				t->insert(temp);
				list.push_back(temp);
				hints.push_back(tempc);
			}
			else{
				cout << "Error: " << temp << " is not a valid word";
				cout << " or has too many letters (max 15)" << endl;
			}
		}

		ifs.close();
		ifclue.close();
	}

	else{
		cout<<"You have not entered filenames of 2 files .... exiting program"<<endl;
		exit(0);
	}

//..........................................................Starting of Display of Game.................................................................................
	system("color 70");
	cout<<endl;
	cout<<endl;
	cout<<"\t\t====================================\t\t"<<endl;
	cout<<"\t\t       CROSSWORD PUZZLE GAME        \t\t"<<endl;
	cout<<"\t\t====================================\t\t"<<endl;
	cout<<endl;
	cout<<endl;
	cout<<" \t\t________________________________________\t\t"<<endl;
	cout<<"\t\t| P | O | W | E | R | P | O | I | N | T |\t\t"<<endl;
	cout<<"\t\t| S |                               | E |\t\t"<<endl;
	cout<<"\t\t| H |   | E |   | W | O | R | D |   | X |\t\t"<<endl;
	cout<<"\t\t| A |   | X |                       | T |\t\t"<<endl;
	cout<<"\t\t| P |   | C |   | A |               | B |\t\t"<<endl;
	cout<<"\t\t| E |   | E |       | C |           | O |\t\t"<<endl;
	cout<<"\t\t| S |   | L |           | C |       | X |\t\t"<<endl;
	cout<<"\t\t    | S | H | E | E | T |   | E |        \t\t"<<endl;
	cout<<"\t\t                                | S |    \t\t"<<endl;
	cout<<"\t\t| W | O | R | K | S | H | E | E | T | S |\t\t"<<endl;
	cout<<"\t\t_________________________________________\t\t"<<endl;
	cout<<endl;
	cout<<endl;
	cout<<"\t\t";
  	system("color 00");
  	int a=133;
    for (int i = 0; i < 60; i++)
        cout<<(char)a;
    getch();
    cout<<"\r";
    cout<<"\t\t";
  	a = 219;

    for (int i = 0; i < 60; i++) {
        cout<<(char)a;
      //  sleep(1);
    }


	cout<<endl<<endl<<"PRESS ANY KEY TO CONTINUE"<<endl;
	getch();
	cout<<"WHICH TYPE OF GAME DO YOU WANT TO PLAY"<<endl;
	cout<<"\n\t1. CLASSIC\n\t2. LIMITED TIMES OF CHECKING\n\t3. AUTO_CORRECT"<<endl;
	LOVE:
	xam = getch();
	if(xam == '1'){
		//simple
	}
	else if(xam == '2'){
		//limited moves wali
	}
	else if(xam == '3'){
		//trie trees
		cout<<"PLEASE ENTER YOUR LETTERS IN SMALL CASE"<<endl;
		getch();
	}
	else{
		goto LOVE;
	}
//.....................................................Starting of Working of Game.............................................................................
	system("CLS");
	sortHighLow(list,hints);
	makeCaps(list);

	board.placeList(list,hints);

	cout << "\n\nHere's the hidden crossword puzzle:\n" << endl;
	board.printHidden();


	cout<<"\n\nHere are the clues! Each clue is an anagram of its solution\n"<<endl;


	for(int t=0; t<list.size(); t++){
		if(hints[t][0] != ' '){
			cout << "Row: "<<board.getRowLoc(t)<<", Column: "<<board.getColLoc(t);
			cout << "\t" << board.getDir(t);
			cout << "\t\t" <<hints[t]<< endl;
		}
	}

//.....................................................................FIRST OPTION......................................................................

	cout<<endl<<endl<<endl;
	cout << "\n\n------------------------------------------------" << endl;
	cout << "Enter Word" << endl;


	string word[20];
	cin>>word[0];
	word[0] = convertcap(word[0]);
	char **problem = new char*[N];
    for(int i=0;i<N;i++){
    	problem[i] = new char [N];
	}
	board.convertboard(problem);
	int T = list.size();

//.....................................................................SECOND OPTIONS......................................................................

	if(xam != '3'){

		solution(problem,word,0,hints,T);

		string wor[20];
		board.continuesolve(problem);
		print(problem,T,hints);
		cin>>word[0];
		wor[0] = convertcap(wor[0]);
		man = 0;
		solution(problem,wor,0,hints,T);

}
//.....................................................................THIRD OPTIONS......................................................................

	if(xam == '3'){
		solution_third(problem,word,0,hints,T);
	}
}


//.......................................................END OF MAIN FUNCTION...............................................................................



string convertcap(string word){
	for (int x=0; x<word.length(); x++)
       	word[x]	= toupper(word[x]);
    return word;
}

void sortHighLow(vector<string>& list, vector<string>&hints){
	string temp;
	string tempc;
	for(int i=0; i<list.size()-1; i++){
		for(int j=0; j<list.size()-i-1; j++){
			if(list[j].size() < list[j+1].size()){
				temp = list[j];
				list[j] = list[j+1];
				list[j+1] = temp;
				tempc = hints[j];
				hints[j] = hints[j+1];
				hints[j+1] = tempc;
				tempc = " ";
			}
		}
	}
}


void makeCaps(vector<string>& list){
	for(int i=0; i<list.size(); i++){
		for(int j=0; j<list[i].size(); j++){
			list[i][j] = toupper((list[i])[j]);
		}
	}
}


bool checkForLetters(string word){

	if(word.length()>15)
		return false;

	for(int i=0; i<word.size(); i++){
		if(word[i]<65 || word[i]>122 || (word[i]>90 && word[i]<97)){
			return false;
		}
	}
	return true;
}

bool* placehorizontally(char **arr, string word, int i, int j){
	bool *we = new bool[word.length()];

	for(int jj=0;jj<word.length();jj++){
		if(arr[i][j+jj] == '-'){
			arr[i][j+jj] = word[jj];
			we[jj] = true;
		}
	}
	return we;
}

bool* placevertically(char **arr, string word, int i, int j){
	bool *we = new bool[word.length()];

	for(int jj=0;jj<word.length();jj++){
		if(arr[i+jj][j] == '-'){
			arr[i+jj][j] = word[jj];
			we[jj] = true;
		}
	}
	return we;
}

void unplacehorizontally(char **arr, bool *we, int i, int j){
	for(int jj=0;jj<sizeof(we);jj++){
		if(we[jj] == true){
			arr[i][j+jj] = '-';
		}
	}
}

void unplacevertically(char **arr, bool *we, int i, int j){
	for(int jj=0;jj<sizeof(we);jj++){
		if(we[jj] == true){
			arr[i+jj][j] = '-';
		}
	}
}

void print(char **arr, int size, vector<string>& hints){
	cout << "\n\n------------------------------------------------" << endl;
	cout<<"   1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6"<<endl;
	for(int i=0; i<15; i++){
		if((i+1)/10 == 0)
			cout<<i+1<<"  ";
		else
			cout<<i+1<<" ";

		for(int j=0; j<15; j++){
				cout << arr[i][j];
			cout << " ";
		}
		cout << endl;
	}
	cout << "------------------------------------------------\n\n" << endl;

	cout<<"\n\nHere are the clues! Each clue is an anagram of its solution\n"<<endl;


	for(int t=0; t<size; t++){
		if(hints[t] != " "){
			cout << "Row: "<<board.getRowLoc(t)<<", Column: "<<board.getColLoc(t);
			cout << "\t" << board.getDir(t);
			cout << "\t\t" <<hints[t]<< endl;
		}
		else
			break;
	}

}

bool horizontally(char **arr, string word, int i, int j){
	if(j-1 >= 0 && arr[i][j-1] != '+')
		return false;
	else if(j+word.length() < N && arr[i][j+word.length()] != '+'){
		return false;
	}
	for(int jj=0;jj<word.length();jj++){
		if( (j+jj) >= N){
			return false;
		}
		if(arr[i][j+jj] == '-' || arr[i][j+jj] == word[jj]){
			continue;
		}
		else{
			return false;
		}
	}
	return true;
}

bool vertically(char **arr, string word, int i, int j){
	if(i-1 >= 0 && arr[i-1][j] != '+')
		return false;
	else if(i+word.length() < N && arr[i+word.length()][j] != '+'){
		return false;
	}
	for(int ii=0;ii<word.length();ii++){
		if( (i+ii) >=  N){
			return false;
		}
		if(arr[i+ii][j] == '-' || arr[i+ii][j] == word[ii]){
			continue;
		}
		else{
			return false;
		}
	}
	return true;
}

