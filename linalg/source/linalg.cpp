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
	if (rows <= 0 || columns <= 0) {
		throw std::runtime_error("Matrix dimensions must be greater than zero");
	}
	m_rows = rows;
	m_columns = columns;
	m_ptr = new double[m_rows * m_columns]();
}

linalg::Matrix::Matrix(size_t rows) {
	if (rows <= 0) {
		throw std::runtime_error("Matrix dimensions must be greater than zero");
	}
	m_rows = rows;
	m_columns = 1;
	m_ptr = new double[m_rows]();
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
		throw std::runtime_error("The matrix can't be empty");
	}

	m_columns = 1;
	m_rows = a.size();
	m_ptr = new double[m_rows * m_columns];
	std::copy(a.begin(), a.end(), m_ptr);
}

linalg::Matrix::Matrix(std::initializer_list<std::initializer_list<double>> a) {
	if (a.size() == 0) {
		throw std::runtime_error("The matrix can't be empty");
	}
	
	m_rows = a.size();
	m_columns = a.begin()->size();
	
	for (const auto& el : a) {
		if (el.size() != m_columns) {
			throw std::runtime_error("The rows of matrix must have the equal size");
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
		throw std::out_of_range("The indexes can't go beyond the size of the matrix");
	}
	return m_ptr[row * m_columns + column];
}

const double& linalg::Matrix::operator() (size_t row, size_t column) const {
	if (row >= m_rows || column >= m_columns) {
		throw std::out_of_range("The indexes can't go beyond the size of the matrix");
	}
	return m_ptr[row * m_columns + column];
}

size_t* widths(const linalg::Matrix& m) {
	std::ostringstream out;
	size_t* widths = new size_t[m.columns()];
	for (size_t j = 0; j < m.columns(); j++) {
		widths[j] = 0;
	}
	for (size_t j = 0; j < m.columns(); j++) {
		for (size_t i = 0; i < m.rows(); i++) {
			out << m(i, j);
			widths[j] = std::max(out.str().size(), widths[j]);
			out.str("");
		}
	}
	return widths;
}

std::ostream& linalg::operator<<(std::ostream& potok, const linalg::Matrix& m) {
	size_t* sizes = widths(m);
	if (m.empty()) {
		potok << "|empty|\n";
		return potok;
	}
	for (size_t i = 0; i < m.rows(); ++i) {
		potok << '|';
		potok << std::setw(sizes[0]) << m(i, 0);
		for (size_t j = 1; j < m.columns(); ++j) {
			potok << std::setw(sizes[j] + 1) << m(i, j);
		}
		potok << "|\n";
	}

	delete[] sizes;

	return potok;
}

linalg::Matrix linalg::Matrix::operator+(const Matrix& obj) const {
	if (m_rows != obj.m_rows || m_columns != obj.m_columns) {
		throw std::runtime_error("The sizes of the matrices don't match");
	}

	Matrix new_matrix(m_rows, m_columns);
	for (size_t i = 0; i < m_rows; i++) {
		for (size_t j = 0; j < m_columns; j++) {
			new_matrix(i, j) = (*this)(i, j) + obj(i, j);
		}
	}
	return new_matrix;
}

linalg::Matrix& linalg::Matrix::operator+=(const Matrix& obj) {
	if (m_rows != obj.m_rows || m_columns != obj.m_columns) {
		throw std::runtime_error("The sizes of the matrices don't match");
		exit(1);
	}

	for (size_t i = 0; i < m_rows; i++) {
		for (size_t j = 0; j < m_columns; j++) {
			(*this)(i, j) += obj(i, j);
		}
	}
	return *this;
}

linalg::Matrix linalg::Matrix::operator-(const Matrix& obj) const {
	if (m_rows != obj.m_rows || m_columns != obj.m_columns) {
		throw std::runtime_error("The sizes of the matrices don't match");
	}

	Matrix new_matrix(m_rows, m_columns);
	for (size_t i = 0; i < m_rows; i++) {
		for (size_t j = 0; j < m_columns; j++) {
			new_matrix(i, j) = (*this)(i, j) - obj(i, j);
		}
	}

	return new_matrix;

};

linalg::Matrix& linalg::Matrix::operator-=(const Matrix& obj) {
	if (m_rows != obj.m_rows || m_columns != obj.m_columns) {
		throw std::runtime_error("The sizes of the matrices don't match");
	}

	for (size_t i = 0; i < m_rows; i++) {
		for (size_t j = 0; j < m_columns; j++) {
			(*this)(i, j) -= obj(i, j);
		}
	}
	return *this;
}

linalg::Matrix linalg::Matrix::operator*(const Matrix& obj) const {
	if (m_columns != obj.m_rows) {
		throw std::runtime_error("The number of columns of the first matrix must match the number of rows of the second matrix");
	}

	linalg::Matrix new_matrix(m_rows, obj.m_columns);
	for (size_t i = 0; i < m_rows; i++) {
		for (size_t j = 0; j < obj.m_columns; j++) {
			new_matrix(i, j) = 0.0;
			for (size_t p = 0; p < m_columns; p++) {
				new_matrix(i, j) += (*this)(i, p) * obj(p, j);
			}
		}
	}
	return new_matrix;
}

linalg::Matrix linalg::Matrix::operator*(double ch) const {
	linalg::Matrix new_matrix(m_rows, m_columns);
	for (size_t i = 0; i < m_rows; i++) {
		for (size_t j = 0; j < m_columns; j++) {
			new_matrix(i, j) = (*this)(i, j) * ch;
		}
	}
	return new_matrix;
}

linalg::Matrix linalg::operator*(double ch, const Matrix& obj) {
	linalg::Matrix new_matrix(obj.rows(), obj.columns());
	for (size_t i = 0; i < obj.rows(); i++) {
		for (size_t j = 0; j < obj.columns(); j++) {
			new_matrix(i, j) = obj(i, j) * ch;
		}
	}
	return new_matrix;
};

linalg::Matrix& linalg::Matrix::operator*=(double ch){
	for (size_t i = 0; i < m_rows; i++) {
		for (size_t j = 0; j < m_columns; j++) {
			(*this)(i, j) = (*this)(i, j) * ch;
		}
	}
	return *this;
}

linalg::Matrix& linalg::Matrix::operator*=(const Matrix& obj) {
	if (m_columns != obj.m_rows) {
		throw std::runtime_error("The number of columns of the first matrix must match the number of rows of the second matrix");
	}

	Matrix new_matrix = (*this) * obj;
	*this = std::move(new_matrix);
	return *this;
}

bool linalg::Matrix::operator==(const Matrix& obj) const {
	if (m_rows != obj.m_rows || m_columns != obj.m_columns) {
		return false;
	}
	for (size_t i = 0; i < m_rows; i++) {
		for (size_t j = 0; j < m_columns; j++) {
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
		throw std::runtime_error("Matrix is empty. So Frobenius norm can't be found");
	}
	double norma2 = 0.0;
	for (size_t i = 0; i < m_rows; i++) {
		for (size_t j = 0; j < m_columns; j++) {
			norma2 += pow(abs((*this)(i, j)), 2);
		}
	}
	return sqrt(norma2);
}

double linalg::Matrix::trace() const {
	if (m_rows != m_columns) {
		throw std::runtime_error("The matrix must be square");
	}
	if ((*this).empty()) {
		throw std::runtime_error("The matrix mustn't be empty");
	}
	double sled = 0.0;
	for (size_t i = 0; i < m_rows; i++) {
		sled += (*this)(i, i);
	}
	return sled;
}

double linalg::Matrix::det() const {
	if (m_rows != m_columns) {
		throw std::runtime_error("The matrix must be square");
	}

	if ((*this).empty()) {
		throw std::runtime_error("The matrix mustn't be empty");
	}

	if (m_rows == 1) {
		return (*this)(0, 0);
	}

	if (m_rows == 2) {
		return (*this)(0, 0) * (*this)(1, 1) - (*this)(1, 0) * (*this)(0, 1);
	}

	double d = 0;

	for (size_t j = 0; j < m_columns; j++) {
		d += pow(-1, j) * (*this)(0, j) * (*this).minor(0, j).det();
	}
	return d;
}

linalg::Matrix linalg::concatenate(const linalg::Matrix& left, const linalg::Matrix& right) {
	if (left.rows() != right.rows()) {
		throw std::runtime_error("Left and right matrix must have the same number of rows");
	}

	linalg::Matrix new_matrix(left.rows(), left.columns() + right.columns());
	for (size_t i = 0; i < left.rows(); i++) {
		for (size_t j = 0; j < left.columns(); j++) {
			new_matrix(i, j) = left(i, j);
		}
		for (size_t j = left.columns(); j < left.columns() + right.columns(); j++) {
			new_matrix(i, j) = right(i, j - left.columns());
		}
	}
	return new_matrix;
};


linalg::Matrix linalg::transpose(const Matrix& obj) {
	linalg::Matrix new_matrix(obj.columns(), obj.rows());
	for (size_t i = 0; i < obj.rows(); i++) {
		for (size_t j = 0; j < obj.columns(); j++) {
			new_matrix(j, i) = obj(i, j);
		}
	}
	return new_matrix;
};

linalg::Matrix linalg::invert(const Matrix& obj) {
	if (obj.rows() != obj.columns()) {
		throw std::runtime_error("The matrix must be square");
	}
	if (obj.empty()) {
		throw std::runtime_error("The matrix mustn't be empty");
	}

	linalg::Matrix algebM(obj.rows(), obj.columns());
	for (size_t i = 0; i < obj.rows(); i++) {
		for (size_t j = 0; j < obj.columns(); j++) {
			algebM(i, j) = pow(-1, i + j) * (obj.minor(i, j)).det();
		}
	}
	return 1/(obj.det())*transpose(algebM);

};

linalg::Matrix linalg::power(const Matrix& obj, size_t a) {
	if (a <= 0) {
		throw std::invalid_argument("The power must be a natural number");
	}
	linalg::Matrix new_matrix(obj.rows(), obj.columns());
	new_matrix = obj;
	for (size_t i = 1; i < a; i++) {
		new_matrix *= obj;
	}
	return new_matrix;
};

linalg::Matrix linalg::Matrix::minor(size_t row, size_t column) const{
	if (m_rows != m_columns) {
		throw std::runtime_error("The matrix must be square");
	}

	if ((*this).empty()) {
		throw std::runtime_error("The matrix mustn't be empty");
	}

	if (m_rows == 1 && m_columns == 1) {
		throw std::runtime_error("The matrix must have more than one argument");
	}

	if (row >= m_rows || row < 0 || column >= m_columns || column < 0) {
		throw std::out_of_range("The indexes are out of range");
	}

	linalg::Matrix private_matrix(m_rows - 1, m_columns - 1);

	for (size_t k = 0; k < private_matrix.rows(); k++) {
		for (size_t p = 0; p < private_matrix.columns(); p++) {
			if (k < row && p < column) {
				private_matrix(k, p) = (*this)(k, p);
			}
			if (k >= row && p < column) {
				private_matrix(k, p) = (*this)(k + 1, p);
			}
			if (k < row && p >= column) {
				private_matrix(k, p) = (*this)(k, p + 1);
			}
			if (k >= row && p >= column) {
				private_matrix(k, p) = (*this)(k + 1, p + 1);
			}
		}
	}

	return private_matrix;
}

