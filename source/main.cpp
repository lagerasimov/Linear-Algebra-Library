#include <linalg.h>
#include <iostream>

int main() {

	linalg::Matrix m(4, 5); //������ ������ ������� m

	std::cout << "The number of rows: " << m.rows() << '\n'; //������� ����� �����
	std::cout << "The number of columns: " << m.columns() << '\n'; //������� ����� �������

	m.reshape(5, 4); //��������� �������� ������� �������, �� ����� ���������� ����������

	std::cout << "New number of rows: " << m.rows() << '\n'; //������� ����� ����� �����
	std::cout << "New number of columns: " << m.columns() << '\n'; //������� ����� ����� �������

	std::cout << "Is the matrix empty? (1 - yes, 0 - no): " << m.empty(); //��������, ����� �� ������� 

	m.reshape(10, 9); //��������� �������� ������� �������, ����� ���������� ���������� (��������� ����������)
}