###############################################################################
# endless.py
# 2018.12.07 
#
# Program runs forever
###############################################################################
import time                                                 # Needed for time.sleep() function

print("Starting up...")
while 1:
    time.sleep(5)                                           # Sleep for 5 seconds
    print("Five more seconds have gone by...")
