
#include <mpi.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <mapreduce.h>
#include <keyvalue.h>
#include <sys/stat.h>

using namespace MAPREDUCE_NS;

void fileread(int itask, char *fname, KeyValue *kv, void *ptr)
{
    struct stat stbuf;
    int flag = stat(fname,&stbuf);
    if (flag < 0) 
    {
        printf("ERROR: Could not query file size\n");
        MPI_Abort(MPI_COMM_WORLD,1);
    }
    int filesize = stbuf.st_size;

    FILE *fp = fopen(fname,"r");
    char *text = new char[filesize+1];
    int nchar = fread(text,1,filesize,fp);
    text[nchar] = '\0';
    fclose(fp);
    char *whitespace = " \'\".,?-!/#(){}[]:;<>\t\n\f\r\0";
    char *word = strtok(text,whitespace);
    while (word) 
    {
        kv->add(word,strlen(word)+1,NULL,0);
        word = strtok(NULL,whitespace);
    }
    delete [] text;
}

void sum(char *key, int keybytes, char *multivalue, int nvalues, int *valuebytes, KeyValue *kv, void *ptr)
{
    kv->add(key,keybytes,(char *) &nvalues,sizeof(int));
}

int main(int argc, char *argv[])
{
    MPI_Init(&argc,&argv);

    int rank,P;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&P);

    if (argc <= 1) 
    {
        if (rank == 0) printf("wordcounter f1 f2 ...\n");
        MPI_Abort(MPI_COMM_WORLD,1);
    }

    MapReduce *m = new MapReduce(MPI_COMM_WORLD);
    m->verbosity = 1;

    MPI_Barrier(MPI_COMM_WORLD);

    int nwords = m->map(argc-1,&argv[1],0,1,0,fileread,NULL);
    int nfiles = m->mapfilecount;
    m->collate(NULL);
    int nunique = m->reduce(sum,NULL);
    m->gather(1);
    MPI_Barrier(MPI_COMM_WORLD);
    
    char *outp = new char[20];
    strncpy(outp, "output", sizeof(outp)-1);
    m->print(outp, 1, 0, 1, 5, 1);

    MPI_Barrier(MPI_COMM_WORLD);

    delete m;

    if (rank == 0) 
    {
     printf("-----------------------------------------------------\n");
        printf("%d total words, %d unique words\n",nwords,nunique);
     printf("-----------------------------------------------------\n");
    }

    MPI_Finalize();
}
