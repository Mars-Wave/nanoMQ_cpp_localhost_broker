A simple broker setup using nanoMQ static libraries compiled in windows with MSVC2022, the command and the cmakelists.txt are editable and the process followed to reach this point can be found in main.cpp.

Once the broker is set up, meaning the executable is ran, you can use your authentication to pub/sub to any topic, for example using mosquitto or QTs MQTT client capabilities. i.e:

mosquitto_sub -h localhost -p 1883 -u myUser -P myPassword -t "#"
mosquitto_pub -h localhost -p 1883 -u myUser -P myPassword -t "MYTOPIC" -m "Hello World" -d

also this can be accessed from other devices that can see an open network interface of your local host.

I.e: your device on network is 192.168.1.X, so you can replace localhost by that on the aforementioned commands and you can publish and subscribe to topics with it. 
