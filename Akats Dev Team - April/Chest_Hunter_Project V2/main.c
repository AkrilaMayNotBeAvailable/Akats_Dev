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
	char *resourcesFile = {"chestHuntRes.rres"};
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
	//===============================================================
	SetRandomSeed(time(NULL));
	// Initialize variables
	int chestClock = 0;
	int id = 0;
	int i;
	// Screen Manager
	Tela_e screen = INIT;
	
	// Main Variables Declaration:
	Chest_t bau[MAX_CHEST] = { 0 };
	Jogador_t jogador = { 0 };
	Mapa_t *mapa = AllocMap(ALTURA, LARGURA);
	Camera2D camera = { 0 };
	Music bgm = { 0 };
	
	// Texture Variables Declaration:
	Texture_t objeto = { 0 };
	Texture_t piso = { 0 };
	Texture_t parede = { 0 };
	
	// Camera 2D Initialization
	camera.target = jogador.pos;
	camera.offset = (Vector2){ T_LARG/2, T_ALT/2 };
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;
	
	// Game bgm Initialization
	void *bgmRawData = NULL;

	//================================================================
	// Window -> Textures, audios etc must be loaded after window.
	InitWindow(T_LARG, T_ALT, TITULO);
	
	InitAudioDevice();
	
	rresCentralDir dir = rresLoadCentralDirectory("chestHuntRes.rres");
	
	//======================================================
	id = rresGetResourceId(dir, "box.png");
	CarregaImagemRRes(resourcesFile, id, &objeto.tex[0]);
	//======================================================
	id = rresGetResourceId(dir, "floor_1.png");
	CarregaImagemRRes(resourcesFile, id, &piso.tex[0]);
	//======================================================
	id = rresGetResourceId(dir, "paredeMeio.png");
	CarregaImagemRRes(resourcesFile, id, &parede.tex[0]);
	id = rresGetResourceId(dir, "paredeDir.png");
	CarregaImagemRRes(resourcesFile, id, &parede.tex[1]);
	id = rresGetResourceId(dir, "paredeEsq.png");
	CarregaImagemRRes(resourcesFile, id, &parede.tex[2]);
	//======================================================
	id = rresGetResourceId(dir, "sprite.png");
	CarregaImagemRRes(resourcesFile, id, &jogador.sprite);
	//======================================================
	id = rresGetResourceId(dir, "BgMusic.mp3");
	CarregaAudioRawData(resourcesFile, id, &bgmRawData, &bgm);
	//======================================================
	SetMusicVolume(bgm, 0.3f);
	PlayMusicStream(bgm);
	
	SetTargetFPS(FPS);
	while(screen){
		switch(screen){
			case INIT: 			// Tela Inicial do jogo
				InitHandler(&screen);
				break;
			case CREDITOS: 	// Créditos
				if(IsKeyPressed(KEY_ENTER)) screen = INIT;
				break;
			case LOADING: 	// Verificações de dados
				ReinitPlayer(&jogador);
				RandomizeMap(mapa->matriz, ALTURA, LARGURA);
				for(i = 0; i < 3; i++)
					SmoothMapCellularAutomata(mapa->matriz, ALTURA, LARGURA);
				SetWall(mapa->matriz, ALTURA, LARGURA);
				
				// Chest Initialization:
				for(i = 0; i < MAX_CHEST; i++){
					bau[i].pos = (Vector2){GetRandomValue(1, ALTURA-2)*16, GetRandomValue(1, LARGURA-2)*16 };
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
			case GAME:
			// Update Variables
			UpdateMusicStream(bgm);
			jogador.tempo--;
			
			ChangePositionRand(&chestClock, bau, MAX_CHEST, mapa->matriz);
			ChestCollected(&jogador, bau, MAX_CHEST);
			
			PlayerMovement(&jogador.pos, mapa->matriz);
			
			camera.target = (Vector2){ jogador.pos.x, jogador.pos.y };
			
			if(jogador.tempo == 0) screen = END;
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
			case INIT:
				ClearBackground(BLACK);
				DrawText("Chest Hunt Ver.0010", T_LARG/2 - (MeasureText("Chest Hunt Ver.0010", 30))/2, T_ALT/4, 30, GREEN);
				DrawText("Pressione N para iniciar", T_LARG/2 - (MeasureText("Pressione N para iniciar", 20))/2, T_ALT/2, 20, RED);
				DrawText("Pressione C para créditos", T_LARG/2 - (MeasureText("Pressione C para créditos", 20))/2, T_ALT/2 + 20, 20, RED);
				DrawText("Pressione Q para sair", T_LARG/2 - (MeasureText("Pressione Q para sair", 20))/2, T_ALT/2 + 40, 20, RED);
			break;
			case CREDITOS:	
				ClearBackground(BLACK);
				// Crédito para contribuições ao projeto:
				DesenhaCreditos(nomes, links, FONT_NORMAL_SIZE, T_LARG, AUTHORS);
			break;
			case GAME:
				ClearBackground(BLACK);
				
				BeginMode2D(camera);
					DrawMap(mapa, ALTURA, LARGURA, piso, parede);
					
					for(i = 0; i < MAX_CHEST; i++){
						if(bau[i].ativo)
							DrawTextureV(objeto.tex[0], bau[i].pos, WHITE);
					}
					
					DrawTextureV(jogador.sprite, jogador.pos, WHITE);
				EndMode2D();
				
				//======================================================
				DrawRectangle(0, T_ALT-20, T_LARG, 22, BLACK);	
				DrawText(TextFormat("Score: %01i", jogador.pont), 10, T_ALT-20, 20, GREEN);
				DrawText(TextFormat("Segundos: %01i", jogador.tempo/FPS), T_LARG - MeasureText("Segundos: 0000", 20), T_ALT-20, 20, GREEN);
				//======================================================
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
	
	UnloadTexture(jogador.sprite);
	for(i = 0; i < MAX_TEXTURES; i++){
		UnloadTexture(objeto.tex[i]);
		UnloadTexture(piso.tex[i]);
		UnloadTexture(parede.tex[i]);
	}
	FreeMap(mapa);
	MemFree(bgmRawData);
	CloseAudioDevice();
	CloseWindow();
	return 0;
}
