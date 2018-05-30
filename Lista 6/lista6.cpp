#include <bits/stdc++.h>

#ifdef WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

using namespace std;

// Vetor com as perguntas a serem feitas
vector<string> questions = {"Nome", "Sobrenome", "RG", "CPF", "Endereco", "CEP", "Nacionalidade","Data de nascimento", "Pais de nascimento", "Transa?"};

// Arquivo de registros
fstream arquivo("input.txt", ios::in | ios::out);

// Arquivo de indices
fstream indice("index.txt");

// Variável para pegar o offset de cada id no arquivo de registro
map<int,int> desloc;

// Variável que possui a quantidade de registros e o offset aonde está o final do arquivo de registros
int header, offset;

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

// Limpa o buffer do cin
void clear(){
	cin.clear(); cin.ignore(INT_MAX,'\n'); 
}

// Le os dados para salvar no arquivo de registors
void read(){

	// String para pegar os dados
    string data;

	// Iteração com o usuário 
	cout << "\n--------- Preencha o formulario com os seus dados ---------\n" << endl;

	// Salva o registro e seu offset no mapa
    desloc[header] = offset;

	// Armazena o registo como id no arquivo
    arquivo << header << "|";

    int x = 0;
    
	// Caminha pelas perguntas
    for(auto question : questions){
    	if(x++ == 2) break;
		// Iteração com o usuário
        cout << "\t" << question << ": ";

		// Le a resposta para a respectiva pergunta
        getline(cin, data) ;
   		
		// Salva o dado no arquivo de registro
        arquivo << data << "|";
    }
    
	// Incrementa a quantidade de registro
    header++;

	// Adciona uma quebra de linha
    arquivo << '\n';

	// Atualiza o offset com a ultima posição do arquivo
    offset	 = arquivo.tellg();

}

// Função para pegar a quantidade de registos e offset do arquivo passado como parâmetro
pair<int,int> get_file_header(fstream &file){

	// Variável auxiliar para pegar a posição que estava o arquivo
	int aux = file.tellg();

	// Variável de retorno da quantidade de registro e de offset
	int idx,off;

	// Descola o ponteiro do arquivo para o começo
	file.seekp (0 ,ios::beg);

	// Le os 2 dados
	file >> idx >> off;

	// Descola o ponteiro do arquivo para aonde estava
	file.seekp(aux,ios::beg);

	// Retorna os 2 dados
	return make_pair(++idx,off); 
}



// Função que retorna a quantidade de digitos daquele número
int qnt_digits(int n){
	return log10(n)+1;
}

// Gera o número de 7 dígitos com 0 a esquerda para o novo valor de header
string create_Header(int num){
	
	// String de retorno
	string ret = "";

	// Quantidade de zeros que deve ser acrescentado a esquerda
	int n = 7 - qnt_digits(num);

	// Adicionando os zeros a esquerda
	while(n--) ret += "0";

	// Retorna o novo número
	return ret + to_string(num);
}

// Atualiza apenas o header do arquivo de registros
void update_datafile_header(){

	// Gera o novo número de acordo com a quantidade de registros
	string newHeader = create_Header(header-1);

	// Gera o novo número de offset de acordo com a variável offset
	string newOffset = create_Header(offset);

	// Volta para o começo para salvar o novo header
	arquivo.seekp (0 ,ios::beg);

	// Salva o novo header
	arquivo << newHeader + " " + newOffset;
}



// Atualiza o arquivo de indices
void update_indexfile(){

	// Variável para pegar o header e o offset do arquivo de indices
	int indiceHeader, indiceOff;

	// Pega os 2 valores
	tie(indiceHeader, indiceOff) = get_file_header(indice);

	// Cria o novo header de arcordo com o header do arquivo de registros
	string newHeader = create_Header(header-1);

	// Desloca o ponteiro para o final do arquivo de indices para a escrita no final
	indice.seekp(indiceOff, ios::beg);

	// Escreve os registros que faltam
	for(int i = indiceHeader; i < header; i++)
		indice << i	<< " " << desloc[i] << endl;

	// Cria o novo dado de fim de arquivo de arcordo com o final do arquivo de indices
	string newOffset = create_Header(indice.tellg());


	// Volta para o começo do arquivo para escrever o novo header
	indice.seekp(0, ios::beg);

	// Escreve o novo header
	indice << newHeader + " " + newOffset;

	// Limpa o mapa
	desloc.clear();
}

// Faz o split da string de acordo com o parametro passado pelo char c
const vector<string> split(const string& s, const char& c){

	// String base
	string buff = "";

	// Vetor que irá salvar os splits
	vector<string> v;
	
	// Andando por cada carcter
	for(auto n:s){

		// Se nao for o char de quebra
		if(n != c)
			buff += n; 

		// Char que deve ser quabrado, logo adicionar a string ao vetor
		else if (n == c && buff != ""){
			// Adicionando no vetor
			v.push_back(buff);

			// Resetando a string buff
			buff = "";
		}
	}
	// Fazendo a ultima adição após o char de quebra
	if(buff != "")
		v.push_back(buff);
	
	// Retornando o vetor com os splits
	return v;
}

// Menu principal
char menu(){

	// Variável de escolha da opção do menu
	char op;
	
	// Limpa a tela
	system(CLEAR);

	// Display de opções
	printf("0 - Sair\n");
	printf("1 - Inserir\n");
	printf("2 - Buscar\n");
	
	// Pega a opção do usuário e repete o mesmo passo caso seja inválido
	while(cin >> op){

		// Se a opção for válida, encerra o loop
		if (op >= '0' and  op <= '2') break;

		// Imprime para o usuário reptir caso a opção escolhida seja inválida
		printf("Digite 0, 1 ou 2: ");

	}

	return op;
}
// Pega a resposta do usuário
char get_op(){

	// Retorno da escolha
	char op;

	// Enquanto le a escolha do usuário
	while(cin >> op){

		// Transforma para minúsculo para facilitar a condição
		op = tolower(op);
		
		// Checa se é y ou n, pois são as únicas 2 escolhas permitidas
		if (op == 'y' or op == 'n') break;

		// Pede para o usuário digitar corretamente
		cout << "\n\tDgite apenas y, Y, n ou N: ";

	}

	// Retorna a escolha
	return op;
}

// Função para inserir no arquivo de registros
void inserir(){
	
	// Caracter para a escolha da operação pelo usuário
	char op;
	
	// Limpa o buffer do cin
   	clear();
	
	// Pega o header e o offset do arquivo
	tie(header,offset) = get_file_header(arquivo);

	// Desloca o ponteiro para o final do arquivo, para inserir novo elemento
	arquivo.seekp(offset,ios::beg);

	// Loop principal
	while(true){

		// Le os dados e insere no arquivo
		read();
	
		// Iteração com o usuário
		cout << "\n   Deseja continuar inserindo ? [y][n]: ";

		// Pega a operação escolhida pelo usuário
		op = get_op();

		// Limpa a tela	
		system(CLEAR);

		// Se a escolha for a de não continuar
		if(op == 'n'){

			// Atualiza o header do arquivo de registros
			update_datafile_header();

			// Atualiza o arquivo de indices
			update_indexfile();

			// Encerra o loop
			break;
		}
		
		// Limpa o buffer do cin
		clear();

	}

	
}

// Função para chegar se a string é um número
bool is_number(const string& s){
    return( strspn( s.c_str(), "-.0123456789" ) == s.size() );
}

int get_id(){

	// Iteração com o usuário
	cout << "Digite o id do registro para realizar a busca: ";

	// String para ler a entrada do usuário
	string id;

	// Le o número digitado
	cin >> id;

	// Checa se o número digitado é realmente um número
	while(!is_number(id)){

		// Iteração com o usuário
		cout << "Por favor, digite um numero valido: ";

		// Le novamente
		cin >> id;
	}

	// Retorna o número que era um string, transformado para inteiro
	return stoi(id);
}


// Imprime os dados do registo do respectivo id
void show_message(int id){

	// Iteração com o usuário
	cout << "\n---------------------------------" << endl;
	cout << "\n\tDados do id " << id << endl << endl;


	// Caso o id não exista
	if(!desloc.count(id)){

		// Imprime que o id não existe
		cout << "\n\tID NOT FOUND" << endl;
		cout << "\n---------------------------------\n" << endl;
		
		// Encerra a função
		return;
	}

	// Desloca o ponteiro do arquivo até o offset do id desejado	
	arquivo.seekp(desloc[id], ios::beg);

	// String para ler a linha de dados do registo 
	string line;

	// Le a linha no respectivo offset
	getline(arquivo, line);

	// Qubra o registo em blocos
	vector<string> msg = split(line,'|');

	// Imprime os dados do registo
	for(int i = 1; i < msg.size(); i++)
		cout << "\t" << questions[i-1] << " : " << msg[i] << endl;
	
	// Iteração com o usuário
	cout << "\n---------------------------------\n" << endl;
}


// Busca os dados do registo pelo id
void buscar(){
	
	// Redireciona para o começo do arquivo
	indice.seekp(0, ios::beg);

	// Variáveis para pegar o header e o offset do arquivo de indicies
	int indiceHeader, indiceOff;

	// Pega os 2 dados do header
	tie(indiceHeader, indiceOff) = get_file_header(indice);

	// Variáveis para pegar o id e o offset do arquivo de indices e armazenar em um mapa para consultar em tempo O(log(n))
	int id,off;	char op;
	
	// Armazenando o id e o offset no mapa
	while(indice >> id >> off)
		desloc[id] = off;
	

	// Loop principal das perguntas
	while(true){
		
		// Busca o id escolhido pelo usuário
		id = get_id();

		// Imprime os dados do registro correspondente
		show_message(id);
		
		// Iteração com o usuário 
		cout << "\n   Deseja continuar buscando ? [y][n]: ";
	
		// Pega a escolha do usuário
		op = get_op();

		// Limpa a tela
		system(CLEAR);

		// Se a escolha do usuário for n, entao encerrar loop
		if(op == 'n')	break;
		
		// Limpar buffer do cin
		clear();

	}

}

void teste(){
	filebuf myfile;
    //myfile.open ("input.txt", ios::in | ios::out);
    if (!myfile.is_open()) cout << "cannot open" << endl;
    myfile.sputn("VAI\n", 4);
    myfile.close();
}

int main(){

	// Loop principal do programa
	while(true){
		
		// Pega o opção com o usuário
		char op = menu();

		// Limpa a tela
		system(CLEAR);

		// Verifica qual opção o usuário irá escolher
		if(op == '0') break;

		else if(op == '1') inserir();

		else buscar();

	}
}