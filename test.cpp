#include <gtest/gtest.h>
#include "stl_impl.h"


TEST(STL_IMPL_UNIQUE_PTR, TEST_DEFAULT_CONSTRUCTOR) {
  stl_impl::unique_ptr<int> ptr{};
  EXPECT_EQ(ptr.get(), nullptr);
}

TEST(STL_IMPL_UNIQUE_PTR, TEST_CONSTRUCTOR_WITH_PARAMETERS) {
  stl_impl::unique_ptr<int> ptr{new int{8}};
  stl_impl::unique_ptr<int> ptr2{new int{8}};
  EXPECT_EQ(*ptr.get(), *ptr2.get());
}
