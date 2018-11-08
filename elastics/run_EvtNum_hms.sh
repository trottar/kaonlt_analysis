0;66;55M3;66;55m#! /bin/bash

#Which spectrometer 
spec=${0##*_}
spec=${spec%%.sh}
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
script="get_EvtNum_${spec}.C"
scriptPlots="plot_Stat_${spec}.C"

#which commands to run
runScript="root -l -b -q \"${script}(${runNum},${numEvts})\""
runScriptPlots="root -l -b -q \"${scriptPlots}(${runNum},${numEvts})\""

#Excecute 
{

echo "Running ${script}"
echo "Getting ${numEvts} number of events for run ${runNum} for ${SPEC}"
eval ${runScript}
eval ${runScriptPlots}
sleep 2
grep "Run #" ../REPORT_OUTPUT/${SPEC}/PRODUCTION/replay_hms_coin_elastics_${runNum}_${numEvts}.report >> outputGrep
grep -i BCM4B ../REPORT_OUTPUT/${SPEC}/PRODUCTION/replay_hms_coin_elastics_${runNum}_${numEvts}.report >> outputGrep

}

done < "$inputFile"

mv *.png OUTPUT/pngFiles/
mv $outputFile OUTPUT/


