#ifndef FUNCTION_DECLARATION_H
#define FUNCTION_DECLARATION_H

//======================================================
// Animation
//======================================================
void UpdateBasicAnim(Rectangle *spriteFrame, int maxFrames);
void UpdateTimedAnim(Rectangle *spriteFrame, int maxFrames, int *timer, int speed);

// Essential Game Functions:
//======================================================
// Player base Functions
//======================================================
void PlayerMovement(Vector2 *pos, int **map, float *dir, float *moveDelay, float currentDelay);
void DrawPlayer(Jogador_t jogador, int assetSize);
void MovementBonus(Vector2 pos, float *moveDelay, float baseDelay, int *timer, Chest_t *chest, int numChest, float *multip, int *tempo);
void ReinitPlayer(Jogador_t *jogador, Event_t *event, int *curTitle);

//======================================================
// General Damage Handler Functions
//======================================================
void TrapDamage(int *timer, int animationCheck);
int TookDamage(Vector2 pos, int **matriz);

//======================================================
// Movement n Spawn limiters
//======================================================
int CanMove(Vector2 pos, int **matriz, int dir);
int CanSpawn(Vector2 pos, int **matriz);

//======================================================
// Basic User Input controls
//======================================================
void InitHandler(Tela_e *screen);

//======================================================
// Collision Check functions
//======================================================
int CollisionCheck(Vector2 checkObjectA, Vector2 checkObjectB);

//======================================================
// Raylib Resource Packer special functions
//======================================================
void CarregaImagemRRes(char *nomeArq, int id, Texture2D *textura);
void CarregaAudioRawData(char *nomeArq, int id, void *dados, Music *music);
void CarregaSFXRRes(char *nomeArq, int id, Sound *sound);

//======================================================
// Front-end auxiliar functions
//======================================================
int BottomScreenText(int scrnHeight, int fontSize, int decrement);
int CenterTextHorizontal(char *string, int fontSize, int largura);

void DesenhaCreditos(char **nome, char **contato, int fontSize, int largura, int limite);
void DrawAkatsTeam(char **logoStrings, int fontSize, int largura, int altura, int limite, Texture2D logotype);
void DrawTitleScreen(char *title, char **menuOptions, int fontSize, int largura, int altura, int totalOp);
void DrawTutorial(char **strings, int fontSize, int largura, int altura, int totalSize);
void DrawCurrentStats(char *chestTitle[MAX_AWARDS], int fontSize, int largura, int altura, Jogador_t jogador, int maxAwards, int currentTitle);
void DrawFinalStatus(char *chestTitle[MAX_AWARDS], int fontSize, int largura, int altura, Event_t events, int lastTitle, int pont);

// Screen Updater Functions
//------------------------------------------------
int FrameCounter(int *counter, int waitTime);

//======================================================
// Chest Functions
//======================================================
void ChangePositionRand(int *timer, Chest_t *chest, int numChest, int **map);
int ChestCollected(Jogador_t *jogador, Chest_t *chest, int numChest, Sound chestSFX, float multip);
void DrawChest(Chest_t *bau, int maxChest, int spriteSize);

//======================================================
// Enemy Functions
//======================================================
void ShouldSpawnEnemy(Vector2 pos, int **matriz, int largura, int altura, Inimigo_t *inimigo);
void DrawEnemy(Inimigo_t inimigo, int spriteSize);
void EnemyMovementLogic(Vector2 reference, int **matriz, Vector2 *pos, int *moveTimer, float *dir);
void EnemyCollision(Inimigo_t *inimigo, Vector2 object, int *tempo, Event_t currentLevel);

//======================================================
// Terrain Modification
//======================================================
void SpawnGenerator(int **map, int largura, int altura);
void TrapGenerator(int **map, int mapLarg, int mapAlt);
// Auxiliar Functions for Terrain modification
//------------------------------------------------------
int SpawnEnemyStructure(Event_t *trigger, Jogador_t jogador);
int SpawnTrapStructure(Event_t *trigger, Jogador_t jogador, int *nextAward);

//======================================================
// Map Basic functions
//======================================================
void DrawMap(Mapa_t *map, int lines, int cols, Texture_t piso, Texture_t parede, AnimatedObj_t trap);
Mapa_t *AllocMap(int lines, int cols);
void RandomizeMap(int **matriz, int lines, int cols);
void SmoothMapCellularAutomata(int **map, int lines, int cols);
int ContaVizinhos(int **map, int x, int y);
void SetWall(int **map, int lines, int cols);
void FreeMap();


#endif
