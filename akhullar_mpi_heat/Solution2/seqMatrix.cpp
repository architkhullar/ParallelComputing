#include <iostream>
#include <mpi.h>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <math.h>
#include <chrono>

using namespace std;

#define MAX_NUMBER 100


int n,power;
long long int *x;
int **A;

void rand_fill_values()
{
    for(int i = 0;i<n; i++)
    {
        x[i] = rand()%MAX_NUMBER + 1;
        //x.push_back(rand()% MAX_NUMBER + 1);
        for(int j = 0;j<n;j++)
        {
            A[i][j] = rand()%MAX_NUMBER + 1;
        }
    }
    return;
}

void print()
{
    for(int i = 0;i<n;i++)
    {
        cout << x[i] << " ";
    }
    cout << endl;
    return;
}


int main (int argc, char* argv[])
{

	if (argc < 6)
  	{
   		std::cerr<<"usage: mpirun "<<argv[0]<<" <functionid> <a> <b> <n> <intensity>"<<std::endl;
    	return -1;
  	}

  	int x_power = 0;

  	n = atoi(argv[1]);
    power = atoi(argv[2]);

    long long int *y = new long long int[n];

    x = new long long int[n];

    A = new int*[n];    
    for(int i = 0; i < n; i++)
    {
        A[i] = new int[n];
    }

    rand_fill_values();

    //clock started
  	std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();  

  	// cout << "x power 0: " << endl;
    // print();

    while(power--)
    {
        for(int i = 0;i<n;i++)
        {
            y[i] = 0;
            for(int j = 0;j<n;j++)
            {
                y[i] += A[i][j]*x[j]; 
            }
        }

        for(int i = 0;i<n;i++)
        {
            x[i] = y[i];
        }
        x_power++;

        // cout << "x power " << x_power << ":"<< endl;
        // print();
    }

    //clock stopped
  	std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now(); 
  	//calculating total duration
  	std::chrono::duration<double> elapsed_seconds = end-start; 
  	//printing total time                                
  	std::cerr<<elapsed_seconds.count()<<std::endl;

    return 0;
}
