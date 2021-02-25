#include <cstdio>

#include "Math/Vector.h"

using namespace std;

int main() {
	
	Vec2f v(2, 5);
	Vec2f z(1, 3);
	 
	printf("%d\n", v.dot(z));
 	
	return 0;
}