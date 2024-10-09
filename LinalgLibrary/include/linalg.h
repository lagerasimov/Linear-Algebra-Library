#pragma once
#include <cstddef>

namespace linalg {
	class Matrix {
	public:
		Matrix();
		Matrix(size_t rows, size_t columns);
		~Matrix();

		size_t rows() const;
		size_t columns() const;
		bool empty() const;
		void reshape(size_t rows, size_t columns);

	private:
		double* m_ptr = nullptr;
		size_t m_rows = 0, m_columns = 0;
	};
}