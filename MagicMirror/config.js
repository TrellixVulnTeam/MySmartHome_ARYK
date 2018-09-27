/* Magic Mirror Config Sample
 *
 * By Michael Teeuw http://michaelteeuw.nl
 * MIT Licensed.
 */

var config = {
	port: 8080,
	ipWhitelist: ["127.0.0.1", "::ffff:127.0.0.1", "::1"], // Set [] to allow all IP addresses.

	language: "de",
	timeFormat: 24,
	units: "metric",

	modules: [
		{
			module: "alert",
		},
		{
			module: "clock",
			position: "top_left",
			config:{
				timezone: "Europe/Berlin" 	
			}
		},
		{
			module: "calendar",
			header: "Feiertage",
			position: "top_left",
			config: {
				calendars: [
					{
						symbol: "calendar-check-o ",
						url: "https://calendar.google.com/calendar/ical/thorbenschnirpel%40gmail.com/private-10e6a72bca4f467c961881dea94c6f90/basic.ics"
					}
				],
				maximumEntries : "3"
			}
		},
		{
			module: "compliments",
			position: "lower_third",
		},
		{
			module: "currentweather",
			position: "top_right",
			config: {
				location: "Hamburg",
				locationID: "2911298",  //ID from http://www.openweathermap.org/help/city_list.txt
				appid: "023d18e46616624690bf4753159650cc"
			}
		},
		{
			module: "weatherforecast",
			position: "top_right",
			header: "Wettervorhersage",
			config: {
				maxNumberOfDays: "3",
				location: "Hamburg",
				locationID: "2911298",  //ID from http://www.openweathermap.org/help/city_list.txt
				appid: "023d18e46616624690bf4753159650cc"
			}
		},

		{
			module: 'MMM-mqtt',
			position: 'bottom_left',
			header: 'Hitzemeter', 
			config: {
				mqttServer: "mqtt://localhost",
				loadingText: "warte auf Sensordaten...",
				topic: "temp_thorben",
				postText : "°C"
			}
		},
		{
			module: 'MMM-mqtt',
			position: 'bottom_center',	
			header: 'Nässigkeitsmeter', 
			config: {
				mqttServer: "mqtt://localhost",
				loadingText: "warte auf Sensordaten...",
				topic: "humid_thorben",
				postText : "%"
			}
		},
		{
			module: 'MMM-mqtt',
			position: 'bottom_right',	
			header: 'Taupünktchen', 
			config: {
				mqttServer: "mqtt://localhost",
				loadingText: "warte auf die Berechnung des Zauberers...",
				topic: "tau_thorben",
				postText : "°C"
			}
		},
		{
			module: 'MMM-mqtt',
			position: 'top_right',	
			header: 'Lüftometer', 
			config: {
				mqttServer: "mqtt://localhost",
				loadingText: "warte auf eine Entscheidung...",
				topic: "air_thorben",
			}
		},


	]

};

/*************** DO NOT EDIT THE LINE BELOW ***************/
if (typeof module !== "undefined") {module.exports = config;}
