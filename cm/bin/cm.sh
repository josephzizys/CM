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
: ${CM_RUNTIME_PREFS:=openmcl cmucl acl clisp guile}

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
    Lisp or Scheme session or by launching an existing Lisp image that has
    been built with Common Music pre-loaded.  Additionally, this process can
    be run stand-alone in a terminal or as a subprocess of an
    Emacs-compatible editor such as xemacs(1), emacs(1), or gnuclient(1).

    Since the script is designed to autodetect all required parameters at
    runtime, it should in virtually all cases suffice to call it without any
    arguments.  This autodetection however may be customized or overridden
    via options and the following environment variables:

      CM_EDITOR
        Name or path of an Emacs-compatible editor under which to run cm,
        e.g. 'xemacs' or '/usr/bin/gnuclient'.  Same as -e option.

      CM_RUNTIME
        Name or path of a Lisp or Scheme system to execute, e.g. 'clisp' or
        '/usr/bin/openmcl'.  Same as -l option.

      CM_RUNTIME_PREFS
        List of CM_RUNTIME_FLAVORs to try during autodetection, in order of
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

    For autodetection to work, it is important that the script be not moved
    from its location inside the Common Music directory tree.  A 'cm' (or
    similar) command in a standard binary location can be easily provided
    either by creating a symlink or by creating a wrapper shell script, e.g.

      # ln -s '/path/to/Common Music/bin/cm.sh' /usr/local/bin/cm

    or

      # cat <<EOD > /usr/local/bin/cm
      #!/bin/sh
      exec /path/to/cm/bin/cm.sh \"$@\"
      EOD
      # chmod 755 /usr/local/bin/cm

    Requirements: bash(1), cat(1), cut(1), echo(1), head(1), sed(1),
    sort(1), tr(1), uname(1), which(1); getopts and ls; a working
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

msg_i () { echo "[Notice ]  $*" >> /dev/stderr ;         }
msg_w () { echo "[Warning]  $*" >> /dev/stderr ;         }
msg_e () { echo "[Error  ]  $*" >> /dev/stderr ;         }
msg_f () { echo "[Fatal  ]  $*" >> /dev/stderr ;         }
msg_x () { echo "$*"            >> /dev/stderr ; exit 1; }

canonicalize_string () {
  echo $* | tr 'A-Z/ ' 'a-z_'
}

sanitize_path () {
  echo "$1" #| sed 's: :\\ :g;'
}

CM_PLATFORM=
OSX_EMACS=/Applications/Emacs.app/Contents/MacOS/Emacs

resolve_bin () {
  # OSX Emacs: check /Applications/Emacs.app first
  if test $CM_PLATFORM && 
     imatch_head_token $CM_PLATFORM darwin &&
     imatch_end_token $1 emacs && 
     test -x $OSX_EMACS ; then 
    echo $OSX_EMACS
  else
    # can't use return code b/c cygwin 'which' is broken
    EXE=`which "$1" 2>/dev/null`
    if test -z "$EXE" ; then
      test $2 && msg_w "'$1' not found in PATH ($PATH)."
      echo ""
    else
      which "$1"
    fi
  fi
}

UNAME=`resolve_bin uname`


#
# Requirements
# ------------

# Cygwin MUST use bash
if test $BASH || test $RE_EXECING ; then
  unset RE_EXECING
else
  if test $UNAME && imatch_head_token `$UNAME -s` cygwin ; then
    BASH_EXE=`resolve_bin bash WARN`
    if [ ! $BASH_EXE ] ; then
      msg_f "Cygwin: 'sh' broken and can't find 'bash'!  Install bash first."
      msg_x "Aborting. "
    fi
    export RE_EXECING=1 
    exec $BASH_EXE -- "$0" "$@"
  fi
fi


#
# Help
# ----

CMD=`basename "$0"`
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

IMG_NAME=cm.img


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
if test -L "$0" ; then
  ARGV0=`\ls -l "$0" | sed 's/.*-> //;'`
else
  ARGV0="$0"
fi

CWD=`pwd`

if [ "$CM_ROOT_DIR" ] ; then
  LOC="$CM_ROOT_DIR"
else
  PTU=`echo "$ARGV0" | sed 's:[^/]*$::;s:\(.\)/$:\1:;'`
  LOC=`real_path "$PTU"`
  if [ ! "$LOC" ] ; then
    msg_e "No such file or directory: '$1'"
    msg_f "Can't determine CM_ROOT_DIR!"
    msg_x "Aborting.  Re-run with -R option."
  else
    LOC="$LOC/.."		# we are now in cm/bin, so get back out of it
  fi
fi

export CM_ROOT_DIR="$LOC"
export CM_ROOT="$LOC"		# backwards compat


#
# Platform Detection
# ------------------

if [ ! "$OS" ] ; then
  if which uname > /dev/null 2>&1 ; then
    for flag in s o ; do
      if uname -$flag >/dev/null 2>&1 ; then
	OS=`uname -$flag 2>/dev/null`
	if [[ ! "$OS" || "$OS" == unknown ]] ; then OS= ; else break ; fi
      fi
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
      if uname -$flag >/dev/null 2>&1 ; then
        ARCH=`uname -$flag 2>/dev/null`
        if [[ "$ARCH" = unknown ]] ; then ARCH= ; else break ; fi
      fi
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
  case $1 in
    cmucl) bin=lisp ;;
    *)     bin=$1 ;;
  esac
  resolve_bin $bin $3		# FIXME version ($2) is ignored for now
}

get_lisp_info () {
  if test $LISP_VRS ; then
    if test $LISP_FLV ; then
      echo ${LISP_FLV}_${LISP_VRS}
    else
      case "$1" in
	*clisp*|*CLISP*)		      flv=clisp ;;
	*acl*|*ACL*)		      flv=acl ;;
	*lisp*|*LISP*|*cmucl*|*CMUCL*)  flv=cmucl ;;
	*openmcl*|*OPENMCL*|*dppccl*)   flv=openmcl ;;
	*guile*)                        flv=guile ;;
	*)
	  msg_e "Can't determine flavor of '$1'.  Re-run with -F option."
	  msg_x "Exiting."
	  ;;
      esac
      echo ${flv}_$LISP_VRS
    fi
  else
    # This is ugly, wasteful, and requires maintenance :(
    q='echo '"'(lisp-implementation-version)'"' | "$1"'
    case "${LISP_FLV:-$1}" in
      *clisp*|*CLISP*)
        flv=clisp
        vrs=`"$1" --version | head -1 | cut -d' ' -f3`
        min=`echo -e "$vrs\n2.31" | sort -n | head -1`
        if [ $min != 2.31 ] ; then
          msg_f "$1: version '$vrs' unsupported."
          msg_i "Need clisp with -repl option (version 2.31 or higher)."
          msg_x "Aborting."
        fi
        ;;
      *acl*|*ACL*)
        flv=acl
        vrs=`echo '(lisp-implementation-version)' | "$1" -batch 2>/dev/null \
             | sed -n 's/^.*"\([^ ]*\) .*/\1/p'`
        ;;
      *lisp*|*LISP*|*cmucl*|*CMUCL*)
        flv=cmucl
        vrs=`echo '(lisp-implementation-version)' | "$1" -quiet -batch \
             | sed -n 's/^.*[^0-9]\([0-9][0-9]*[a-z]\).*/\1/p'`
        ;;
      *openmcl*|*OPENMCL*|*dppccl*)
        flv=openmcl
        vrs=`echo '(lisp-implementation-version)' | "$1" -b \
             | sed -n 's/.* \([-0-9.]*\)".*/\1/p'`
        ;;
      *guile*)
        LISP_DIA=SCHEME
        flv=guile
        vrs=`"$1" --version | head -1 | cut -d' ' -f2`
        ;;
    esac
    if test $vrs ; then
      echo ${flv}_${vrs}
    else
      msg_e "Can't detect version of '$1'.  Re-run with -V option."
      msg_x "Exiting."
    fi
  fi
}

if [ "$LISP_OPT" ] ; then
  if [[ "$LISP_OPT" == */* ]] ; then
    thing=`real_path "$LISP_OPT"`
    if [ ! "$thing" ] ; then
      msg_e "No such file or directory: '$LISP_OPT'"
    fi
  else
    thing=`resolve_bin "$LISP_OPT" WARN`
  fi
  if [ ! "$thing" ] ; then
    msg_x "Aborting."
  elif [ ! -f "$thing" -a ! -h "$thing" ] ; then
    msg_e "Not a file or link: '$thing'"
    msg_x "Aborting."
  fi
  
  if is_image "$thing" ; then
    LISP_INF=`echo "$thing" | sed 's:^.*/\([^/]*\)/[^/]*$:\1:;'`
    if [ ! $LISP_INF ] ; then
      msg_e "Not in proper location: '$thing'."
      msg_x "Aborting."
    fi
    LISP_FLV=`echo $LISP_INF | sed 's:\([^_]*\)_.*$:\1:;'`
    LISP_VRS=`echo $LISP_INF | sed 's:[^_]*_\([^_]*\)_.*:\1:;'`
    if [ -x "$thing" ] ; then
      LISP_EXE="$thing"
      LISP_IMG=
      LOAD=
    else
      LISP_EXE=`find_lisp $LISP_FLV $LISP_VRS WARN`
      if [ "$LISP_EXE" ] ; then
        LISP_IMG="$thing"
        LOAD=
      else
        msg_e "Can't find a '$LISP_FLV' executable with version '$LISP_VRS'." 
        msg_x "Aborting."
      fi
    fi
  else
    if [ ! -x "$thing" ] ; then
      msg_e "Not an executable: '$thing'"
      msg_x "Aborting."
    fi
    LISP_EXE="$thing"
    LISP_INF=`get_lisp_info "$LISP_EXE"`
    if [ $? == 1 ] ; then exit 1 ; fi
    LISP_FLV=`echo $LISP_INF | sed 's:_.*::'`
    LISP_VRS=`echo $LISP_INF | sed 's:.*_::'`
    if [ -e "$LOC/bin/${LISP_INF}_$CM_PLATFORM/$IMG_NAME" ] ; then
      LISP_IMG="$LOC/bin/${LISP_INF}_$CM_PLATFORM/$IMG_NAME"
      LOAD=
    else
      LISP_IMG=
      LOAD=1
    fi
  fi
else
  if ls "$LOC"/bin/*_*_$CM_PLATFORM/$IMG_NAME >/dev/null 2>&1; then
    for pref in $LISP_PREFS ; do
      for img in "$LOC"/bin/${pref}_*_$CM_PLATFORM/$IMG_NAME ; do
        if [ "$img" != "$LOC/bin/${pref}_*_$CM_PLATFORM/$IMG_NAME" ] ; then
	  LISP_INF=`echo "$img" | sed 's:^.*/\([^/]*\)/[^/]*$:\1:;'`
	  LISP_FLV=`echo $LISP_INF | sed 's:\([^_]*\)_.*$:\1:;'`
	  LISP_VRS=`echo $LISP_INF | sed 's:[^_]*_\([^_]*\)_.*:\1:;'`
	  if [ -x "$img" ] ; then
	    LISP_EXE="$img"
	    LISP_IMG=
	    LOAD=
	    break
	  else
	    LISP_EXE=`find_lisp $LISP_FLV $LISP_VRS`
	    if [ "$LISP_EXE" ] ; then
	      LISP_IMG="$img"
	      LOAD=
	      break
	    fi
	  fi
	  LISP_FLV=
	  LISP_VRS=
        fi
      done
      if [ "$LISP_EXE" ] ; then break ; fi
    done
  fi

  if [ ! "$LISP_EXE" ] ; then
    for pref in $LISP_PREFS ; do
      LISP_EXE=`find_lisp $pref`
      if [ "$LISP_EXE" ] ; then
	LISP_INF=`get_lisp_info "$LISP_EXE"`
	if [ $? == 1 ] ; then exit 1 ; fi
	LISP_FLV=`echo $LISP_INF | sed 's:_.*::'`
	LISP_VRS=`echo $LISP_INF | sed 's:.*_::'`
        LOAD=1
        break
      fi
    done
  fi
fi

if [ ! "$LISP_EXE" ] ; then 
  msg_e "No executable found."
  msg_x "Aborting."
else
  # FIXME
  true
  # if LISP_EXE is in windows realm
  #   translate LISP_EXE
  #   if CM_ROOT is in windows realm
  #     translate as well
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
    LISP_CMD="'$LISP_EXE' -I -q -ansi"
    if [ $LOAD ] ; then
      LISP_CMD="$LISP_CMD -x '$LISP_EVL' -x t -repl"
    else
      test $LISP_INI && LISP_INI="-i $LISP_INI"
      LISP_CMD="$LISP_CMD -M '$LISP_IMG' $LISP_INI"
    fi
    ;;
  acl)
    LISP_CMD="'$LISP_EXE'"
    if [ $LOAD ] ; then
      LISP_CMD="$LISP_CMD -e '$LISP_EVL'"
    else
      test $LISP_INI && LISP_INI="-L $LISP_INI"
      LISP_CMD="$LISP_CMD -I '$LISP_IMG' $LISP_INI"
    fi
    ;;
  cmucl)
    LISP_CMD="'$LISP_EXE'"
    if [ $LOAD ] ; then
      LISP_CMD="$LISP_CMD -eval '$LISP_EVL'"
    else
      test $LISP_INI && LISP_INI="-init $LISP_INI"
      LISP_CMD="$LISP_CMD -core '$LISP_IMG' $LISP_INI"
    fi
    ;;
  openmcl)
    LISP_CMD="'$LISP_EXE'"
    if [ $LOAD ] ; then
      LISP_CMD="$LISP_CMD --eval '$LISP_EVL'"
    else
      test $LISP_INI && LISP_INI="--load $LISP_INI"
      LISP_CMD="$LISP_CMD --image-name '$LISP_IMG' $LISP_INI"
    fi
    ;;
  guile)
    LISP_CMD="'$LISP_EXE' -l '$CM_ROOT/src/cm.scm' -e cm"
    ;;
  *)
    msg_e "Don't know how to call '$LISP_FLV' yet... =:("
    msg_x "Fatal."
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

if [ "$EDITOR_OPT" ] ; then
  if under_editor && ! imatch_end_token "$EDITOR_OPT" gnuclient ; then
    msg_i "Already running under emacs.  Looking for gnuclient(1)."
    GNUCLIENT=`resolve_bin gnuclient WARN`
    if [ ! "$GNUCLIENT" ] ; then
      msg_i "Ignoring '$EDITOR_OPT'."
      EDITOR_OPT=
    else
      EDITOR_OPT="$GNUCLIENT"
      # FIXME: might check for a running gnuserv first
    fi
  fi

  if [ "$EDITOR_OPT" ] ; then
    if [[ "$EDITOR_OPT" == */* ]] ; then
      thing=`real_path "$EDITOR_OPT"`
      if [ ! "$thing" ] ; then
        msg_e "No such file or directory: '$EDITOR_OPT'"
      fi
    else
      thing=`resolve_bin "$EDITOR_OPT" WARN`
    fi
    if [ ! "$thing" ] ; then
      msg_w "Command not found: '$EDITOR_OPT'.  Ignoring."
    elif [ ! -f "$thing" -a ! -h "$thing" ] ; then
      msg_w "Not a file or link: '$thing'.  Ignoring."
    else
      EL1="$LOC/etc/xemacs/listener.el"
      EL2="$LOC/etc/xemacs/cm.el"
      LEX="$LISP_EXE"
      #LEX=`echo "$LISP_EXE" | sed 's: :\\\\\\\ :g'`
      LCM=`echo "$LISP_CMD" |tr -d "'" |sed "s:$LISP_EXE:$LEX:g;"'s:":\\\":g;'`
      INI="(progn (load \"$EL1\") (load \"$EL2\") (lisp-listener \"$LCM\"))"
      EDITOR_EXE="$thing"
      EDITOR_CMD="'$EDITOR_EXE' -eval '$INI'"
      if [[ "$EDITOR_EXE" == *client ]] ; then
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
  echo ""
  echo "Executable:  ${LISP_EXE:-<missing>}"
  echo "Image:       ${LISP_IMG:-<none>}"
  echo "Flavor:      ${LISP_FLV:-<n/a>}"
  echo "Version:     ${LISP_VRS:-<n/a>}"
  echo "Load:        $LOAD"
  echo -n "Command:     "
  if [ "$EDITOR_CMD" ] ; then
    echo "$EDITOR_CMD"
  else
    echo "$LISP_CMD"
  fi
  echo ""
fi

if [ "$EDITOR_CMD" ] ; then
  eval $EXEC $EDITOR_CMD
else
  eval $EXEC $LISP_CMD
fi

#
# EOF
