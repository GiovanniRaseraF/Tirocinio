from periphery import GPIO
dir(GPIO)
gpio4_12 = GPIO("/dev/gpiochip4", 12, "in")
gpio_green = GPIO("/dev/gpiochip1", 24, "out")
gpio_red = GPIO("/dev/gpiochip1", 25, "out")
gpio_blue = GPIO("/dev/gpiochip2", 23, "out")

gpio4_12.edge("rising")

while True:
    #value = gpio4_12.read()
    event_gpio = gpio4_12.read_event()
    print(str(event_gpio))
    #print(str(value))
