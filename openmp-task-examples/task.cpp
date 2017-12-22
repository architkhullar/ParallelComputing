#include <iostream>

void A1()
{std::cout<<"A1"<<std::endl;}
void A2()
{std::cout<<"A2"<<std::endl;}
void B1()
{std::cout<<"B1"<<std::endl;}
void B2()
{std::cout<<"B2"<<std::endl;}

void A() {
#pragma omp task
  A1();
#pragma omp task
  A2();
}

void B() {
#pragma omp task
  B1();
#pragma omp task
  B2();
}

void maintask() {
#pragma omp task
  A();
#pragma omp task
  B();
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
