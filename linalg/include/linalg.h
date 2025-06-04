#pragma once
#include <cstddef> //size_t
#include <ostream> //<<
#include <initializer_list> 

namespace linalg {
	class Matrix {
	public:
		Matrix() noexcept; //конструктор по умолчанию

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

		Matrix& operator+=(const Matrix& obj);
		Matrix& operator-=(const Matrix& obj);
		Matrix& operator*=(const Matrix& obj);
		Matrix& operator*=(double ch) noexcept;
		
		//основные методы
		size_t rows() const noexcept;
		size_t columns() const noexcept;
		bool empty() const noexcept;
		void reshape(size_t rows, size_t columns);
		int rank() const;

		//дополнительные методы
		double norm() const;
		double trace() const;
		double det() const;
		double minor(size_t row, size_t column) const;

	private:
		double* m_ptr = nullptr;
		size_t m_rows = 0, m_columns = 0;
	};
	//основные функции
	Matrix concatenate(const Matrix& left, const Matrix& right);
	Matrix transpose(const Matrix& obj);
	Matrix invert(const Matrix& obj);
	Matrix power(const Matrix& obj, int a);

	//метод Крамера
	Matrix Kramer(const Matrix& obj);

	//основные операторы
	Matrix operator-(const Matrix& left, const Matrix& right);
	Matrix operator+(const Matrix& left, const Matrix& right);
	Matrix operator*(const Matrix& left, const Matrix& right);
	Matrix operator*(const Matrix& obj, double ch) noexcept;
	Matrix operator*(double ch, const Matrix& obj) noexcept;
	bool operator==(const Matrix& left, const Matrix& right) noexcept;
	bool operator!=(const Matrix& left, const Matrix& right) noexcept;

	//оператор вывода
	std::ostream& operator<<(std::ostream& potok, const Matrix& m) noexcept;
}
