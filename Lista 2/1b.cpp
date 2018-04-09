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


int main() {
    // Open file
    fstream file ("teste.txt", ios::in | ios::binary);

    // Fail opening file
    if(!file) return cout << RED << "File could not be opened\n" << RESET,0;

    // Block factors
    vector<int> factors = {512, 4096/4, 4096/2, 3*4096/4, 4096};

    // Messages for each blocks
    vector<char*> message[5]; 

    // File length:
    file.seekg (0, ios::end);

    // Length = file length
    int length = file.tellg(), block, i = 0;

    // Iterate through all block factors
    for(int buf : factors){

        // returns to begin of file
        file.seekg(0); 
        
        //reset block size
        block = 0;

        // Iterate while block size < file length
        while(block < length){

            // Var to read message from file
            char* curr_blk = (char*) malloc(buf);

            // Set all block to 0. May not fill it all block and null spaces needed to be 0
            memset(curr_blk, 0, buf);
            
            // To not read more than block length
            if(block + buf <= length)
                file.read(curr_blk, buf);
            else
                file.read(curr_blk, length-block);
            
            // adds message to that block factor
            message[i].push_back(curr_blk);    
                
            // shift block size if file need more than 1 block         
            block += buf;
        }
        i++;
    }

    // OK message
    cout << GREEN << "Blocks completed\n" << RESET;
    for(int i = 0; i < 5; i++) printf("%dK : %d block(s)\n", factors[i], (int) message[i].size());

    // Output file
    fstream out; i = 0;

    // Iterate through all factors to write a new file
    for(auto buf : factors){

        // Open factor size file name
        out.open("out_" + to_string(buf) + ".txt", ios::out);

        // Writed message from blocks to another file
        for(auto blk : message[i++]) out.write(blk, buf);

        // Close file
        out.close();
    }
    
}