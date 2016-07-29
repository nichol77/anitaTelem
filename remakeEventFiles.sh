#!/bin/bash
if [ "$2" = "" ]
then
   echo "usage: `basename $0` <start run> <end run>" 1>&2
   exit 1
fi

if [ "$ANITA_TELEM_DATA_DIR" = "" ]
then
   echo "ANITA_TELEM_DATA_DIR must be set to where the raw_los, openport and tdrss directories are"
   exit 1
fi

if [ "$ANITA_TREE_MAKER_DIR" = "" ]
then
   echo "ANITA_TREE_MAKER_DIR must be set"
   exit 1
fi


if [ "$ANITA_AWARE_FILEMAKER_DIR" = "" ]
then
   echo "ANITA_AWARE_FILEMAKER_DIR must be set"
   exit 1
fi




for run in `seq $1 $2`; do
    cd $ANITA_TREE_MAKER_DIR
    rm $ANITA_TELEM_DATA_DIR/root/run${run}/eventHeadFile${run}.root
    rm $ANITA_TELEM_DATA_DIR/root/run${run}/eventFile${run}.root

    ./runTelemEventMaker.sh ${run} $ANITA_TELEM_DATA_DIR/raw/run${run} $ANITA_TELEM_DATA_DIR/root/run${run}

    cd $ANITA_AWARE_FILEMAKER_DIR 
    ./makeWaveformSummaryJsonFiles $ANITA_TELEM_DATA_DIR/root/run${run}/eventHeadFile${run}.root $ANITA_TELEM_DATA_DIR/root/run${run}/eventFile${run}.root


done



