#pragma once
#include <cstddef>
#include <iostream>

namespace linalg {
	class Matrix {
	public:
		Matrix(); //конструктор по умолчанию

		//конструкторы с параметрами
		Matrix(size_t rows, size_t columns);
		Matrix(size_t rows);

		Matrix(const Matrix& m);  //конструктор копирования lvalue-объекта		
		Matrix(Matrix&& m); //конструктор копирования rvalue-объекта

		//конструкторы с унифицированной инициализацией
		Matrix(std::initializer_list<double> a); 
		Matrix(std::initializer_list<std::initializer_list<double>> a);

		~Matrix(); //деструктор по умолчанию

		//операторы
		Matrix& operator=(const Matrix& obj); 
		Matrix& operator=(Matrix&& obj);
		double& operator() (size_t row, size_t column);
		const double& operator() (size_t row, size_t column) const;
			 
		
		size_t rows() const;
		size_t columns() const;
		bool empty() const;
		void reshape(size_t rows, size_t columns);

	private:
		double* m_ptr = nullptr;
		size_t m_rows = 0, m_columns = 0;
	};
}