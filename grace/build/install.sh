#!/bin/bash

# install.sh: Grace runtime support installation script.
# Directions: Build the application(s), copy this script into your OS
# subdirectory and call it with the appropiate argument, eg:
#
# $ cp ../install.sh linux
# $ cd linux
# $ ./install.sh Grace
# $ ./install.sh GraceCL

# Note: when this script installs GraceCL runtime support it uses curl
# and ftp to download the bundled software systems CM CLM and FOMUS
# from the internet into the resource directory.

CHOICE=
CONFIG="Release"
OSNAME=`uname`
GRACE1="Grace"
GRACE2="GraceCL"

case "$1" in
    Grace) CHOICE=1 ;;
    GraceCL) CHOICE=2 ;;
    all) CHOICE=3 ;;
    *) echo usage: install.sh [Grace "|" GraceCL "|" all ]
    exit 1
    ;;
esac

case "$OSNAME" in
    Darwin) 
	RESDIR1="build/Release/${GRACE1}.app/Contents/Resources"
	RESDIR2="build/Release/${GRACE2}.app/Contents/Resources"
	;;
    Linux)
	RESDIR1="build/Release/${GRACE1}/lib/$GRACE1"
	RESDIR2="build/Release/${GRACE2}/lib/$GRACE2"
	;;
    MINGW*)
	RESDIR1="build/$GRACE1/Resources"
	RESDIR2="build/$GRACE2/Resources"
	;;
    *) 	echo install.sh: unsupported OS: $OSNAME
	exit 1
	;;
esac

install_doc () {
    # create doc directorys under the resource dir
    for d in `find ../../doc \( \( -name ".svn" -prune \) -or \( -type d -print \) \)` 
    do
	dd="$1"/`echo $d | sed s/^[..\/]*//`
	mkdir -p "$dd"
    done
    # copy doc files if they dont exist or are newer than resourced
    for f in `find ../../doc \( \( -name ".svn" -prune \) -or \( -type f -print \) \)` 
    do
	ff="$1"/`echo $f | sed s/^[../]*//`
	if [[ ! -e "$ff" || "$f" -nt "$ff" ]] ; then
	    cp -v "$f" "$ff"
	fi
    done
}

#
# Grace resources:
#

if [[ "$CHOICE" == 1 || "$CHOICE" == 3 ]] ; then
    if [[ ! -d "$RESDIR1" ]] ; then
	mkdir "$RESDIR1"
    fi
    install_doc "$RESDIR1"

    mkdir -p "$RESDIR1"/csound
    # install lisp runtime
    for f in $( ls ../../src/*.orc  )
    do
	ff="$RESDIR1"/csound`echo "$f" | sed 's/^[..\/]*src//'`
	if [[ ! -e "$ff" || "$f" -nt "$ff" ]] ; then
	    cp -v "$f" "$ff"
	fi
    done
fi

#
# GraceCL resources:
#

if [[ "$CHOICE" == 2 || "$CHOICE" == 3 ]] ; then
    if [[ ! -d "$RESDIR2" ]] ; then
	mkdir "$RESDIR2"
    fi
    install_doc "$RESDIR2"
    mkdir -p "$RESDIR2"/grace
    # install lisp runtime
    for f in $( ls ../../src/*.lisp ../../src/*.asd )
    do
	ff="$RESDIR2"/grace`echo "$f" | sed 's/^[..\/]*src//'`
	if [[ ! -e "$ff" || "$f" -nt "$ff" ]] ; then
	    cp -v "$f" "$ff"
	fi
    done
    if [[ `which svn` ]] ; then
	if [[ ! -d "$RESDIR2"/cm ]] ; then
	    echo "Downloading CM from Sourceforge with svn:"
	    mkdir "$RESDIR2"/cm
	    svn co "http://commonmusic.svn.sf.net/svnroot/commonmusic/trunk/cm" "$RESDIR2"/cm
	fi
    else
	echo "Warning: no CM installation because svn command does not exist."
    fi
    if [[ `which svn` ]] ; then
	if [[ ! -d "$RESDIR2"/fomus ]] ; then
	    echo "Downloading FOMUS from Common-Lisp.net with svn:"
	    mkdir "$RESDIR2"/fomus
	    svn co "svn://common-lisp.net/project/fomus/svn/fomus/tags/current" "$RESDIR2"/fomus
	fi
    else
	echo "Warning: no FOMUS installation because svn command does not exist."
    fi
    if [[ `which curl` ]] ; then
	if [[ ! -d "$RESDIR2"/clm-3 ]] ; then
	    echo "Downloading CLM from ccrma-ftp with curl:"
	    curl "ftp://ccrma-ftp.stanford.edu/pub/Lisp/clm-3.tar.gz" | ( cd "$RESDIR2" ; tar -xzf - )
	fi
    else
	echo "Warning: no CLM installation because curl command does not exist."
    fi
    chmod -R a+w "$RESDIR2"/*
fi

# EOF
