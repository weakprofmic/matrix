#include <gtest/gtest.h>
#include "matrix.hpp"

TEST(Matrix, equals)
{
  EXPECT_EQ(Matrix{}, Matrix{});
  EXPECT_EQ(Matrix::identity(3), Matrix::identity(3));
  EXPECT_NE(Matrix{}, Matrix::identity(1));

  const Matrix all_zero{3, 3, {0}};
  const Matrix all_one{3, 3, {1}};
  const Matrix all_default{3, 3};
  EXPECT_EQ(all_zero, all_default);
  EXPECT_NE(all_zero, all_one);

  const Matrix two_by_three{2, 3};
  const Matrix three_by_two{3, 2};
  EXPECT_NE(two_by_three, three_by_two);
}

TEST(Matrix, accessors)
{
  const Matrix two_by_three{2, 3};
  EXPECT_EQ(2, two_by_three.rows());
  EXPECT_EQ(3, two_by_three.cols());
  // EXPECT_EQ(6, two_by_three.size());
  EXPECT_FALSE(two_by_three.is_square());
  EXPECT_FALSE(two_by_three.is_identity());
  EXPECT_TRUE(two_by_three.is_constant());
  EXPECT_TRUE(two_by_three.is_zero());

  const Matrix null{};
  EXPECT_TRUE(null.is_zero());
  EXPECT_TRUE(null.is_square());
  EXPECT_TRUE(null.is_symmetric());
  EXPECT_TRUE(null.is_skewSymmetric());

  const Matrix zero{2, 2};
  EXPECT_TRUE(zero.is_zero());
  EXPECT_TRUE(zero.is_square());
  EXPECT_FALSE(zero.is_identity());
  EXPECT_TRUE(zero.is_symmetric());
  EXPECT_TRUE(zero.is_skewSymmetric());

  const Matrix one{2, 2, {1}};
  EXPECT_FALSE(one.is_zero());
  EXPECT_TRUE(one.is_constant());
  EXPECT_TRUE(one.is_square());
  EXPECT_FALSE(one.is_identity());
  EXPECT_TRUE(one.is_symmetric());
  EXPECT_FALSE(one.is_skewSymmetric());
  EXPECT_FALSE(one.is_upperTriangular());
  EXPECT_FALSE(one.is_lowerTriangular());

  const Matrix identity = Matrix::identity(2);
  EXPECT_FALSE(identity.is_zero());
  EXPECT_FALSE(identity.is_constant());
  EXPECT_TRUE(identity.is_square());
  EXPECT_TRUE(identity.is_identity());
  EXPECT_TRUE(identity.is_symmetric());
  EXPECT_TRUE(identity.is_skewSymmetric());
  EXPECT_TRUE(identity.is_upperTriangular());
  EXPECT_TRUE(identity.is_lowerTriangular());

  Matrix two_by_two{2, 2, {1, 2, 0, 4}};
  EXPECT_TRUE(two_by_two.is_upperTriangular());
  EXPECT_FALSE(two_by_two.is_lowerTriangular());
  EXPECT_FALSE(two_by_two.is_skewSymmetric());
  EXPECT_FALSE(two_by_two.is_symmetric());
  two_by_two(1, 0) = 2;
  EXPECT_FALSE(two_by_two.is_skewSymmetric());
  EXPECT_TRUE(two_by_two.is_symmetric());
  two_by_two(1, 0) = -2;
  EXPECT_TRUE(two_by_two.is_skewSymmetric());
  EXPECT_FALSE(two_by_two.is_symmetric());
  two_by_two(0, 1) = 0;
  EXPECT_FALSE(two_by_two.is_upperTriangular());
  EXPECT_TRUE(two_by_two.is_lowerTriangular());
}

TEST(Matrix, plus_minus)
{
  Matrix zero{3, 2};
  Matrix one{3, 2, {1}};
  Matrix two{3, 2, {2}};
  Matrix three{3, 2, {3}};
  ASSERT_EQ(one, one + zero);
  ASSERT_EQ(three, one + two);
  ASSERT_EQ(two, three - one);
  ASSERT_EQ(zero, one - one);
}

TEST(Matrix, transposed)
{
  Matrix a{2, 3, {1, 2, 3, 4, 5, 6}};
  Matrix b{3, 2, {1, 4, 2, 5, 3, 6}};
  ASSERT_EQ(a, Matrix::transposed(b));
  ASSERT_EQ(b, Matrix::transposed(b));
}

TEST(Matrix, determinant)
{
  // identity matrices have determinant == 1
  ASSERT_EQ(1, Matrix::identity(3).det());
  // example from Wikipedia
  Matrix a{3, 3, {-2, 2, -3, -1, 1, 3, 2, 0, -1}};
  ASSERT_EQ(18, a.det());
  // from https://people.richland.edu/james/lecture/m116/matrices/determinant.html
  Matrix b{4, 4, {3, 2, 0, 1, 4, 0, 1, 2, 3, 0, 2, 1, 9, 2, 3, 1}};
  ASSERT_EQ(24, b.det());
}

TEST(Matrix, inverse)
{
  Matrix a{3, 3, {-2, 2, -3, -1, 1, 3, 2, 0, -1}};
  Matrix b = Matrix::inversed(a);
  ASSERT_EQ(a * b, Matrix::identity(3));
  ASSERT_EQ(b * a, Matrix::identity(3));
}