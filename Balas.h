#ifndef _BALAS_H_
#define _BALAS_H_

class Balas
{
public:
	Balas(int pos, int dir);
	~Balas();
	int getPosicion(){ return posicion; }
	void actualizarPosicion(){ posicion += direccion;}
private:
	int posicion;
	int direccion;
};

#endif
