// @AkrilaMayNotBeAvailable - Akats Dev Team, Leader Dev
/* Esse código foi feito com objetivos didáticos.
* É estritamente proíbida a venda deste código.
* 
*/
#include <raylib.h>
#include <time.h>

#define T_LARG	480
#define T_ALT		500
#define TITULO "Good Morning Motherfuckers"

#define LINES_X_COLS 30
#define FPS 60

typedef struct{
	Texture2D parede;
	Texture2D paredeDireita;
	Texture2D paredeEsquerda;
	Texture2D chao;
	Vector2 tamanhos;
} Mapa_t;

typedef struct{
	Texture2D box;
	Vector2 pos;
	int ativo;
} Chest_t;

typedef struct{
	Texture2D sprite;
	Vector2 pos;
	int pont;
	int tempo;
} Jogador_t;

typedef enum{
	INIT = 0,
	GAME,
	END
} Tela_e;

void PlayerMovement(Vector2 *pos, Vector2 ref);
void LimiterMovementBasic(Vector2 *limitedObject, Vector2 checkObject, int limiterUnder, int limiterUpper);
void DrawMap(Mapa_t mapa, int limit);
void ReinitPlayer(Jogador_t *jogador);
int InitHandler();
int CollisionCheck(Vector2 checkObjectA, Vector2 checkObjectB);

int main(){
	SetRandomSeed(time(NULL));
	// Initialize variables
	int contFrame = 0;
	int close = 0;
	int op = -1;
	
	// Screen Manager
	Tela_e screen = INIT;
	
	// Map Initialization
	Mapa_t mapa = { 0 };
	mapa.tamanhos = (Vector2){16, 16};
	
	// Chest Initialization
	Chest_t bau = { 0 };
	bau.pos = (Vector2){GetRandomValue(1, LINES_X_COLS-2)*mapa.tamanhos.x, GetRandomValue(1, LINES_X_COLS-2)*mapa.tamanhos.y};
	
	// Player Initialization
	Jogador_t jogador = { 0 };
	jogador.pos = (Vector2){GetRandomValue(1, LINES_X_COLS-2)*mapa.tamanhos.x, GetRandomValue(1, LINES_X_COLS-2)*mapa.tamanhos.y};
	jogador.tempo = FPS*10;
	
	// Window -> Textures, audios etc must be loaded after window.
	InitWindow(T_LARG, T_ALT, TITULO);
	
	// Textures mapa
	mapa.paredeDireita = LoadTexture("resources/paredeDir.png");
	mapa.parede = LoadTexture("resources/paredeMeio.png");
	mapa.paredeEsquerda = LoadTexture("resources/paredeEsq.png");
	mapa.chao = LoadTexture("resources/floor_1.png");
	// Textures bau
	bau.box = LoadTexture("resources/box.png");
	// Textures jogador
	jogador.sprite = LoadTexture("resources/sprite.png");
	
	SetTargetFPS(FPS);
	while(!close){
		switch(screen){
			case INIT:
				op = InitHandler();
				if(op == 1){
					op = -1;
					ReinitPlayer(&jogador);
					screen = GAME;
				}
				if(op == 2) close = 1;
			break;
			
			case GAME:
			// Update Variables
			jogador.tempo--;
			
			contFrame++;
			if(contFrame == FPS*2){
				bau.pos = (Vector2){GetRandomValue(1, LINES_X_COLS-2)*mapa.tamanhos.x, GetRandomValue(1, LINES_X_COLS-2)*mapa.tamanhos.y};
				bau.ativo = 1;
				contFrame = 0;
			}
			if(CollisionCheck(jogador.pos, bau.pos) && bau.ativo){
				bau.ativo = 0;
				jogador.pont += 20;
				jogador.tempo += FPS*5;
			}
			PlayerMovement(&jogador.pos, mapa.tamanhos);
			LimiterMovementBasic(&jogador.pos, mapa.tamanhos, 16, 288);
			
			if(jogador.tempo == 0) screen = END;
			break;
			
			case END:
				if(IsKeyPressed(KEY_ENTER)) screen = INIT;
			break;
			
			default: 
			
			break;
		}
		// Drawing Ambient
		BeginDrawing();
		switch(screen){
			case INIT:
				ClearBackground(BLACK);
				DrawText("Chest Hunt Ver.0001", T_LARG/2 - (MeasureText("Chest Hunt Ver.0001", 30))/2, T_ALT/4, 30, GREEN);
				DrawText("Pressione N para iniciar", T_LARG/2 - (MeasureText("Pressione N para iniciar", 20))/2, T_ALT/2, 20, RED);
				DrawText("Pressione Q para sair", T_LARG/2 - (MeasureText("Pressione Q para sair", 20))/2, T_ALT/2 + 20, 20, RED);
				DrawText("Main programmer: @AkrilaMayNotBeAvailable", 
					T_LARG/2 - (MeasureText("Main programmer: @AkrilaMayNotBeAvailable", 20))/2,
					T_ALT-70,
					20,
					GREEN);
					
				DrawText("Assets by: Robert (0x72)", 
					T_LARG/2 - (MeasureText("Assets by: Robert (0x72)", 20))/2,
					T_ALT-45,
					20,
					YELLOW);
				DrawText("https://0x72.itch.io/dungeontileset-ii", 
					T_LARG/2 - (MeasureText("https://0x72.itch.io/dungeontileset-ii", 20))/2,
					T_ALT-20,
					20,
					YELLOW);
			break;
			case GAME:
				ClearBackground(BLACK);
				// Draws Map grid 20x20
				DrawMap(mapa, LINES_X_COLS);
				DrawTexture(bau.box, bau.pos.x, bau.pos.y, WHITE);
				DrawTexture(jogador.sprite, jogador.pos.x, jogador.pos.y, WHITE);
				
				DrawText(TextFormat("Score: %01i", jogador.pont), 10, T_ALT-20, 20, GREEN);
				DrawText(TextFormat("Segundos: %01i", jogador.tempo/FPS), T_LARG - MeasureText("Segundos: 0000", 20), T_ALT-20, 20, GREEN);
			break;
			case END:
				ClearBackground(BLACK);
				DrawText("Game Over", T_LARG/2 - (MeasureText("Game Over", 20))/2, T_ALT/2, 20, RED);
				DrawText("Pressione ENTER para voltar", 
					T_LARG/2 - (MeasureText("Pressione ENTER para voltar", 20))/2, 
					T_ALT/2-20, 
					20, 
					RED);
				DrawText(
					TextFormat("Sua Pontuação foi: %01i", jogador.pont), 
					T_LARG/2 - (MeasureText("Sua Pontuação foi: 0", 20))/2, 
					T_ALT-20, 
					20, 
					GREEN);
			break;
			default:
			break;
		}
		EndDrawing();
	}
	
	UnloadTexture(mapa.paredeEsquerda);
	UnloadTexture(mapa.parede);
	UnloadTexture(mapa.paredeDireita);
	UnloadTexture(mapa.chao);
	
	UnloadTexture(bau.box);
	
	CloseWindow();
	return 0;
}
// Verifica colisão entre dois Vector2
int CollisionCheck(Vector2 checkObjectA, Vector2 checkObjectB){
	if(checkObjectA.x == checkObjectB.x && checkObjectA.y == checkObjectB.y){
		return 1;
	}
	return 0;
}

// Movimenta qualquer tipo de Vector2 tendo um outro vetor como referência
void PlayerMovement(Vector2 *pos, Vector2 ref){
	if(IsKeyPressed(KEY_LEFT)) pos->x -= ref.x;
	if(IsKeyPressed(KEY_RIGHT)) pos->x += ref.x;
	if(IsKeyPressed(KEY_UP)) pos->y -= ref.y;
	if(IsKeyPressed(KEY_DOWN)) pos->y += ref.y;
}
/* Limite de movimento simples, caso o Vector2 esteja com um valor maior que o limite superior
* sua posição é retornada para o limite superior, caso seja menor que o limite inferior, retorna para
* o limite inferior, o ponteiro de Vector sempre considera o Vector check para confirmar as condições.
*/
void LimiterMovementBasic(Vector2 *limitedObject, Vector2 checkObject, int limiterUnder, int limiterUpper){
	if(limitedObject->x > (LINES_X_COLS-2) * checkObject.x) limitedObject->x = limiterUpper;
	if(limitedObject->x < checkObject.x) limitedObject->x = limiterUnder;
	if(limitedObject->y < checkObject.y) limitedObject->y = limiterUnder;
	if(limitedObject->y > (LINES_X_COLS-2) * checkObject.x) limitedObject->y = limiterUpper;
}
// Desenha um mapa de Grid dependente de um valor limite
void DrawMap(Mapa_t mapa, int limit){
	int i, j;
	
	for(i = 0; i < limit; i++){
		for(j = 0; j < limit; j++){
			if(j != 0 && j != limit-1 && i != 0 && i != limit-1)
				DrawTexture(mapa.chao, mapa.tamanhos.x * j, mapa.tamanhos.y * i, WHITE);
			if(i == 0 || i == limit-1)
				DrawTexture(mapa.parede, mapa.tamanhos.x * j, mapa.tamanhos.y * i, WHITE);
			if(j == 0)
				DrawTexture(mapa.paredeEsquerda, mapa.tamanhos.x * j, mapa.tamanhos.y * i, WHITE);
			if(j == limit-1)
				DrawTexture(mapa.paredeDireita, mapa.tamanhos.x * j, mapa.tamanhos.y * i, WHITE);
		}
	}
}
// Controle Básico para iniciar jogo
int InitHandler(){
	if(IsKeyPressed(KEY_N)) return 1;
	if(IsKeyPressed(KEY_Q)) return 2;
	
	return -1;
}
// Reinicialização da struct jogador
void ReinitPlayer(Jogador_t *jogador){
	jogador->pont = 0;
	jogador->tempo = FPS*10;
}
