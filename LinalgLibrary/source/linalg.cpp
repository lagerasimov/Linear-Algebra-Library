#include <linalg.h>
#include <stdexcept>
#include <iostream>
#include <sstream>
//#include <string>
#include <iomanip> //для std::setw
#include <cmath>

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

linalg::Matrix& linalg::Matrix::operator=(const Matrix& obj) {
	if (this == &obj) {
		return *this;
	}
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

linalg::Matrix& linalg::Matrix::operator=(Matrix&& obj) noexcept{
	if (this == &obj) {
		return *this;
	}
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

size_t element_length(double a) {
	std::ostringstream out;
	out << a;
	std::string s = out.str();
	out.str("");
	return s.size();
}

size_t* widths(const linalg::Matrix& m) {
	size_t* widths = new size_t[m.columns()]();
	for (int j = 0; j < m.columns(); j++) { //пробегаемся по столбцам матрицы
		for (int i = 0; i < m.rows(); i++) {
			widths[j] = std::max(element_length(m(i, j)), widths[j]);
		}
	}
	return widths;
}

std::ostream& linalg::operator<<(std::ostream& potok, const linalg::Matrix& m) {
	size_t* sizes = widths(m);
	if (m.rows() == 0 || m.columns() == 0) {
		potok << "|empty|\n";
		return potok;
	}
	for (int i = 0; i < m.rows(); ++i) {
		potok << '|';
		potok << std::setw(sizes[0]) << m(i, 0);
		for (int j = 1; j < m.columns(); ++j) {
			potok << std::setw(sizes[j] + 1) << m(i, j);
		}
		potok << "|\n";
	}

	delete[] sizes;

	return potok;
}

linalg::Matrix linalg::Matrix::operator+(const Matrix& obj) const {
	if (m_rows != obj.m_rows || m_columns != obj.m_columns) {
		std::cout << "The sizes of the matrices don't match";
		exit(1);
	}

	Matrix new_matrix(m_rows, m_columns);
	for (int i = 0; i < m_rows; i++) {
		for (int j = 0; j < m_columns; j++) {
			new_matrix(i, j) = (*this)(i, j) + obj(i, j);
		}
	}
	return new_matrix;
}

linalg::Matrix& linalg::Matrix::operator+=(const Matrix& obj) {
	if (m_rows != obj.m_rows || m_columns != obj.m_columns) {
		std::cout << "The sizes of the matrices don't match";
		exit(1);
	}

	for (int i = 0; i < m_rows; i++) {
		for (int j = 0; j < m_columns; j++) {
			(*this)(i, j) += obj(i, j);
		}
	}
	return *this;
}

linalg::Matrix linalg::Matrix::operator-(const Matrix& obj) const {
	if (m_rows != obj.m_rows || m_columns != obj.m_columns) {
		std::cout << "The sizes of the matrices don't match";
		exit(1);
	}

	Matrix new_matrix(m_rows, m_columns);
	for (int i = 0; i < m_rows; i++) {
		for (int j = 0; j < m_columns; j++) {
			new_matrix(i, j) = (*this)(i, j) - obj(i, j);
		}
	}

	return new_matrix;

};

linalg::Matrix& linalg::Matrix::operator-=(const Matrix& obj) {
	if (m_rows != obj.m_rows || m_columns != obj.m_columns) {
		std::cout << "The sizes of the matrices don't match";
		exit(1);
	}

	for (int i = 0; i < m_rows; i++) {
		for (int j = 0; j < m_columns; j++) {
			(*this)(i, j) -= obj(i, j);
		}
	}
	return *this;
}

linalg::Matrix linalg::Matrix::operator*(const Matrix& obj) const {
	if (m_columns != obj.m_rows) {
		std::cout << "The number of columns of the first matrix must match the number of rows of the second matrix";
		exit(1);
	}

	linalg::Matrix new_matrix(m_rows, obj.m_columns);
	for (int i = 0; i < m_rows; i++) {
		for (int j = 0; j < obj.m_columns; j++) {
			new_matrix(i, j) = 0.0;
			for (int p = 0; p < m_columns; p++) {
				new_matrix(i, j) += (*this)(i, p) * obj(p, j);
			}
		}
	}
	return new_matrix;
}

linalg::Matrix linalg::Matrix::operator*(double ch) const {
	linalg::Matrix new_matrix(m_rows, m_columns);
	for (int i = 0; i < m_rows; i++) {
		for (int j = 0; j < m_columns; j++) {
			new_matrix(i, j) = (*this)(i, j) * ch;
		}
	}
	return new_matrix;
}

linalg::Matrix linalg::operator*(double ch, const Matrix& obj) {
	linalg::Matrix new_matrix(obj.rows(), obj.columns());
	for (int i = 0; i < obj.rows(); i++) {
		for (int j = 0; j < obj.columns(); j++) {
			new_matrix(i, j) = obj(i, j) * ch;
		}
	}
	return new_matrix;
};

linalg::Matrix& linalg::Matrix::operator*=(double ch){
	for (int i = 0; i < m_rows; i++) {
		for (int j = 0; j < m_columns; j++) {
			(*this)(i, j) = (*this)(i, j) * ch;
		}
	}
	return *this;
}

linalg::Matrix& linalg::Matrix::operator*=(const Matrix& obj) {
	if (m_columns != obj.m_rows) {
		std::cout << "The number of columns of the first matrix must match the number of rows of the second matrix";
		exit(1);
	}

	Matrix new_matrix = (*this) * obj;
	*this = std::move(new_matrix);
	return *this;
}

bool linalg::Matrix::operator==(const Matrix& obj) const {
	if (m_rows != obj.m_rows || m_columns != obj.m_columns) {
		return false;
	}
	for (int i = 0; i < m_rows; i++) {
		for (int j = 0; j < m_columns; j++) {
			if ((*this)(i, j) != obj(i, j)) {
				return false;
			}
		}
	}
	return true;
}

bool linalg::Matrix::operator!=(const Matrix& obj) const {
	return !(*this == obj);
}

double linalg::Matrix::norm() const{
	if ((*this).empty()) {
		std::cout << "Matrix is empty. So Frobenius norm can't be found";
		exit(1);
	}
	double norma2 = 0.0;
	for (int i = 0; i < m_rows; i++) {
		for (int j = 0; j < m_columns; j++) {
			norma2 += pow(abs((*this)(i, j)), 2);
		}
	}
	return sqrt(norma2);
}

double linalg::Matrix::trace() const {
	if (m_rows != m_columns) {
		std::cout << "The matrix must be square";
		exit(1);
	}
	double sled = 0.0;
	for (int i = 0; i < m_rows; i++) {
		sled += (*this)(i, i);
	}
	return sled;
}

double linalg::Matrix::det() const {
	if (m_rows != m_columns) {
		std::cout << "The matrix must be square";
		exit(1);
	}

	if (m_rows == 2) {
		return (*this)(0, 0) * (*this)(1, 1) - (*this)(1, 0) * (*this)(0, 1);
	}

	double d = 0;

	for (int j = 0; j < m_columns; j++) {
		linalg::Matrix obj(m_rows - 1, m_columns - 1); 
		for (int k = 0; k < obj.m_rows; k++) {
			for (int p = 0; p < obj.m_columns; p++) {
				if (p < j) {
					obj(k, p) = (*this)(k+1, p);
				}
				if (p >= j) {
					obj(k, p) = (*this)(k + 1, p + 1);
				}
			}
		}
		d += pow(-1, j) * (*this)(0, j) * obj.det();
	}
	return d;
}



                