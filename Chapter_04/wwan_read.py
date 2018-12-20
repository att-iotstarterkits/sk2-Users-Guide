WWAN_LED = r'/sys/class/leds/wwan/brightness'

try:
    f_wwan = open(WWAN_LED, 'r')

    v = f_wwan.read()
    print(str(v))

except IOError:
    print("I/O error")
    pass
    
finally:
    f_wwan.close()
