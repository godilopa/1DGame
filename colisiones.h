#ifndef  _COLISIONES_H_
#define _COLISIONES_H_

void ColisionRecargaJugador() {
	if (posicionRecarga - posicionJugador == 0) {
		Beep(14000, 100);
		hayRecarga = false;
		numBalas++;
	}
}

void ColisionTeleportJugador() {
	if (posicionTeleport - posicionJugador == 0) {
		Beep(100, 10);
		posicionTeleport = 300;
		teleportActivo = true;
	}
}

void ColisionEnemigoJugador() {
	if (abs(enemigoX - posicionJugador) <= 1) {
		Beep(8000, 200);
		enemigoX = inicioEnemigoX;
		existeEnemigo = false;
		vidas--;
	}
}

void ColisionBalaEnemigo() {
	for (unsigned int i = 0; i < municion.size(); i++) {
		if (abs(municion[i]->getPosicion() - enemigoX) <= 1) {
			Beep(4000, 100);
			existeEnemigo = false;
			//Eliminamos la bala chocada, esa posicion se apunta a null, luego se ocupa por la ultima bala y se elimina una bala
			delete municion[i];
			municion[i] = nullptr;
			municion[i] = municion.back();
			municion.pop_back();
			puntuacion++;
		}
	}
}

void ComprobarNivel(){
	if (puntuacion == 5) estadoLluvia = MODERADO;
	if (puntuacion == 10) estadoLluvia = FUERTE;
	if (puntuacion == 15) estadoLluvia = TORRENCIAL;
	if (puntuacion == 20) estadoLluvia = DEMENCIAL;
}

#endif 
