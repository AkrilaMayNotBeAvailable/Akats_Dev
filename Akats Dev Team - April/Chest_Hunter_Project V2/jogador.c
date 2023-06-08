#include "header_manager.h"
#include "function_declaration.h"

// Verifica colisão entre dois Vector2
int CollisionCheck(Vector2 checkObjectA, Vector2 checkObjectB){
	if(checkObjectA.x == checkObjectB.x && checkObjectA.y == checkObjectB.y){
		return 1;
	}
	return 0;
}
// Verifica se algum objeto pode se mover para a próxima célula da matriz
int CanMove(Vector2 pos, int **matriz, int dir){
	int proxPosX = pos.x;
	int proxPosY = pos.y;
	// Conforme o @Param dir define qual posição deve ser verificada:
	if(dir == 0) proxPosX += 16; // Direita
	else if(dir == 1) proxPosX -= 16; // Esquerda
	else if(dir == 2) proxPosY += 16; // Baixo
	else if(dir == 3) proxPosY -= 16; // Cima
	
	if(matriz[proxPosY/ASSET_SIZE][proxPosX/ASSET_SIZE] == 1) return 0;
	
	return 1;
}
// Verifica se algum objeto vai ser posicionado em uma parede
int CanSpawn(Vector2 pos, int **matriz){
	int posX = pos.x;
	int posY = pos.y;
	
	if(matriz[posY/ASSET_SIZE][posX/ASSET_SIZE] == 1) return 0;
	
	return 1;
}
// Trap Damage verifier
int TookDamage(Vector2 pos, int **matriz){
	int posX = pos.x;
	int posY = pos.y;

	if(matriz[posY/ASSET_SIZE][posX/ASSET_SIZE] == 3) return 1;
	
	return 0;
}
// Reinicialização da struct jogador
void ReinitPlayer(Jogador_t *jogador, Event_t *event, int *curTitle){
	jogador->pont = 0;
	jogador->tempo = FPS*10;
	jogador->multiplicator = 0;
	*curTitle = 0;
	event->enemySpawn = 0;
	event->trapSpawn = 0;
}

// Ambiente Gráfico
void DrawPlayer(Jogador_t jogador, int spriteSize){
	
	DrawTextureRec(jogador.sprite, jogador.spriteFrame, jogador.pos, WHITE);

}
