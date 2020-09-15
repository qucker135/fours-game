#include <iostream>

using namespace std;

int rows=0,columns=0;
bool player_nr = 0;
int Xs=0,Os=0;

void showBoard(char** tab,int columns, int rows)
{
	for(int i=0;i<rows;i++){
		for(int j=0;j<columns;j++){
			cout<<"  "<<tab[j][rows-1-i];
		}
		cout<<endl<<endl;
	}
	for(int i=1;i<=columns;i++){
		if(i<10) cout<<"  "<<i;
		else cout<<" "<<i;
	}
	cout<<endl<<endl;
}

char checkBoardState(char** tab,int columns,int rows){
	bool BoardFull = true;
	for(int i=0;i<columns;i++){
		for(int j=0;j<rows;j++){
			if(tab[i][j]=='_') BoardFull = false;
			//check if someone's just won
			bool down=false,up=false,right=false,left=false; //directions to check
			
			if(j>=3){
				down=true;
				if(tab[i][j]==tab[i][j-1]&&tab[i][j-1]==tab[i][j-2]&&tab[i][j-2]==tab[i][j-3]){
					if(tab[i][j]=='x'){
						return 'x';break;
					}
					else if(tab[i][j]=='o'){
						return 'o';break;
					}
				}
			}
			
			if(j<=rows-4){
				up=true;
				if(tab[i][j]==tab[i][j+1]&&tab[i][j+1]==tab[i][j+2]&&tab[i][j+2]==tab[i][j+3]){
					if(tab[i][j]=='x'){
						return 'x';break;
					}
					else if(tab[i][j]=='o'){
						return 'o';break;
					}
				}
			}
			
			if(i>=3){
				left=true;
				if(tab[i][j]==tab[i-1][j]&&tab[i-1][j]==tab[i-2][j]&&tab[i-2][j]==tab[i-3][j]){
					if(tab[i][j]=='x'){
						return 'x';break;
					}
					else if(tab[i][j]=='o'){
						return 'o';break;
					}
				}
			}
			
			if(i<=columns-4){
				right=true;
				if(tab[i][j]==tab[i+1][j]&&tab[i+1][j]==tab[i+2][j]&&tab[i+2][j]==tab[i+3][j]){
					if(tab[i][j]=='x'){
						return 'x';break;
					}
					else if(tab[i][j]=='o'){
						return 'o';break;
					}
				}
			}
			
			//SKEWS
			
			if(up&&right){
				if(tab[i][j]==tab[i+1][j+1]&&tab[i+1][j+1]==tab[i+2][j+2]&&tab[i+2][j+2]==tab[i+3][j+3]){
					if(tab[i][j]=='x'){
						return 'x';break;
					}
					else if(tab[i][j]=='o'){
						return 'o';break;
					}
				}
			}
			
			if(up&&left){
				if(tab[i][j]==tab[i-1][j+1]&&tab[i-1][j+1]==tab[i-2][j+2]&&tab[i-2][j+2]==tab[i-3][j+3]){
					if(tab[i][j]=='x'){
						return 'x';break;
					}
					else if(tab[i][j]=='o'){
						return 'o';break;
					}
				}
			}
			
			if(down&&left){
				if(tab[i][j]==tab[i-1][j-1]&&tab[i-1][j-1]==tab[i-2][j-2]&&tab[i-2][j-2]==tab[i-3][j-3]){
					if(tab[i][j]=='x'){
						return 'x';break;
					}
					else if(tab[i][j]=='o'){
						return 'o';break;
					}
				}
			}
			
			if(down&&right){
				if(tab[i][j]==tab[i+1][j-1]&&tab[i+1][j-1]==tab[i+2][j-2]&&tab[i+2][j-2]==tab[i+3][j-3]){
					if(tab[i][j]=='x'){
						return 'x';break;
					}
					else if(tab[i][j]=='o'){
						return 'o';break;
					}
				}
			}
			
		}
	}
	if(!BoardFull) return 'n';
	else return 'd';
}

int main(){
	
	cout<<endl;
	
	do{
		cout<<"  Insert number of columns(4-99): ";cin>>columns;
	}while(columns<4||columns>99);
	
	do{
		cout<<"  Insert number of rows(4-99): ";cin>>rows;
	}while(rows<4||rows>99);
	
	char** tab = new char*[columns];
	
	for(int i=0;i<columns;i++){
		tab[i] = new char[rows];
	}
	
	for(int i=0;i<columns;i++){
		for(int j=0;j<rows;j++){
			tab[i][j] = '_';
		}
	}
	
	int* indeces = new int[columns];
	
	for(int i=0;i<columns;i++){
		indeces[i] = 0;
	}
	
	while(checkBoardState(tab,columns,rows)=='n') // while nobody won
	{
		showBoard(tab,columns,rows);
		int bfr;
		a:
		bfr=0;
		while(bfr<1||bfr>columns||indeces[bfr-1]>=rows){
			if(!player_nr)cout<<"  PlayerX>";
			else cout<<"  PlayerO>";
			cin>>bfr;
		}
		
		if(!player_nr) // Player1
		{
			tab[bfr-1][indeces[bfr-1]] = 'x';
			indeces[bfr-1]++;
			Xs++;
		}
		if(player_nr) // Player2
		{
			tab[bfr-1][indeces[bfr-1]] = 'o';
			indeces[bfr-1]++;
			Os++;
		}		
		
		if(checkBoardState(tab,columns,rows)=='x'&&Xs==4){
			indeces[bfr-1]--;
			tab[bfr-1][indeces[bfr-1]] = '_';
			Xs--;
			showBoard(tab,columns,rows);
			cout<<"  It is not permitted!!!"<<endl;
			cout<<"  You are not allowed to win in the first four moves."<<endl;
			cout<<"  Try to choose another column."<<endl;
			goto a;
		}
		
		if(checkBoardState(tab,columns,rows)=='o'&&Os==4){
			indeces[bfr-1]--;
			tab[bfr-1][indeces[bfr-1]] = '_';
			Os--;
			showBoard(tab,columns,rows);
			cout<<"  It is not permitted!!!"<<endl;
			cout<<"  You are not allowed to win in the first four moves."<<endl;
			cout<<"  Try to choose another column."<<endl;
			goto a;
		}
		
		player_nr = 1 - player_nr;
		
	}
	
	showBoard(tab,columns,rows);
	
	switch(checkBoardState(tab,columns,rows))
	{
		case 'x':
			cout<<"PlayerX wins!"<<endl;break;
		case 'o':
			cout<<"PlayerO wins!"<<endl;break;
		case 'd':
			cout<<"Draw"<<endl;break;
			
	}
	
	for(int i=0;i<columns;i++){
		delete[] tab[i];
	}
	
	delete[] tab;
	delete[] indeces;
 	
	return 0;
}
