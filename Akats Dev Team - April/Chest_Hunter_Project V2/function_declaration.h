#ifndef FUNCTION_DECLARATION_H
#define FUNCTION_DECLARATION_H

// Essential Game Functions:
	// Player
void PlayerMovement(Vector2 *pos, int **map);
void ReinitPlayer(Jogador_t *jogador);
	
	// Limiters
void LimiterMovementBasic(Vector2 *limitedObject, Vector2 checkObject, int limiterUnder, int limiterUpper);
int CanMove(Vector2 pos, int **matriz, int dir);
int CanSpawn(Vector2 pos, int **matriz);

	// UI
void InitHandler(Tela_e *screen);

	// Dual Vector Collision Check
int CollisionCheck(Vector2 checkObjectA, Vector2 checkObjectB);

// Resource Packager Functions:
void CarregaImagemRRes(char *nomeArq, int id, Texture2D *textura);
void CarregaAudioRawData(char *nomeArq, int id, void *dados, Music *music);

// UI functions:
int BottomScreenText(int scrnHeight, int fontSize, int decrement);
int CenterTextHorizontal(char *string, int fontSize, int largura);
void DesenhaCreditos(char **nome, char **contato, int fontSize, int largura, int limite);

// Chest Logic:
void ChangePositionRand(int *timer, Chest_t *chest, int numChest, int **map);
void ChestCollected(Jogador_t *jogador, Chest_t *chest, int numChest);

// Mapa:
void DrawMap(Mapa_t *map, int lines, int cols, Texture_t piso, Texture_t parede);
Mapa_t *AllocMap(int lines, int cols);
void RandomizeMap(int **matriz, int lines, int cols);
void SmoothMapCellularAutomata(int **map, int lines, int cols);
int ContaVizinhos(int **map, int x, int y);
void SetWall(int **map, int lines, int cols);
void FreeMap();


#endif
