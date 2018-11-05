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

#Output file
output=${rtype}_${runNum}.out


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
echo "COMMAND:/home/trottar/Analysis/hallc_replay/run_Replay_${rtype}.sh ${runNum}" >> ${batch}
echo "COMMAND: ls -alF > ${output}" 
echo "OUTPUT_DATA: ${output}" >> ${batch}
echo "OUTPUT_TEMPLATE: /home/trottar/ResearchNP/ROOTAnalysis/kaonlt_analysis/batch_OUTPUT/${rtype}_${runNum}.out" >> ${batch}
echo "MAIL: trotta@cua.edu" >> ${batch}

echo "Submitting batch"
eval "jsub ${batch}"

}

done < "$inputFile"
