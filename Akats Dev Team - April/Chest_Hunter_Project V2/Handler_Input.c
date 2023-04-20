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
	if(IsKeyPressed(KEY_Q)) *screen = CLOSE; // Q para sair do jogo
	// Future updates...
}


//================================================
// Controles de Jogo
//================================================
