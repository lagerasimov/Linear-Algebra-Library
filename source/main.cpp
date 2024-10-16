#include <linalg.h>
#include <iostream>

int main() {

	//linalg::Matrix m(4, 5); //создаём пустую матрицу m

	//std::cout << "The number of rows: " << m.rows() << '\n'; //выведем число строк
	//std::cout << "The number of columns: " << m.columns() << '\n'; //выведем число колонок

	//m.reshape(5, 4); //попробуем изменить размеры матрицы, не меняя количество аргументов

	//std::cout << "New number of rows: " << m.rows() << '\n'; //выведем новое число строк
	//std::cout << "New number of columns: " << m.columns() << '\n'; //выведем новое число колонок

	//std::cout << "Is the matrix empty? (1 - yes, 0 - no): " << m.empty(); //проверим, пуста ли матрица 

	//m.reshape(10, 9); //попробуем изменить размеры матрицы, меняя количество аргументов (вызовется исключение)

	linalg::Matrix matr = {1, 2, 3, 4, 5, 6};
	double value = matr(5, 0);
	std::cout << value << '\n';
	matr(5, 0) = 8.0;
	std::cout << matr(5, 0) << '\n'; //успешно изменится

	const linalg::Matrix matr1 = { 1, 2, 3, 4, 5, 6 };
	double value1 = matr1(4, 0);
	std::cout << value1 << '\n';
	//matr1(4, 0) = 8.0; //произойдёт ошибка

	const linalg::Matrix matr2 = { {1, 5, 8, 9}, {4, 8, 12, 16} };
	double value2 = matr2(1, 0);
	std::cout << value2 << '\n';

	linalg::Matrix m1;
	m1 = matr2;
	m1 = linalg::Matrix{ 1, 2, 3, 4, 5, 6 };

}