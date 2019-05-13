# C/C++ examples for AT&T's IoT Starter Kit (gen 2) User's Guide (SK2) #

Chapter 3 in the *SK2 User's Guide* provides an introduction to building C/C++ programs for the SK2.

Example                 | Description
------------------------|--------------------------------------------------------------------------
hello			| Simple 'Hello World' example; useful for verifying the C/C++ build system
fileio_red_led          | Using C/C++ file I/O to blink the Red LED
fileio_export		| Using C/C++ file I/O to export GPIO resource (i.e. allocate GPIO pin)
fileio_unexport		| Using C/C++ file I/O to unexport GPIO resource (i.e. release GPIO pin)
fileio_wwan_led		| Use C/C++ file I/O to control WWAN LED
api_red_led		| Blink the Red LED using the SDK's API
api_red_led_with_deinit	| Blink the Red LED using the SDK's API (releasing resource when complete)
fork			| Generic example of Linux fork() command
sigint			| Handling the Linux SIGINT signal
sigint2			| Exploring the SIGINT without pause()
sigint2_with_pause	| Explore SIGINT with pause()
sigaction		| Example for handling signals with 'sigaction'
fileio_button_input	| Handling GPIO button push using File I/O
api_button_interrupt    | Handling GPIO button using the SDK's API
api_button_irq_led	| Example turns on blue LED when button is pressed
myGpio_example		| Reusable example for GPIO
wnc_interrupt_test	| Original example written for WNC module - adapted for SK2

To use these programs, install ADB (Android Debug Bridge) to your computer. (See the User's Guide PDF file for installation directions, if you need them.)

With ADB installed, you can push a C executable file to the SK2 using the command:

    adb push <file> /CUSTAPP

This will push the 'file' to the "/CUSTAPP" directory on the SK2. The CUSTAPP (i.e. customer app directory) is a read/write directory on the SK2 that you can use to download and run your scripts and programs.

Once the file has been pushed to the SK2, run the scrip using the following commands:

    adb shell      # opens up a command-line session on the SK2
    cd /CUSTAPP    # makes /CUSTAPP the active directory
    ./file         # executes the program "file" 

To re-build the executable programs from the source files, please install the tools as described in Chapter 3.
