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


dc31_prm_dir="/home/sh13/art_analysis/user/$2/prm/mwdc/dc31/dt2dl"
cd $dc31_prm_dir
if [ -d $1 ] ; then
    echo dc31_prm $1 is current
    rm -f current
    ln -sf $1 current
else
    echo "$dc31_prm_dir/$1 not found."
fi

dc32_prm_dir="/home/sh13/art_analysis/user/$2/prm/mwdc/dc32/dt2dl"
cd $dc32_prm_dir
if [ -d $1 ] ; then
    echo dc32 $1 is current
    rm -f current
    ln -sf $1 current
else
    echo "$dc32_prm_dir/$1 not found."
fi


dca1_prm_dir="/home/sh13/art_analysis/user/$2/prm/mwdc/dca1/dt2dl"
cd $dca1_prm_dir
if [ -d $1 ] ; then
    echo dca1_prm $1 is current
    rm -f current
    ln -sf $1 current
else
    echo "$dca1_prm_dir/$1 not found."
fi

dca2_prm_dir="/home/sh13/art_analysis/user/$2/prm/mwdc/dca2/dt2dl"
cd $dca2_prm_dir
if [ -d $1 ] ; then
    echo dca2 $1 is current
    rm -f current
    ln -sf $1 current
else
    echo "$dca2_prm_dir/$1 not found."
fi


dc21_prm_dir="/home/sh13/art_analysis/user/$2/prm/mwdc/dc21/dt2dl"
cd $dc21_prm_dir
if [ -d $1 ] ; then
    echo dc21_prm $1 is current
    rm -f current
    ln -sf $1 current
else
    echo "$dc21_prm_dir/$1 not found."
fi

dc22_prm_dir="/home/sh13/art_analysis/user/$2/prm/mwdc/dc22/dt2dl"
cd $dc22_prm_dir
if [ -d $1 ] ; then
    echo dc22 $1 is current
    rm -f current
    ln -sf $1 current
else
    echo "$dc22_prm_dir/$1 not found."
fi


sr91_prm_dir="/home/sh13/art_analysis/user/$2/prm/srppac/sr91/dq2dx"
cd $sr91_prm_dir
if [ -d $1 ] ; then
    echo sr91_prm $1 is current
    rm -f current
    ln -sf $1 current
else
    echo "$sr91_prm_dir/$1 not found."
fi

sr92_prm_dir="/home/sh13/art_analysis/user/$2/prm/srppac/sr92/dq2dx"
cd $sr92_prm_dir
if [ -d $1 ] ; then
    echo sr92_prm $1 is current
    rm -f current
    ln -sf $1 current
else
    echo "$sr92_prm_dir/$1 not found."
fi

src1_prm_dir="/home/sh13/art_analysis/user/$2/prm/srppac/src1/dq2dx"
cd $src1_prm_dir
if [ -d $1 ] ; then
    echo src1_prm $1 is current
    rm -f current
    ln -sf $1 current
else
    echo "$src1_prm_dir/$1 not found."
fi

src2_prm_dir="/home/sh13/art_analysis/user/$2/prm/srppac/src2/dq2dx"
cd $src2_prm_dir
if [ -d $1 ] ; then
    echo src2_prm $1 is current
    rm -f current
    ln -sf $1 current
else
    echo "$src2_prm_dir/$1 not found."
fi


sr0_prm_dir="/home/sh13/art_analysis/user/$2/prm/srppac/sr0/dq2dx"
cd $sr0_prm_dir
if [ -d $1 ] ; then
    echo sr0_prm $1 is current
    rm -f current
    ln -sf $1 current
else
    echo "$sr0_prm_dir/$1 not found."
fi


cd ../..
