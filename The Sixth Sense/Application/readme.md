The Sixth Sense App
===================

The app controls the vibrations in the t-shirt to give the wearer a new sense of direction. The app has two main components - connecting to the device by bluetooth and GPS navigation.

The bluetooth connection part of the app is based in the Bluefruit LE Connect Android app provided by Adafruit as an example of an Android app communicating with one of their BLE devices. The Github repository can be found at https://github.com/adafruit/Bluefruit_LE_Connect_Android. The app uses the UART example code to connect and communicate with the nRf8001.

The GPS navigation is done using step-by-step (turn-by-turn) directions. These directions are calculated using the Google Maps Directions API through the Java client library for Google Maps API Web Services, https://github.com/googlemaps/google-maps-services-java.

Google Maps APIs
================

Google Maps Android API
-----------------------

Designed for adding maps to an android app. Enables the integration of different types of maps, placing of markers, styles and places. This could be used in future to give a visualisation/alteration of the route. CHECK if this can do directions.

https://developers.google.com/maps/documentation/android-api


Google Directions API
----------------------

Get directions as a series of waypoints - different modes of transport available. This will be the primary way of getting directions. This is a web service. Up to 2500 requests per day for free.

https://developers.google.com/maps/documentation/directions

Using the Google Directions API through the Java Client for Google Maps Services, see https://github.com/googlemaps/google-maps-services-java