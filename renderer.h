#ifndef _RENDERER_H_
#define _RENDERER_H_

#pragma warning(disable:4668)
#pragma warning(disable:4820)

#include "juego.h"
#include <cstdio>
#include <conio.h>
#include <windows.h>

enum Color { ROJO = 0x04, ROJOF = 0x0C, AMARILLO = 0x06, VERDE = 0x02, BLANCO = 0x07, AZUL = 0x01, MORADO= 0x05, GRIS = 0x08, CELESTE = 0x0B };

void PintarFondo();
void PintarMundo();
void PintarMarcador();
void PintarVida();
void PintarMunicion();
void PrintColorText(char* cadena, Color color);
void SetColorText(Color color);
void DefaultColorText();
void Gotoxy(short int x, short int y);
void DrawGameOver();

#endif
