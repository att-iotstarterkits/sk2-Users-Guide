import iot_hw

#Initialize the ADC and read the ambient light level
light_sensor = iot_hw.adc()
light_value = light_sensor.read()
light_sensor.close()

print("Light sensor value = {}".format(light_value))
