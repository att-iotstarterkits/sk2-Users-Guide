import iot_mal
import iot_hw
from m2x.client import M2XClient

#Before running this example, read the ATT M2X Dashboard section in the Getting Started Guide

KEY = "Your API key goes here (inside the quotation marks)"
DEVICE_ID = "Your Device ID goes here (inside the quotation marks)"
STREAM_NAME = "light_sensor"

#Setup the MAL and data connection
network_handler = iot_mal.network()
network_handler.set_connection_mode(1,10,2)

#Initialize the ADC and read the ambient light level
light_sensor = iot_hw.adc()
light_value = light_sensor.read()
light_sensor.close()

# Setup the M2X stream based on the values input above
client = M2XClient(key=KEY)
device = client.device(DEVICE_ID)
light_sensor_stream = device.stream(STREAM_NAME)

#Add the light sensor value to the data stream
light_sensor_stream.add_value(float(light_value))

