# Is there a car in the garage?
*Is there a car in the garage?* is a small Arduino webserver that uses an ultrasonic sensor to tell if there's a car or not in the garage. It's to be used in conjunction to a Apple Shorcut or the equivalent in Android.

It is originaly programmed to detect a car in a closed space, but it can be used to detect any static object is a closed space

## Prerequisites

This program is tested and used on a [Wemos D1 Mini](https://wiki.wemos.cc/products:d1:d1_mini) board. Even though other boards are not testes, this program should run without problems on boards with a ESP-8266EX chip.

## Installation

1. Download [is-there-a-car-in-the-garage.ino](https://github.com/SrGMC/is-there-a-car-in-the-garage/raw/master/is-there-a-car-in-the-garage.ino) and open the file in the Arduino IDE.
2. Edit the line containing `#DEFINE SECRET <secret>` and insert your secret code. Only share this secret with trusted people.
3. Press compile and verify, and wait for the program to load onto the board.
4. Connect pins X on the ultrasonic sensor to pins X on the board respectively (TODO: Fill in pins)
5. Power the board up and connect to the wireless network called "garage-sensor". A captive portal should pop up. Use this to set your home's wireless credentials for the Arduino to connect.
6. Download this Shortcut (for iOS users) and fill in the server address and the secret you inserted on step 2. Rename the Shortcut if you want

If this is the only server that you'll run open to the internet, open port `8080` to the Arduino Server IP on your router. If not, use a [reverse proxy](#reverse-proxy) in one of your servers.

### Reverse proxy
TODO: Reverse proxy setup Nginx

## Usage
### iOS
There are two ways to use this

#### Using Shortcuts
Open the Shortcuts app, the run the shorcut

#### Using Siri
Open Siri and tell her the name of the shorcut.

For example, if the shortcut name is "Is there a car in my garage?", ask Siri: "Hey Siri, is there a car in my garage"

## Acknowledgements

[WiFiManager](https://github.com/tzapu/WiFiManager) by @tzapu