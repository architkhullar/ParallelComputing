#!/bin/sh

RESULTDIR=result_weak/
h=`hostname`

if [ "$h" = "mba-i1.uncc.edu"  ];
then
    echo Do not run this on the headnode of the cluster, use qsub!
    exit 1
fi

if [ ! -d ${RESULTDIR} ];
then
    mkdir ${RESULTDIR}
fi
#echo   ${N}  

mpirun ./parHeat ${N} 30 2> ${RESULTDIR}/parHeat_weak_${N}_${PROC}  >/dev/null

