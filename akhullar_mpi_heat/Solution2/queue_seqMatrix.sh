#!/bin/sh

qsub -d $(pwd) -q mamba -l mem=120GB -l nodes=1:ppn=16 ./run_seqMatrix.sh


