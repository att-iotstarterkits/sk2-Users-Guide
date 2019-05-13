# Shell script examples for AT&T's IoT Starter Kit (gen 2) User's Guide #

Chapter 2 in the *SK2 User's Guide* provides a brief Linux tutorial. One advantage of using Linux is its support for command-line utilities and shell scripting. Here are a few examples that you can push to your SK2 and run from its command-line.

Example           | Description
------------------|------------------------------------------------------------------
list.sh           | Simple listing of a directory
list_dev.sh       | Two commands - change directory and then list it
list_pipe_cat.sh  | List the directory into a file, then use CAT to display the file
TurnOnWwanLed.sh  | Turn on the WWAN LED using file i/o from a shell script
TurnOffWwanLed.sh | Turn off the WWAN LED using using file i/o from a shell script
blink.sh          | Blink the WWAN LED

To use these commands, install ADB (Android Debug Bridge) to your computer. (See the User's Guide PDF file for installation directions, if you need them.)

With ADB installed, you can push a file to the SK2 using the command:

    adb push file /CUSTAPP

This will push the 'file' to the "/CUSTAPP" directory on the SK2. The CUSTAPP (i.e. customer app directory) is a read/write directory on the SK2 that you can use to download and run your scripts and programs.

Once the file has been pushed to the SK2, run the scrip using the following commands:

    adb shell      # opens up a command-line session on the SK2
    cd /CUSTAPP    # makes /CUSTAPP the active directory
    ./file         # executes the program "file" 

You will find additional shell script examples in the Appendix.
