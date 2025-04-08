# NANOMQ broker with MQTT auth
A simple broker setup using nanoMQ static libraries available for Windows with MSVC2022 and for Linux with GCC, the command and the cmakelists.txt are editable and the process followed to reach this point can be found in main.cpp.

## How to work with it
Once the broker is set up, meaning the executable is ran, you can use your authentication to pub/sub to any topic, for example using mosquitto or QTs MQTT client capabilities. i.e:

mosquitto_sub -h localhost -p 1883 -u myUser -P myPassword -t "#"
mosquitto_pub -h localhost -p 1883 -u myUser -P myPassword -t "MYTOPIC" -m "Hello World" -d

also this can be accessed from other devices that can see an open network interface of your local host.

I.e: your device on network is 192.168.1.X, so you can replace localhost by that on the aforementioned commands and you can publish and subscribe to topics with it. 

## Additional information

- SSL Encryption is not present, but can be added with tweaking.
- you can also use the following QML + QT sister program to view the contents: https://github.com/Mars-Wave/QTMqttSubPlusBrokerRunner/
