
#include "renderer.h"
#include "gestorLluvia.h"
#include <cstdlib>

void PintarFondo() {
	PrintColorText("                                                           %%%%%%%%\n",VERDE);
	PrintColorText("                                                        %%%%%%%%%%%%%%""\n",VERDE);
	PrintColorText("                                                       %%%%%%%%%%%%%%%%\n", VERDE);
	PrintColorText("                                    .......", AMARILLO); PrintColorText("           %%%%%%%%%%%%%%%%%%\n",VERDE);
	PrintColorText("                                ..:::::::::::..",AMARILLO); PrintColorText("            %%%%%%%%\n",VERDE);
	PrintColorText("                              .:::::::::::::::::.", AMARILLO);  PrintColorText("             \\/ \n", GRIS);
	PrintColorText("                             :::::::::::::::::::::", AMARILLO); PrintColorText("            \\/ \n", GRIS);
	PrintColorText("                            :::::::::::::::::::::::", AMARILLO);PrintColorText("           \\/ \n", GRIS);
	PrintColorText("---____-----__---------_____----....-----..--......-----_____-",AZUL); PrintColorText("\\/",GRIS); PrintColorText("---_____---____\n",AZUL);
	PrintColorText("-----___---___----____--__--_.----...----...----..---__--_-___", AZUL); PrintColorText("\\/", GRIS); PrintColorText("---_____---____\n", AZUL);
	PrintColorText("--____----__-___-----____----_...-----..--..---..___-------___", AZUL); PrintColorText("\\/", GRIS); PrintColorText("---_____---____\n", AZUL);
	PrintColorText("___----____------____---__--___..--..-..----....___-----___---", AZUL); PrintColorText("\\/", GRIS); PrintColorText("---_____---____\n", AZUL);
	PrintColorText("---___--___--__---__----___---___..----------._---____-----___", AZUL); PrintColorText("\\/", GRIS); PrintColorText("---_____---____\n", AZUL);
	PrintColorText("--___---_-___-------______------___--___----___--__------___--", AZUL); PrintColorText("\\/", GRIS); PrintColorText("---_____---____\n", AZUL);
	//Ponemos el cursor 3 lineas mas abajo para pintar el terreno de juego
	for (int i = 0; i < 3; i++) {
		printf("\n");
	}
}

void PintarMundo() {
	for (unsigned short int i = 0; i < ANCHO-1; i++) {
		for (unsigned int j = 0; j < municion.size(); j++) {
			//La 2º condicion controla que no se pinte en la posicion ANCHO si el jugador esta en ANCHO - 1
			if (i == municion[j]->getPosicion() && municion[j]-> getPosicion() < ANCHO - 1) {
				SetColorText(ROJO);
				printf("%c", 14);
				DefaultColorText();
				i++;//aumenta para que siempre se pinten ANCHO-1 caracteres
			}
		} 
		if (i == posicionJugador) {
			printf("%c", 1);
		}
		else if (HayLluvia()) {
			SetColorText(CELESTE);
			printf("%c", FrameLluvia());
			DefaultColorText();
		}
		else if (i == posicionTeleport && pintarTeleport) {
			SetColorText(AMARILLO);
			printf("T", FrameLluvia());
			DefaultColorText();
		}
		else if (i == enemigoX && existeEnemigo) {
			SetColorText(MORADO);
			printf("%c", 2);
			DefaultColorText();
		}
		else if (i == posicionRecarga) {
			SetColorText(VERDE);
			printf("%c", 225);
			DefaultColorText();
		}
		else if (i < ANCHO -1) { //Este if controla el caso en que una bala se pinta en el ultimo lugar, para que no se pinte luego otra ralla
			SetColorText(ROJOF);
			printf("_");
			DefaultColorText();
		}	
	}

	//Actualizamos todas las balas
	for (unsigned int j = 0; j < municion.size(); j++) {
		municion[j]->actualizarPosicion();
	}
	ActualizarFrameLluvia();
}

void PintarMarcador() {
	Gotoxy(40, 20);
	printf("Marcador:");
	SetColorText(AMARILLO);
	printf("%d", puntuacion);
	DefaultColorText();
	if (teleportActivo) {
		printf("       ");
		SetColorText(AMARILLO);
		printf("TELEPORT");
		DefaultColorText();
	}
	else{
		printf("                           ");
	}
	Gotoxy(0, 17);
}

void PintarVida() {
	Gotoxy(10, 20);
	printf("Vidas: ");
	for (int i = 0; i < vidas; i++) {
		SetColorText(ROJO);
		printf("%c ", 3);
		DefaultColorText();
	}

	printf("  ");//Espacio para borrar una vida al volver a entrar
	Gotoxy(0, 17);
}

void PintarMunicion() {
	Gotoxy(10, 22);
	printf("Municion: ");
	for (int i = 0; i < numBalas; i++) {
		SetColorText(MORADO);
		printf("%c ", 225);
		DefaultColorText();
	}

	printf("  ");
	Gotoxy(0, 17);
}

void PrintColorText(char* cadena, Color color) {
	SetColorText(color);
	printf("%s", cadena);
	DefaultColorText();
}

void SetColorText(Color color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(color));
}

void DefaultColorText() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLANCO);
}

void Gotoxy(short int x, short int y) {
	COORD pos = { x, y };
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, pos);
}

void DrawGameOver() {
	system("cls");
	printf("\n");
	printf("%s", "                   ,----.       / . --. /  ,--.   ,--.)(,------.\n");    
	printf("%s", "                  '  .-./-')    | \\-.  \\   |   `.'   |  |  .---'\n");
	printf("%s", "                  |  |_( O- ) .-'-'  |  |  |         |  |  |    \n");
	printf("%s", "                  |  | .--, \\  \\| |_.'  |  |  |'.'|  | (|  '--. \n");
	printf("%s", "                 (|  | '. (_/   |  .-.  |  |  |   |  |  |  .--' \n");
	printf("%s", "                  |  '--'  |    |  | |  |  |  |   |  |  |  `---.\n");
	printf("%s", "                   `------'     `--' `--'  `--'   `--'  `------'\n\n");
	printf("%s", "              ,-----. ,--(_/   ,. \\(,------.  ,------.\n");
	printf("%s", "              '  .-.  '\\   \\   /(__/ |  .---'  |   /`. '\n");
	printf("%s", "              |  | |  | \\   \\ /   /  |  |      |  /  | |\n");
	printf("%s", "              |  | |  |  \\   '   /, (|  '--.   |  |_.' |\n");
	printf("%s", "              |  | |  |   \\     /__) |  .--'   |  .  '.'\n");
	printf("%s", "              '  '-'  '    \\   /     |  `---.  |  |\\  \\ \n");  
	printf("%s", "               `-----'      `-'      `------'  `--' '--'");
}