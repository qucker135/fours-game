#include <iostream>

using namespace std;

int wierszy=0,kolumn=0;
bool nr_gracza = 0;
int iksow=0,kolek=0;

void wyswietlPlansze(char** tab,int kolumn, int wierszy)
{
	for(int i=0;i<wierszy;i++){
		for(int j=0;j<kolumn;j++){
			cout<<"  "<<tab[j][wierszy-1-i];
		}
		cout<<endl<<endl;
	}
	for(int i=1;i<=kolumn;i++){
		if(i<10) cout<<"  "<<i;
		else cout<<" "<<i;
	}
	cout<<endl<<endl;
}

char sprawdzStanPlanszy(char** tab,int kolumn,int wierszy){
	bool czyPelnaPlansza = true;
	for(int i=0;i<kolumn;i++){
		for(int j=0;j<wierszy;j++){
			if(tab[i][j]=='_') czyPelnaPlansza = false;
			//sprawdzenie czy nie nastapila czyjas wygrana
			bool dol=false,gora=false,prawo=false,lewo=false; //zmienne okreslajace ktore kierunki sprawdzic
			
			if(j>=3){
				dol=true;
				if(tab[i][j]==tab[i][j-1]&&tab[i][j-1]==tab[i][j-2]&&tab[i][j-2]==tab[i][j-3]){
					if(tab[i][j]=='x'){
						return 'x';break;
					}
					else if(tab[i][j]=='o'){
						return 'o';break;
					}
				}
			}
			
			if(j<=wierszy-4){
				gora=true;
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
				lewo=true;
				if(tab[i][j]==tab[i-1][j]&&tab[i-1][j]==tab[i-2][j]&&tab[i-2][j]==tab[i-3][j]){
					if(tab[i][j]=='x'){
						return 'x';break;
					}
					else if(tab[i][j]=='o'){
						return 'o';break;
					}
				}
			}
			
			if(i<=kolumn-4){
				prawo=true;
				if(tab[i][j]==tab[i+1][j]&&tab[i+1][j]==tab[i+2][j]&&tab[i+2][j]==tab[i+3][j]){
					if(tab[i][j]=='x'){
						return 'x';break;
					}
					else if(tab[i][j]=='o'){
						return 'o';break;
					}
				}
			}
			
			//SKOSY
			
			if(gora&&prawo){
				if(tab[i][j]==tab[i+1][j+1]&&tab[i+1][j+1]==tab[i+2][j+2]&&tab[i+2][j+2]==tab[i+3][j+3]){
					if(tab[i][j]=='x'){
						return 'x';break;
					}
					else if(tab[i][j]=='o'){
						return 'o';break;
					}
				}
			}
			
			if(gora&&lewo){
				if(tab[i][j]==tab[i-1][j+1]&&tab[i-1][j+1]==tab[i-2][j+2]&&tab[i-2][j+2]==tab[i-3][j+3]){
					if(tab[i][j]=='x'){
						return 'x';break;
					}
					else if(tab[i][j]=='o'){
						return 'o';break;
					}
				}
			}
			
			if(dol&&lewo){
				if(tab[i][j]==tab[i-1][j-1]&&tab[i-1][j-1]==tab[i-2][j-2]&&tab[i-2][j-2]==tab[i-3][j-3]){
					if(tab[i][j]=='x'){
						return 'x';break;
					}
					else if(tab[i][j]=='o'){
						return 'o';break;
					}
				}
			}
			
			if(dol&&prawo){
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
	if(!czyPelnaPlansza) return 'n';
	else return 'r';
}

int main(){
	
	cout<<endl;
	
	do{
		cout<<"  Podaj liczbe kolumn(4-99): ";cin>>kolumn;
	}while(kolumn<4||kolumn>99);
	
	do{
		cout<<"  Podaj liczbe wierszy(4-99): ";cin>>wierszy;
	}while(wierszy<4||wierszy>99);
	
	char** tab = new char*[kolumn];
	
	for(int i=0;i<kolumn;i++){
		tab[i] = new char[wierszy];
	}
	
	for(int i=0;i<kolumn;i++){
		for(int j=0;j<wierszy;j++){
			tab[i][j] = '_';
		}
	}
	
	int* indexy = new int[kolumn];
	
	for(int i=0;i<kolumn;i++){
		indexy[i] = 0;
	}
	
	while(sprawdzStanPlanszy(tab,kolumn,wierszy)=='n') // w praktyce do momentu, a¿ ktoœ nie wygra
	{
		wyswietlPlansze(tab,kolumn,wierszy);
		int bfr;
		a:
		bfr=0;
		while(bfr<1||bfr>kolumn||indexy[bfr-1]>=wierszy){
			if(!nr_gracza)cout<<"  GraczX>";
			else cout<<"  GraczO>";
			cin>>bfr;
		}
		
		if(!nr_gracza) // Gracz1
		{
			tab[bfr-1][indexy[bfr-1]] = 'x';
			indexy[bfr-1]++;
			iksow++;
		}
		if(nr_gracza) // Gracz2
		{
			tab[bfr-1][indexy[bfr-1]] = 'o';
			indexy[bfr-1]++;
			kolek++;
		}		
		
		if(sprawdzStanPlanszy(tab,kolumn,wierszy)=='x'&&iksow==4){
			indexy[bfr-1]--;
			tab[bfr-1][indexy[bfr-1]] = '_';
			iksow--;
			wyswietlPlansze(tab,kolumn,wierszy);
			cout<<"  Oj, tak nie wolno!!!"<<endl;
			cout<<"  Nie wolno wygrac w pierszych czterech ruchach."<<endl;
			cout<<"  Sprobuj wybrac inna kolumne."<<endl;
			goto a;
		}
		
		if(sprawdzStanPlanszy(tab,kolumn,wierszy)=='o'&&kolek==4){
			indexy[bfr-1]--;
			tab[bfr-1][indexy[bfr-1]] = '_';
			kolek--;
			wyswietlPlansze(tab,kolumn,wierszy);
			cout<<"  Oj, tak nie wolno!!!"<<endl;
			cout<<"  Nie wolno wygrac w pierszych czterech ruchach."<<endl;
			cout<<"  Sprobuj wybrac inna kolumne."<<endl;
			goto a;
		}
		
		nr_gracza = 1 - nr_gracza;
		
	}
	
	wyswietlPlansze(tab,kolumn,wierszy);
	
	switch(sprawdzStanPlanszy(tab,kolumn,wierszy))
	{
		case 'x':
			cout<<"Wygrana GraczaX"<<endl;break;
		case 'o':
			cout<<"Wygrana GraczaO"<<endl;break;
		case 'r':
			cout<<"Remis"<<endl;break;
			
	}
	
	for(int i=0;i<kolumn;i++){
		delete[] tab[i];
	}
	
	delete[] tab;
	delete[] indexy;
 	
	return 0;
}
