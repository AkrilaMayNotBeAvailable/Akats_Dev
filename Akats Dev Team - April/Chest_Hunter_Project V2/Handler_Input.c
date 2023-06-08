// @AkrilaMayNotBeAvailable
// Esse subprograma tem como objetivo tratar sobre as funções de controles / Inputs do usuário
#include "header_manager.h"
#include "function_declaration.h"

//================================================
// Controles de Menu
//================================================
// Controle Básico do menu inicial
void InitHandler(Tela_e *screen){
	if(IsKeyPressed(KEY_N)) *screen = LOADING;; // N para novo jogo
	if(IsKeyPressed(KEY_C)) *screen = CREDITOS; // C para créditos
	if(IsKeyPressed(KEY_T)) *screen = TUTORIAL; // T para tutorial
	if(IsKeyPressed(KEY_Q)) *screen = CLOSE; // Q para sair do jogo
	// Future updates...
}


//================================================
// Controles de Jogo
//================================================
// Movimenta qualquer tipo de Vector2 tendo uma matriz como referência
void PlayerMovement(Vector2 *pos, int **map, float *dir, float *moveDelay, float currentDelay){
	// Basic Input movement vector
	Vector2 inputVector = { // This will result in: Dom(inputVector){1, 0, -1}
  	IsKeyDown(KEY_RIGHT) - IsKeyDown(KEY_LEFT), 
  	IsKeyDown(KEY_DOWN) - IsKeyDown(KEY_UP)
	};
	// Key Hold any
	if(IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_UP)){
		(*moveDelay)--;
	}
	if(inputVector.x == -1) { // Move left
		if(*moveDelay <= 0){
			if(CanMove(*pos, map, 1)) pos->x -= 16;
			if(*dir > 0) *dir *= -1;
			*moveDelay = currentDelay;
		}
	}
	else if(inputVector.x == 1) { // Move right
		if(*moveDelay <= 0){
			if(CanMove(*pos, map, 0)) pos->x += 16;
			if(*dir < 0) *dir *= -1;
			*moveDelay = currentDelay;
		}
	}
	else{ 
		// No horizontal movement
	}

	if(inputVector.y == -1){ // Move up
		if(*moveDelay <= 0){
			if(CanMove(*pos, map, 3)) pos->y -= 16;
			*moveDelay = currentDelay;
		}
	}
	else if(inputVector.y == 1) { // Move down
		if(*moveDelay <= 0){
			if(CanMove(*pos, map, 2)) pos->y += 16;
			*moveDelay = currentDelay;
		}
	}
	else {
			// No vertical movement
	}
}
