#pragma once
#include <Arduino.h>

//Speed detection related
uint16_t speed = 0;                       //Last calculated value
uint16_t p_speed = 0;                     //Previous refresh value
uint16_t speed_raw = 0;                   //Last raw value (PPS)
uint16_t p_speed_raw = 0;                 //Previous raw value (PPS)

//Distance measurement related
uint32_t odometer = 0;
uint32_t p_odometer = 0;
uint16_t trip = 0;
uint16_t p_trip = 0;

//RPM detection related
uint16_t rpm = 0;
uint16_t p_rpm = 0;
uint16_t rpm_raw = 0;
uint16_t p_rpm_raw = 0;

//Fuel level measurement
uint8_t fuelLevel = 0;
uint8_t p_fuelLevel = 0;
uint32_t fuel_raw = 0;
uint32_t p_fuel_raw = 0;

//Coolant temperature measurement
uint8_t coolant = 0;
uint8_t p_coolant = 0;
uint16_t coolant_raw = 0;
uint16_t p_coolant_raw = 0;

//Direct inputs
uint32_t   analogV1 = 0;
uint32_t p_analogV1 = 0;
uint32_t   analogV2 = 0;
uint32_t p_analogV2 = 0;
uint32_t   analogV3 = 0;
uint32_t p_analogV3 = 0;
uint32_t   analogV4 = 0;
uint32_t p_analogV4 = 0;
uint32_t   analogR1 = 0;
uint32_t p_analogR1 = 0;
uint32_t   analogR2 = 0;
uint32_t p_analogR2 = 0;
uint32_t   analogR3 = 0;
uint32_t p_analogR3 = 0;
uint32_t   analogR4 = 0;
uint32_t p_analogR4 = 0;
uint32_t   analogKR1 = 0;
uint32_t p_analogKR1 = 0;

//TellTales
bool   lowFuelON = false;
bool p_lowFuelON = false;
bool   oilON = false;
bool p_oilON = false;
bool   fullbeamsON = false;
bool p_fullbeamsON = false;
bool   coolantON = false;
bool p_coolantON = false;
bool   MILON = false;
bool p_MILON = false;
bool   turnON = false;
bool p_turnON = false;
bool   parkingON = false;
bool p_parkingON = false;
bool   absON = false;
bool p_absON = false;
bool   brakesON = false;
bool p_brakesON = false;
bool   overheatON = false;
bool p_overheatON = false;
bool   airbagON = false;
bool p_airbagON = false;
bool   alternatorON = false;
bool p_alternatorON = false;
bool   buttonON = false;
