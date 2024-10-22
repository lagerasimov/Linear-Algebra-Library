#include <linalg.h>
#include <stdexcept> 
#include <sstream> //ostringstream
#include <iomanip> //setw
#include <cmath>

size_t linalg::Matrix::rows() const noexcept{
	return m_rows;
}

size_t linalg::Matrix::columns() const noexcept{
	return m_columns;
}

bool linalg::Matrix::empty() const noexcept{
	return (m_rows == 0 || m_columns == 0);
}

void linalg::Matrix::reshape(size_t rows, size_t columns) {
	if (rows * columns != m_rows * m_columns) {
		throw std::runtime_error("The number of elements mustn't be changed");
	}
	m_rows = rows;
	m_columns = columns;
}

linalg::Matrix::Matrix() noexcept{
	
}

linalg::Matrix::Matrix(size_t rows, size_t columns) {
	if (rows == 0 || columns == 0) {
		throw std::runtime_error("Matrix dimensions must be greater than zero");
	}
	m_rows = rows;
	m_columns = columns;
	m_ptr = new double[m_rows * m_columns] {};
}

linalg::Matrix::Matrix(size_t rows) {
	if (rows == 0) {
		throw std::runtime_error("Matrix dimensions must be greater than zero");
	}
	m_rows = rows;
	m_columns = 1;
	m_ptr = new double[m_rows] {};
}

linalg::Matrix::~Matrix(){
	delete[] m_ptr;
}

linalg::Matrix::Matrix(const Matrix& m) {
	m_rows = m.m_rows;
	m_columns = m.m_columns;
	m_ptr = new double[m_rows * m_columns];
	for (size_t i = 0; i < m_rows * m_columns; ++i) {
		m_ptr[i] = m.m_ptr[i];
	}
}

linalg::Matrix::Matrix(Matrix&& m) noexcept{
	std::swap(m_ptr, m.m_ptr);
	std::swap(m_rows, m.m_rows);
	std::swap(m_columns, m.m_columns);
}


linalg::Matrix::Matrix(std::initializer_list<double> a) {
	if (a.size() == 0) {
		throw std::runtime_error("The matrix can't be empty");
	}

	m_columns = 1;
	m_rows = a.size();
	m_ptr = new double[m_rows];
	size_t i = 0;

	for (const double& el: a) {
		m_ptr[i++] = el;
	}
}

linalg::Matrix::Matrix(std::initializer_list<std::initializer_list<double>> a) {
	if (a.size() == 0) {
		throw std::runtime_error("The matrix can't be empty");
	}
	
	m_rows = a.size();
	m_columns = a.begin()->size();
	m_ptr = new double[m_rows * m_columns];
	size_t i = 0;

	for (const std::initializer_list<double>& el : a) {
		if (el.size() != m_columns) {
			throw std::runtime_error("The rows of matrix must have the equal size");
		}
		for (const double& ch : el) {
			m_ptr[i++] = ch;
		}
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

	for (size_t i = 0; i < m_rows * m_columns; ++i) {
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
	for (size_t i = 0; i < m_rows * m_columns; ++i) {
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
	size_t* widths = new size_t[m.columns()]{};
	for (size_t j = 0; j < m.columns(); ++j) {
		for (size_t i = 0; i < m.rows(); ++i) {
			out << m(i, j);
			widths[j] = std::max(out.str().size(), widths[j]);
			out.str("");
		}
	}
	return widths;
}

std::ostream& linalg::operator<<(std::ostream& potok, const linalg::Matrix& m) noexcept{
	if (m.empty()) {
		potok << "|empty|\n";
		return potok;
	}

	size_t* sizes = widths(m);

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

linalg::Matrix& linalg::Matrix::operator+=(const Matrix& obj) {
	if (m_rows != obj.m_rows || m_columns != obj.m_columns) {
		throw std::runtime_error("The sizes of the matrices don't match");
	}

	for (size_t i = 0; i < m_rows; ++i) {
		for (size_t j = 0; j < m_columns; ++j) {
			(*this)(i, j) += obj(i, j);
		}
	}
	return *this;
}

linalg::Matrix linalg::operator+(const Matrix& left, const Matrix& right) {

	Matrix new_matrix(left);
	new_matrix += right;
	return new_matrix;
}

linalg::Matrix linalg::operator-(const Matrix& left, const Matrix& right) {
	Matrix new_matrix(left);
	new_matrix -= right;
	return new_matrix;

};

linalg::Matrix& linalg::Matrix::operator-=(const Matrix& obj) {
	if (m_rows != obj.m_rows || m_columns != obj.m_columns) {
		throw std::runtime_error("The sizes of the matrices don't match");
	}

	for (size_t i = 0; i < m_rows; ++i) {
		for (size_t j = 0; j < m_columns; ++j) {
			(*this)(i, j) -= obj(i, j);
		}
	}
	return *this;
}

linalg::Matrix linalg::operator*(const Matrix& obj, double ch) noexcept{
	linalg::Matrix new_matrix(obj);
	new_matrix *= ch;
	return new_matrix;
}

linalg::Matrix linalg::operator*(const Matrix& left, const Matrix& right) {
	linalg::Matrix new_matrix(left);
	new_matrix *= right;
	return new_matrix;
}

linalg::Matrix linalg::operator*(double ch, const Matrix& obj) noexcept{
	linalg::Matrix new_matrix(obj);
	new_matrix *= ch;
	return new_matrix;
};

linalg::Matrix& linalg::Matrix::operator*=(double ch) noexcept{
	for (size_t i = 0; i < m_rows; ++i) {
		for (size_t j = 0; j < m_columns; ++j) {
			(*this)(i, j) = (*this)(i, j) * ch;
		}
	}
	return *this;
}

linalg::Matrix& linalg::Matrix::operator*=(const Matrix& obj) {
	if (m_columns != obj.m_rows) {
		throw std::runtime_error("The number of columns of the first matrix must match the number of rows of the second matrix");
	}

	Matrix new_matrix(obj.rows(), obj.columns());
	for (size_t i = 0; i < m_rows; ++i) {
		for (size_t j = 0; j < obj.m_columns; ++j) {
			for (size_t p = 0; p < m_columns; ++p) {
				new_matrix(i, j) += (*this)(i, p) * obj(p, j);
			}
		}
	}
	*this = std::move(new_matrix);
	return *this;
}

bool linalg::operator==(const Matrix& left, const Matrix& right) noexcept{
	if (left.rows() != right.rows() || left.columns() != right.columns()) {
		return false;
	}
	for (size_t i = 0; i < left.rows(); ++i) {
		for (size_t j = 0; j < left.columns(); ++j) {
			if (fabs(left(i, j) - right(i, j)) >= 0.00001) {
				return false;
			}
		}
	}
	return true;
}

bool linalg::operator!=(const Matrix& left, const Matrix& right) noexcept{
	return !(left == right);
}

double linalg::Matrix::norm() const{
	if ((*this).empty()) {
		throw std::runtime_error("Matrix is empty. So Frobenius norm can't be found");
	}
	double norma2 = 0.0;
	for (size_t i = 0; i < m_rows; ++i) {
		for (size_t j = 0; j < m_columns; ++j) {
			norma2 += pow(fabs((*this)(i, j)), 2);
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
	for (size_t i = 0; i < m_rows; ++i) {
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

	for (size_t j = 0; j < m_columns; ++j) {
		d += pow(-1, j) * (*this)(0, j) * (*this).minor(0, j);
	}
	return d;
}

linalg::Matrix linalg::concatenate(const linalg::Matrix& left, const linalg::Matrix& right) {
	if (left.rows() != right.rows()) {
		throw std::runtime_error("Left and right matrix must have the same number of rows");
	}

	linalg::Matrix new_matrix(left.rows(), left.columns() + right.columns());
	for (size_t i = 0; i < left.rows(); ++i) {
		for (size_t j = 0; j < left.columns(); ++j) {
			new_matrix(i, j) = left(i, j);
		}
		for (size_t j = left.columns(); j < left.columns() + right.columns(); ++j) {
			new_matrix(i, j) = right(i, j - left.columns());
		}
	}
	return new_matrix;
};


linalg::Matrix linalg::transpose(const Matrix& obj){
	linalg::Matrix new_matrix(obj.columns(), obj.rows());
	for (size_t i = 0; i < obj.rows(); ++i) {
		for (size_t j = 0; j < obj.columns(); ++j) {
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
	for (size_t i = 0; i < obj.rows(); ++i) {
		for (size_t j = 0; j < obj.columns(); ++j) {
			algebM(i, j) = pow(-1, i + j) * obj.minor(i, j);
		}
	}
	return 1/(obj.det())*transpose(algebM);

};

linalg::Matrix linalg::power(const Matrix& obj, int a) {

	if (a < 0) {
		return power(invert(obj), abs(a));
	}

	linalg::Matrix new_matrix(obj.rows(), obj.columns());
	for (size_t i = 0; i < obj.rows(); ++i) {
		new_matrix(i, i) = 1;
	}

	if (a == 0) {
		return new_matrix;
	}

	for (size_t i = 0; i < a; i++) {
		new_matrix *= obj;
	}

	return new_matrix;
};

double linalg::Matrix::minor(size_t row, size_t column) const{
	if (m_rows != m_columns) {
		throw std::runtime_error("The matrix must be square");
	}

	if ((*this).empty()) {
		throw std::runtime_error("The matrix mustn't be empty");
	}

	if (m_rows == 1 && m_columns == 1) {
		throw std::runtime_error("The matrix must have more than one argument");
	}

	if (row >= m_rows || column >= m_columns) {
		throw std::out_of_range("The indexes are out of range");
	}

	linalg::Matrix private_matrix(m_rows - 1, m_columns - 1);

	for (size_t k = 0; k < private_matrix.rows(); ++k) {
		for (size_t p = 0; p < private_matrix.columns(); ++p) {
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

	return private_matrix.det();
}

linalg::Matrix linalg::Kramer(const Matrix& obj) {
	if (obj.columns() != obj.rows() + 1) {
		throw::std::runtime_error("The number of equations must be equal to the number of unknown variables");
	}

	Matrix solutions(obj.rows());

	Matrix M(obj.rows(), obj.rows());
	for (size_t i = 0; i < obj.rows(); ++i) {
		for (size_t j = 0; j < obj.columns() - 1; ++j) {
			M(i, j) = obj(i, j);
		}
	}

	if (M.det() == 0) {
		throw std::runtime_error("The system has infinitely many solutions or is incompatible");
	}

	Matrix M1(M);

	for (size_t j = 0; j < obj.rows(); ++j) {
		for (size_t i = 0; i < obj.rows(); ++i) {
			M1(i, j) = obj(i, obj.columns() - 1);
		}
		solutions(j, 0) = M1.det() / M.det();
		M1 = M;
	}

	return solutions;
}

