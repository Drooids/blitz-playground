#include <math.h>
#include "Vector2D.h"

float Vector2D::length() {
	// sqrt returns dobule, let's cast it to float
	// it doesn't feel right, but let us see
	// FIX ME
	return (float)sqrt(m_x * m_x + m_y * m_y);
}

/*
Vector2D &operator+(Vector2D& v1, Vector2D& v2) {
	v1.m_x = v2.m_x;
	v1.m_y = v2.m_y;

	return v1;
}
*/
