#ifndef HEADER_MANAGER_H
#define HEADER_MANAGER_H
//======================================================
//  Libraries
//======================================================
#include <raylib.h>								// Main Library
#include <time.h>									// Random seed implementation
#include <stdlib.h>								// Memory Allocation implementation
#include <stdio.h>								// Standard formating functions
#include <string.h>								// String functions
#include <math.h>									// Ceil and Floor functions
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

// Enemy Spawner:
#define SPAWN_LARG 8
#define SPAWN_ALT 8

// Trap Spawn:
#define TRAP_SPW_SQR 4

//======================================================
// Game Configuration Data:
//======================================================
#define FPS 60
#define AKATS_LOGO 4 // Total strings in logo screen
#define MAX_MENU_OP 4
#define MAX_STRING_ID 64
#define AUTHORS 3 // Total de autores que tiveram envolvimento na aplicação 
#define FONT_NORMAL_SIZE 20
#define MAX_CHEST 30
#define DELAY_SPD 15.0f
#define MAX_AWARDS 15
#define TUTORIAL_SIZE 6
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
	Texture2D sprite;
	Rectangle spriteFrame;
	Vector2 pos;
	int ativo; // Flag
	int despawn; 	// Clock
} Chest_t;

typedef struct{
	Texture2D sprite;
	Rectangle spriteFrame;
	Vector2 pos;
	int animClock; // Clock
	int pont; // Accumulator
	int tempo; // Clock
	int sentido; // Flag
	float multiplicator; // Accumulator
} Jogador_t;

typedef struct{
	Texture2D sprite;
	Rectangle spriteFrame;
	Vector2 pos;
	int animClock;
	int tempo;
	int sentido;
	int moveDelay;
} Inimigo_t;

typedef struct{
	Texture2D sprite;
	Rectangle spriteFrame;
	int animClock;
} AnimatedObj_t;

typedef struct{
	int enemySpawn;
	int trapSpawn;
} Event_t;

// Screen Manager
typedef enum{
	CLOSE = 0,
	LOGO,
	INIT,
	LOADING,
	GAME,
	CREDITOS,
	TUTORIAL,
	END
} Tela_e;

#endif
