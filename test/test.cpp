#include <linalg.h>
#include <test.h>
#include <iostream>

void test::testDefaultConstructor(){
	linalg::Matrix m0;
	std::cout << "The matrix created by default constructor:\n" << m0 << std::endl;
	std::cout << "The number of rows: " << m0.rows() << std::endl;
	std::cout << "The number of columns: " << m0.columns() << std::endl;
	std::cout << "Is the matrix empty? - " << std::boolalpha << m0.empty() << std::endl;
}

void test::testOneParametrConstructor() {
	try {
		linalg::Matrix m1(4);
		std::cout << "The matrix created by constructor with one parametr:\n" << m1 << std::endl;
		std::cout << "The number of rows: " << m1.rows() << std::endl;
		std::cout << "The number of columns: " << m1.columns() << std::endl;
		std::cout << "Is the matrix empty? - " << std::boolalpha << m1.empty() << std::endl;
	}
	catch (const std::exception& exc) {
		std::cout << "Error in the test: " << exc.what() << std::endl;
	}
};

void test::testBadOneParametrConstructor() {
	try {
		linalg::Matrix m1(0);
		std::cout << "The matrix created by constructor with one parametr:\n" << m1 << std::endl;
		std::cout << "The number of rows: " << m1.rows() << std::endl;
		std::cout << "The number of columns: " << m1.columns() << std::endl;
		std::cout << "Is the matrix empty? - " << std::boolalpha << m1.empty() << std::endl;
	}
	catch (const std::exception& exc) {
		std::cout << "Error: " << exc.what() << std::endl;
	}
}

void test::testTwoParametrsConstructor() {
	linalg::Matrix m2(4, 6);
	std::cout << "The matrix created by constructor with two parametrs:\n" << m2 << std::endl;
	std::cout << "The number of rows: " << m2.rows() << std::endl;
	std::cout << "The number of columns: " << m2.columns() << std::endl;
	std::cout << "Is the matrix empty? - " << std::boolalpha << m2.empty() << std::endl;
};

void test::testBadTwoParametrsConstructor() {
	try {
		linalg::Matrix m2(-1, 6);
		std::cout << "The matrix created by constructor with two parametrs:\n" << m2 << std::endl;
		std::cout << "The number of rows: " << m2.rows() << std::endl;
		std::cout << "The number of columns: " << m2.columns() << std::endl;
		std::cout << "Is the matrix empty? - " << std::boolalpha << m2.empty() << std::endl;
	}
	catch (const std::exception& exc){
		std::cout << "Error: " << exc.what() << std::endl;
	}
}

void test::testCopyConstructor() {
	linalg::Matrix m;
	linalg::Matrix m3(m);
	std::cout << "Copying default matrix m to m3:" << std::endl;
	std::cout << "The matrix m3: " << m3 << std::endl;
}

void test::testBadCopyConstructor() {
	try {
		linalg::Matrix m;
		linalg::Matrix m3(m);
		std::cout << "Copying default matrix m to m3:" << std::endl;
		std::cout << "The matrix m3: " << m3 << std::endl;
	}
	catch (const std::exception& exc) {
		std::cout << "Error:" << exc.what() << std::endl;
	}
}

void test::testMoveConstructor() {
	linalg::Matrix m4(2, 6);
	linalg::Matrix m5(std::move(m4));
	std::cout << "The constructor have successfully worked";
}

void test::testEqualOperator() {
	linalg::Matrix M = { {7.7, 7.7, 7.7, 7.7}, {7.7, 7.7, 7.7, 7.7} };
	linalg::Matrix M1 = { {1.1, 1.1, 1.1, 1.1 }, {1.1, 1.1, 1.1, 1.1 } };
	std::cout << "M*7 == M1? - " << std::boolalpha << (7.0 * M1 == M) << std::endl;
}


