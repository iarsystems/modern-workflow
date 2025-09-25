#include <errno.h>
#include <acutest.h>

int foo(int a){
  return a+1;
}

///* __argc, the number of arguments in __argv. */
//__no_init __root int __argc;
///* __argv, an array of pointers to strings that holds the arguments; must
//be large enough to fit the number of parameters.*/
//__no_init __root const char * __argv[1000];
///* __argvbuf, a storage area for __argv; must be large enough to hold all
//command line parameters. */
//__no_init __root char __argvbuf[1000];


void test_foo() {
  int t;
  
  TEST_CASE("normal 10");
  t = foo(10);
  TEST_CHECK(t==11 );
  
  TEST_CASE("normal 1");
  t = foo(1);
  TEST_CHECK(t==2 );
  
  TEST_CASE("normal 2");
  t = foo(2);
  TEST_CHECK(t==3 );
  
}

void test_foo2() {
  int t;
  
  TEST_CASE("normal 100");
  t = foo(100);
  TEST_CHECK(t==101 );
  
}

TEST_LIST= {
  {"test_foo", test_foo},
  {"test_foo2", test_foo},

  {NULL, NULL}
};

