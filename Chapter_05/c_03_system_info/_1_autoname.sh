#!/bin/bash

###############################################################################
# contains(string, substring)
#
# Returns 0 if the specified string contains the specified substring,
# otherwise returns 1.
###############################################################################
contains() {
    string="$1"
    substring="$2"
echo strings: $string , $substring
    if test "${string#*$substring}" != "$string"
    then
        return 0    # $substring is in $string
    else
        return 1    # $substring is not in $string
    fi
}
###############################################################################

###############################################################################
# create_file(fullname, filename, ext)
###############################################################################
create_file() {
    fullname="$1"
    filename="$2"
    ext="$3"

    newext="$NOW.$ext.bak"
    newname=$filename'_'$newext

    # Rename 'file' before creating a new one
    # The backup filename is date-timestamped
    mv $fullname $newname

    # Create a new 'file' using the 'touch' command
    touch $fullname

    # Open file descriptor (fd) 3 for read/write on a text file
    exec 3<> $fullname

    # Write the contents to the new file
    echo -e $CONTENTS >&3

    # Close file number 3 (fd 3)
    exec 3>&-
}
###############################################################################

# Capture current directory into 'myDir'
myDir=${PWD##*/}

# Set 'NOW' to current date-time
NOW=$(date +"%Y.%m.%d-%H.%M.%S")

# Get list of c files in directory
cd src
cFiles=`ls *.{c,cpp}`
#echo cFiles: $cFiles
cd ..



if contains "$cFiles" "main.cpp"
then
    ACSRC='AC_CONFIG_SRCDIR([src/main.cpp])'
else
    ACSRC="AC_CONFIG_SRCDIR([src/main.c])"
fi
#echo ACSRC: $ACSRC

# Create src/Makefile.am
USOURCES='_SOURCES = '
CONTENTS="# file: src/Makefile.am\n
    ACLOCAL_AMFLAGS = -I m4\n
	\n
	AM_LDFLAGS = -static -ljson-c -lcurl -lpthread -lhw \n
	\n
	$myDir$USOURCES$cFiles \n
	\n
	bin_PROGRAMS = $myDir \n"
create_file "src/Makefile.am" "src/Makefile" "am"

# Create configure.ac
CONTENTS='# file: configure.ac\n
    AC_PREREQ(2.61)\n
    AC_INIT([host-mode-demo], 1.0.0)\n
    AM_INIT_AUTOMAKE([foreign])\n
    AM_MAINTAINER_MODE\n
    '$ACSRC' \n
    AC_CONFIG_HEADER([config.h])\n
    AC_CONFIG_MACRO_DIR([m4])\n
    AC_PROG_LIBTOOL\n
    AC_PROG_CXX\n
    PKG_PROG_PKG_CONFIG\n
    \n
    # Checks for libraries.\n
    \n
    AC_ARG_WITH([common_includes],\n
          AC_HELP_STRING([--with-common-includes=@<:@dir@:>@],\n
             [Specify the location of the common headers]),\n
          [common_incdir=$withval],\n
          with_common_includes=no)\n
    \n
    if test "x$with_common_includes" != "xno"; then\n
       CFLAGS="${CFLAGS} -I${common_incdir}"\n
    fi\n
    \n
    AC_SUBST([CFLAGS])\n
    AC_SUBST([CPPFLAGS])\n
    \n
    AC_CONFIG_FILES([Makefile src/Makefile])\n
    AC_OUTPUT'

create_file "configure.ac" "configure" "ac"

# Create autogen.sh
CONTENTS='# file: autogen.sh \n
    #!/bin/sh\n
    \n
    # autogen.sh -- Autotools bootstrapping\n
    #\n
    \n
    libtoolize --copy --force\n
    aclocal &&\\\n
    autoheader &&\\\n
    autoconf &&\\\n
    automake --add-missing --copy\n'
create_file "autogen.sh" "autogen" "sh"

# Create Makefile.am
CONTENTS='# file: Makefile.am\n
    SUBDIRS = src\n'
create_file "Makefile.am" "Makefile" "am"


