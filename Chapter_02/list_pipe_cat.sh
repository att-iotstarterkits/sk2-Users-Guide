# list_pipe_cat.sh
#
# - This script writes a listing of /dev directory
#   into the file mylisting.txt in /CUSTAPP
# - The ">" pipes tells the shell to pipe the output
#   into the txt file rather than to the standard output
# - It then prints out the contents of mylisting.txt
#   using the "cat" command
#
ls -ls /dev > /CUSTAPP/mylisting.txt
cat /CUSTAPP/mylisting.txt
