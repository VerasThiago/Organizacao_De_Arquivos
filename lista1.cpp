#include <stdio.h>
#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <map>

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

using namespace std;

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
		printf("How many files you want to read ? : ");
}

// Check if all files exists and can be opened
bool open_all(vector<string> files){
	// Return if all files could be opened
	bool ans = true;

	fstream arquivo;
	
	// Walk through files vector to get file name
	for(auto file : files){
	  	// Open file
		arquivo.open(file); 
		//Check if opened  the file

		cout << "Opening " << file << " : ";
		if(!arquivo){ 
			cout << RED << "FAILED" << RESET << endl;
			ans = false;
		}
		else{
			cout << GREEN << "SUCCESS" << RESET << endl;
			// Close file if was opened
			arquivo.close();
		}
	}
	return ans;
}

// Reading the n files names
vector<string> read(int n){ 

	// Vector of string to store all files names
	vector<string> files;
	
	// String to get the file by file name
	string file;

	for(int i = 1; i <= n; i++){
		cout << "Input file " << i << " name (With extention) : ";
		// Read file name
		cin >> file;
		// Push file to files vector 
		files.push_back(file); 
	}
	return files;
}

// Concatenate all files
void concatenate(vector<string> files){
	// String to read line by line in the file
	string line;
	// Vector to store all lines concatenated
	vector<string> all;
	fstream arquivo;
	// Walk through all files
	for(auto file : files){
		// Open the file
		arquivo.open(file);

		// Read all lines and store in vector all
		while(getline(arquivo,line))all.push_back(line);

		// Close file
		arquivo.close();
	}

	// Open the final file that have all files concatenated
	arquivo.open("final.txt");

	// Check if file exist
	if(!arquivo){ 

		// If the file don't exist create a file called final.txt
		cout << RED << "File final.txt don't exist ... Creating a new one..." << RESET << endl;
		
		// Clear all fstream content
		arquivo.clear();
		
		// Create a file
		arquivo.open("final.txt", ios::out); 

		cout << GREEN << "File final.txt created successfuly" << RESET << endl;
   	}
   	else{
   		// If already exist, close the final.txt file 
   		arquivo.close();

   		// Reopen file with ios:app mode that all operations will be performed at the end of the file
   		arquivo.open("final.txt", ios::app);

   		cout << GREEN << "Concatenating all files to final.txt" << RESET << endl; 
   	}

   	// Walk through all concatenated files and write at the end of final.txt file
	for(auto line : all) arquivo << line;

	// Close file	
    arquivo.close();

	// Success message
	cout << GREEN << "Concatenation successful.\n" << RESET;
}

int main(){

	// Vector to store all files name
	vector<string> files;

	// Read amount of files number
	int n;

	// Display intro message
	intro();

	// Read amount of files number
	cin >> n;

	// Read n files names
	files = read(n);

	// If can open all files, concatenate all
	if(open_all(files))
		concatenate(files);
	else
		cout << "Opening all files status : " << RED << "FAILED" << RESET << endl <<  "System finished" << endl;
}
