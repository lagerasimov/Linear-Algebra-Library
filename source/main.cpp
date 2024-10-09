#include <linalg.h>
#include <iostream>

int main() {

	linalg::Matrix m(4, 5); //создаём пустую матрицу m

	std::cout << "The number of rows: " << m.rows() << '\n'; //выведем число строк
	std::cout << "The number of columns: " << m.columns() << '\n'; //выведем число колонок

	m.reshape(5, 4); //попробуем изменить размеры матрицы, не меняя количество аргументов

	std::cout << "New number of rows: " << m.rows() << '\n'; //выведем новое число строк
	std::cout << "New number of columns: " << m.columns() << '\n'; //выведем новое число колонок

	std::cout << "Is the matrix empty? (1 - yes, 0 - no): " << m.empty(); //проверим, пуста ли матрица 

	m.reshape(10, 9); //попробуем изменить размеры матрицы, меняя количество аргументов (вызовется исключение)
}