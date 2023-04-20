#ifndef HEADER_MANAGER_H
#define HEADER_MANAGER_H
//======================================================
//  Libraries
//======================================================
#include <raylib.h>								// Main Library
#include <time.h>									// Random seed implementation
#include <stdlib.h>								// Memory Allocation implementation
#include <string.h>								// String functions
//======================================================
//  Raylib Resource Packager
//======================================================
#include "src/rres.h"              // Necessário para ler dados de chunks dos arquivos .rres
#include "src/rres-raylib.h"       // Necessário para mapear os dados das chunks
//======================================================
// Window Data
//======================================================
#define T_LARG	780
#define T_ALT		620
#define TITULO "Chest Hunter"
//======================================================
// Celullar Automata Algorithm defines
//======================================================
// Mapa Principal: Definições de Tamanho
#define ALTURA 64
#define LARGURA 64
//======================================================
// Game Configuration Data:
//======================================================
#define FPS 60
#define AUTHORS 3 // Total de autores que tiveram envolvimento na aplicação 
#define FONT_NORMAL_SIZE 20
#define MAX_CHEST 30
//======================================================
// Assets Configuration:
//======================================================
#define ASSET_SIZE 16 // Define de texturas 16x16

#define MAPA_IMAGES_QTD 4 // Define quantas tiles de mapa existem
#define MAX_TEXTURES 20
//======================================================
typedef struct{
	Texture2D tex[MAX_TEXTURES];
} Texture_t;
//------------------------------------------------------
// Essentials
typedef struct{
	int **matriz;
} Mapa_t;

typedef struct{
	Vector2 pos;
	int ativo;
} Chest_t;

typedef struct{
	Texture2D sprite;
	Vector2 pos;
	int pont;
	int tempo;
} Jogador_t;


// Screen Manager
typedef enum{
	CLOSE = 0,
	INIT,
	LOADING,
	GAME,
	CREDITOS,
	END
} Tela_e;

#endif
