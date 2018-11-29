#! /bin/bash

#Which spectrometer
spec=$1
#spec=${0##*_}
#spec=${spec%%.sh}
SPEC=$(echo "$spec" | tr '[:lower:]' '[:upper:]')

#Input run numbers
inputFile="inputRuns"
outputFile="outputGrep"

while IFS='' read -r line || [[ -n "$line" ]];
do
    echo "Run number read from file: $line"

#Which run
runNum=$line

#Number of events
numEvts=-1

#Which scripts to run
script="get_EvtNum.C"
scriptPlots="plot_Stat.C"

#which commands to run
runScript="root -l -b -q \"${script}(${runNum},${numEvts},${spec})\""
runScriptPlots="root -l -b -q \"${scriptPlots}(${runNum},${numEvts},${spec})\""

#Excecute 
{

echo "Running ${script}"
echo "Getting ${numEvts} number of events for run ${runNum} for ${SPEC}"
eval ${runScript}
eval ${runScriptPlots}
sleep 2
grep "Run #" /home/trottar/ResearchNP/ROOTAnalysis/REPORT_OUTPUT/COIN/PRODUCTION/replay_coin_production_${runNum}_${numEvts}.report >> outputGrep
grep -i BCM4B /home/trottar/ResearchNP/ROOTAnalysis/REPORT_OUTPUT/COIN/PRODUCTION/replay_coin_production_${runNum}_${numEvts}.report >> outputGrep

}

done < "$inputFile"

mv *.png OUTPUT/pngFiles/
mv $outputFile OUTPUT/


