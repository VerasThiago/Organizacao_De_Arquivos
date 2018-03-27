#include <stdio.h>
#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <map>


using namespace std;

void intro(){ // Escrever alguma coisa para introduzir
		printf("\n");


}

bool open_all(vector<string> files){
	fstream arquivo;
	for(auto file : files){
		arquivo.open(file);
		if(!arquivo){
			cout << "Failed to open " << file << endl;
			return false;
		}
		cout << "Opened " << file << " successfuly " << endl;
		arquivo.close();
	}
	return true;
}

void concatenate(vector<string> files){
	string line;
	vector<string> all;
	fstream arquivo;
	for(auto file : files){
		arquivo.open(file);
		while(getline(arquivo,line))all.push_back(line);
		arquivo.close();
	}
	arquivo.open("final.txt");
	if(!arquivo){ // Check if file is open
		cout << "Failed to open final.txt file... Creating a new one." << endl;
		arquivo.clear();
		arquivo.open("final.txt", ios::out); // create a file 
   	}
   	else{
   		arquivo.close();
   		arquivo.open("final.txt", ios::app); // reopen file to write in the final
   	}
	for(auto line : all) arquivo << line;
    arquivo.close();
	cout << "Concatenation successful.\n";
}

void menu(vector<string> files){
	int option;
	printf("Concatenate files by:\n");
	printf("1 - Line\n");
	printf("2 - Word\n");
	printf("3 - Char\n");
	printf("Input option : ");
	while(cin >> option){
		if(option < 1 or option > 3){
			printf("Input option (1,2,3): ");
			continue;
		}
		break;
	}
	switch(option){
		case 1:
			concatenate(files);
			break;
		case 2:
			printf("Word concatenation not done yet\n");
			break;
		case 3:
			printf("Char concatenation not done yet\n");
			break;
	}
	return;
}

int main(){
	vector<string> files;
	string file;
	int n;
	intro();

	cout << "Digite a quantidade de arquivos que deseja concatenar: ";
	cin >> n;
	for(int i = 1; i <= n; i++){
		cout << "Input file " << i << " name: ";
		cin >> file;
		files.push_back(file + ".txt");
	}
	if(open_all(files))
		menu(files);
	else	
		cout << "System finished" << endl;

	

}
