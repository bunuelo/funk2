typedef unsigned long long f2ptr;

f2ptr counter;

f2ptr bytecode__fiber(f2ptr fiber);
  //  counter = counter * fiber;
  //  return fiber;
  //}

f2ptr bytecode__fiber_arg0(f2ptr fiber, f2ptr arg0);
  //  counter = counter * fiber * arg0;
  //  return fiber + arg0;
  //}

f2ptr bytecode__fiber_arg0_arg1(f2ptr fiber, f2ptr arg0, f2ptr arg1);
// {
//  counter = counter * fiber * arg0 * arg1;
//  return fiber + arg0 + arg1;
//}

f2ptr (*position_independent_function)();

void execute_bytecodes(f2ptr fiber) {
  (*position_independent_function)();
  bytecode__fiber(fiber);
  bytecode__fiber_arg0(fiber, 0x0123456789abcdefll);
  bytecode__fiber_arg0_arg1(fiber, 0xf0123456789abcdell, 0xef0123456789abcdll);
}

int test_fiber_func(f2ptr fiber) {
  return (int)fiber;
}

void return_if_not_eq(f2ptr fiber) {
  if (test_fiber_func(fiber)) {
    fiber = 2;
    return;
  }
  return;
}

int main() {
  return 0;
}
