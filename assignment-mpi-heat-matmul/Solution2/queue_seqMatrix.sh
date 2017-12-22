#!/bin/sh

qsub -q mamba -l mem=120GB -l nodes=1:ppn=16 -d $(pwd) ./run_seqMatrix.sh


