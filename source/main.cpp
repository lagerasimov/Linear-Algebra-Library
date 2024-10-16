#include <linalg.h>
#include <iostream>

int main() {

	//linalg::Matrix m(4, 5); //������ ������ ������� m

	//std::cout << "The number of rows: " << m.rows() << '\n'; //������� ����� �����
	//std::cout << "The number of columns: " << m.columns() << '\n'; //������� ����� �������

	//m.reshape(5, 4); //��������� �������� ������� �������, �� ����� ���������� ����������

	//std::cout << "New number of rows: " << m.rows() << '\n'; //������� ����� ����� �����
	//std::cout << "New number of columns: " << m.columns() << '\n'; //������� ����� ����� �������

	//std::cout << "Is the matrix empty? (1 - yes, 0 - no): " << m.empty(); //��������, ����� �� ������� 

	//m.reshape(10, 9); //��������� �������� ������� �������, ����� ���������� ���������� (��������� ����������)

	linalg::Matrix matr = {1, 2, 3, 4, 5, 6};
	double value = matr(5, 0);
	std::cout << value << '\n';
	matr(5, 0) = 8.0;
	std::cout << matr(5, 0) << '\n'; //������� ���������

	const linalg::Matrix matr1 = { 1, 2, 3, 4, 5, 6 };
	double value1 = matr1(4, 0);
	std::cout << value1 << '\n';
	//matr1(4, 0) = 8.0; //��������� ������

	const linalg::Matrix matr2 = { {1, 5, 8, 9}, {4, 8, 12, 16} };
	double value2 = matr2(1, 0);
	std::cout << value2 << '\n';

	linalg::Matrix m1;
	m1 = matr2;
	m1 = linalg::Matrix{ 1, 2, 3, 4, 5, 6 };

}