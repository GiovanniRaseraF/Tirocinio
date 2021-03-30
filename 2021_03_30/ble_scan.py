# bluetooth low energy scan
from bluetooth.bluez import DeviceDiscoverer as dd 

blue_store = dd()
blue_store.find_devices(duration=255)

print(str(len(blue_store.names_found)))