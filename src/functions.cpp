#include "matrix.hpp"
#include "vector.hpp"
#include "functions.hpp"

namespace __Matrix__
{
  void print_matrix(const Matrix &vector)
  {
    auto h = vector.rows();
    auto w = vector.cols();
    auto data__ = vector.data();
    std::cout << vector.id() << "# "
              << h
              << 'x'
              << w
              << ":"
              << std::endl;
    for (auto i = 0; i < h; ++i)
    {
      for (auto j = 0; j < w; ++j)
      {
        std::cout << data__[i * w + j] << " ";
      }
      std::cout << std::endl;
    }
  }

  void eigens_power_law(const Matrix &matrix)
  {
    size_t dim = matrix.cols();
    std::vector<double> vector_x(dim, 1);

    std::copy(vector_x.begin(), vector_x.end(), std::ostream_iterator<double>(std::cout, (" ")));

    double eigen_dominant_value;
    auto i = 0;

    while (true && i < 100)
    {
      std::vector<double> vector_x0(vector_x);
      std::vector<double> vector_y(dim, 0);

      for (auto i = 0; i < dim; ++i)
      {
        for (auto j = 0; j < dim; ++j)
        {
          vector_y[i] += matrix[i][j] * vector_x0[j];
        }
      }

      eigen_dominant_value = vector_y[0];

      for (int i = 1; i < dim; ++i)
      {
        if (eigen_dominant_value < vector_y[i])
        {
          eigen_dominant_value = vector_y[i];
        }
      }
      for (int i = 0; i < dim; ++i)
      {
        vector_x[i] = vector_y[i] / eigen_dominant_value;
      }

      int count;
      for (count = 0; count < dim; ++count)
      {
        if (std::fabs(vector_x[count] - vector_x0[count]) > std::numeric_limits<double>::epsilon())
        {
          ++count;
          break;
        }
      };

      if (count == dim)
      {
        break;
      }
    }

    std::cout << "\nEigen dominant values:" << std::endl;
    std::cout << eigen_dominant_value << std::endl;

    std::cout << "\nEigen dominant vector:";
    std::copy(vector_x.begin(), vector_x.end(), std::ostream_iterator<double>(std::cout, (" ")));
  }

  void lu_decomposition(const Matrix &matrix)
  {
    size_t size = matrix.cols();
    Matrix L{Matrix::identity(size)}, U{size};

    for (auto i = 0; i < size; ++i)
    {
      U[0][i] = matrix[0][i];
    }
    for (auto i = 0; i < size; ++i)
    {
      L[i][0] = matrix[i][0] / matrix[0][0];
    }

    for (auto i = 1; i < size; ++i)
    {
      for (auto j = i; j < size; ++j)
      {
        double sum = 0;
        for (auto k = 0; k < i; ++k)
        {
          sum += L[i][k] * U[k][j];
        }
        U[i][j] = matrix[i][j] - sum;
      }

      for (auto j = i + 1; j < size; ++j)
      {
        double sum = 0;
        for (auto k = 0; k < i; ++k)
        {
          sum += L[j][k] * U[k][i];
        }
        L[j][i] = double(matrix[j][i] - sum) / U[i][i];
      }
    }

    print_matrix(U);
    print_matrix(L);

    print_matrix(matrix);
    print_matrix(L * U);
    print_matrix(U * L);
  }

  void qr_decomposition(const Matrix &matrix)
  {
    size_t width = matrix.cols();
    size_t height = matrix.rows();
    Matrix Q{Matrix::zero(height, width)}, R{width};

    for (auto i = 0; i < width; ++i)
    {
      double sum = 0;
      for (auto j = 0; j < i; ++j)
      {
        for (auto k = 0; k < height; ++k)
        {
          R[j][i] += Q[k][i] * matrix[k][j];
          sum += Q[k][i] * Q[k][i] * matrix[k][j];
        }
      }
      for (auto j = 0; j < height; ++j)
      {
        Q[j][i] = matrix[j][i] - sum;
      }
      sum = 0;
      for (auto j = 0; j < height; ++j)
      {
        sum += Q[j][i] * Q[j][i];
      }
      R[i][i] = std::sqrt(sum);

      for (auto j = 0; j < height; ++j)
      {
        Q[j][i] /= R[i][i];
      }
    }

    print_matrix(Q);
    print_matrix(R);

    print_matrix(matrix);
    print_matrix(Q * R);
    print_matrix(R * Q);
  }

  void print_vector(const Vector &vector)
  {
    auto size = vector.size();
    auto data__ = vector.data();
    std::cout << vector.id() << "# "
              << size
              << ":"
              << std::endl;
    for (auto i = 0; i < size; ++i)
    {
      std::cout << vector[i] << " ";
    }
  }

}
