#include <stdio.h>   // Use function Prinf()
#include <iostream>  // Use cin and cout functions
#include <fstream>   // Use open() and all files functions
#include <regex>     // Use vector class
#include <string>    // Use String to read files name

// Use collors on printf
#define RED     "\x1b[31m"  
#define GREEN   "\x1b[32m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

// Used to omit ::std syntax
using namespace std;

vector<string> message = {"Nome: ", "Sobrenome: ", "Endereço: ", "CEP: ", "Telefone: "}, data(5);


// Print menu on terminal
void intro(){ 
		printf(CYAN"\n");
		printf("#####################################\n");
		printf("#                                   #\n");
		printf("#        FILE CONCATENATOR          #\n");
		printf("#                                   #\n");
		printf("#####################################\n");
		printf("#                                   #\n");
		printf("#     Aluno: Thiago Veras Machado   #\n");
		printf("#         M: 16/0146682             #\n");
		printf("# Aluno: Gabriel Cunha Bessa Vieira #\n");
		printf("#         M: 16/0120811             #\n");
		printf("#                                   #\n");
		printf("#####################################\n");
		printf("\n" RESET);
}


void save_by_fixed_size(){

	
	fstream arquivo;
	arquivo.open("fixed_size.txt");
	if(arquivo)remove("fixed_size.txt");
	arquivo.close();
	arquivo.open("fixed_size.txt", ios::app);
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 20; j++){
			if(j >= data[i].size()) arquivo << '-';
			else arquivo << data[i][j];
		}
	}


}

void save_by_begin_size(){
	fstream arquivo;
	arquivo.open("begin_size.txt");
	if(arquivo)remove("begin_size.txt");
	arquivo.close();
	arquivo.open("begin_size.txt", ios::app);
	for(int i = 0; i < data.size(); i++) arquivo << data[i].size() << data[i];

}

void save_by_separator(){
	fstream arquivo;
	arquivo.open("separator.txt");
	if(arquivo)remove("separator.txt");
	arquivo.close();
	arquivo.open("separator.txt", ios::app);
	for(int i = 0; i < data.size(); i++) arquivo <<  data[i] << '%';

}

int main() {

	// Display intro message
    intro();

    for(int i = 0; i < 5; i++){
    	cout << message[i];
    	getline(cin,data[i]);
    }

    save_by_fixed_size();

    save_by_begin_size();

    save_by_separator();

    //save_by_valor();



}
