WWAN_LED = r'/sys/class/leds/wwan/brightness'

try:
    f_wwan = open(WWAN_LED, 'w')
    f_wwan.write('1')

except IOError:
    print("I/O error")
    pass
    
finally:
    f_wwan.close()
