mpicxx  -I mrmpi-7Apr14/src -c -o sorting.o sorting.cpp
mpicxx -o sorting sorting.o mrmpi-7Apr14/src/libmrmpi_mpicc.a
mpirun -n 1 ./sorting gutenberg.txt
