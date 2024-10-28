#pragma once
#include <iostream>
#include <sstream>
#include <string>

struct Vector2 {
	float m_x, m_y;
	Vector2(float x = 0, float y = 0) : m_x(x), m_y(y) {}

	Vector2 operator+(const Vector2* i) {
		return Vector2(m_x + i->m_x, m_y + i->m_y);
	}
	Vector2 operator-(const Vector2* i) {
		return Vector2(m_x - i->m_x, m_y - i->m_y);
	}
	Vector2 operator*(const Vector2* i) {
		return Vector2(m_x * i->m_x, m_y * i->m_y);
	}
	Vector2 operator*(const float i) {
		return Vector2(m_x * i, m_y * i);
	}
};