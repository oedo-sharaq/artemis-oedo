#!/bin/csh

set runnum=$1
set COPYDIR="run"$runnum

mkdir $COPYDIR

if($2 == 0)then
cp -vi ../../test/TTT.txt       $COPYDIR/ttt.front.txt
cp -vi ../../test/TTT_param.txt $COPYDIR/ttt_param.front.txt
cp -vi ../../test/TTT_calib.txt $COPYDIR/ttt_calib.front.txt
else
cp -vi ../../test/TTT.txt       $COPYDIR/ttt.back.txt
cp -vi ../../test/TTT_param.txt $COPYDIR/ttt_param.back.txt
cp -vi ../../test/TTT_calib.txt $COPYDIR/ttt_calib.back.txt
endif

ls -rlth $COPYDIR
