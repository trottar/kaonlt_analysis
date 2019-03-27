#! /bin/bash

runNum=$1

oldroot="OUTPUT/trigPlots_${runNum}_all.root"

echo
echo "Removing $oldroot ..."
echo
rm $oldroot
echo
eval "root -l -b -q \"chain_TDC.C($runNum)\""
echo
echo "Opening TBrowser.."
echo
eval "root -l $oldroot"<<-EOF
new TBrowser
EOF
