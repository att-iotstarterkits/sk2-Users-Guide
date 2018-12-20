# wwan_blink.py
#
# This code provides a simple example for
# instantiating and using the 'wwan' class

import time
from wwan_class import wwan

COUNT = 4

print("Starting wwan_blink.py...")
w = wwan()
w.off()

for i in range(0, COUNT*2):
    v = w.toggle()
    time.sleep(1)

