#include <linalg.h>
#include <iostream>
#include <test.h>

int main() {
	//test::testDefaultConstructor();	
	//test::testOneParametrConstructor();
	/*test::testBadOneParametrConstructor();
	test::testBadTwoParametrsConstructor();*/
	//test::testMoveConstructor();
	//test::testTwoParametrsConstructor();
	//test::testCopyConstructor();
	//test::testEqualOperator();
	//

	linalg::Matrix A = { {2, 5, 4, 30}, {1, 3, 2, 150}, {2, 10, 9, 110} };
	std::cout << Kramer(A) << std::endl;

	linalg::Matrix B = { {506, 66, 2315.1}, {66, 11, 392.3} };
	std::cout << Kramer(B) << std::endl;
 
}
