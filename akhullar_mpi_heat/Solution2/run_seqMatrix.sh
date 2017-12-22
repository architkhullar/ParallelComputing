#!/bin/sh

RESULTDIR=result/
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
    

#make sequential

. ./params_matrix_seq.sh


for n in $NS;
do
FILE=${RESULTDIR}/sequential_matrix_${n}

if [ ! -f ${FILE} ]
then
	./seqMatrix ${n} 2>${RESULTDIR}/sequential_matrix_${n}  >/dev/null
fi
done

