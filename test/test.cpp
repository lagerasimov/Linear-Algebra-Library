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
		std::cout << "Error: " << exc.what() << std::endl;
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

void test::testNonEqualOperator() {
	linalg::Matrix M1 = { {1, 2, 3, 4}, {5, 6, 7, 8} };
	linalg::Matrix M2 = { {0, 2, 5, 6}, {9, 1, 5, 8} };
	std::cout << "Matrix M1:\n" << M1 << std::endl;
	std::cout << "Matrix M2:\n" << M2 << std::endl;
	std::cout << "M1 == M2 ? - " << std::boolalpha << (M1 == M2) << std::endl;
}

void test::testPowerWithInvert() {
	linalg::Matrix A = { {11, 12, 13}, {17, 18, 15}, {19, 21, 88} };
	linalg::Matrix B = { {1, 2, 4}, {5, 9, 8}, {11, 17, 9} };

	std::cout << "Matrix A:\n" << A << std::endl;
	std::cout << "Matrix B:\n" << B << std::endl;

	std::cout << "\nA^0 = \n" << power(A, 0) << std::endl;
	std::cout << "(A^T)^(-1) = \n" << power(transpose(A), -1) << std::endl;
	std::cout << "(A^(-1))^T? = \n" << transpose(power(A, -1)) << std::endl;
	std::cout << "(A^T)^(-1) == (A^(-1))^T? -" << std::boolalpha << (power(transpose(A), -1) == transpose(power(A, -1))) << std::endl;

	std::cout << "\n(A*B)^(-1) = \n" << power(A * B, -1) << std::endl;
	std::cout << "B^(-1) * A^(-1) = \n" << power(B, -1) * power(A, -1) << std::endl;
	std::cout << "(A * B) ^ (-1) == B^(-1) * A^(-1)? - "<< std::boolalpha << (power(A * B, -1) == power(B, -1) * power(A, -1)) << std::endl;

	std::cout << "\n(A^(-1))^6 = \n" << power(power(A, -1), 6) << std::endl;
	std::cout << "(A^(-2))^3 = \n" << power(power(A, -2), 3) << std::endl;
	std::cout << "(A^(-1))^6 == (A^(-2))^3? - " << std::boolalpha << (power(power(A, -1), 6) == power(power(A, -2), 3)) << std::endl;
}

void test::testMatrixPlusNumber() {
	try {
		linalg::Matrix A = { 1, 2, 3, 4, 5 };
		std::cout << "Matrix A:\n" << A << std::endl;
		std::cout << "A + 5 = \n" << A + 5 << std::endl;
		std::cout << "A + 6 = \n" << A + 6 << std::endl;
	}
	catch (const std::exception& exc) {
		std::cout << "Error: " << exc.what() << std::endl;
	}
}

void test::testReshape() {
	try {
		linalg::Matrix S = { {1, 2}, {3, 4}, {5, 6}, {7, 8} };
		std::cout << "Matrix S:\n" << S << std::endl;
		S.reshape(1, 8);
		std::cout << "Reshaped matrix S (1*8):\n" << S << std::endl;
		std::cout << "Let's try to specify the size 5*4\n";
		S.reshape(5, 4);
	}
	catch (const std::exception& exc) {
		std::cout << "Error: " << exc.what() << std::endl;
	}
}