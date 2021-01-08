#include "../math/cMatrix.hpp"
#include "gtest/gtest.h"

TEST(projection_matrix, create) {
  cMatrix m = cMatrix::GetProjectionMatrix(1, 2000, 90);

  std::cout << m << "\n";

  ASSERT_EQ(round(m[0][0]), 2);
  ASSERT_EQ(round(m[0][1]), 0);
  ASSERT_EQ(round(m[0][2]), 0);
  ASSERT_EQ(round(m[0][3]), 0);
  ASSERT_EQ(round(m[1][0]), 0);
  ASSERT_EQ(round(m[1][1]), 2);
  ASSERT_EQ(round(m[1][2]), 0);
  ASSERT_EQ(round(m[1][3]), 0);
  ASSERT_EQ(round(m[2][0]), 0);
  ASSERT_EQ(round(m[2][1]), 0);
  ASSERT_EQ(round(m[2][2]), -1);
  ASSERT_EQ(round(m[2][3]), -1);
  ASSERT_EQ(round(m[3][0]), 0);
  ASSERT_EQ(round(m[3][1]), 0);
  ASSERT_EQ(round(m[3][2]), -1);
  ASSERT_EQ(round(m[3][3]), 0);
}