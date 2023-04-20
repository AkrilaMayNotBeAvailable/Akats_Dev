// @AkrilaMayNotBeAvailable
// Esse subprograma tem como objetivo tratar as lógicas do jogo em geral.
#include "header_manager.h"
#include "function_declaration.h"

//===============================================================
// Chest Logic:
//===============================================================
void ChangePositionRand(int *timer, Chest_t *chest, int numChest, int **map){
	int i;
	(*timer)++; // Update Counter
	
	if(*timer == FPS*2){ // 2 sec to respawn chest
		for(i = 0; i < numChest; i++){ // Iterate through array
			chest[i].pos = (Vector2){ GetRandomValue(1, ALTURA-2)*16, GetRandomValue(1, LARGURA-2)*16 };
			if(CanSpawn(chest[i].pos, map)){
				chest[i].ativo = 1;
			}
			else{
				i--;
			}
		}
		*timer = 0;
	}
}
void ChestCollected(Jogador_t *player, Chest_t *chest, int numChest){
	int i;
	
	for(i = 0; i < numChest; i++){
		if(CollisionCheck(player->pos, chest[i].pos) && chest[i].ativo){
			chest[i].ativo = 0;
			player->pont += 20;
			player->tempo += FPS*3;
		}
	}
}
//===============================================================
// Map Unlock:
//===============================================================

