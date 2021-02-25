#include <iostream>

#include "Math/Vector.h"
#include "Math/Matrix.h"

int main() {

	Mat4f mat = perspective(90, 1920, 1080, 0.1f, 100);
	mat.scale(10);

	std::cout << mat.toString();

	return 0;
}