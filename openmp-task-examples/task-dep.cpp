#include <unistd.h>
#include <iostream>

void maintask() {
  int a, b;
#pragma omp task depend(out:a)
  a=0;
#pragma omp task depend(out:b)
  {b=1; sleep(10);}
#pragma omp task depend(in:a)
  std::cout<<"a="<<a<<std::endl;
#pragma omp task depend(in:a,b)
  std::cout<<"a="<<a<<" b="<<b<<std::endl;
#pragma omp taskwait
  std::cout<<"main"<<std::endl;
}

int main() {
#pragma omp parallel
  {
#pragma omp single
    maintask();
  }
  return 0;
}
