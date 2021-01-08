#include "../math/cMatrix.hpp"
#include "gtest/gtest.h"

TEST(identity_matrix, create) {
  // 1 0 0 0
  // 0 1 0 0
  // 0 0 1 0
  // 0 0 0 1

  cMatrix m = cMatrix::GetIdentityMatrix();

  std::cout << m << "\n";

  ASSERT_EQ(m[0][0], 1);
  ASSERT_EQ(m[0][1], 0);
  ASSERT_EQ(m[0][2], 0);
  ASSERT_EQ(m[0][3], 0);
  ASSERT_EQ(m[1][0], 0);
  ASSERT_EQ(m[1][1], 1);
  ASSERT_EQ(m[1][2], 0);
  ASSERT_EQ(m[1][3], 0);
  ASSERT_EQ(m[2][0], 0);
  ASSERT_EQ(m[2][1], 0);
  ASSERT_EQ(m[2][2], 1);
  ASSERT_EQ(m[2][3], 0);
  ASSERT_EQ(m[3][0], 0);
  ASSERT_EQ(m[3][1], 0);
  ASSERT_EQ(m[3][2], 0);
  ASSERT_EQ(m[3][3], 1);
}