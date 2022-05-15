#include "shared_ptr.hpp"
#include <gtest/gtest.h>

struct Foo {
  static size_t delete_count;
  size_t s;
  ~Foo() {
    delete_count++;
  }
};
size_t Foo::delete_count = 0;
TEST(SharedPtr, SharedPtr) {
  {
    k::shared_ptr<Foo> sp{new Foo{}};
    k::shared_ptr<Foo> sp2{sp};
  }
  ASSERT_EQ(Foo::delete_count, 1);

  {
    k::shared_ptr<Foo> sp1{new Foo{}};
    k::shared_ptr<Foo> sp2{new Foo{}};
    sp1 = sp2;
  }
  ASSERT_EQ(Foo::delete_count, 3);

  {
    k::shared_ptr<Foo> sp1{new Foo{}};
    k::shared_ptr<Foo> sp2{std::move(sp1)};
  }
  ASSERT_EQ(Foo::delete_count, 4);
  {
    k::shared_ptr<Foo> sp1{new Foo{}};
    k::shared_ptr<Foo> sp2{new Foo{}};
    sp1 = std::move(sp2);
  }
  ASSERT_EQ(Foo::delete_count, 6);

  {
    k::shared_ptr<Foo> sp1{new Foo{}};
    ASSERT_EQ(Foo::delete_count, 6);
    {
      k::shared_ptr<Foo> sp2{sp1};
      {
        k::shared_ptr<Foo> sp3{sp2};
      }
      ASSERT_EQ(Foo::delete_count, 6);
    }
    ASSERT_EQ(Foo::delete_count, 6);
  }
  ASSERT_EQ(Foo::delete_count, 7);
}
