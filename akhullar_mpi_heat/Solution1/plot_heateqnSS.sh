#!/bin/sh

. ./paramsSS.sh

if [ ! -d ${RESULTDIR} ];
then
    mkdir ${RESULTDIR}
fi

#strong scaling

for POWER in ${POWERS};
do
    for N in ${NS};
    do
	FILE=${RESULTDIR}/seqHeat_${N}_${POWER}
	if [ ! -f ${FILE} ]
	then
	    echo missing sequential result file "${FILE}".
	fi

	seqtime=$(cat ${RESULTDIR}/seqHeat_${N}_${POWER})
	
	for PROC in ${PROCS}
	do
	
	    FILE=${RESULTDIR}/parHeat_${N}_${POWER}_${PROC}
	    
	    if [ ! -f ${FILE} ]
	    then
		echo missing parallel heat result file "${FILE}".
	    fi

	    partime=$(cat ${RESULTDIR}/parHeat_${N}_${POWER}_${PROC})
	    
	    echo ${PROC} ${seqtime} ${partime}
	done > ${RESULTDIR}/speedup_heateqn_ni_${N}_${POWER}


	GNUPLOTSTRONG="${GNUPLOTSTRONG} set title 'strong scaling. n=${N} i=${POWER}'; plot '${RESULTDIR}/speedup_heateqn_ni_${N}_${POWER}' u 1:(\$2/\$3);"
    done
done


gnuplot <<EOF
set terminal pdf
set output 'heateqn_plots.pdf'

set style data linespoints

set key top left

set xlabel 'Proc'
set ylabel 'Speedup'

${GNUPLOTSTRONG}
EOF
