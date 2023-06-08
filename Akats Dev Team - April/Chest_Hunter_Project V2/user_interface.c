#include "header_manager.h"
#include "function_declaration.h"

// Recebe o tamanho da tela, tamanho da fonte e um decremento para ajustar a posição
/* 
* @Param scrnHeight -> Altura total da tela
* @Param fontSize -> Tamanho da fonte
* @Param decrement -> Decremento da altura da tela para posicionamento
* Return -> Posição para base da tela
*/
int BottomScreenText(int scrnHeight, int fontSize, int decrement){
	return scrnHeight - fontSize - decrement;
}
int CenterTextHorizontal(char *string, int fontSize, int largura){
	return largura/2 - (MeasureText(string, fontSize))/2;
}
void DesenhaCreditos(char **nome, char **contato, int fontSize, int largura, int limite){
	int autor, linha;
	int incrementoLinha = 3;
	
	ClearBackground(BLACK);
	
	for(autor = 0, linha = 0; autor < limite; autor++){
		linha += incrementoLinha;
		
		// Cargo: Nome
		DrawText(
			nome[autor], 
			CenterTextHorizontal(nome[autor], fontSize, largura),
			fontSize * (linha),
			fontSize,
			GREEN
		);
		
		// Link / Contato
		DrawText(
			contato[autor],
			CenterTextHorizontal(contato[autor], fontSize, largura),
			fontSize * (linha + 1),
			fontSize,
			YELLOW
		);
		
		// Library Credits
		if(autor+1 == limite){
				DrawText("Made using: Raylib", 
					CenterTextHorizontal("Made Using: Raylib", fontSize, largura),
					BottomScreenText(T_ALT, fontSize, fontSize),
					fontSize,
					RED
				);
				DrawText("Pressione ENTER para retornar", 
					CenterTextHorizontal("Pressione ENTER para retornar", fontSize, largura),
					BottomScreenText(T_ALT, fontSize, 0),
					fontSize,
					RED
				);
		}
	}
}

// Verifica se passaram determinada quantidade de quadros desde a chamada da função
int FrameCounter(int *counter, int waitTime){
	(*counter)++;
	
	if(*counter >= waitTime){
		*counter = 0;
		return 1;
	}
	return 0;
}

// Desenha o logo da equipe de desenvolvimento
void DrawAkatsTeam(char **logoStrings, int fontSize, int largura, int altura, int limite, Texture2D logotype){	
	int basePosY = (altura/3)+(0*(fontSize*2));
	
	Rectangle basicData = { 0, 0, logotype.width, logotype.height };
	NPatchInfo resizeImage = {basicData, NPATCH_NINE_PATCH };
	Rectangle fullScreen = { 0, 0, largura, altura };
	const float rot = 0.0f;
	const Vector2 origem = { 0.0f, 0.0f };
	Color imageColor = {255, 255, 255, 32};
	
	ClearBackground(BLACK);
	
	// Texture above text:
	//======================
	DrawTextureNPatch(logotype, resizeImage, fullScreen, origem, rot, imageColor);
	
	// Akats Dev Team 
	DrawText(
		logoStrings[0],
		CenterTextHorizontal(logoStrings[0], fontSize+20, largura),
		basePosY,
		fontSize+20,
		ORANGE
	);
	// Involved Members (Loopable)
	DrawText(
		logoStrings[1], // AkrilaMayNotBeAvailable Project
		CenterTextHorizontal(logoStrings[1], fontSize, largura),
		basePosY+(fontSize*2),
		fontSize,
		YELLOW
	);
	// Project
	DrawText(
		logoStrings[2], // April Game Challenge
		CenterTextHorizontal(logoStrings[2], fontSize+20, largura),
		basePosY+(fontSize*5),
		fontSize+20,
		ORANGE
	);
}

// Main Initial Screen
void DrawTitleScreen(char *title, char **menuOptions, int fontSize, int largura, int altura, int totalOp){
	int i;
	
	ClearBackground(BLACK);
	DrawText(title, CenterTextHorizontal(title, fontSize+20, largura), altura/4, fontSize+20, YELLOW);
	
	for(i = 0; i < totalOp; i++)
		DrawText(menuOptions[i], CenterTextHorizontal(menuOptions[i], fontSize, largura), altura/2 + i*fontSize, fontSize, RED);
}

// In-game Status UI
void DrawCurrentStats(char *chestTitle[MAX_AWARDS], int fontSize, int largura, int altura, Jogador_t jogador, int maxAwards, int currentTitle){
	Color titleColors[MAX_AWARDS] = { 
		RAYWHITE, WHITE, GRAY, // Initial Tier
		LIGHTGRAY, DARKGRAY, LIME, // Secondary Tier
		GREEN, DARKGREEN, YELLOW, // Third tier
		ORANGE, GOLD, BLUE, // Fourth Tier
		SKYBLUE, DARKBLUE, RED // Champion Tier
	};
	DrawRectangle(0, 0, T_LARG, fontSize+5, (Color){ 0, 0, 0, 128 });
	
	DrawText(chestTitle[currentTitle], fontSize, 0, fontSize, titleColors[currentTitle]);

	DrawRectangle(0, T_ALT-20, T_LARG, fontSize+2, BLACK);
		
	DrawText(TextFormat("Score: %02i", jogador.pont), 10, altura-20, fontSize, GREEN);
	DrawText(TextFormat("Segundos: %01i", jogador.tempo/60), largura - MeasureText("Segundos: 0000", 20), altura-fontSize, fontSize, GREEN);
}
// End Game Screen
void DrawFinalStatus(char **chestTitle, int fontSize, int largura, int altura, Event_t events, int lastTitle, int pont){
	Color titleColors[MAX_AWARDS] = { 
		RAYWHITE, WHITE, GRAY, // Initial Tier
		LIGHTGRAY, DARKGRAY, LIME, // Secondary Tier
		GREEN, DARKGREEN, YELLOW, // Third tier
		ORANGE, GOLD, BLUE, // Fourth Tier
		SKYBLUE, DARKBLUE, RED // Champion Tier
	};
	ClearBackground(BLACK);
	
	DrawText("Game Over", largura/2 - (MeasureText("Game Over", fontSize*2))/2, altura/3, fontSize*2, RED);
	DrawText("Pressione ENTER para voltar", 
		largura/2 - (MeasureText("Pressione ENTER para voltar", fontSize))/2, 
		altura-fontSize, 
		fontSize, 
		RED);
	DrawText(
		TextFormat("Sua Pontuação foi: %01i", pont), 
		largura/2 - (MeasureText("Sua Pontuação foi: 00000", fontSize+10))/2, 
		altura/2, 
		fontSize+10, 
		GREEN);
	DrawText(
		chestTitle[lastTitle], 
		CenterTextHorizontal(chestTitle[lastTitle], fontSize*2, largura), 
		altura/2+(fontSize*2),
		fontSize*2,
		titleColors[lastTitle]);
	DrawText(
		TextFormat("Você ativou: %01i armadilhas!", events.trapSpawn), 
		largura/2 - (MeasureText("Você ativou 00 armadilhas!", fontSize))/2, 
		altura/2 + 90, 
		fontSize, 
		titleColors[lastTitle]);
	DrawText(
		TextFormat("Você ativou: %01i spawners!", events.enemySpawn), 
		largura/2 - (MeasureText("Você ativou 00 spawners!", fontSize))/2, 
		altura/2 + 120, 
		fontSize, 
		titleColors[lastTitle]);
}
// Tutorial Screen
void DrawTutorial(char **strings, int fontSize, int largura, int altura, int totalSize){
	int i;
	
	ClearBackground(BLACK);
	
	for(i = 0; i < totalSize; i++){
	DrawText(
		strings[i], 
		fontSize, 
		altura/4+i * fontSize,
		fontSize,
		YELLOW);
	}
	
	DrawText("Pressione ENTER para voltar", 
		largura/2 - (MeasureText("Pressione ENTER para voltar", fontSize))/2, 
		altura-fontSize, 
		fontSize, 
		RED);
}

