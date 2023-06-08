// @AkrilaMayNotBeAvailable - Akats Dev Team, Leader Dev
/* Esse código foi feito com objetivos didáticos.
* É estritamente proíbida a venda deste código.
*/
#include "header_manager.h"
#include "function_declaration.h"

int main(){
	//===============================================================
	// String Section:
	//===============================================================
	// Lista de Strings
	//---------------------------------------------------------------
	char *nomes[AUTHORS] = {
		"Lead programmer: @AkrilaMayNotBeAvailable",
		"Textures by: Robert (0x72)",
		"Sound Designer: William Abreu"
	};
	char *links[AUTHORS] = {
		"https://github.com/AkrilaMayNotBeAvailable/",
		"https://0x72.itch.io/dungeontileset-ii",
		"Instagram: @williamabreuuu"
	};
	char *logoInit[AKATS_LOGO] = {
		"Akats Development Team",
		"@AkrilaMayNotBeAvailable",
		"April Edition - Akats Game Challenge"
	};
	char *menuOptions[MAX_MENU_OP] = {
		"Pressione N para iniciar",
		"Pressione C para créditos",
		"Pressione T para tutorial",
		"Pressione Q para sair"
	};
	char *chestTitles[MAX_AWARDS] = {
		"Caçador Novato",
		"Quase-caçador",
		"Verme da Masmorra",
		"Cosplayer de Mimic",
		"Onde esta meu baú?",
		"EU QUERO PAUSAAAAR",
		"Deus da caça de baús",
		"Baú da Felicidade MAH OI!",
		"Eu e meu amigo demônio",
		"Quanto tempo se passou?",
		"Infinitus Chestus",
		"Padoru está chegando?",
		"A Masmorra mais absurda",
		"Quase enfrentando o limite",
		"Mestre do Chest Hunter!"
	};
	char *tutorial[TUTORIAL_SIZE] = {
		"Segure as setas para se mover!",
		"Pegar baús aumenta sua velocidade até certo ponto!",
		"O pequeno demônio causa instakill!",
		"Armadilhas causam dano ao seu tempo.",
		"Conforme o jogo avança o mapa fica mais caótico!",
		"Aperte P para fechar a aplicação."
	};
	// Strings Simples
	//---------------------------------------------------------------
	char *resourcesFile = {"chest_hunter_res.rres"};
	char *gameTitle = {"Chest Hunter Alpha Version 2023"};
	char *identificator = malloc(MAX_STRING_ID * sizeof(char));
	//===============================================================
	SetRandomSeed(time(NULL));
	// Initialize variables
	int chestClock = 0;
	int bonusClock = 0;
	int frameCounter = 0;
	int id = 0;
	int curTitle = 0;
	int name;
	int i;

	float moveDelay = 12.0f;
	float currentDelay = 12.0f;
	
	// Screen Manager
	Tela_e screen = LOGO;
	
	// Main Variables Declaration:
	Chest_t bau[MAX_CHEST] = { 0 };
	Jogador_t jogador = { 0 };
	Mapa_t *mapa = AllocMap(ALTURA, LARGURA);
	Event_t trigger = { 0 };
	AnimatedObj_t trap = { 0 };
	Inimigo_t inimigo = { 0 };
	Camera2D camera = { 0 };
	Music bgm = { 0 };
	
	// Texture Variables Declaration:
	Rectangle basicFrameRect = { 0.0f, 0.0f, 16.0f, 16.0f };
	
	Texture2D akatsLogo = { 0 };
	Texture_t piso = { 0 };
	Texture_t parede = { 0 };
	
	// Camera 2D Initialization
	camera.target = jogador.pos;
	camera.offset = (Vector2){ T_LARG/2, T_ALT/2 };
	camera.rotation = 0.0f;
	camera.zoom = 2.0f;
	
	// Game bgm Initialization
	void *bgmRawData = NULL;
	Sound chestSounds = { 0 };

	//================================================================
	// Window -> Textures, audios etc must be loaded after window.
	InitWindow(T_LARG, T_ALT, TITULO);
	
	InitAudioDevice();
	
	rresCentralDir dir = rresLoadCentralDirectory("chest_hunter_res.rres");
	//======================================================
	for(i = 0; i < MAX_CHEST; i++){
		id = rresGetResourceId(dir, "Chest_Anim.png");
		CarregaImagemRRes(resourcesFile, id, &bau[i].sprite);
	}
	id = rresGetResourceId(dir, "Goblin_Idle.png");
	CarregaImagemRRes(resourcesFile, id, &jogador.sprite);
	id = rresGetResourceId(dir, "Mini_demon_idle.png");
	CarregaImagemRRes(resourcesFile, id, &inimigo.sprite);
	//======================================================
	for(i = 0, name = 1; i < 9; i++, name++){
		sprintf(identificator, "floor_%i.png", name);
		id = rresGetResourceId(dir, identificator);
		CarregaImagemRRes(resourcesFile, id, &piso.tex[i]);
	}
	//======================================================
	id = rresGetResourceId(dir, "paredeMeio.png");
	CarregaImagemRRes(resourcesFile, id, &parede.tex[0]);
	id = rresGetResourceId(dir, "paredeDir.png");
	CarregaImagemRRes(resourcesFile, id, &parede.tex[1]);
	id = rresGetResourceId(dir, "paredeEsq.png");
	CarregaImagemRRes(resourcesFile, id, &parede.tex[2]);
	//======================================================
	id = rresGetResourceId(dir, "Trap.png");
	CarregaImagemRRes(resourcesFile, id, &trap.sprite);
	//======================================================
	id = rresGetResourceId(dir, "BgMusic.mp3");
	CarregaAudioRawData(resourcesFile, id, &bgmRawData, &bgm);
	//======================================================
	
	Wave chestOpen = LoadWave("resources/BGM/chest_open_4.wav");
	chestSounds = LoadSoundFromWave(chestOpen);
	UnloadWave(chestOpen);
	
	akatsLogo = LoadTexture("resources/Texture/Akats_Dev_Logo.png");
	
	free(identificator);
	
	// Atribuição de Sprite Frame
	jogador.spriteFrame = basicFrameRect;
	trap.spriteFrame = basicFrameRect;
	inimigo.spriteFrame = basicFrameRect;
	for(i = 0; i < MAX_CHEST; i++){
		bau[i].spriteFrame = basicFrameRect;
	}
	
	SetMusicVolume(bgm, 0.3f);
	PlayMusicStream(bgm);
	
	SetTargetFPS(FPS);
	while(screen && !IsKeyPressed(KEY_P)){
		switch(screen){
			case LOGO:
				if(FrameCounter(&frameCounter, FPS*5) || IsKeyPressed(KEY_ENTER)){
					UnloadTexture(akatsLogo);
					screen = INIT;
				}
				break;
			case INIT: 			// Tela Inicial do jogo
				InitHandler(&screen);
				break;
			case CREDITOS: 	// Créditos
				if(IsKeyPressed(KEY_ENTER)) screen = INIT;
				break;
			case TUTORIAL:	// Basic Tutorial
				if(IsKeyPressed(KEY_ENTER)) screen = INIT;
				break;
			case LOADING: 	// Verificações de dados
				ReinitPlayer(&jogador, &trigger, &curTitle);
				RandomizeMap(mapa->matriz, ALTURA, LARGURA);
				for(i = 0; i < 3; i++)
					SmoothMapCellularAutomata(mapa->matriz, ALTURA, LARGURA);
				SetWall(mapa->matriz, ALTURA, LARGURA);
				
				// Chest Initialization:
				for(i = 0; i < MAX_CHEST; i++){
					bau[i].pos = (Vector2){GetRandomValue(1, ALTURA-2)*16, GetRandomValue(1, LARGURA-2)*16 };
					bau[i].spriteFrame = basicFrameRect;
					if(CanSpawn(bau[i].pos, mapa->matriz)) bau[i].ativo = 1;
					else i--;
				}
				// Player Initialization
				do{
					jogador.pos = (Vector2){GetRandomValue(1, ALTURA-2)*16, GetRandomValue(1, LARGURA-2)*16 };
				}while(!CanSpawn(jogador.pos, mapa->matriz));
				
				screen = GAME;
				break;
			// Jogo
			case GAME: // Update Variables
			UpdateMusicStream(bgm);
			// Atualiza animações
			UpdateTimedAnim(&jogador.spriteFrame, 4, &jogador.animClock, 10);
			UpdateTimedAnim(&trap.spriteFrame, 4, &trap.animClock, 15);
			UpdateTimedAnim(&inimigo.spriteFrame, 4, &inimigo.animClock, 10);
			
			// Atualiza Inimigos
			if(inimigo.tempo <= 0){
				ShouldSpawnEnemy(jogador.pos, mapa->matriz, LARGURA, ALTURA, &inimigo);
				if(inimigo.tempo == 0){
					inimigo.pos = (Vector2){ 0.0f, 0.0f };
					inimigo.moveDelay = 0;
				}
			}
			else{
				inimigo.tempo--;
			}
			EnemyMovementLogic(jogador.pos, mapa->matriz, &inimigo.pos, &inimigo.moveDelay, &inimigo.spriteFrame.width);
			EnemyCollision(&inimigo, jogador.pos, &jogador.tempo, trigger);
			
			// Event Handler
			if(SpawnTrapStructure(&trigger, jogador, &curTitle)) TrapGenerator(mapa->matriz, LARGURA, ALTURA);
			if(SpawnEnemyStructure(&trigger, jogador)) SpawnGenerator(mapa->matriz, LARGURA, ALTURA);
			
			// Chest Updater
			ChangePositionRand(&chestClock, bau, MAX_CHEST, mapa->matriz);
			ChestCollected(&jogador, bau, MAX_CHEST, chestSounds, jogador.multiplicator);
			
			// Player Updater
			jogador.tempo--;
			if(TookDamage(jogador.pos, mapa->matriz)) TrapDamage(&jogador.tempo, trap.animClock); 
			PlayerMovement(&jogador.pos, mapa->matriz, &jogador.spriteFrame.width, &moveDelay, currentDelay);
			MovementBonus(jogador.pos, &currentDelay, DELAY_SPD, &bonusClock, bau, MAX_CHEST, &jogador.multiplicator, &jogador.tempo);
			
			camera.target = (Vector2){ jogador.pos.x, jogador.pos.y };
			
			if(jogador.tempo <= 0) screen = END;
			break;
			
			case END:
				SeekMusicStream(bgm, 0.0f);
				if(IsKeyPressed(KEY_ENTER)) screen = INIT;
			break;
			
			default: 
			break;
		}
		
		// Drawing Ambient
		BeginDrawing();
		switch(screen){
			case LOGO:
				DrawAkatsTeam(logoInit, FONT_NORMAL_SIZE, T_LARG, T_ALT, AKATS_LOGO, akatsLogo);
				break;
			case INIT:
				DrawTitleScreen(gameTitle, menuOptions, FONT_NORMAL_SIZE, T_LARG, T_ALT, MAX_MENU_OP);
				break;
			case TUTORIAL:
				DrawTutorial(tutorial, FONT_NORMAL_SIZE, T_LARG, T_ALT, TUTORIAL_SIZE);
				break;
			case CREDITOS:	
				DesenhaCreditos(nomes, links, FONT_NORMAL_SIZE, T_LARG, AUTHORS);
				break;
			case GAME:
				ClearBackground(BLACK);
				
				BeginMode2D(camera);
				
					DrawMap(mapa, ALTURA, LARGURA, piso, parede, trap);
					DrawChest(bau, MAX_CHEST, ASSET_SIZE);
					DrawEnemy(inimigo, ASSET_SIZE);
					DrawPlayer(jogador, ASSET_SIZE);
					
				EndMode2D();
				
				DrawCurrentStats(chestTitles, FONT_NORMAL_SIZE, T_LARG, T_ALT, jogador, MAX_AWARDS, curTitle);
				break;
			case END:
				DrawFinalStatus(chestTitles, FONT_NORMAL_SIZE, T_LARG, T_ALT, trigger, curTitle, jogador.pont);
				break;
			default:
				break;
		}
		EndDrawing();
	}
	
	UnloadTexture(akatsLogo);
	UnloadTexture(jogador.sprite);
	UnloadSound(chestSounds);
	UnloadTexture(trap.sprite);
	UnloadTexture(inimigo.sprite);
	
	for(i = 0; i < MAX_CHEST; i++){
		UnloadTexture(bau[i].sprite);
	}
	
	for(i = 0; i < MAX_TEXTURES; i++){
		UnloadTexture(piso.tex[i]);
		UnloadTexture(parede.tex[i]);
	}
	FreeMap(mapa);
	MemFree(bgmRawData);
	
	CloseAudioDevice();
	CloseWindow();
	
	return 0;
}
