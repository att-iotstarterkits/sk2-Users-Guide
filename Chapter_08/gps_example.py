import iot_mal
import time

timeout_max = 120
wait_interval = 1

# Create a location handler
location_handler = iot_mal.location()

print("\nDisabling Location Services\n-------------------------------------")

location_handler.set_config(False)
gps_cfg = location_handler.get_config()
print(gps_cfg)

# Enabled location services (Standalone mode)
print("\nEnabling Location Services\n-------------------------------------")
location_handler.set_mode(4)
location_handler.set_config(True)
gps_cfg = location_handler.get_config()
print(gps_cfg)

# Give it 30 seconds or so to get GPS info
print("\nWaiting for GPS fix\n-------------------------------------")
timeout = 0
while timeout < timeout_max:
    # Get the location info
    loc_info = location_handler.get_position_info()
    print(loc_info)
    print('Location Status: {} (0: In Progress, 1: Completed)'.format(loc_info.get('loc_status')))
    
    latitude = loc_info.get('latitude')
    longitude = loc_info.get('longitude')
    if latitude is not None and longitude is not None:
        # loc_info will not contain the latitude and longitude keys until it has a GPS fix
        # Until then, get() will return None
        break

    timeout = timeout + wait_interval
    print('Waiting... ({} secs)'.format(timeout))
    time.sleep(wait_interval)


# Print the output
print("\nGPS Results\n-------------------------------------")
if latitude is None:
    print("Failed to get GPS info\n")
else:
    print("Latitude:  " + str(latitude))
    print("Longitude: " + str(longitude))
