# Apple Home with ESP32 and Swift

# Overview

This project demonstrates how to use Swift to control an ESP32 microcontroller, which is connected to an Apple HomeKit environment. 

The ESP32 acts as a bridge between the Swift application and the Apple Home ecosystem, allowing for seamless integration of IoT devices.

# History

I Started with main.c that print temperatura and humidity from DHT11 sensor, then I added RGB LED control,


And then (with main_apple_homekit.c) integrated with Apple HomeKit using Swift.

Now, i am trying to use Swift Embedded ( RISC-V ) to run the code on the ESP32.

# Building the Project

```bash
swiftc main.swift -o main -enable-experimental-feature Embedded -wmo
```

# References

https://www.swift.org/install/macos/

https://www.swift.org/swiftly/documentation/swiftly/getting-started/

https://www.youtube.com/watch?v=LqxbsADqDI4&t=1056s