// @AkrilaMayNotBeAvailable - Akats Dev Team, Leader Dev
/* Esse código foi feito com objetivos didáticos.
* É estritamente proíbida a venda deste código.
*/
// RRes packager defines must come before include header_manager
#define RRES_IMPLEMENTATION
#define RRES_RAYLIB_IMPLEMENTATION

#include "header_manager.h"
#include "function_declaration.h"

// Carrega Imagem de arquivo rres e atribui para uma Textura
void CarregaImagemRRes(char *nomeArq, int id, Texture2D *texture){
	//  Carrega dados do arquivo rres
	rresResourceChunk chunk = rresLoadResourceChunk(nomeArq, id);
	
	// Descompacta chunck retorna sucesso ou erro
	int loadResult = UnpackResourceChunk(&chunk); 
	
	if(loadResult == RRES_SUCCESS){
    // Carrega imagem da chunk encontrada
    Image image = LoadImageFromResource(chunk);
    *texture = LoadTextureFromImage(image);
    UnloadImage(image);
  }
   
  // Descarrega dados dados do arquivo rres 
  rresUnloadResourceChunk(chunk);
}

// Cria MusicStream a partir de dados brutos de um arquivo .mp3
void CarregaAudioRawData(char *nomeArq, int id, void *dados, Music *music){
	//  Carrega dados do arquivo rres
	rresResourceChunk chunkBgm = rresLoadResourceChunk(nomeArq, id);
	
	// Tamanho dos dados carregados
	int dataSize = 0;
	dados = LoadDataFromResource(chunkBgm, &dataSize); // Atribuição de tamanho
	
	// Atribuição da música no formato MP3 (IMPORTANTE)
	*music = LoadMusicStreamFromMemory(".mp3", (unsigned char*)dados, dataSize);

	// Descarrega dados dados do arquivo rres
	rresUnloadResourceChunk(chunkBgm);
}
