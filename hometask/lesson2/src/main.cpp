#include <iostream>
#include "../src/box2d.hpp"
#include "../src/ray2d.hpp"

int main() {
	Box2D b11(1, 1, 4, 2);
	Box2D b12(2, 0, 3, 3);

	Box2D b21(5, 1, 7, 2);
	Box2D b22(6, 2, 7, 5);

	Box2D b31(8, 1, 10, 3);
	Box2D b32(9, 0, 11, 2);

	Box2D b41(1, 4, 4, 7);
	Box2D b42(2, 5, 3, 6);

	std::cout << b11 << std::endl;
	std::cout << b11.IntersectBox(b12) << std::endl;
	std::cout << b21.IntersectBox(b22) << std::endl;
	std::cout << b31.IntersectBox(b32) << std::endl;
	std::cout << b41.IntersectBox(b42) << std::endl;

	Ray2D r1(3, 1, 40);

	std::cout << r1 << std::endl;
	std::cout << r1.IntersectBox(b22) << std::endl;

	return 0;
}