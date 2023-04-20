// @AkrilaMayNotBeAvailable
// Esse subprograma tem como objetivo tratar sobre os dados do Mapa do jogo
#include "header_manager.h"
#include "function_declaration.h"
//=============================================================
// Histórico:
// 10/04/23 -> Alocação Dinâmica implementada
// 19/04/23 -> AAAAAAAAAAAAAAAAAA não deu certo
// 19/04/23 -> Arrumei cacetadas
//=============================================================

//==========================================================================================
// Alocação Dinâmica dos Campos de Mapa_t (1.0)
//==========================================================================================
Mapa_t *AllocMap(int lines, int cols){
	int i, j;
	// Alocação da struct mapa
	Mapa_t *map = malloc(sizeof(Mapa_t));
	if(map == NULL){
		return NULL;
	}
	
	// Alocação da matriz de inteiros dentro de mapa
	map->matriz = malloc(lines * sizeof(int *)); // Linhas
	if(map->matriz == NULL){
		free(map); // Caso em que não foi possível alocar as linhas
		return NULL;
	}
	for(i = 0; i < lines; i++){ // Colunas
		map->matriz[i] = malloc(cols * sizeof(int));
		if(map->matriz[i] == NULL){
			for(j = 0; j < i; j++){
				free(map->matriz[j]); // Caso em que não foi possível alocar as colunas
			}
			free(map->matriz);
			free(map);
			return NULL;
		}
	}
	
	return map;
}
//==========================================================================================
// Inicialização de Mapa (1.1)
//==========================================================================================
void RandomizeMap(int **matriz, int lines, int cols){
	int x, y;

	// Gera dados iniciais para a matriz principal
  for(y = 0; y < lines; y++){
    for(x = 0; x < cols; x++){
        matriz[y][x] = rand() % 2; // Utiliza a premissa que qualquer valor % 2 é 0 ou 1
    }
  }
}
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
// Cellular Automata Algorithm:
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
//
void SetWall(int **map, int lines, int cols){
	int y, x;
	
	for(y = 0; y < lines; y++){
		for(x = 0; x < cols; x++){
			if(y == 0 || y == lines -1){
				map[y][x] = 1;
			}
			if(x == 0 || x == cols - 1){
				map[y][x] = 1;
			}
		}
	}
}
//==========================================================================================
// Ambiente Gráfico (2.0)
//==========================================================================================
void DrawMap(Mapa_t *map, int lines, int cols, Texture_t piso, Texture_t parede){
	int x, y;
	
	for(y = 0; y < lines; y++){
		for(x = 0; x < cols; x++){
			if(map->matriz[y][x] == 1)
				DrawTexture(parede.tex[0], x*16, y*16, PURPLE); // Parede == 1
			if(map->matriz[y][x] == 0)
				DrawTexture(piso.tex[0], x*16, y*16, WHITE); // Piso == 0
		}
	}
	
	/* Debug Purrposes *purr*
	for(y = 0; y < lines; y++){
		for(x = 0; x < cols; x++){
			if(map->matriz[y][x] == 1)
				DrawText("1", x*16, y*16, 16, BLUE);
			if(map->matriz[y][x] == 0)
				DrawText("0", x*16, y*16, 16, BLACK);
		}
	}
	*/
}
//==========================================================================================
// Descarrega Dados da Memória (3.0)
//==========================================================================================
void FreeMap(Mapa_t *map, int lines){
	int i;

	for(i = 0; i < lines; i++)
		free(map->matriz[i]);
	free(map->matriz);
	free(map);
}

