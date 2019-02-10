# list_pipe_cat.sh
#
# - This script writes a listing of /dev directory into
#   a file named "mylisting.txt" in /CUSTAPP
# - The ">" pipe symbole tells the shell to pipe the output
#   from the "ls -ls /dev" command into the txt file rather 
#   than printing it to the standard output
# - It then prints out the contents of mylisting.txt
#   using the Linux "cat" command
#
ls -ls /dev > /CUSTAPP/mylisting.txt
cat /CUSTAPP/mylisting.txt
