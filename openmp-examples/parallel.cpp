#include <omp.h>
#include <iostream>
using namespace std;

int main () {

  std::cout<<"Before"<<std::endl;

#pragma omp parallel
  {
    std::cout<<"During"<<std::endl;
  }
  
  std::cout<<"After"<<std::endl;
  
  return 0;
}
