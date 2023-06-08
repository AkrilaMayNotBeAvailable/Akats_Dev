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
	
	if(*timer == FPS*10){ // 10 sec to respawn chest
		for(i = 0; i < numChest; i++){ // Iterate through array
			chest[i].pos = (Vector2){ GetRandomValue(1, ALTURA-2)*16, GetRandomValue(1, LARGURA-2)*16 };
			if(CanSpawn(chest[i].pos, map)){
				chest[i].ativo = 1; // Restart flag if it was catch last update
				chest[i].spriteFrame.x = 0; // Reset Animation
			}
			else{
				i--;
			}
		}
		*timer = 0;
	}
}
int ChestCollected(Jogador_t *player, Chest_t *chest, int numChest, Sound chestSounds, float multip){
	int i, j;
	
	for(i = 0; i < numChest; i++){
		if(CollisionCheck(player->pos, chest[i].pos) && chest[i].ativo){
			player->pont += 5 * multip;
			player->tempo += FPS*3 + (ceil(multip));
			
			chest[i].despawn += 30;
			
			for(j = 0; j < 2; j++) UpdateBasicAnim(&chest[i].spriteFrame, 3);
			SetSoundPitch(chestSounds, 1.0f);
		
			PlaySound(chestSounds);
			
			chest[i].ativo = 0;
			return 1;
		}
		if(chest[i].despawn > 0) chest[i].despawn--;
	}
	return 0;
}
void DrawChest(Chest_t *bau, int maxChest, int spriteSize){
	int i;
	
	for(i = 0; i < maxChest; i++){
		if(bau[i].ativo || bau[i].despawn){
			DrawTextureRec(bau[i].sprite, bau[i].spriteFrame, bau[i].pos, WHITE);
		}
	}
}

void UpdateBasicAnim(Rectangle *spriteFrame, int maxFrames){
	int size = 16*maxFrames;
	
	spriteFrame->x += 16;
	if(spriteFrame->x >= size){
		spriteFrame->x = 0;
	}
}

void UpdateTimedAnim(Rectangle *spriteFrame, int maxFrames, int *timer, int speed){
	int size = 16*maxFrames;
	(*timer)++;

	if(*timer > speed){
		spriteFrame->x += 16;
		if(spriteFrame->x == size)
			spriteFrame->x = 0;
		*timer = 0;
	}
}

void MovementBonus(Vector2 pos, float *moveDelay, float baseDelay, int *timer, Chest_t *chest, int numChest, float *multip, int *tempo){
	int i;
	
	for(i = 0; i < numChest; i++){
		if(CollisionCheck(pos, chest[i].pos) && chest[i].ativo){
			*moveDelay -= 0.5f;
			if(*moveDelay < 4.0f) *moveDelay = 4.0f;
			*timer += 180;
			if(*timer > 500) *timer = 500;
			*multip += 0.5f;
			
		}
	}
	if(*timer > 0){
		(*timer)--;
		if(*timer == 0){
			*moveDelay = baseDelay;
			*multip = 0.0f;
		}
	}
	
	if(*tempo <= 0){
		*timer = 0;
		*moveDelay = baseDelay;
		*multip = 0.0f;
	}
}
//===============================================================
// Map Unlock:
//===============================================================
int SpawnEnemyStructure(Event_t *trigger, Jogador_t jogador){
	int currentLevel = trigger->enemySpawn;
	int nextLevel = 60 * (currentLevel + 1) * 5;
	// Dom(x) = {600 + (300 * x)}
	if(jogador.tempo > nextLevel){
		trigger->enemySpawn++;
		return 1;
	}

	return 0;
}
int SpawnTrapStructure(Event_t *trigger, Jogador_t jogador, int *nextAward){
	int currentLevel = trigger->trapSpawn;
	int nextLevel = 50 * (currentLevel + 1) * 5;
	// Dom(x) = {500 + (250 * x)}
	if(jogador.tempo > nextLevel){
		trigger->trapSpawn++;
		if(trigger->trapSpawn % 1 == 0){
			if(*nextAward < MAX_AWARDS - 1){
		 		(*nextAward)++; // Watch out for vector boundaries, this can't be higher than MAX_AWARDS (15)
		 	}
		}
		return 1;
	}

	return 0;
}
// Generates a structure inside map to spawn enemies
void SpawnGenerator(int **map, int largura, int altura){
	int i, j;
	int x, y;
	int sectionX = GetRandomValue(1, largura - SPAWN_LARG -1);
	int sectionY = GetRandomValue(1, altura - SPAWN_ALT -1);
	int **spawnerDesign = calloc(SPAWN_ALT, sizeof(int *));
	
  for(i = 0; i < SPAWN_ALT; i++){
      spawnerDesign[i] = calloc(SPAWN_LARG, sizeof(int));
      for(j = 0; j < SPAWN_LARG; j++){
      	if(i == 1 && (j == 1 || j == 2 || j == 5 || j == 6)) // Linha 1
      		spawnerDesign[i][j] = 1;
      	if(i == 2 && (j == 1 || j == 6)) // Linha 2
      		spawnerDesign[i][j] = 1;
      	if(i == 3 && (j == 3 || j == 4) || i == 4 && (j == 3 || j == 4))
      		spawnerDesign[i][j] = 2;
      	if(i == 5 && (j == 1 || j == 6)) // Linha 5
      		spawnerDesign[i][j] = 1;
      	if(i == 6 && (j == 1 || j == 2 || j == 5 || j == 6)) // Linha 6
      		spawnerDesign[i][j] = 1;
    	}
  } 
	
	// Change main map
	for(y = 0; y < SPAWN_ALT; y++){
		for(x = 0; x < SPAWN_LARG; x++){
			map[sectionY+y][sectionX+x] = spawnerDesign[y][x];
		}
	}
	
	// Libera Memória alocada
	for(i = 0; i < SPAWN_ALT; i++){
		free(spawnerDesign[i]);
	}
	free(spawnerDesign);
	
}
// Generates Trap field
void TrapGenerator(int **map, int mapLarg, int mapAlt){
	int i, j;
	int x, y;
	int sectionX = GetRandomValue(1, mapLarg - TRAP_SPW_SQR - 1);
	int sectionY = GetRandomValue(1, mapAlt - TRAP_SPW_SQR - 1);
	int **trapDesign = calloc(TRAP_SPW_SQR, sizeof(int *));
	
  for(i = 0; i < TRAP_SPW_SQR; i++){
      trapDesign[i] = calloc(TRAP_SPW_SQR, sizeof(int));
      for(j = 0; j < TRAP_SPW_SQR; j++){
      	if(i == 1 && (j == 1 || j == 2) || i == 2 && (j == 1 || j == 2) || i == 3 && (j == 1 || j == 2))
      		trapDesign[i][j] = 3;
    	}
  } 
	
	// Change main map
	for(y = 0; y < TRAP_SPW_SQR; y++){
		for(x = 0; x < TRAP_SPW_SQR; x++){
			map[sectionY+y][sectionX+x] = trapDesign[y][x];
		}
	}
	
	// Libera Memória alocada
	for(i = 0; i < TRAP_SPW_SQR; i++){
		free(trapDesign[i]);
	}
	free(trapDesign);
}

// Trap Logic:
void TrapDamage(int *timer, int animationCheck){
	int seconds = 60;
	
	if(animationCheck % 8 == 0){
		*timer -= seconds*1;
	}
}

// Spawn Enemy logic
void ShouldSpawnEnemy(Vector2 pos, int **matriz, int largura, int altura, Inimigo_t *inimigo){
	int seconds = 60;
	int posX = pos.x;
	int posY = pos.y;
	int dist = ASSET_SIZE * 4;
	int x, y;

	for(x = posX - dist; x <= posX + dist; x += ASSET_SIZE){
		for(y = posY - dist; y <= posY + dist; y += ASSET_SIZE){
			if(x < 0 || y < 0 || x >= LARGURA*ASSET_SIZE || y >= ALTURA*ASSET_SIZE){
				continue; // Verifica se a posição está dentro dos limites da matriz
			}
			if(matriz[y/ASSET_SIZE][x/ASSET_SIZE] == 2){
				inimigo->pos.x = x;
				inimigo->pos.y = y;
				inimigo->tempo = seconds*30;
				inimigo->moveDelay = 20;
				return; // Sai da função assim que encontrar a primeira posição válida
			}
		}
	}
}
// Movement not optimized
void EnemyMovementLogic(Vector2 reference, int **matriz, Vector2 *pos, int *moveTimer, float *dir){
	int playerX = reference.x;
	int playerY = reference.y;
	int seconds = 15;
	(*moveTimer)--;

	if(*moveTimer == 0){
		if(pos->x < playerX){
			if(CanMove(*pos, matriz, 0)) pos->x += ASSET_SIZE; // Direita
			if(*dir < 0) *dir *= -1;
			*moveTimer = seconds;
		}
		if(pos->x > playerX){
			if(CanMove(*pos, matriz, 1)) pos->x -= ASSET_SIZE; // Esquerda
			if(*dir > 0) *dir *= -1;
			*moveTimer = seconds;
		}
		if(pos->y < playerY){
			if(CanMove(*pos, matriz, 2)) pos->y += ASSET_SIZE; // Baixo
			*moveTimer = seconds;
		}
		if(pos->y > playerY){
			if(CanMove(*pos, matriz, 3)) pos->y -= ASSET_SIZE; // Cima
			*moveTimer = seconds;
		}	
	}
}
// Collision effect Enemy:
void EnemyCollision(Inimigo_t *inimigo, Vector2 object, int *tempo, Event_t currentLevel){
	int seconds = 60;
	
	if(CollisionCheck(inimigo->pos, object)){
		inimigo->tempo = 0;
		inimigo->pos = (Vector2){ 0 };
		
		if(currentLevel.enemySpawn <= 4) *tempo -= seconds*30;
		if(currentLevel.enemySpawn >= 5 && currentLevel.enemySpawn < 8) *tempo -= seconds*50;
		if(currentLevel.enemySpawn >= 8 && currentLevel.enemySpawn < 12) *tempo -= seconds*100;
		if(currentLevel.enemySpawn >= 12 && currentLevel.enemySpawn < 20) *tempo -= seconds*300;
		if(currentLevel.enemySpawn >= 20) *tempo -= seconds*999;
	}
}
// Desenha Inimigo
void DrawEnemy(Inimigo_t inimigo, int spriteSize){
	if(inimigo.pos.x != 0.0f){
		DrawTextureRec(inimigo.sprite, inimigo.spriteFrame, inimigo.pos, WHITE);
	}
}
