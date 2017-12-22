
mpicxx  -I mrmpi-7Apr14/src -c -o histogram.o histogram.cpp
mpicxx -o histogram histogram.o mrmpi-7Apr14/src/libmrmpi_mpicc.a
mpirun -n 1 ./histogram gutenberg.txt
