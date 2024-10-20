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
		Matrix(Matrix&& m) noexcept; //конструктор копирования rvalue-объекта

		//конструкторы с унифицированной инициализацией
		Matrix(std::initializer_list<double> a); 
		Matrix(std::initializer_list<std::initializer_list<double>> a);

		~Matrix(); //деструктор по умолчанию

		//операторы
		Matrix& operator=(const Matrix& obj); 
		Matrix& operator=(Matrix&& obj) noexcept;
		double& operator() (size_t row, size_t column);
		const double& operator() (size_t row, size_t column) const;

		Matrix operator+(const Matrix& obj) const;
		Matrix& operator+=(const Matrix& obj);
		Matrix operator-(const Matrix& obj) const;
		Matrix& operator-=(const Matrix& obj);
		Matrix operator*(const Matrix& obj) const;
		Matrix operator*(double ch) const;
		Matrix& operator*=(const Matrix& obj);
		Matrix& operator*=(double ch);
		bool operator==(const Matrix& obj) const;
		bool operator!=(const Matrix& obj) const;
			 		
		size_t rows() const;
		size_t columns() const;
		bool empty() const;
		void reshape(size_t rows, size_t columns);

		double norm() const;
		double trace() const;
		double det() const;

		Matrix Minor(size_t row, size_t column) const;

	private:
		double* m_ptr = nullptr;
		size_t m_rows = 0, m_columns = 0;
	};
	Matrix concatenate(const Matrix& left, const Matrix& right);
	Matrix transpose(const Matrix& obj);
	Matrix invert(const Matrix& obj);
	Matrix power(const Matrix& obj, size_t a);
	std::ostream& operator<<(std::ostream& potok, const Matrix& m);
	Matrix operator*(double ch, const Matrix& obj);
}
