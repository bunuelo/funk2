typedef unsigned long long f2ptr;

f2ptr counter;

f2ptr bytecode__thread(f2ptr thread);
  //  counter = counter * thread;
  //  return thread;
  //}

f2ptr bytecode__thread_arg0(f2ptr thread, f2ptr arg0);
  //  counter = counter * thread * arg0;
  //  return thread + arg0;
  //}

f2ptr bytecode__thread_arg0_arg1(f2ptr thread, f2ptr arg0, f2ptr arg1);
// {
//  counter = counter * thread * arg0 * arg1;
//  return thread + arg0 + arg1;
//}

f2ptr (*position_independent_function)();

void execute_bytecodes(f2ptr thread) {
  (*position_independent_function)();
  bytecode__thread(thread);
  bytecode__thread_arg0(thread, 0x0123456789abcdefll);
  bytecode__thread_arg0_arg1(thread, 0xf0123456789abcdell, 0xef0123456789abcdll);
}

int test_thread_func(f2ptr thread) {
  return (int)thread;
}

void return_if_not_eq(f2ptr thread) {
  if (test_thread_func(thread)) {
    thread = 2;
    return;
  }
  return;
}

int main() {
  return 0;
}
