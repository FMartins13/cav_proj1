#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include <stdio.h>
#include <string>
#include <cstdlib>
#include <string.h>
#include <vector>

using namespace std;

class FCM{

private:
	// Este mapa devolve como resultado uma linha da tabela que e'
	// representada por um array de inteiros com os valores de cada celula
	map<string, int[]> table;

	// Variavel para guardar a ordem do modelo
	int order;

	/*
	 * !!! Ainda falta o "Returning the statistical information about a symbol,
	 *  based on the current context;"
	 *  !!! e falta o "Returning the accumulated entropy of the text
	 *   already processed;"
	 */

public:
	// Construtor
	FCM(int ordem);

	// obtem a posicao no array para os caracteres suportados (a-z e espaço)
	int charToInteger(char in);

	// Guarda o valor da ordem do modelo
	void setOrder(int ordem){order = ordem;}

	// Devolve o valor da ordem do modelo
	int returnOrder(void){return order;}

	// Função que transforma maisculas em minusculas para uma string
	string correctUpperCase(string estado);

	// Adiciona um novo simbolo ao mapa
	// ou caso ja exista adiciona a ocurrencia no array
	void setSymbol(string estado, char simbolo);

	// Adiciona o array de simbolos ao mapa
	// ou caso ja exista substitui-o
	void setSymbolArray(string estado, int arrayInt[]);

	// Devolve o numero de ocurrencias de um certo simbolo baseado no contexto
	// passado como argumento
	int getSymbolInfo(string estado, char simbolo);

	// Guardar o modelo num ficheiro
	void saveModelToFile(char fileName[]);

	// Ler o modelo de um ficheiro para a tabela
	void readModelFromFile(char fileName[]);


	// Imprime o modelo
	void printModel();
};

	// Construtor
	FCM::FCM(int ordem){
		setOrder(ordem);
	}

	// obtem a posicao no array para os caracteres suportados (a-z e espaço)
	int FCM::charToInteger(char in) {
		int res;
		int sym = (int)in;
		if(in == ' ')
			res = 26;
		else if(isalpha(in)){
			res = (int)in - 65;
			if(res >27)
				res = res-32;
		}
		return res;
	}

	// Guarda o valor da ordem do modelo
	void FCM::setOrder(int ordem){order = ordem;}

	// Devolve o valor da ordem do modelo
	int FCM::returnOrder(void){return order;}

	// Função que transforma maisculas em minusculas para uma string
	string FCM::correctUpperCase(string estado){

		// http://www.cplusplus.com/reference/cctype/isupper/
		int i=0;
		string state = estado;
		char c;
		while (state[i])
		{
			c=state[i];

		    if (isupper(c))
		    	c=tolower(c);
		    putchar(c);
		    i++;
		}

		return state;
	}

	// Adiciona um novo simbolo ao mapa
	// ou caso ja exista adiciona a ocurrencia no array
	void FCM::setSymbol(string estado, char simbolo){

		string state = correctUpperCase(estado);

		// Atualizar o simbolo para um inteiro de modo a ficar de acordo com o array
		int symbol = charToInteger(simbolo);

		// Verificar se o estado ainda nao existe na tabela
		if(table.count(state) == 0){
			// Inicializar array a zero
			int arrayZero[27] = {0};

			// Adicionar uma nova linha 'a tabela (mapa)
			table.insert(make_pair(state,arrayZero));
		}


		// Obter o ponteiro para o array a modificar
		map<string, int[]>::iterator it = table.find(state);
		// Alterar o valor do array
		if (it != table.end()){

		    int temp[] = it->second;
		    // Incrementar o numero de ocorrencias
		    temp[symbol] += 1;
		    // Fazer o update
		    it->second = temp;
		}


	}

	// Adiciona o array de simbolos ao mapa
	// ou caso ja exista substitui-o
	void FCM::setSymbolArray(string estado, int arrayInt[]){

		string state = correctUpperCase(estado);

		// Verificar se o estado ainda nao existe na tabela
		if(table.count(state) == 0){

			// Adicionar uma nova linha 'a tabela (mapa)
			table.insert(make_pair(state, arrayInt));
		}


		// Obter o ponteiro para o array a modificar
		map<string, int[]>::iterator it = table.find(state);

		// Alterar o valor do array
		if (it != table.end()){

			// Fazer o update
			it->second = arrayInt;
		}


	}

	// Devolve o numero de ocurrencias de um certo simbolo baseado no contexto
	// passado como argumento
	int FCM::getSymbolInfo(string estado, char simbolo){
		// Corrigir as maisculas num estado caso seja necessario
		string state = correctUpperCase(estado);

		// Atualizar o simbolo para um inteiro de modo a ficar de acordo com o array
		int symbol = charToInteger(simbolo);

		// Obter o ponteiro para o array
		map<string, int[]>::iterator it = table.find(state);

		// Alterar o valor do array
		if (it != table.end()){

		    int temp[] = it->second;
		    return temp[symbol];
		}

		// Caso o estado correspondente nao seja encontrado
		return -1;
	}

	// Guardar o modelo num ficheiro
	void FCM::saveModelToFile(char fileName[]){

		// Abrir o ficheiro em modo de escrita
		//https://www.tutorialspoint.com/cplusplus/cpp_files_streams.htm
		ofstream outfile;

		outfile.open(fileName);

		// Percorrer o mapa
		for(map<string, int[]>::iterator it = table.begin(); it != table.end(); ++it){
			int i = 0;

			// Escrever a chave para o ficheiro
			outfile << it->first << "-";

			// Percorrer o array dentro do mapa
			for(;i < 27; i++){
				// Escrever um valor para o ficheiro
				outfile << it->second[i] << " ";
			}

			// Passar para a linha seguinte
			outfile << endl;
		}

		// Fechar o ficheiro
		outfile.close();
	}

	// Ler o modelo de um ficheiro para a tabela
	void FCM::readModelFromFile(char fileName[]){

		// Abrir o ficheiro em modo de leitura
		//https://www.tutorialspoint.com/cplusplus/cpp_files_streams.htm
		ifstream infile;

		infile.open(fileName);

		string linha = "";

		// Ler linha por linha
		while(infile >> linha){
			// Transformar em char[] para a analise ser mais facil
			const char *linhaLida = linha.c_str();

			// Assegurar que a linha tem conteudo
			if(sizeof(linhaLida) <= 0){
				cout << "Linha lida estava vazia" << endl;
				break;
			}

			int i = 0;

			// Obter o contexto para a chave do mapa
			string estado = "";
			for(; i < sizeof(linhaLida); i++){
				// Se aparecer o carater que divide a chave do array
				// entao o ciclo termina
				if(linhaLida[i] == '-'){
					i++;
					break;
				}
				estado += linhaLida[i];
			}

			// Obter o array de inteiros para o valor do mapa
			int arrayInt[27];
			int arrayIdx = 0;
			string inteiro = "";
			for(; i < sizeof(linhaLida); i++){
				// Se aparecer o carater de espaco guarda um novo inteiro no array
				// e limpa a string que vai criar o novo inteiro
				if(linhaLida[i] == ' '){
					arrayInt[arrayIdx] = atoi(inteiro.c_str());
					arrayIdx++;
					inteiro = "";
					i++;
					continue;
				}

				inteiro += linhaLida[i];
			}

			// Guardar na tabela
			setSymbolArray(estado, arrayInt);

			// Limpar a linha, para ler a seguinte
			linha = "";
		}

		// Fechar o ficheiro
		infile.close();
	}


	// Imprime o modelo
	void FCM::printModel(){
		cout << setw(5) << " ";

		// Imprimir as letras
		for(int i = 0; i < 26; i++){
			cout << setw(4) << 'a' + i;
		}

		// Imprimir o espaco
		cout << " space";

		// Percorrer o mapa
		for(map<string, int[]>::iterator it = table.begin(); it != table.end(); ++it){
			int i = 0;

			// Escrever a chave
			cout << setw(5) << it->first;

			// Percorrer o array dentro do mapa
			for(;i < 27; i++){
				// Escrever o numero de ocorrencias
				cout << setw(4) << it->second[i];
			}

			// Passar para a linha seguinte
			cout << endl;
		}

	}


