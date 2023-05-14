# VX Dash
<a href="https://www.buymeacoffee.com/magicmartin" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/default-orange.png" alt="Buy Me A Coffee" height="41" width="174"></a>      View this project on [CADLAB.io](https://cadlab.io/project/26765). 
## What is it ?
VX Dash is an attempt at proposing a modular, cheap and entirely open-source digital instrument cluster for the Vauxhall VX220 ( also known as the Opel Speedster ). 
It is based on an ESP32 MCU coupled over Serial with a Nextion screen and an inexpertly designed vehicle interface PCB.
## What can it do ?
As this project is not yet in the prototype phase, the current base capabilities targeted are very similar to the original cluster :
 - Full coverage of all the original Active Hi and Active Low inputs in the VX instrument clusters ( MIL light, Parking brake light, indicator lights ... )
 - Fuel level display
 - Engine coolant temperature display 
 - RPM and Speed display
 
Some additional functionalities are planned :
 - Four 5V "ECU" sensor voltage inputs for things such as oil pressure sensors, MAP sensors, IAT/boost sensors...
 - Four additional "VDO-style" analog resistive inputs, for "low impedance" voltage divider sensors, such as the ubiquitous VDO oil pressure and temperature sensors (typically 0-250Ohm)
 - One "High Resistance" analog resistive input, for higher impedance sensors (typically 0-2K)
 - Modular design to allow some changes between the analog resistive inputs (as in less low-R and more high-R inputs) with simple soldering
 - User-personalizable sensor curves via simple code pages in Arduino IDE
 - Additional free pins can be used and reassigned for variants with CAN interfaces for other vehicles
 ## What makes it tick ?
 Currently the hardware design (under CERN OHL v2 Strongly Reciprocal license) features the following :
 - Opto-isolated readouts of the Active Hi and Active Low cluster inputs (SFH617 optos)
 - Cheap and easily flashable EPS32 dev kit C main MCU
 - TVS diode protection for the 12V input, as well as a Schottky barrier for accidental over voltages
 - 12V -> 5V power conversion stage built around the AP63200WU-7 converter, with a max 2A output
 - 5V -> 3V3 power conversion stage built around the MP2322GQH, mimicking the power stages of the amazing Arduino Giga Wifi
 - Speed and RPM pulses amplification and normalisation with an old-school C4050 non-inverting hex buffer CMOS
 - Multiplexed non-critical binary inputs (Oil alarm, airbag light, ABS light, Ignition signal, Full beams light, Low coolant alarm, Brakes alarm, Alternator light, Parking Brake light, Immobilizer and Door light through a C4067 MUX
 - JAE MX34036UF2 36 pin connector (unfortunately not native directly with the original harness, but adapters can be made
 - Backfeed protection on the analog resistive sensor inputs
 - ESD protection on the voltage sensor inputs
 - Regulated 5V output to feed 5V sensors
 - 3 to 4 ( in the current configuration ) direct interrupts from the binary inputs into the MCU for fast response.
 - Odometer and trip distance saved in the flash memory of the MCU
 - Serial communication towards a [Nextion "Intelligent" 7in display (NX8048P070)](https://nextion.tech/datasheets/NX8048P070-011R/), with free user-customizable interface sets
 - Not-yet designed, 3D printable and wrappable mechanical interface that *should* fit under the original instruments binnacle

## What is the timeline ?
Currently, this is the status of the project : 
### A-sample
 - [X] Preliminary circuit schematic for default variant (A-sample)
 - [X] First PCB packaging
 - [ ] Test of coolant temperature input readability
 - [ ] Test of fuel level sensor
 - [ ] Test of analog resistive sensor inputs
 - [ ] Test of 5V sensor inputs
 - [ ] Test of RPM pulse counter
 - [ ] Test of Speed pulse counter
 - [ ] Test of input muxing
 - [ ] Preliminary screen HMI publication
 - [X] Arduino code first draft with only signal acquisition architecture (no odometer, no trip) and screen interface variables
 - [ ] Implementation of sensor interpolation tables
 - [ ] Publication of current consumption tables per functional modules
 ### B-sample
 - [ ] Revision of power circuit
 - [ ] Revision of fusing
 - [ ] Revision of MCU input attributions
 - [ ] Possible revision of MUXing strategy and "on-demand" MUXing on input change (OR CMOS needed)
 - [ ] Revision of practical main connector pinout and I/O attributions (more V sensors, less R sensors, more direct MCU alarm lines ?)
 - [ ] Implementation of Screen set-up pages
 - [ ] Implementation of odometer and trip functions including flash saving
 - [ ] PCB re-packaging
 - [ ] Space-constrained enclosure design release
 - [ ] Function-to-core splitting of the sensor detection loops and write-to-screen loops
 ### C-sample
 - [ ] Hopefully just bug-fixing ? LOL
 - [ ] Enclosure refinements
 - [ ] Ultimate schematic changes
 - [ ] HMI refinements
 - [ ] PCB DFM iterations ( probably with PCBWay SMT services )
 - [ ] ??????
 - [ ] Enjoy
