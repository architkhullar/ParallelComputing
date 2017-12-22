#include <iostream>
#include <chrono>


__global__ void polynomial_expansion (float* poly, int degree, int n, float* array)
{
    float out = 0.;
    float xdegree = 1.;
  
    int i = blockIdx.x*blockDim.x + threadIdx.x;
    if (i < n)
    {
        float x = array[i];
        for (int k=0; k<=degree; ++k)
        {
            out += xdegree*poly[k];
            xdegree *= x;
        }
        array[i] = out;
    }


}


int main (int argc, char* argv[])
{
  
    if (argc < 3)
    {
        std::cerr<<"usage: "<<argv[0]<<" n degree"<<std::endl;
        return -1;
    }

    int n = atoi(argv[1]); 
    int degree = atoi(argv[2]);
    int nbiter = 1;

    float* array = new float[n];
    float* poly = new float[degree+1];
    for (int i=0; i<n; ++i)
        array[i] = 1.;

    for (int i=0; i<degree+1; ++i)
        poly[i] = 1.;

  
    float *xArrayPointer, *coefficientArrayPointer; 

    //Allocating space in device
    cudaMalloc(&xArrayPointer, n*sizeof(float)); 
    cudaMalloc(&coefficientArrayPointer, (degree+1)*sizeof(float)); 
 
    //copying arrays to device array
    cudaMemcpy(xArrayPointer, array, n*sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(coefficientArrayPointer, poly, (degree+1)*sizeof(float), cudaMemcpyHostToDevice); 
    
    std::chrono::time_point<std::chrono::system_clock> begin, end;
    begin = std::chrono::system_clock::now();
  
  
    for (int iter = 0; iter<nbiter; ++iter)
    {
        polynomial_expansion<<<(n+512)/512+1, 512>>>(coefficientArrayPointer, degree, n, xArrayPointer);
    }

    cudaDeviceSynchronize(); //Cuda sync
  
    //checking for any errors
    cudaError_t err = cudaGetLastError();
    if (err != cudaSuccess) 
        printf("Error: %s\n", cudaGetErrorString(err)); 

    //copying the device array to CPU   
    cudaMemcpy(array, xArrayPointer, n*sizeof(float), cudaMemcpyDeviceToHost);
  
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> totaltime = (end-begin)/nbiter;

    std::cerr<<array[0]<<std::endl;
    std::cout<<n<<" "<<degree<<" "<<totaltime.count()<<std::endl;

    delete[] array;
    delete[] poly;
    cudaFree(xArrayPointer); //free cuda mem
    cudaFree(coefficientArrayPointer);
    return 0;
}
