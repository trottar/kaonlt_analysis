#! /bin/bash

##Number of runs##
numRuns=5

##Lumi plot script##
script="plot_Yield.C"
runScript="root -l \"${script}(${numRuns})\""

##Output table##
output="/home/trottar/ResearchNP/ROOTAnalysis/kaonlt_analysis/lumiscan/OUTPUT/LuminosityScans.txt"
oldout="/home/trottar/ResearchNP/ROOTAnalysis/kaonlt_analysis/lumiscan/OUTPUT/LuminosityScans_all.txt"


##Run script##
cp /dev/null ${output}
echo "Running ${script}"
eval ${runScript}
echo " "

more ${output}

cat ${output} >> ${oldout}
