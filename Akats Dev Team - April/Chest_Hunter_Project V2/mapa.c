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
// Preenche todas extremidades com paredes
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
void DrawMap(Mapa_t *map, int lines, int cols, Texture_t piso, Texture_t parede, AnimatedObj_t trap){
	int x, y;
	
	for(y = 0; y < lines; y++){
		for(x = 0; x < cols; x++){
			if(map->matriz[y][x] == 3)
				DrawTextureRec(trap.sprite, trap.spriteFrame, (Vector2){x*ASSET_SIZE, y*ASSET_SIZE}, WHITE); // Piso == 0
			if(map->matriz[y][x] == 2)
				DrawTexture(piso.tex[1], x*ASSET_SIZE, y*ASSET_SIZE, RED); // Enemy Spawn
			if(map->matriz[y][x] == 1)
				DrawTexture(parede.tex[0], x*ASSET_SIZE, y*ASSET_SIZE, PURPLE); // Parede == 1
			if(map->matriz[y][x] == 0)
				DrawTexture(piso.tex[2], x*ASSET_SIZE, y*ASSET_SIZE, WHITE); // Piso == 0
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

