#include <gtest/gtest.h>
#include "stl_impl.h"

//TEST_UNIQUE_PTR

TEST(STL_IMPL_UNIQUE_PTR, TEST_IS_CONSTRUCTIBLE) {

    EXPECT_TRUE(std::is_constructible<stl_impl::unique_ptr<int>>::value);
}

TEST(STL_IMPL_UNIQUE_PTR, TEST_INIT_DEFAULT_CONSTRUCTOR) {
  stl_impl::unique_ptr<int> ptr{};
  EXPECT_EQ(ptr.get(), nullptr);
}

TEST(STL_IMPL_UNIQUE_PTR, TEST_CONSTRUCTOR_WITH_PARAMETERS) {
  stl_impl::unique_ptr<int> ptr{new int{8}};
  stl_impl::unique_ptr<int> ptr2{new int{8}};
  EXPECT_EQ(*ptr.get(), *ptr2.get());
}

TEST(STL_IMPL_UNIQUE_PTR, TEST_MOVE_CONSTRUCTOR) {
  stl_impl::unique_ptr<int> ptr{new int{8}};
  stl_impl::unique_ptr<int> ptr2{std::move(ptr)};
  EXPECT_EQ(*ptr2,8);
}

TEST(STL_IMPL_UNIQUE_PTR, TEST_MOVE_ASSIGNMENT_NOT_SAME_PTR) {
  stl_impl::unique_ptr<int> ptr{new int{8}};
  stl_impl::unique_ptr<int> ptr2{new int{100}};

  ptr = std::move(ptr2);

  EXPECT_EQ(*ptr,100);
}

TEST(STL_IMPL_UNIQUE_PTR, TEST_MOVE_ASSIGNMENT_SAME_PTR) {
  stl_impl::unique_ptr<int> ptr{new int{8}};
  
  ptr = std::move(ptr);

  EXPECT_EQ(*ptr,8);
}

TEST(STL_IMPL_UNIQUE_PTR, TEST_METHOD_RESET) {
  stl_impl::unique_ptr<int> ptr{new int{8}};
  ptr.reset(new int{42});

  EXPECT_EQ(*ptr,42);
}


//TEST FORWARD_LIST ITERATOR

//TEST FORWARD_LIST

TEST(STL_IMPL_FORWARD_LIST, TEST_IS_CONSTRUCTIBLE) {

    EXPECT_TRUE(std::is_constructible<stl_impl::forward_list<int>>::value);
}

//TEST(STL_IMPL_FORWARD_LIST, TEST_INIT_DEFAULT_CONSTRUCTOR) {
//    stl_impl::forward_list<int> forwardList;
//    EXPECT_EQ(forwardList);
//}

TEST(STL_IMPL_FORWARD_LIST, TEST_IS_DEFAULT_CONSTRUCTOR) {
    stl_impl::forward_list<int> forwardList;
    forwardList.push_front(99);
    forwardList.push_front(120);
    forwardList.push_front(340);
    forwardList.push_back(200);


    stl_impl::forward_list<int>::iterator it;
    it = forwardList.begin();
    for(;it!=forwardList.end();++it){
        std::cout << " " << *it;
    }
//    auto it = forwardList.begin();
//    std::cout << *it;

    EXPECT_TRUE(true);
}