#include <stdio.h>
#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <map>


using namespace std;

void intro(){ // Escrever alguma coisa para introduzir
		printf("\n");
		printf("Aluno: Thiago Veras Machado\n");
		printf("M: 16/0146682\n");
		printf("Aluno: Gabriel Cunha Bessa Vieira\n");
		printf("M: 16/0120811\n");


		printf("\n");
		printf("Welcome to Veras Concatenator\n");
		printf("You first name the amount of files that you want to concatenate\n");
		printf("After that name 2 existing files without the extension '.txt'\n");
		printf("Should be able to concatenate 'n' amount of files successfully\n\n");
}

bool open_all(vector<string> files){
	fstream arquivo;
	for(auto file : files){  // Walk through files vector
		arquivo.open(file); // Open file
		if(!arquivo){ //Check if opened  the file
			cout << "Failed to open " << file << endl;
			return false;
		}
		cout << "Opened " << file << " successfuly " << endl;
		arquivo.close();
	}
	return true;
}

vector<string> read(int n){ // Reading the n files name
	vector<string> files;
	string file;
	for(int i = 1; i <= n; i++){
		cout << "Input file " << i << " name: ";
		cin >> file;
		files.push_back(file + ".txt"); // Adding the .txt extension
	}
	return files;
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

int main(){
	vector<string> files;
	int n;
	intro();
	cout << "Digite a quantidade de arquivos que deseja concatenar: ";
	cin >> n;
	files = read(n);
	if(open_all(files))
		concatenate(files);
	else
		cout << "System finished" << endl;
}
