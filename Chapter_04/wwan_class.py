###############################################################################
# wwan_class.py
# Created 2018.12.09
#
# WWAN LED routine uses os and subprocess to call shell commands to read and
# modify the WWAN device driver file descriptor. It was found that Python
# file I/O was an unreliable method for managing the WWAN LED.
# 
###############################################################################
import os
import time
import subprocess

WWAN_LED = r'/sys/class/leds/wwan/brightness'

OFF = '0'
ON  = '1'

COUNT = 1

class wwan:
    value = '0'
    
    def __init__(self):
        self.value = self.read()
        
    def on(self):
        self.value = '1'
        os.system("echo 1 > " + WWAN_LED)
    
    def off(self):
        self.value = '0'
        os.system("echo 0 > " + WWAN_LED)
    
    def toggle(self):
        i = int(self.value) ^ 1
        self.value = str(i)
        msg = "echo " + self.value +  " > " + WWAN_LED
        os.system(msg)
        return self.value
    
    def value(self):
        return self.value
    
    def read(self):
        p = subprocess.Popen(["cat", WWAN_LED], stdout=subprocess.PIPE)
        s = p.communicate()
        r = s[0].strip()
        return r


#def TestWWAN:
#    w = wwan()
#    print("inital value: " + w.value)
#    print("len: " + str(len(w.value)))
#    w.on()
#    print("turned on: " + w.value)
#    time.sleep(1)
#    w.toggle()
#    print "off"
#    time.sleep(1)
#    new = w.toggle()
#    print "on : " + new
#    time.sleep(1)
#    w.off()
#    print("turned off: " + w.value)
#    print("symore, read me: " + w.read() + "\n")