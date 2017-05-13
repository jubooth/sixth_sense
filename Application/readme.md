The Sixth Sense App
===================

The app controls the vibrations in the t-shirt to give the wearer a new sense of direction. The app has two main components - connecting to the device by bluetooth and GPS navigation.

The bluetooth connection part of the app is based in the Bluefruit LE Connect Android app provided by Adafruit as an example of an Android app communicating with one of their BLE devices. The Github repository can be found at https://github.com/adafruit/Bluefruit_LE_Connect_Android. The app uses the UART example code to connect and communicate with the nRf8001.

The GPS navigation is done using step-by-step (turn-by-turn) directions. These directions are calculated using the Google Maps Directions API through the Java client library for Google Maps API Web Services, https://github.com/googlemaps/google-maps-services-java.

Notes
-----

getDirections(...) and newRequest()... return DirectionResult.

DirectionResult
	geocodedWaypoints[]
		geocoderStatus (OK | ZERO_RESULTS)
		partialMatch (boolean)
		placeId (String)
		types[] (AIRPORT | BUS_STATION | CHURCH | etc.)
	routes[]
		bounds (northeast and southwest points to form map bounds)
		copyrights (String)
		fare (currency and amount)
		legs[]
			arrivalTime (DateTime)
			departureTime (DateTime)
			distance
				humanReadable (String)
				inMeters (long)
			duration
				humanReadable (String)
				inSeconds (long)
			durationInTraffic
				humanReadable (String)
				inSeconds (long)
			endAddress (string)
			endLocation (LatLng)
			startAddress (string)
			startLocation (LatLng)
			steps[] - holds single instruction eg. turn left onto exhibition rd.
				distance
					humanReadable (String)
					inMeters (long)
				duration
					humanReadable (String)
					inSeconds (long)
				endLocation
				htmlInstructions
				polyline - representation of path (decodePath() returns LatLng list and getEncodedPath() returns string)
				startLocation (latLng)
				steps[] (more detailed)
				transitDetails
					arrivalStop
						location (LatLng)
						name (string)
					arrivalTime
					departureStop
						location (LatLng)
						name (string)
					departureTime
					headsign (String - specifies the direction in which to travel on this line)
					headway (long - expected number of seconds between departures from the same stop)
					line
						agencies[]
							name
							phone
							url
						color
						icon
						name
						shortName
						textColor
						url
						vehicle
					numStops
				travelMode (BICYCLING | DRIVING | TRANSIT | UNKNOWN | WALKING)
		overviewPolyline (decodePath() returns LatLng list and getEncodedPath() returns string)
		summary (String)
		warnings[] (string)
		waypointOrder[] (int)
