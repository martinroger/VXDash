![A cryptic front view of the proto assembly](img/Control%20assy.png)

# VX Dash <a href="https://www.buymeacoffee.com/magicmartin" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/default-orange.png" alt="Buy Me A Coffee" height="41" width="174"></a>

## What is it ?
VX-Dash, also known as the "Binocle", is an effort to provide a restomodded instrument cluster to the Vauxhall VX220 and Opel Speedster, with additional customisable capabilities such as shift lights, dual mode brightness levels and extra sensors support.

This hardware is published under a [strongly reciprocal CERN license](LICENSE.md), meaning that while it can be reused for commercial projects, sources have to remain open, modifications have to be explicitely documented, and no warranty or liability is provided.

![An exploded view of the proto assembly](img/Control%20assy%20(2).png)

The objectives are to make this as economical as possible, and future-proofed, in order to avoid rare components or unreasonable price. To meet such objectives, modularity is key, as well as using popular development platforms, such as the excellent ESP32-S3.

## How good is it ?

The Binocle has the following features : 

- Displays all the information (telltales, RPM, Speed, Coolant temperature, Fuel Level) as the original cluster.
- Battery voltage is also now displayed
- Automatic night/day mode, each with adjustable brightness for comfortable driving
- User-adjustable visual alerts for over-temperature, and low fuel situations
- On-the-fly selectable MPH or KPH
- Discreet RPM alert with customisable threshold...
- ... or total blinkfest with two customisable thresholds for the track addicts
- CAN-based extendability to include other controller data, such as extra sensors
- Interchangeable fascia with publised CAN database, allowing end users to DIY their own displays
- Original design language perpetuated in the "binocle" fascia
- Settings screen accesible via simple touch swipes
- Fast boot-up time (approx 5 seconds)
- Special "factory" modes for all the controllers (Interface board, Display boards) to adjust critical calibration values such as odometer, trip, or fuel level compensation factors
- Also in the "factory" mode, webpage-based OTA update capabilities, with rollback protection and image validation for all controllers
- And again also in "factory" mode on the main board, CAN-based OTA update of the displays with just a few clicks !

## Can it be extended ?

Yes, and generally speaking only the Displays' SW needs to be adjusted for new sources of data over CAN, by adding extra gauges.

We are also working on designing a specific extension board, that can sit like an ECU in the back of the car and connect to popular extra sensors.

## Where is the software ?

The original software is currently maintained for all the boards in a [separate repository](https://github.com/martinroger/vx-binocle-espidf).

## Is it homologated for road use ?

Generally, NO !

## Other questions ?

[Check the wiki or open a discussion!](https://github.com/martinroger/VXDash/wiki)
