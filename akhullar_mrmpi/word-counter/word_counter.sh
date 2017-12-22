
mpicxx  -I mrmpi-7Apr14/src -c -o word_counter.o word_counter.cpp
mpicxx -o word_counter word_counter.o mrmpi-7Apr14/src/libmrmpi_mpicc.a
mpirun -n 1 word_counter gutenberg.txt 
