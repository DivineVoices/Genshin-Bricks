#include "Decla_blocks.h"

//Gets Brick
int Brick::GetLife() {
	return m_life;
}
Vector2 Brick::GetDim() {
	return m_dimension;
}

//Gets Anemo_Brick
Vector2 Anemo_Brick::GetDir() {
	return m_direction;
}
float Anemo_Brick::GetVit() {
	return m_vitesse;
}

//Gets Pyro_Brick
Vector2 Pyro_Brick::GetRay() {
	return m_rayon;
}
int Pyro_Brick::GetDeg() {
	return m_degats;
}