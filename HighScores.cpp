#include "highScores.h"
#include <list>

std::list<marcador> puntuaciones;
std::list<marcador>::const_iterator it;

bool comparacion(const marcador& marcador1, const marcador& marcador2) {
	return (marcador1.puntuacion > marcador2.puntuacion);
}

void AnadirPuntuacion(const int puntuacion, const std::string& nombre) {
	marcador marcador;
	marcador.nombre = nombre;
	marcador.puntuacion = puntuacion;
	puntuaciones.push_back(marcador);
}

void ImprimirPuntuaciones() {
	printf("Las mejores puntuaciones son: \n\n");
	if (puntuaciones.size() > 1){
		puntuaciones.sort(comparacion);
	}

	int i = 1;
	for(it = puntuaciones.begin(); it != puntuaciones.end(); it++) {
		printf("%d. %s: %d \n",i, it->nombre.c_str(), it->puntuacion);
		i++;
	}
}
