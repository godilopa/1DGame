#ifndef _HIGH_SCORES_H_
#define _HIGH_SCORES_H_

#include <string>

struct marcador {
	int puntuacion;
	std::string nombre;
};

void AnadirPuntuacion(const int puntuacion, const std::string& nombre);
void ImprimirPuntuaciones();

#endif