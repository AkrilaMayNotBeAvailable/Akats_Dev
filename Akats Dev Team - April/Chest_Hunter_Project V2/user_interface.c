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
					CenterTextHorizontal("Pressione ENTER para retornar", FONT_NORMAL_SIZE, T_LARG),
					BottomScreenText(T_ALT, fontSize, 0),
					fontSize,
					RED
				);
		}
	}
}
