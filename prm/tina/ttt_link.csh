#!/bin/csh

set runnum=$1
set COPYDIR="run"$runnum

ln -sf $COPYDIR/ttt.front.txt       ttt.front.txt
ln -sf $COPYDIR/KW_ttt_param.front.txt ttt_param.front.txt
ln -sf $COPYDIR/ttt_calib.front.txt ttt_calib.front.txt

ln -sf $COPYDIR/ttt.back.txt       ttt.back.txt
ln -sf $COPYDIR/KW_ttt_param.back.txt ttt_param.back.txt
ln -sf $COPYDIR/ttt_calib.back.txt ttt_calib.back.txt


