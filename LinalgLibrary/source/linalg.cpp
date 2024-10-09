#include <linalg.h>
#include <stdexcept>
#include <iostream>

namespace linalg {

	size_t Matrix::rows() const {
		return m_rows;
	}

	size_t Matrix::columns() const{
		return m_columns;
	}

	bool Matrix::empty() const {
		return (m_rows == 0 || m_columns == 0);
	}

	void Matrix::reshape(size_t rows, size_t columns) {
		if (rows * columns == m_rows * m_columns) {
			m_rows = rows;
			m_columns = columns;
		}
		else {
			throw std::runtime_error("The number of elements shouldn't be changed");
		}

	}

	Matrix::Matrix(size_t rows, size_t columns) {
		m_rows = rows;
		m_columns = columns;
		m_ptr = new double[m_rows * m_columns]();
	}

	Matrix::~Matrix(){
		delete[] m_ptr;
	}
}