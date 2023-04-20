// @AkrilaMayNotBeAvailable - Akats Dev Team, Leader Dev
/* Esse código foi feito com objetivos didáticos.
* É estritamente proíbida a venda deste código.
*/
#include "header_manager.h"
#include "function_declaration.h"

// Verifica colisão entre dois Vector2
int CollisionCheck(Vector2 checkObjectA, Vector2 checkObjectB){
	if(checkObjectA.x == checkObjectB.x && checkObjectA.y == checkObjectB.y){
		return 1;
	}
	return 0;
}
// Movimenta qualquer tipo de Vector2 tendo um outro vetor como referência
void PlayerMovement(Vector2 *pos, int **map){
	if(IsKeyPressed(KEY_RIGHT)) 
		if(CanMove(*pos, map, 0)) pos->x += 16;
	if(IsKeyPressed(KEY_LEFT)) 
		if(CanMove(*pos, map, 1)) pos->x -= 16;
	if(IsKeyPressed(KEY_DOWN)) 
		if(CanMove(*pos, map, 2)) pos->y += 16;
	if(IsKeyPressed(KEY_UP)) 
		if(CanMove(*pos, map, 3)) pos->y -= 16;
}
/* Limite de movimento simples, caso o Vector2 esteja com um valor maior que o limite superior
* sua posição é retornada para o limite superior, caso seja menor que o limite inferior, retorna para
* o limite inferior, o ponteiro de Vector sempre considera o Vector check para confirmar as condições.
*/
void LimiterMovementBasic(Vector2 *limitedObject, Vector2 checkObject, int limiterUnder, int limiterUpper){
	if(limitedObject->x > (20-2) * checkObject.x) limitedObject->x = limiterUpper;
	if(limitedObject->x < checkObject.x) limitedObject->x = limiterUnder;
	if(limitedObject->y < checkObject.y) limitedObject->y = limiterUnder;
	if(limitedObject->y > (20-2) * checkObject.x) limitedObject->y = limiterUpper;
}
//
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
//
int CanSpawn(Vector2 pos, int **matriz){
	int posX = pos.x;
	int posY = pos.y;
	
	if(matriz[posY/ASSET_SIZE][posX/ASSET_SIZE] == 1) return 0;
	
	return 1;
}
// Reinicialização da struct jogador
void ReinitPlayer(Jogador_t *jogador){
	jogador->pont = 0;
	jogador->tempo = FPS*3;
}
