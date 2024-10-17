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

	//linalg::Matrix matr = {1, 2, 3, 4, 5, 6};
	//double value = matr(5, 0);
	//std::cout << value << '\n';
	//matr(5, 0) = 8.0;
	//std::cout << matr(5, 0) << '\n'; //успешно изменится

	//const linalg::Matrix matr1 = { 1, 2, 3, 4, 5, 6 };
	//double value1 = matr1(4, 0);
	//std::cout << value1 << '\n';
	////matr1(4, 0) = 8.0; //произойдёт ошибка

	//const linalg::Matrix matr2 = { {1, 5, 8, 9}, {4, 8, 12, 16} };
	//double value2 = matr2(1, 0);
	//std::cout << value2 << '\n';

	///*linalg::Matrix m1;
	//m1 = matr2;
	//m1 = linalg::Matrix{ 1, 2, 3, 4, 5, 6 };*/
	
	/*linalg::Matrix mnew = { {1}, {2}, {3}, {4}, {5}, {6} };*/
	//std::cout << mnew(5, 0);

	linalg::Matrix M = { {1, 2, 4, 5}, {2, 4, 6, 8} };
	linalg::Matrix P = { {1, 333, 45, 89}, {-1, 7896, 5678, 1234}, {1234, 2345, 3456, 4567} };
	linalg::Matrix N = { {1, 2, 3, 4, 5}, {2, 4, 6, 8, 10}, {3, 6, 9, 12, 15}, {4, 8, 12, 16, 20}, {5, 10, 15, 20, 25} };
	linalg::Matrix Q = { {1, 333, 1, 1, 333}, {22, 1, 1, 333, 333}, {1, 1, 1, 333, 1}, {1, 22, 1, 22, 22} };
	linalg::Matrix R = {};

	std::cout << M << '\n';
	std::cout << P << '\n';
	std::cout << N << '\n';
	std::cout << Q << '\n';
	std::cout << R << '\n';
}