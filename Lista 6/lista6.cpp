#include <bits/stdc++.h>

using namespace std;


fstream arquivo;
int header;

// Print menu on terminal
void intro(){ 
		printf("\n");
		printf("#####################################\n");
		printf("#                                   #\n");
		printf("#        LIST CREATOR BY KEY        #\n");
		printf("#                                   #\n");
		printf("#####################################\n");
		printf("#                                   #\n");
		printf("#     Aluno: Thiago Veras Machado   #\n");
		printf("#         M: 16/0146682             #\n");
		printf("# Aluno: Gabriel Cunha Bessa Vieira #\n");
		printf("#         M: 16/0120811             #\n");
		printf("#                                   #\n");
		printf("#####################################\n");
		printf("\n");
}

void clear(){
	cin.clear(); cin.ignore(INT_MAX,'\n'); 
}

void read(int id, fstream& arquivo){
    string data;

    vector<string> questions = {"Nome", "Sobrenome", "RG", "CPF", "Endereco", "CEP", "Nacionalidade","Data de nascimento", "Pais de nascimento", "Transa?"};
       
    cout << "## Preencha o formulario com base nas informacoes do seu Computador ##" << endl;
    
    arquivo << id << "|";

    int x = 0;
    
    for(auto question : questions){
    	if(x++ == 2) break;
        cout << question << ": ";
    
        getline(cin, data) ;
   		

        arquivo << data << "|";
    }
    
    arquivo << endl;
}

int get_header(){
	arquivo.open("input.txt");
	int idx;
	arquivo >> idx;
	arquivo.close();
	return ++idx; 
}


void update_datafile(fstream &arquivo){

	puts("xota");

}


char menu(){
	char op;
	
	printf("0 - Sair\n");
	printf("1 - Inserir\n");
	printf("2 - Buscar\n");
	
	while(cin >> op){

		if (op >= '0' and  op <= '2') break;

		printf("Digite 0, 1 ou 2: ");

	}

	return op;
}

void inserir(){
	
	header = get_header();
	
	char op;
	
   	clear();
	
   	arquivo.open("input.txt", ios::app);

	while(true){
	
		read(header++,arquivo);
	
		cout << "Deseja continuar inserindo ? [y][n]: ";
	
	
		while(cin >> op){
			op = tolower(op);
			
			if (op == 'y' or op == 'n') break;

			cout << "Dgite apenas y, Y, n ou N: ";

		}
	
		if(op == 'n') break;
		
		clear();

	}
	
	arquivo.close();

}

void buscar(){
	puts("penis");
}

int main(){

	filebuf myfile;
    myfile.open ("input.txt", ios::in | ios::out);
    if (!myfile.is_open()) cout << "cannot open" << endl;
    myfile.sputn("XOT\n", 4);
    myfile.close();
	
	while(true){

		char op = menu();

		if(op == '0') break;

		else if(op == '1') inserir();

		else buscar();

	}



	
	update_datafile(arquivo);



}