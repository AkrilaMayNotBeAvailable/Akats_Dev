#include "header_manager.h"
#include "function_declaration.h"

//=============================================
// Inicialização:
//=============================================
// Inicia Matriz Principal: Preenche uma matriz com 0s e 1s
// @Param matriz[][] -> t# da Cellular Automata para preencher aleatoriamente
void IniciaMatrizPrincipal(int **matriz){
	int x, y;

	// Gera dados iniciais para a matriz principal
  for(y = 0; y < ALTURA; y++){
    for(x = 0; x < LARGURA; x++){
        matriz[y][x] = rand() % 2; // Utiliza a premissa que qualquer valor % 2 é 0 ou 1
    }
  }
}

//=============================================
// Cellular Automata Functions:
//=============================================
// Em uma matriz randomica, atualiza dados até que sejam compreensíveis e possam ser utilizados como mapa
void SmoothMapCellularAutomata(int **map, int lines, int cols){
	int x, y; // Percorre as posições da matriz principal
	int vizinhanca; // Quantidade de vizinhos (Definida por auxiliar)
	int proxGeracao[ALTURA][LARGURA]; // t + 1 Automata Algorithm
	
	for(y = 0; y < lines; y++){
		for(x = 0; x < cols; x++){
			vizinhanca = ContaVizinhos(map, x, y);
			
			if(vizinhanca > 4){
				proxGeracao[y][x] = 1;
			}
			else if(vizinhanca <= 4){
				proxGeracao[y][x] = 0;
			}
		}
	}
	// Cópia:
	for(y = 0; y < lines; y++){
		for(x = 0; x < cols; x++){
			map[y][x] = proxGeracao[y][x];
		}
	}
}
//=============================================
// Auxiliares:
//=============================================
// Auxiliar para contar quantidade de vizinhos
int ContaVizinhos(int **map, int x, int y){
	int vizinho = 0;
	int vizinhoY, vizinhoX;

	for(vizinhoY = y -1; vizinhoY <= y +1; vizinhoY++){
		for(vizinhoX = x -1; vizinhoX <= x +1; vizinhoX++){
			if(vizinhoX >= 0 && vizinhoX < LARGURA && vizinhoY >= 0 && vizinhoY < ALTURA){
				if(vizinhoX != x || vizinhoY != y){
					vizinho += map[vizinhoY][vizinhoX];
				}
			}
			else{
				vizinho++;
			}
		}
	}
	return vizinho;
}
//=============================================
// Ambiente Gráfico:
//=============================================
void DesenhaCelulas(int matriz[ALTURA][LARGURA]) {
	int x, y;
	
  for(y = 0; y < ALTURA; y++){
		for(x = 0; x < LARGURA; x++){
	    if(matriz[y][x] == 0){
	        DrawRectangle(10*x, 10*y,  10, 10, RED); // Dead
	    } else {
	        DrawRectangle(10*x, 10*y,  10, 10, BLUE); // Alive
	    }
		}
  }
}
