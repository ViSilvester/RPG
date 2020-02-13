#include "../../bibliotecas-pessoais/Janela.h"

#define MAP_SIZE 100

int main(int argc, char* argv[]) {
	
	Janela janela;
	janela.altura = 500;
	janela.largura = 1000;
	janela.Title = L"Sua aplicação";
	MSG mensagem;
	LARGE_INTEGER timeStart, Frequency;
	_int64 contador;
	double performance;
	char str[20];
	int rodando = 1, i, j;

	// variaveis do jogo
	int mapa[MAP_SIZE * MAP_SIZE] = {0};
	int tile_size = 20;
	Rect genRect;
	Texture tiles[100];



	StartWindow(*argv, argc, &janela);

	createTexture(&tiles[0], "grama.bmp");

	QueryPerformanceFrequency(&Frequency);



	while (rodando == 1) {
		QueryPerformanceCounter(&timeStart);

		contador = timeStart.QuadPart;
		if (PeekMessage(&mensagem, NULL, 0, 0, PM_REMOVE))
		{
			if (mensagem.message == WM_QUIT)
			{
				rodando = 0;
			}
			else
			{
				TranslateMessage(&mensagem);
				DispatchMessage(&mensagem);
			}
		}

		

		//render
		ClearScreen(0.5, 0.5, 1, 0);

		iniRect(&genRect, 0, 0, tile_size, tile_size);
		for (i = 0; i < MAP_SIZE; i++) {
			for (j = 0; j < MAP_SIZE; j++) {
				genRect.X = j * tile_size;
				genRect.Y = i * tile_size;



				if (mapa[j * MAP_SIZE + i] == 0) {
					drawTexture(tiles[0], &genRect, NULL);
				}
			}
		}



		RefreshBuffer(&janela.hDC);



		QueryPerformanceCounter(&timeStart);
		performance = (timeStart.QuadPart - contador);
		performance * 1000000;
		performance /= Frequency.QuadPart;
		performance = 1 / performance;

		sprintf_s(str, 20, "FPS:%f", performance);
		SetWindowTextA(janela.hwnd, str);
	}
}