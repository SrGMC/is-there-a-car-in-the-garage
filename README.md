# Is there a car in the garage?
*Is there a car in the garage?* is a small Arduino webserver that uses an ultrasonic sensor to tell if there's a car or not in the garage. It's to be used in conjunction to a Apple Shorcut or the equivalent in Android.

It is originaly programmed to detect a car in a closed space, but it can be used to detect any static object is a closed space

Consider donating if you found this useful

[![Donate](images/donate.gif)](https://www.paypal.me/alvarogalisteo/1.00)

## Prerequisites

This program is tested and used on a [Wemos D1 Mini](https://wiki.wemos.cc/products:d1:d1_mini) board. Even though other boards are not tested, this program should run without problems on boards with a ESP-8266EX chip.

## Installation
### Server and sensor

- Download [is-there-a-car-in-the-garage.ino](https://github.com/SrGMC/is-there-a-car-in-the-garage/raw/master/is-there-a-car-in-the-garage.ino) and open the file in the Arduino IDE.
- Edit the values between `"` for both the username and password in the lines:

```c
const char* username = "arduino";
const char* password = "arduino";
```

![Arduino IDE](images/ide.png)

- Press compile and verify, and wait for the program to load onto the board.
- Connect pins the following pins on the ultrasonic sensor to corresponding pins in the board:

| Sensor pin | Board pin |
| ---------- | --------- |
| Trig       | D1        |
| Echo       | D2        |
| Vcc        | 5v        |
| Gnd        | G         |


- Power the board up and connect to the wireless network called "garage-sensor". A captive portal should pop up. Use this to set your home's wireless credentials for the Arduino to connect. It should look like this:

![Captive portal](images/captive.png)

- Your server should be fully functioning. If this is the only server that you'll run open to the internet, open port `80` to the Arduino Server IP on your router. If not, use a [reverse proxy](#reverse-proxy) in one of your servers.

### iOS

- Download this [Shortcut](https://www.icloud.com/shortcuts/2c882fd182f14ea6b3fa74673e178815) and fill in the server credentials, the server address and the phrases you want Siri to tell in every case you inserted on step. Then, you can rename the shortcut to whatever you want:
  - On iOS 13, you need to ask Siri the name of the shortcut for it to be run.
  - On iOS 12 or lower, you need to setup a Siri Shortcut by clicking on the three dots in the shortcut, and then the shortcut settings.

### Android
TODO


### Reverse proxy
#### Nginx
Add the following to your sites-enabled configuration:

```nginx
location /<Path> {
    proxy_pass http://<IP Address>/;
    add_header Cache-Control 'no-store, no-cache, must-revalidate, max-age=0';
    add_header Cache-Control 'post-check=0, pre-check=0';
    add_header Pragma 'no-cache';
}
```

Change `<Path>` and `<IP Address>` accordingly. For example, accessing the server at `172.168.0.13` through the `/home` path:

```nginx
location /home {
    proxy_pass http://172.168.0.13/;
    add_header Cache-Control 'no-store, no-cache, must-revalidate, max-age=0';
    add_header Cache-Control 'post-check=0, pre-check=0';
    add_header Pragma 'no-cache';
}
```

## Acknowledgements

- [WiFiManager](https://github.com/tzapu/WiFiManager) by [@tzapu](https://github.com/tzapu)
- [HC-SR04](https://github.com/Martinsos/arduino-lib-hc-sr04) by [@Martinsos](https://github.com/Martinsos)
