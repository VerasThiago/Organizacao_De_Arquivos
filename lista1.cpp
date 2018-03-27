#include <stdio.h>
#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <map>


using namespace std;

void menu(){ // Escrever alguma coisa para introduzir
		printf("\n");


}

bool open_all(vector<string> files){
	fstream arquivo;
	for(auto file : files){
		arquivo.open(file);
		if(!arquivo){
			cout << "Falha no arquivo " << file << endl;
			return false;
		}
		cout << "Abriu o " << file << endl;
		arquivo << "Penis" << endl;
		arquivo.close();
	}
	return true;
}

/*void concatenate(vector<string> files){
    std::fstream fa = std::fstream(file1, std::ios::out | std::ios::app);
    std::fstream fb = std::fstream(file2, std::ios::in)

    std::string line;
    while( std::getline(fb, line)){
        fa << line << "\n";
    }
   

    return "Concatenation successful.\n";
}*/

int main(){
	vector<string> files;
	string file;
	int n;
	menu();

	cout << "Digite a quantidade de arquivos que deseja concatenar" << endl;
	cin >> n;
	for(int i = 1; i <= n; i++){
		cout << "Digite o nome do arquivo " << i << ":";
		cin >> file;
		files.push_back(file + ".txt");
	}
	if(open_all(files)){
		//concatenate(files);
	}
	//else

}