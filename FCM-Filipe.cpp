#include <iostream>
#include <map>
#include <stdio.h>
#include <string>

using namespace std;

class FCM{

private:
	// Este mapa devolve como resultado uma linha da tabela que e'
	// representada por outro mapa que devolve o valor de uma celula
	map<string, int[]> table;

	// Variável para guardar a ordem do modelo
	int order;


public:
	// Construtor
	FCM(int ordem){
		setOrder(ordem);
	}

	// Guarda o valor da ordem do modelo
	void setOrder(int ordem){order = ordem;}

	// Devolve o valor da ordem do modelo
	int returnOrder(void){return order;}

	// Adiciona um novo simbolo ao mapa
	// ou caso já exista adiciona a ocurrência no array
	void setSymbol(string estado, char simbolo){

		// Verificar se o estado esta em letra maiuscula
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

		// Atualizar o simbolo para um inteiro de modo a ficar de acordo com o array
		int symbol = asciiToInteger(simbolo);

		// Verificar se o simbolo ainda nao existe na tabela
		if(table.count(state) == 0){
			// Inicializar array a zero
			int arrayZero[27] = {0};

			// Adicionar uma nova linha 'a tabela (mapa)
			pair<string, int[]> linha (state, arrayZero);
			table.insert(linha);
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
};
