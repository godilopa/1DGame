
#include "renderer.h"
#include "highScores.h"
#include "colisiones.h"
#include <stdlib.h>
#include <ctime>
#include <iostream>

//Declaramos las variables globales
int posicionJugador;
int puntuacion;
int enemigoX;
bool existeEnemigo;
int vidas;
int numBalas;
int posicionRecarga;
bool hayRecarga;
bool teleportActivo;
int posicionTeleport;
bool pintarTeleport;
std::vector<Balas*> municion;
EstadoLluvia estadoLluvia;

//Protipo de las funciones
void CheckFinalJuego();
void IniciarVariables();

int main() {

	PintarFondo();
	IniciarVariables();

	//Bucle del juego
	while (vidas) {

		//Si pulsamos una tecla pasamos a realizar la accion dependiendo de cual se trate
		if (_kbhit()) {
			char tecla = (char)_getch();
			if (tecla == 'o' && posicionJugador > 0) { // si es o el jugador se mueve a la izquierda siempre que no revasemos el limite de la pantalla 
				posicionJugador--;
			}

			if (tecla == 'p' && posicionJugador < ANCHO - 1) { // si es p el jugador se mueve a la derecha siempre que no revasemos el limite de la pantalla 
				posicionJugador++;
			}

			if (tecla == 't' && teleportActivo) { // si pulsamos t el jugador se traslada 20 puntos a la derecha controlando que no se salga de la pantalla
				posicionJugador += 20;
				if (posicionJugador > ANCHO - 1) {
					posicionJugador = ANCHO - 1;
				}
				teleportActivo = false;
				pintarTeleport = false; //cuando usas el teleport se activa el que vuelv a aparecer
			}

			if (tecla == 'q' && numBalas) { // si es q la bala comienza en la posicion del jugador a la izquierda, y si esa posicion no es -1 no podemos volver a lanzar otra
				Beep(1000, 100);
				Balas* bala = new Balas(posicionJugador - 1, -1);
				municion.push_back(bala);
				numBalas--;
			}

			if (tecla == 'w' && numBalas) { // si es w la bala activamos la bala y comienza a la derecha de la posicion del jugador
				Beep(1000, 100);
				Balas* bala = new Balas(posicionJugador + 1, 1);
				municion.push_back(bala);
				numBalas--;
			}
		}

		//Inicializamos la semilla para el random
		srand(static_cast<unsigned int>(time(0)));

		//Aparicion del enemigo
		int random = rand() % 2;
		if (random == 1 && !existeEnemigo) {
			enemigoX = 0;
			existeEnemigo = true;
		}

		if (random == 0 && !existeEnemigo) {
			enemigoX = ANCHO - 1;
			existeEnemigo = true;
		}

		//Colisiones
		ColisionRecargaJugador();
		ColisionTeleportJugador();
		ColisionEnemigoJugador();
		ColisionBalaEnemigo();

		//Si la puntuacion alcanza una cifra determinada subimos la dificultad aumentando la lluvia
		ComprobarNivel();

		//Borramos las balas si se salen del ancho de la pantalla
		for (unsigned int i = 0; i < municion.size(); i++) {
			if (municion[i]->getPosicion() < 0 || municion[i]->getPosicion() > ANCHO - 1) {
				//Borramos la bala que cumple la condicion, guardamos en su posicion la ultima y eliminamos del vector la ultima posicion
				delete municion[i];
				municion[i] = nullptr;
				municion[i] = municion.back();
				municion.pop_back();
			}
		}

		//Para controlar el movimiento del enemigo a derecha o izquierda
		if (existeEnemigo && enemigoX > posicionJugador) {
			enemigoX--;
		}
		else {
			enemigoX++;
		}

		//Antes de pintar el mundo calculamos la posicion de la recarga y el teleport
		if (!hayRecarga) {
			posicionRecarga = (rand() % (ANCHO - 10)) + 5;
			hayRecarga = true;
		}

		if (!pintarTeleport && (rand()%100) < 2) { //Probabilidad de 1/50 de que salga el teleport
			posicionTeleport = rand() % (ANCHO - 10) + 5;
			pintarTeleport = true;
		}

		PintarMundo();
		PintarMarcador();
		PintarVida();
		PintarMunicion();

		printf("\r");//Colocar el cursor al principio 
		Sleep(100);
		CheckFinalJuego();
	}
	return 0;
}

void IniciarVariables() {
	PlaySound(TEXT("Macaron.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	posicionJugador = 10;
	puntuacion = 0;
	enemigoX = inicioEnemigoX;
	existeEnemigo = false;
	vidas = 3;
	numBalas = 10;
	hayRecarga = false;
	posicionTeleport = 300;
	teleportActivo = false;
	pintarTeleport = false;
	posicionRecarga = 300;
	std::vector<Balas*> municion = {};
	estadoLluvia = SECO;
}

void CheckFinalJuego() {
	if (!vidas){
		PlaySound(NULL, NULL, NULL);
		DrawGameOver();
		printf("\nTu nombre ?");
		std::string nombre;
		std::getline(std::cin,nombre);
		AnadirPuntuacion(puntuacion, nombre);
		ImprimirPuntuaciones();
		char decision;
		printf("\nVolver a jugar? s/n: ");
		std::cin >> decision;
		getchar();
		switch (decision){
		case 's':
			//Inicializamos de nuevo las variables, borramos y pintamos de nuevo el fondo
			IniciarVariables();
			system("cls");
			PintarFondo();
			break;
		case 'n':
			exit(1);
			break;
		}
	}
}



