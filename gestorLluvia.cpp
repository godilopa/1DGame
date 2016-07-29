#include "gestorLluvia.h"

int frameLluvia = 0;

char FrameLluvia() {
	if (frameLluvia == 0) {
		return '|';
	}

	if (frameLluvia == 1) {
		return '_';
	}

	if (frameLluvia == 2) {
		return '.';
	}
	return '\0';
}

bool HayLluvia() {
	if (estadoLluvia > rand() % ANCHO)
		return true;
	return false;
}

void ActualizarFrameLluvia() {
	if (frameLluvia > 2) {
		frameLluvia = 0;
	}
	else {
		frameLluvia++;
	}
}