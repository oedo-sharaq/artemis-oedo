#!/bin/env zsh

function usage() {
cat <<EOF
usage: $1 setting_name
usage: $2 user_name
EOF
}

if [ $1_ = _ ] ; then
    usage $0
    exit
fi

dc71_prm_dir="/home/r3_01r1/art_analysis/user/$2/prm/mwdc/dc71/dt2dl"
cd $dc71_prm_dir
if [ -d $1 ] ; then
    echo ln -sf $1 current
    rm -f current
    ln -sf $1 current
else
    echo "$dc71_prm_dir/$1 not found."
fi

dc72_prm_dir="/home/r3_01r1/art_analysis/user/$2/prm/mwdc/dc72/dt2dl"
cd $dc72_prm_dir
if [ -d $1 ] ; then
    echo ln -sf $1 current
    rm -f current
    ln -sf $1 current
else
    echo "$dc72_prm_dir/$1 not found."
fi


sr91_prm_dir="/home/r3_01r1/art_analysis/user/$2/prm/srppac/sr91/dq2dx"
cd $sr91_prm_dir
if [ -d $1 ] ; then
    echo ln -sf $1 current
    rm -f current
    ln -sf $1 current
else
    echo "$sr91_prm_dir/$1 not found."
fi

sr92_prm_dir="/home/r3_01r1/art_analysis/user/$2/prm/srppac/sr92/dq2dx"
cd $sr92_prm_dir
if [ -d $1 ] ; then
    echo ln -sf $1 current
    rm -f current
    ln -sf $1 current
else
    echo "$sr92_prm_dir/$1 not found."
fi

dcc1_prm_dir="/home/r3_01r1/art_analysis/user/$2/prm/mwdc/dcc1/dt2dl"
cd $dcc1_prm_dir
if [ -d $1 ] ; then
    echo ln -sf $1 current
    rm -f current
    ln -sf $1 current
else
    echo "$dcc1_prm_dir/$1 not found."
fi

dcc2_prm_dir="/home/r3_01r1/art_analysis/user/$2/prm/mwdc/dcc2/dt2dl"
cd $dcc2_prm_dir
if [ -d $1 ] ; then
    echo ln -sf $1 current
    rm -f current
    ln -sf $1 current
else
    echo "$dcc2_prm_dir/$1 not found."
fi





cd ../..
