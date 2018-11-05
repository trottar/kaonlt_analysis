#! /bin/bash

#What kind of runs?
rtype=$1

#output batch script
batch="trotta_${rtype}Job.txt"

#Input run numbers
inputFile="/home/trottar/ResearchNP/ROOTAnalysis/kaonlt_analysis/${rtype}/inputRuns"

while IFS='' read -r line || [[ -n "$line" ]];
do
    echo "Run number read from file: $line"

#Run number
runNum=$line


{
echo "Running ${batch} for ${runNum}"
cp /dev/null ${batch}
#sleep 2

echo "PROJECT: e01011" >> ${batch}
#echo "TRACK: analysis" >> ${batch}
echo "TRACK: debug" >> ${batch}
echo "JOBNAME: ${rtype}_${runNum}" >> ${batch}
echo "MEMORY: 2000 MB" >> ${batch}
echo "OS: centos7" >> ${batch}
echo "CPU: 1" >> ${batch}
#echo "INPUT_FILES:/home/trottar/ResearchNP/ROOTAnalysis/kaonlt_analysis/${rtype}/inputRuns" >> ${batch}
echo "COMMAND:/home/trottar/Analysis/hallc_replay/run_Replay_${rtype}.sh ${runNum}" >> ${batch}
#echo "OTHER_FILES: /home/trottar/Analysis/hallc_replay/run_Replay_${rtype}.sh" >> ${batch}
echo "OUTPUT_DATA: ${rtype}_${runNum}.out" >> ${batch}
echo "OUTPUT_TEMPLATE: /home/trottar/batchAnalysis/${rtype}_${runNum}.out" >> ${batch}
echo "MAIL: trotta@cua.edu" >> ${batch}

echo "Submitting batch"
eval "jsub ${batch}"

}

done < "$inputFile"
