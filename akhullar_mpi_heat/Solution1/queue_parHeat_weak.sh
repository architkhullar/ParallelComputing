#!/bin/sh

. ./paramsWS.sh


if [ ! -d ${RESULTDIR} ];
then
    mkdir ${RESULTDIR}
fi

#weak scaling


qsub -d $(pwd) -q mamba -l mem=120GB -l procs=2 -v N=2048,PROC=2 ./run_parHeat_weak.sh
qsub -d $(pwd) -q mamba -l mem=120GB -l procs=4 -v N=4096,PROC=4 ./run_parHeat_weak.sh
qsub -d $(pwd) -q mamba -l mem=120GB -l procs=8 -v N=8192,PROC=8 ./run_parHeat_weak.sh
qsub -d $(pwd) -q mamba -l mem=120GB -l procs=16 -v N=16384,PROC=16 ./run_parHeat_weak.sh
qsub -d $(pwd) -q mamba -l mem=120GB -l procs=32 -v N=32768,PROC=32 ./run_parHeat_weak.sh

qsub -d $(pwd) -q mamba -l mem=120GB -l procs=2 -v N=4096,PROC=2 ./run_parHeat_weak.sh
qsub -d $(pwd) -q mamba -l mem=120GB -l procs=4 -v N=8192,PROC=4 ./run_parHeat_weak.sh
qsub -d $(pwd) -q mamba -l mem=120GB -l procs=8 -v N=16384,PROC=8 ./run_parHeat_weak.sh
qsub -d $(pwd) -q mamba -l mem=120GB -l procs=16 -v N=32768,PROC=16 ./run_parHeat_weak.sh
qsub -d $(pwd) -q mamba -l mem=120GB -l procs=32 -v N=65536,PROC=32 ./run_parHeat_weak.sh

qsub -d $(pwd) -q mamba -l mem=120GB -l procs=2 -v N=8192,PROC=2 ./run_parHeat_weak.sh
qsub -d $(pwd) -q mamba -l mem=120GB -l procs=4 -v N=16384,PROC=4 ./run_parHeat_weak.sh
qsub -d $(pwd) -q mamba -l mem=120GB -l procs=8 -v N=32768,PROC=8 ./run_parHeat_weak.sh
qsub -d $(pwd) -q mamba -l mem=120GB -l procs=16 -v N=65536,PROC=16 ./run_parHeat_weak.sh
qsub -d $(pwd) -q mamba -l mem=120GB -l procs=32 -v N=131072,PROC=32 ./run_parHeat_weak.sh



