#include <linalg.h>
#include <stdexcept>
#include <iostream>
#include <sstream>
//#include <string>
#include <iomanip> //для std::setw

size_t linalg::Matrix::rows() const {
	return m_rows;
}

size_t linalg::Matrix::columns() const{
	return m_columns;
}

bool linalg::Matrix::empty() const {
	return (m_rows == 0 || m_columns == 0);
}

void linalg::Matrix::reshape(size_t rows, size_t columns) {
	if (rows * columns == m_rows * m_columns) {
		m_rows = rows;
		m_columns = columns;
	}
	else {
		throw std::runtime_error("The number of elements shouldn't be changed");
	}

}

linalg::Matrix::Matrix() {

}

linalg::Matrix::Matrix(size_t rows, size_t columns) {
	m_rows = rows;
	m_columns = columns;
	m_ptr = new double[m_rows * m_columns]();
}

linalg::Matrix::Matrix(size_t rows) {
	m_rows = rows;
	m_columns = 1;
}

linalg::Matrix::~Matrix(){
	delete[] m_ptr;
}

linalg::Matrix::Matrix(const Matrix& m) {
	m_rows = m.m_rows;
	m_columns = m.m_columns;
	m_ptr = new double[m_rows * m_columns];
	std::copy(m.m_ptr, m.m_ptr + m_rows * m_columns, m_ptr);
}

linalg::Matrix::Matrix(Matrix&& m) noexcept{
	m_rows = m.m_rows;
	m_columns = m.m_columns;
	m_ptr = m.m_ptr;

	m.m_rows = 0;
	m.m_columns = 0;
	m.m_ptr = nullptr;
}


linalg::Matrix::Matrix(std::initializer_list<double> a) {
	if (a.size() == 0) {
		std::cout << "The matrix can't be empty";
		exit(1);
	}

	m_columns = 1;
	m_rows = a.size();
	m_ptr = new double[m_rows * m_columns];
	std::copy(a.begin(), a.end(), m_ptr);
}

linalg::Matrix::Matrix(std::initializer_list<std::initializer_list<double>> a) {
	if (a.size() == 0) {
		m_rows = 0;
		m_columns = 0;
		return;
	}
	
	m_rows = a.size();
	m_columns = a.begin()->size();
	
	for (const auto& el : a) {
		if (el.size() != m_columns) {
			std::cout << "The rows of matrix must have the equal size";
			exit(1);
		}
	}

	m_ptr = new double[m_rows * m_columns];
	double* p = m_ptr;
	for (const auto& el : a) {
		std::copy(el.begin(), el.end(), p);
		p += m_columns;
	}

}

linalg::Matrix& linalg::Matrix::operator=(const linalg::Matrix& obj) {
	if (m_rows != obj.m_rows || m_columns != obj.m_columns) {
		delete[] m_ptr;
		m_rows = obj.m_rows;
		m_columns = obj.m_columns;
		m_ptr = new double[m_rows * m_columns];
	}
	for (int i = 0; i < m_rows * m_columns; i++) {
		m_ptr[i] = obj.m_ptr[i];
	}
	return *this;
}

linalg::Matrix& linalg::Matrix::operator=(linalg::Matrix&& obj) noexcept{
	if (m_rows != obj.m_rows || m_columns != obj.m_columns) {
		delete[] m_ptr;
		m_rows = obj.m_rows;
		m_columns = obj.m_columns;
		m_ptr = new double[m_rows * m_columns];
	}
	for (int i = 0; i < m_rows * m_columns; i++) {
		m_ptr[i] = obj.m_ptr[i];
	}

	obj.m_ptr = nullptr;
	obj.m_rows = 0;
	obj.m_columns = 0;

	return *this;
}

double& linalg::Matrix::operator() (size_t row, size_t column) {
	if (row >= m_rows || column >= m_columns) {
		std::cout << "The indexes can't go beyond the size of the matrix";
		exit(1);
	}
	return m_ptr[row * m_columns + column];
}

const double& linalg::Matrix::operator() (size_t row, size_t column) const {
	if (row >= m_rows || column >= m_columns) {
		std::cout << "The indexes can't go beyond the size of the matrix";
		exit(1);
	}
	return m_ptr[row * m_columns + column];
}

int element_length(double a) {
	std::ostringstream out;
	out << a;
	std::string s = out.str();
	return s.length();
}

int* widths(const linalg::Matrix& m) {
	int* widths = new int[m.columns()]();
	for (int j = 0; j < m.columns(); j++) { //пробегаемся по столбцам матрицы
		for (int i = 0; i < m.rows(); i++) {
			if (element_length(m(i, j)) > widths[j]){
				widths[j] = element_length(m(i, j));
			}
		}
	}
	return widths;
}

std::ostream& operator<<(std::ostream& potok, const linalg::Matrix& m) {
	int* sizes = widths(m);
	if (m.rows() == 0 || m.columns() == 0) {
		potok << "The matrix is empty";
		return potok;
	}
	for (int i = 0; i < m.rows(); ++i) {
		potok << '|';
		for (int j = 0; j < m.columns(); ++j) {
			if (j == 0) {
				potok << std::setw(sizes[j]) << m(i, j);
			}
			else {
				potok << std::setw(sizes[j] + 1) << m(i, j);
			}
		}
		potok << "|\n";
	}

	delete[] sizes;

	return potok;
}

