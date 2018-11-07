#! /bin/bash

#Run type (e.g. elastics? lumiscan?)
rtype=$1

#Output file
historyfile=hist_${rtype}.$( date "+%Y-%m-%d_%H-%M-%S" ).log

#output batch script
batch="trotta_${rtype}Job.txt"

#Input run numbers
inputFile="/home/trottar/ResearchNP/ROOTAnalysis/kaonlt_analysis/${rtype}/inputRuns"
i=-1

(

while IFS='' read -r line || [[ -n "$line" ]]; do
    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    echo "Run number read from file: $line"
    echo ""
    #Run number
    runNum=$line
    tmp=tmp 
    numlines=$(eval "wc -l < ${inputFile}")
    echo "Job $(( $i + 1 ))/$numlines"    
    echo "Running ${batch} for ${runNum}"
    cp /dev/null ${batch}    
    echo "PROJECT: e01011" >> ${batch}
    #echo "TRACK: analysis" >> ${batch}
    echo "TRACK: debug" >> ${batch}
    echo "JOBNAME: ${rtype}_${runNum}" >> ${batch}
    echo "MEMORY: 2000 MB" >> ${batch}
    echo "OS: centos7" >> ${batch}
    echo "CPU: 2" >> ${batch}
    #echo "TIME: 1" >> ${batch}
    echo "COMMAND:/home/trottar/Analysis/hallc_replay/run_Replay.sh ${runNum} ${rtype}" >> ${batch}
    echo "MAIL: trotta@cua.edu" >> ${batch}    
    echo "Submitting batch"
    eval "jsub ${batch} 2>/dev/null" 
    echo " "
    i=$(( $i + 1 ))
    string=$(cat ${inputFile} |tr "\n" " ")
    rnum=($string)
    #echo "array is ${rnum[@]}"   
    #eval "jobstat -u trottar 2>/dev/null"
    eval "jobstat -u trottar 2>/dev/null" > ${tmp}   
    for j in "${rnum[@]}"
    do
	if [ $(grep -c $j ${tmp}) -gt 0 ]; then
	    ID=$(echo $(grep $j ${tmp}) | head -c 8)
	    augerID[$i]=$ID
	fi	
    done   
    #echo "${augerID[@]}"
    echo "${rnum[$i]} has an AugerID of ${augerID[$i]}" 
    if [ $i == $numlines ]; then
	echo "###############################################################################################################"
	echo "############################################ END OF JOB SUBMISSIONS ###########################################"
	echo "###############################################################################################################"
	echo " "	
	k=-1
      	for j in "${augerID[@]}"
	do
	    k=$(( $k + 1 ))
	    echo "${rnum[$k]} has an AugerID of $j"
	done
	#echo "${augerID[@]}"
	while [  $(eval "wc -l < ${tmp}") != 1 ]; do
	    cp /dev/null ${tmp}
	    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"  
	    eval "jobstat -u trottar 2>/dev/null"
	    eval "jobstat -u trottar 2>/dev/null" > ${tmp}
	    echo " "  
	    echo "There are $(( $(eval "wc -l < ${tmp}") - 1 )) jobs remaining"
	    sleep 10
	done
	l=-1
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"  
	sleep 30
	for j in "${augerID[@]}"
	do
	    l=$(( $l + 1 ))
	    output=${rtype}_${rnum[$l]}.out
	    check="/home/trottar/.farm_out/${rtype}_${rnum[$l]}.$j.err"
	    #echo "error file is $check"
	    if [ -e "$check" ]; then
		echo "ID-$j (run ${rnum[$l]}) is ready to print to file"
		echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" >> ${output}
		echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" >> ${output}
		echo "Errors..." >> ${output}
		echo " " >> ${output}
		cat /home/trottar/.farm_out/${rtype}_${rnum[$l]}.$j.err >> ${output}
		echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" >> ${output}
		echo "Job info..." >> ${output}
		echo " " >> ${output}
		eval "jobinfo $j 2>/dev/null" >> ${output}
		echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" >> ${output}
		echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" >> ${output}
		mv ${output} batch_OUTPUT/
	    else
		echo "File not found [ID-$j]"		      
	    fi
	done	
    fi
    cp /dev/null ${tmp}

done < "$inputFile"

) 2>&1 | tee ${historyfile}

mv ${historyfile} batch_OUTPUT/

echo ""
echo "###############################################################################################################"
echo "############################################# ALL JOBS COMPLETED ##############################################"
echo "###############################################################################################################"
