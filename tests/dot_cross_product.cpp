#include "../math/cVector.hpp"
#include "gtest/gtest.h"

TEST(dot_product, checked_with_online_calc_555_123) {
  // aka Inproduct

  cVector v1 = {5, 5, 5};
  cVector v2 = {1, 2, 3};

  double dotProd = v1.DotProduct(v2);

  ASSERT_EQ(dotProd, 30);
}

TEST(dot_product, checked_with_online_calc_135_975) {
  // aka Inproduct

  cVector v1 = {1, 3, 5};
  cVector v2 = {9, 7, 5};

  double dotProd = v1.DotProduct(v2);

  ASSERT_EQ(dotProd, 55);
}

TEST(dot_product, checked_with_online_calc_111_222) {
  // aka Inproduct

  cVector v1 = {1, 1, 1};
  cVector v2 = {2, 2, 2};

  double dotProd = v1.DotProduct(v2);

  ASSERT_EQ(dotProd, 6);
}

TEST(dot_product, checked_with_online_calc_larger_numbers) {
  // aka Inproduct

  cVector v1 = {345, 947, 468};
  cVector v2 = {583, 826, 784};

  double dotProd = v1.DotProduct(v2);

  ASSERT_EQ(dotProd, 1350269);
}

TEST(cross_product, webdictaat_example1) {
  // aka Uitproduct (of kruisproduct)

  cVector v1 = {1, 0, 0};
  cVector v2 = {0, 1, 0};

  cVector crossProd = v1.CrossProduct(v2);

  ASSERT_EQ(crossProd.X, 0);
  ASSERT_EQ(crossProd.Y, 0);
  ASSERT_EQ(crossProd.Z, 1);
}

TEST(cross_product, webdictaat_example2) {
  // aka Uitproduct (of kruisproduct)

  cVector v1 = {1, 0, 0};
  cVector v2 = {-1, 0, 0};

  cVector crossProd = v1.CrossProduct(v2);

  ASSERT_EQ(crossProd.X, 0);
  ASSERT_EQ(crossProd.Y, 0);
  ASSERT_EQ(crossProd.Z, 0);
}

TEST(cross_product, checked_with_online_calc_larger_numbers) {
  // aka Uitproduct (of kruisproduct)

  cVector v1 = {345, 947, 468};
  cVector v2 = {583, 826, 784};

  cVector crossProd = v1.CrossProduct(v2);

  ASSERT_EQ(crossProd.X, 355880);
  ASSERT_EQ(crossProd.Y, 2364);
  ASSERT_EQ(crossProd.Z, -267131);
}