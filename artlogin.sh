#!/bin/sh 

if [ _$1 = _ ] ; then
    echo "usage: artlogin username"
    return 1
#    exit 1
fi

if [ x$ART_ANALYSIS_DIR = x"" ] ; then
    echo " set environmental value ART_ANALYSIS_DIR"
    return 1
else
    artemis_dir=$ART_ANALYSIS_DIR
fi

if [ x$ART_USER_REPOS = x"" ] ; then
    echo " set environmental value ART_USER_REPOS to point the URL of user source repository"
    return 1
else
    reposdir=${ART_USER_REPOS}
fi    

if [ -z ${ART_DATA_DIR+x} ]; then
    echo " set ART_DATA_DIR to point the data directory"
    return 1
fi

username=$1
userdir=$artemis_dir/user/$username

alias acd='cd ${ARTEMIS_WORKDIR}'

export ARTEMIS_USER=$username
export ARTEMIS_WORKDIR=$userdir

if [ -d $userdir ] ; then
    cd $userdir
    export ART_USER_FULLNAME="`git config user.name`"
    export ART_USER_EMAIL=`git config user.email`
    return 0
#    exec zsh
#    exit 0
#    exit 0
elif [ -e $userdir ] ; then
    echo "error: file $userdir exist."
    return 1
#    exit 1
fi

echo "user '$1' not found."

while true; do
    echo -n "create new user? (y/n): "
    read answer
    case $answer in
	y)
	    break
	    ;;
	n)
	    echo "cancelled."
	    return 0
	    ;;
    esac
done

git clone $reposdir $userdir
cd $userdir
yes '' | git flow init > /dev/null
git submodule init
git submodule update

while true; do
    echo -n "input fullname: "
    read fullname
    echo -n "OK? (y/n): "
    read answer
    case $answer in
	y)
	    break
	    ;;
    esac
done

git config user.name "$fullname"

while true; do
    echo -n "input email address: "
    read email
    echo -n "OK? (y/n): "
    read answer
    case $answer in
	y)
	    break
	    ;;
    esac
done

git config user.email "$email"

if [ -z ${ART_DATA_DIR+x} ]; then
    echo "a"
else
    if [ -d ${ART_DATA_DIR} ]; then
	ln -s $ART_DATA_DIR ridf
	echo symbolic link ridf to directory ${ART_DATA_DIR} created
    else
	echo Warning: directory ${ART_DATA_DIR} does not exist
    fi
fi

ln -s $ART_SHARE_DIR share

echo -n "compiling sources .."
mkdir build
pushd build >> /dev/null && cmake .. && make -j install && popd >> /dev/null
if [ "$?" != "0" ]; then
echo failed
else
echo done
fi

source thisartemis-oedo.sh

cat <<EOF

new user '$1' created.
If you want to use some editor other than vi, set core.editor in git configuration.

example: git config core.editor 'emacs -nw'

EOF

#cd $userdir

#exec zsh
