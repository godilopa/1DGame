#ifndef _JUEGO_H_
#define _JUEGO_H_

#include "balas.h"
#include <vector>

#define inicioEnemigoX 500

enum EstadoLluvia { SECO = -1, MODERADO = 10, FUERTE = 30, TORRENCIAL = 50, DEMENCIAL = 80 };

static const int ANCHO = 80;
extern int posicionJugador;
extern int puntuacion;
extern int enemigoX;
extern bool existeEnemigo;
extern int vidas;
extern int numBalas;
extern int posicionRecarga;
extern bool hayRecarga;
extern bool pintarTeleport;
extern int posicionTeleport;
extern bool teleportActivo;
extern std::vector<Balas*> municion;
extern EstadoLluvia estadoLluvia;

#endif
