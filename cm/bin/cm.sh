#!/bin/sh -
#
# File:           cm.sh
#
SUMMARY="         run Common Music"
#
# Author:         Tobias Kunze Briseño
# E-Mail:         t AT fictive DOT com
# Org:            
#
# $Source$
# $Date$
# $Revision$

# Defaults

: ${CM_EDITOR:=}
: ${CM_RUNTIME:=}
: ${CM_RUNTIME_PREFS:=openmcl lisp acl clisp guile}

: ${CM_OS:=}
: ${CM_ARCH:=}
: ${CM_RUNTIME_FLAVOR:=}
: ${CM_RUNTIME_VERSION:=}
: ${CM_ROOT_DIR:=}


# Description --------------------------------------------------------------
OPTIONS="
    -h           print this help
    -q           don't run cm, only echo platform as 'os-arch' string
    -n           dry run
    -v           be verbose
    -e editor    run under this editor (default: '${CM_EDITOR:-<none>}')
    -l lisp      run this Lisp/Scheme (default: '${CM_RUNTIME:-<unset>}') 
    -P prefs	 preferred runtimes (default: '$CM_RUNTIME_PREFS')
    -O OS        OS in case autodetection fails
    -A arch      machine architecture in case autodetection fails
    -F flavor    Lisp flavor in case autodetection fails
    -V version   Lisp version in case autodetection fails
    -R cmroot    Common Music root directory in case autodetection fails
"
DESCRIPTION="
    This script starts Common Music (cm) either by loading it into a fresh
    Lisp session or by launching an existing image that has been built with
    cm pre-loaded.  The cm process can be run in a terminal or as a
    subprocess of any Emacs-compatible editor such as xemacs(1), emacs(1),
    or gnuclient(1).

    Since parameters are autodetected at runtime, it should in virtually all
    cases suffice to call it without any arguments.  However, autodetection
    may be overridden via options and the following environment variables.

      CM_EDITOR
        Name or path of an Emacs-compatible editor under which to run cm,
        e.g. 'xemacs' or '/usr/bin/gnuclient'.  Same as -e option.

      CM_RUNTIME
        Name or path of a Lisp or Scheme system to execute, e.g. 'clisp' or
        '/usr/bin/openmcl'.  Same as -l option.

      CM_RUNTIME_PREFS
        List of CM_RUNTIMEs to try during autodetection, in order of
        preference.  Same as -r option.

      CM_OS
        Symbolic name of host OS, e.g. 'linux' or 'darwin'.  Same as -O
        option.

      CM_ARCH
        Symbolic name of host architecture, e.g. 'i386' or 'powerpc'.  Same
        as -A option.

      CM_RUNTIME_FLAVOR
        Symbolic name of the Lisp/Scheme flavor to run, e.g. 'clisp' or
        'cmucl'.  Useful in conjuction with CM_RUNTIME or the -l option if
        the flavor can't be derived from the command name or path.  Same as
        -F option.

      CM_RUNTIME_VERSION
        Version of the Lisp/Scheme to run.  Useful in conjuction
        with CM_RUNTIME or the -l option if the version can't be derived from
        the command name or path.  Same as -V option.

      CM_ROOT_DIR
        Absolute path of the Common Music root directory in case
        autodetection fails.  Same as -R option.


    Requirements: getopts, ls, sed, sh, tr, uname, which; a working
    installation of a Lisp or Scheme runtime; the '-repl' option if clisp is
    used (clisp 2.31 or higher).
"

# --------------------------------------------------------------------------


#
# Utils
# -----

imatch_head_token () {
  test `echo $1 | tr '[A-Z]' '[a-z]' | sed 's/[^a-z].*//;'` = $2
}
imatch_end_token () {
  test `echo $1 | tr '[A-Z]' '[a-z]' | sed 's/.*[^a-z]//;'` = $2
}

msg_i () { echo "[Notice ]  $*" > /dev/stderr ;         }
msg_w () { echo "[Warning]  $*" > /dev/stderr ;         }
msg_e () { echo "[Error  ]  $*" > /dev/stderr ;         }
msg_f () { echo "[Fatal  ]  $*" > /dev/stderr ;         }
msg_x () { echo "$*"            > /dev/stderr ; exit 1; }

canonicalize_string () {
  echo $* | tr 'A-Z/ ' 'a-z_'
}

sanitize_path () {
  echo "$1" | sed 's: :\ :g;'
}

CM_PLATFORM=
OSX_EMACS=/Applications/Emacs.app/Contents/MacOS/Emacs

resolve_bin () {
  # OSX Emacs: check /Applications/Emacs.app first
  if [ $CM_PLATFORM ] && 
     imatch_head_token $CM_PLATFORM darwin &&
     imatch_end_token $1 emacs && 
     [  -x $OSX_EMACS ] ; then 
    echo $OSX_EMACS
  elif which $1 > /dev/null 2>&1 ; then
    which $1
  else
    test $2 && msg_w "'$1' not found in PATH ($PATH)."
    echo ""
  fi
}

UNAME=`resolve_bin uname`


#
# Requirements
# ------------

# Cygwin MUST use bash
if [ $RE_EXECING ] ; then
  unset RE_EXECING
else
  if [ $UNAME ] && imatch_head_token `$UNAME -s` cygwin ; then
    BASH_EXE=`resolve_bin bash WARN`
    if [ ! $BASH_EXE ] ; then
      msg_f "Cygwin: 'sh' broken and can't find 'bash'!  Install bash first."
      msg_x "Aborting. "
    fi
    export RE_EXECING=1 
    exec $BASH_EXE -- $0 "$@"
  fi
fi


#
# Help
# ----

CMD=`basename $0`
USAGE="
  Usage: $CMD -h
         $CMD [-qnv] [-e editor] [-l lisp] [-P prefs] [-O OS] [-A arch]
               [-F lisp-flavor] [-V lisp-version] [-R cmroot]
"

print_help() {
  echo ""
  echo "  $CMD --"$SUMMARY
  echo "$USAGE"
  echo "  Options:"
  echo "$OPTIONS"
  echo "$DESCRIPTION"
}


#
# Variables
# ---------

QUERY_PLATFORM=
EXEC=exec
VERBOSE=

EDITOR_OPT=$CM_EDITOR
LISP_OPT=$CM_RUNTIME
LISP_PREFS=$CM_RUNTIME_PREFS
OS=$CM_OS
ARCH=$CM_ARCH
LISP_FLV=$CM_RUNTIME_FLAVOR
LISP_VRS=$CM_RUNTIME_VERSION

PAGER=`which less 2>/dev/null || which more 2>/dev/null || echo cat`

IMG_NAME=cm
IMG_SUFFIX=.img



#
# Options
# -------

while getopts hqnve:l:P:O:A:F:V:R: OPT
do
  case $OPT in
    h)  print_help | $PAGER
        exit 2
        ;;
    q)  QUERY_PLATFORM=1 ;;
    n)  EXEC=true ;;
    v)  VERBOSE=1 ;;
    e)  EDITOR_OPT=$OPTARG ;;
    l)  LISP_OPT=$OPTARG ;;
    P)  LISP_PREFS=$OPTARG ;;
    O)  OS=$OPTARG ;;
    A)  ARCH=$OPTARG ;;
    F)  LISP_FLV=$OPTARG ;;
    V)  LISP_VRS=$OPTARG ;;
    R)  CM_ROOT_DIR=$OPTARG ;;
    \?) echo "$USAGE"
        exit 1 ;;
  esac    
done

shift `expr $OPTIND - 1`


#
# Path Detection
# --------------

real_path () {
  if [[ "$1" == /* ]] ; then
    CHK="$1"
  elif [ -z "$1" ] ; then
    CHK="$CWD"
  else
    CHK="$CWD/$1"
  fi
  if [ -e "$CHK" ] ; then
    sanitize_path "$CHK"
  else 
    echo ''
  fi
}


# Resolve symbolic links
if test -L $0 ; then
  ARGV0=`\ls -l $0 | sed 's/.*-> //;'`
else
  ARGV0="$0"
fi

CWD=`pwd`
PTU=`echo $ARGV0 | sed 's:[^/]*$::;s:\(.\)/$:\1:;'`
LOC=`real_path "$PTU"`

if [ ! $LOC ] ; then
  msg_e "No such file or directory: '$1'"
  msg_f "Can't determine CM_ROOT_DIR!"
  msg_x "Aborting.  Re-run with -R option."
else
  LOC="$LOC/.."			# we are now in cm/bin, so get back out of it
  export CM_ROOT_DIR=$LOC
  export CM_ROOT=$LOC		# backwards compat
fi


#
# Platform Detection
# ------------------

if [ ! "$OS" ] ; then
  if which uname > /dev/null 2>&1 ; then
    for flag in s o ; do
      OS=`uname -$flag 2>/dev/null`
      if [[ ! "$OS" || "$OS" == unknown ]] ; then OS= ; else break ; fi
    done
  fi
  if [ ! "$OS" ] ; then
    msg_e "Can't detect OS type."
    msg_i "Pass in -O option or set OS environment variable."
    msg_x "Aborting."
  fi
  OS=`canonicalize_string "$OS"`
fi

if [ ! "$ARCH" ] ; then
  if which uname > /dev/null 2>&1 ; then
    for flag in p m i ; do
      ARCH=`uname -$flag`
      if [[ "$ARCH" = unknown ]] ; then ARCH= ; else break ; fi
    done
  fi
  if [ ! "$ARCH" ] ; then
    msg_e "Can't detect ARCH type."
    msg_i "Pass in -A option or set ARCH environment variable."
    msg_x "Aborting."
  fi
  ARCH=`canonicalize_string "$ARCH"`
fi

export CM_PLATFORM="$OS-$ARCH"

if [ $QUERY_PLATFORM ] ; then
  echo $CM_PLATFORM
  exit 0;
fi


#
# Lisp Detection
# --------------
# Determine which Lisp/Scheme to start:
#
#   { <lisp> { <initform> | <memdump> } | <image> }

LISP_EXE=
LISP_IMG=
LISP_DIA=LISP
LOAD=1

is_image () {
  [[ $1 == */${IMG_NAME}.* ]]
}

find_lisp () {
  resolve_bin $1 $3		# FIXME version ($2) is ignored for now
}

get_lisp_info () {
  # This is ugly, wasteful and probably requires future maintenance :(
  case $1 in
    *clisp*|*CLISP*)
      vrs=`$1 --version | head -1 | cut -d' ' -f3`
      min=`echo -e "$vrs\n2.31" | sort -n | head -1`
      if [ $min != 2.31 ] ; then
        msg_f "$1: version '$vrs' unsupported."
        msg_i "Need clisp with -repl option (version 2.31 or higher)."
        msg_x "Aborting."
      fi
      echo clisp_$vrs
      ;;
    *acl*|*ACL*)
      echo acl_`echo '(lisp-implementation-version)' | $1 -batch | sed -n 's/^.*"\([0-9.]*\) .*/\1/p'`
      ;;
    *lisp*|*LISP*|*cmucl*|*CMUCL*)
      echo cmucl_`echo '(lisp-implementation-version)' | $1 -quiet -batch | sed -n 's/^.*[^0-9]\([0-9][0-9]*[a-z]\).*/\1/p;'`
      ;;
    *openmcl*|*OPENMCL*|*dppccl*)
      echo openmcl_`echo '(lisp-implementation-version)' | $1 -b | sed -n 's/^".* \([0-9.]*\)"/\1/p'` 
      ;;
    *guile*)
      LISP_DIA=SCHEME
      echo guile_`$1 --version | head -1 | cut -d' ' -f2`
      ;;
    *)
      if [ $LISP_FLV -a $LISP_VRS ] ; then
        echo ${LISP_FLV}_${LISP_VRS}
      else
        msg_e "Unknown implementation '$1'.  Re-run with -F and -V options."
        msg_x "Exiting."
      fi
      ;;
  esac
}

if [ "$LISP_OPT" ] ; then
  if [[ "$LISP_OPT" == */* ]] ; then
    thing=`real_path "$LISP_OPT"`
    if [ ! $thing ] ; then
      msg_e "No such file or directory: '$LISP_OPT'"
    fi
  else
    thing=`resolve_bin "$LISP_OPT" WARN`
  fi
  if [ ! $thing ] ; then
    msg_x "Aborting."
  elif [ ! -f $thing -a ! -h $thing ] ; then
    msg_e "Not a file or link: '$thing'"
    msg_x "Aborting."
  fi
  
  if is_image $thing ; then
    LISP_INF=`echo $thing | sed 's:^.*/\([^/]*\)/[^/]*$:\1:;'`
    if [ ! $LISP_INF ] ; then
      msg_e "Not in proper location: '$thing'."
      msg_x "Aborting."
    fi
    LISP_FLV=`echo $LISP_INF | sed 's:\([^_]*\)_.*$:\1:;'`
    LISP_VRS=`echo $LISP_INF | sed 's:[^_]*_\([^_]*\)_.*:\1:;'`
    if [ -x $thing ] ; then
      LISP_EXE=$thing
      LISP_IMG=
      LOAD=
    else
      LISP_EXE=`find_lisp $LISP_FLV $LISP_VRS WARN`
      if [ $LISP_EXE ] ; then
        LISP_IMG=$thing
        LOAD=
      else
        msg_e "Can't find a '$LISP_FLV' executable with version '$LISP_VRS'." 
        msg_x "Aborting."
      fi
    fi
  else
    if [ ! -x $thing ] ; then
      msg_e "Not an executable: '$thing'"
      msg_x "Aborting."
    fi
    LISP_EXE=$thing
    LISP_INF=`get_lisp_info $LISP_EXE`
    if [ $? == 1 ] ; then exit 1 ; fi
    LISP_FLV=`echo $LISP_INF | sed 's:_.*::'`
    LISP_VRS=`echo $LISP_INF | sed 's:.*_::'`
    if [ -e $LOC/bin/${LISP_INF}_${CM_PLATFORM}/$IMG_NAME.$IMG_SUFFIX ] ; then
      LISP_IMG=$LOC/bin/${LISP_INF}_${CM_PLATFORM}/$IMG_NAME.$IMG_SUFFIX
      LOAD=
    else
      LISP_IMG=
      LOAD=1
    fi        
  fi
else
  if ls $LOC/bin/*_*_$CM_PLATFORM/$IMG_NAME.* > /dev/null 2>&1 ; then
    for pref in $LISP_PREFS ; do
      for img in `ls $LOC/bin/${pref}_*_$CM_PLATFORM/$IMG_NAME.* 2>/dev/null` ; do
        LISP_INF=`echo $img | sed 's:^.*/\([^/]*\)/[^/]*$:\1:;'`
	LISP_FLV=`echo $LISP_INF | sed 's:\([^_]*\)_.*$:\1:;'`
	LISP_VRS=`echo $LISP_INF | sed 's:[^_]*_\([^_]*\)_.*:\1:;'`
        if [ -x $img ] ; then
          LISP_EXE=$img
          LISP_IMG=lllllllllllllllll
          LOAD=
          break
        else
	  LISP_EXE=`find_lisp $LISP_FLV $LISP_VRS`
	  if [ $LISP_EXE ] ; then
	    LISP_IMG=$img
	    LOAD=
	    break
          fi
        fi
        LISP_FLV=
        LISP_VRS=
      done
      if [ $LISP_EXE ] ; then break ; fi
    done
  fi

  if [ ! $LISP_EXE ] ; then
    for pref in $LISP_PREFS ; do
      LISP_EXE=`find_lisp $pref`
      if [ $LISP_EXE ] ; then
	LISP_INF=`get_lisp_info $LISP_EXE`
	if [ $? == 1 ] ; then exit 1 ; fi
	LISP_FLV=`echo $LISP_INF | sed 's:_.*::'`
	LISP_VRS=`echo $LISP_INF | sed 's:.*_::'`
        LOAD=1
        break
      fi
    done
  fi
fi

if [ ! $LISP_EXE ] ; then 
  msg_e "No executable found."
  msg_x "Aborting."
fi


#
# Lisp Command Line Assembly
# --------------------------
# Syntax:
# 
#   <lisp> <options> <initform>
#
# this is also the place to add implementation-specific provisions.

LISP_CMD=
LISP_INI=
LISP_EVL="(progn (load \"$CM_ROOT/src/cm.lisp\" :verbose nil) (cm))"

case $LISP_FLV in
  clisp)
    LISP_CMD="$LISP_EXE -I -q -ansi"
    if [ $LOAD ] ; then
      LISP_CMD="$LISP_CMD -x '$LISP_EVL' -x t -repl"
    else
      test $LISP_INI && LISP_INI="-i $LISP_INI"
      LISP_CMD="$LISP_CMD -M $LISP_IMG $LISP_INI"
    fi
    ;;
  acl)
    LISP_CMD="$LISP_EXE"
    if [ $LOAD ] ; then
      LISP_CMD="$LISP_CMD -e '$LISP_EVL'"
    else
      test $LISP_INI && LISP_INI="-L $LISP_INI"
      LISP_CMD="$LISP_CMD -I $LISP_IMG $LISP_INI"
    fi
    ;;
  cmucl)
    LISP_CMD="$LISP_EXE"
    if [ $LOAD ] ; then
      LISP_CMD="$LISP_CMD -eval '$LISP_EVL'"
    else
      test $LISP_INI && LISP_INI="-init $LISP_INI"
      LISP_CMD="$LISP_CMD -core $LISP_IMG $LISP_INI"
    fi
    ;;
  openmcl)
    LISP_CMD="$LISP_EXE"
    if [ $LOAD ] ; then
      LISP_CMD="$LISP_CMD --eval '$LISP_EVL'"
    else
      test $LISP_INI && LISP_INI="--load $LISP_INI"
      LISP_CMD="$LISP_CMD --image-name $LISP_IMG $LISP_INI"
    fi
    ;;
  guile)
    LISP_CMD="$LISP_EXE -l '$CM_ROOT/src/cm.scm' -e cm"
    ;;
  *)
    msg_e "Don't know how to call '$LISP_FLV' yet... =:("
    msg_x "Please tell me."
    ;;
esac


#
# Editor Detection & Command Line Assembly
# ----------------------------------------

EDITOR_EXE=
EDITOR_CMD=

under_editor () {
  test $EMACS
}

if [ $EDITOR_OPT ] ; then
  if under_editor ; then
    EDITOR_EXE=
    EDITOR_CMD=
  else
    EDITOR=`resolve_bin $EDITOR_OPT WARN`
    if [ ! $EDITOR ] ; then
      msg_w "Command not found: '$EDITOR_OPT'.  Ignoring."
      EDITOR_EXE=
      EDITOR_CMD=
    else
      EL1="$LOC/etc/xemacs/listener.el"
      EL2="$LOC/etc/xemacs/cm.el"
      LCM=`echo $LISP_CMD | sed 's:":\\\":g;' | tr -d "'"`
      INI="(progn (load \"$EL1\") (load \"$EL2\") (lisp-listener \"$LCM\"))"
      EDITOR_EXE=$EDITOR
      EDITOR_CMD="$EDITOR_EXE -eval '$INI'"
      if [[ $EDITOR_EXE == *gnuclient ]] ; then
        EDITOR_CMD="$EDITOR_CMD -batch"
      fi
    fi
  fi
fi


#
# All Systems Go
# --------------
# Final command line syntax is:
# 
#   [ <editorcmd> | run_in_editor ] \
#     { LISP { LOAD [ DUMP ; RESTART_CM_IMAGE=> ] } | [ LISP ] CM_IMAGE }

if [ $VERBOSE ] ; then
  echo "LISP_EXE:    '$LISP_EXE'"
  echo "LISP_FLV:    '$LISP_FLV'"
  echo "LISP_VRS:    '$LISP_VRS'"
  echo "LISP_IMG:    '$LISP_IMG'"
  echo "LOAD:        '$LOAD'"
  echo "LISP_CMD:    '$LISP_CMD'"
  echo "EDITOR_CMD:  '$EDITOR_CMD'"
fi

if [ "$EDITOR_CMD" ] ; then
  test $VERBOSE && echo "exec $EDITOR_CMD"
  eval $EXEC $EDITOR_CMD
else
  test $VERBOSE && echo "exec $LISP_CMD"
  eval $EXEC $LISP_CMD
fi

#
# EOF
