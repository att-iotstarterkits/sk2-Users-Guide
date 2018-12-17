#!/bin/bash

# Capture current directory into 'myDir'
myDir=${PWD##*/}

# Set 'NOW' to current date-time
NOW=$(date +"%Y.%m.%d-%H.%M.%S")

# Get list of c files in directory
cd src
cFiles=`ls *.{c,cpp}`
cd ..

# Rename 'Makefile.am' in 'src' directory before creating a new one
# The new filename is date-timestamped
mv src/Makefile.am src/Makefile_$NOW.am.bak

# Create a new 'Makefile.am' using the 'touch' command
touch src/Makefile.am

# Open file descriptor (fd) 3 for read/write on a text file
exec 3<> src/Makefile.am

# Use 'echo' to write the following lines to the new 'Makefile.am'
echo 'ACLOCAL_AMFLAGS = -I m4' >&3
echo '' >&3
echo 'AM_LDFLAGS = -static -ljson-c -lcurl -lpthread -lhw ' >&3
echo '' >&3
echo $myDir'_SOURCES = '$cFiles >&3
echo '' >&3
echo 'bin_PROGRAMS = '$myDir >&3

# Close file number 3 (fd 3)
exec 3>&-



#dirlist=`ls ${prefix}*.text`
#doesn't make an array, it makes a only a string with space separated file names.
#
#you have to do
#
#dirlist=(`ls ${prefix}*.text`)
#to make it an array.
#
#Then $dirlist will reference only the first element, you have to use
#
#${dirlist[*]}
#to reference all of them in the loop.
#
#--KarelSk
