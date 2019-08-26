import iot_mal
import time

# Create a location handler
location_handler = iot_mal.location()

# Enabled location services (Standalone mode)
print("Enabling Location Services")
location_handler.set_config(True)
location_handler.set_mode(4)

# Give it 30 seconds or so to get GPS info
print("Waiting for GPS fix")
timeout = 0
while timeout < 30:
    # Get the location info
    loc_info = location_handler.get_position_info()
    latitude = loc_info.get('latitude')
    longitude = loc_info.get('longitude')
    if latitude is not None and longitude is not None:
        # loc_info will not contain the latitude and longitude keys until it has a GPS fix
        # Until then, get() will return None
        break
        
    timeout = timeout + 1
    time.sleep(1)
    
# Print the output
if latitude is None:
    print("Failed to get GPS info")
else:
    print("Latitude:  " + str(latitude))
    print("Longitude: " + str(longitude))

