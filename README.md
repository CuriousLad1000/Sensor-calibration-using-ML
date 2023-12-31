﻿
# Sensor calibration using Machine Learning

## Introduction

This repository presents one of the projects I built during the start of
the COVID-19 pandemic when there was a severe shortage of medical
equipment. Even something simple as a thermometer was either not
available or too costly to purchase. In this project, I used some
consumer-grade temperature sensors and calibrated them to provide
medical-grade precision and accuracy.

## Project Objective

The objective is to calibrate a commonly available temperature sensor to
provide medical grade accuracy. The sensor is calibrated by taking
readings from multiple medical grade thermometers as a benchmark and
then averaging them out.

The reading taken from thermometer and the sensor being calibrated are
then fit to a regression model to increase sensor's accuracy.

The model is then uploaded to the controller and after interfacing with
sensors and peripherals required, it produces accurate results under
calibrated range of a clinical thermometer (94-108 degrees F).

*Full list of features and capabilities are listed in a separate section below.*

## Hardware used

-   Arduino nano/pro min

-   3D printer casing for the temperature gun

-   Bright OLED display

-   battery

-   Laser pointer

-   Contactless Temperature sensor

-   Custom-built calibration heat bed

-   Clinical thermometers

-   Precision temperature sensors for heat-bed and reference

## Software used

-   Arduino IDE (C/C++ Programming)

-   Excel for data collection and regression model

-   GIMP for UI designing

-   Eagle for PCB designing

-   Fritzing for prototyping wiring diagram

## Features offered

-   Calibrated contactless temperature sensor.

-   Power-saving mode.

-   Inbuilt rechargeable batteries.

-   Temperature range similar to clinical thermometer.

-   Bright OLED display with easy-to-read readouts.

## Device pics

**Device**

<br/>

<p align="Center">
  <img src="https://raw.githubusercontent.com/wiki/CuriousLad1000/Sensor-calibration-using-ML/images/6a57b863d280692d7a448476c5cb43f4597e4751.jpg">
</p>

<br/>
<br/>

**Calibration setup <i>(gotta work with whatever you have during pandemic... this is a makeshift Heatbed PID controlled)</i>**


<br/>

<p align="Center">
  <img src="https://raw.githubusercontent.com/wiki/CuriousLad1000/Sensor-calibration-using-ML/images/4f452e595bead12b9ff8467f1f5cd5611851e4a5.jpg">
</p>

<br/>
<br/>


<br/>

<p align="Center">
  <img src="https://raw.githubusercontent.com/wiki/CuriousLad1000/Sensor-calibration-using-ML/images/ed4d7449cce9861583291f160f81ce9d10a367c1.jpg">
</p>

<br/>
<br/>

**Circuit board**


<br/>

<p align="Center">
  <img src="https://raw.githubusercontent.com/wiki/CuriousLad1000/Sensor-calibration-using-ML/images/26b1a07663ad9a0393994a9daebea9a6f7b6eaa3.png">
</p>

<br/>
<br/>

**Calibration process**


<br/>

<p align="Center">
  <img src="https://raw.githubusercontent.com/wiki/CuriousLad1000/Sensor-calibration-using-ML/images/Calibration.gif">
</p>

<br/>
<br/>

**UI Testing**


<br/>

<p align="Center">
  <img src="https://raw.githubusercontent.com/wiki/CuriousLad1000/Sensor-calibration-using-ML/images/UI.gif">
</p>

<br/>
<br/>
