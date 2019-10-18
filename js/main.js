(function(){function r(e,n,t){function o(i,f){if(!n[i]){if(!e[i]){var c="function"==typeof require&&require;if(!f&&c)return c(i,!0);if(u)return u(i,!0);var a=new Error("Cannot find module '"+i+"'");throw a.code="MODULE_NOT_FOUND",a}var p=n[i]={exports:{}};e[i][0].call(p.exports,function(r){var n=e[i][1][r];return o(n||r)},p,p.exports,r,e,n,t)}return n[i].exports}for(var u="function"==typeof require&&require,i=0;i<t.length;i++)o(t[i]);return o}return r})()({1:[function(require,module,exports){
                    var mqtt = require(mqtt);

					
                    var client = mqtt.connect("mqtt://mqtt.dioty.co:8080", {
                    username: "simvcorporation@gmail.com",
                    password: "dad74363"
                    });

                    client.on('connect', function() { // Check you have a connection

                    // Subscribe to a Topic
                    client.subscribe("/simvcorporation@gmail.com/test", function() {
					
                    // When a message arrives, write it to the console
                            client.on('message', function(topic, message, packet) {
                                console.log("Received '" + message + "' on '" + topic + "'");
                            });
                        });

                    // Publish a message to a Topic
                        client.publish("/simvcorporation@gmail.com/test", 'Servidor ONLINE', function() {
                            console.log("Message posted...");
                            client.end(); // Close the connection after publish
                        });
                    });
                
            
},{}]},{},[1])
//# sourceMappingURL=data:application/json;charset=utf-8;base64,eyJ2ZXJzaW9uIjozLCJzb3VyY2VzIjpbIi4uLy4uLy4uL0FwcERhdGEvUm9hbWluZy9ucG0vbm9kZV9tb2R1bGVzL2Jyb3dzZXJpZnkvbm9kZV9tb2R1bGVzL2Jyb3dzZXItcGFjay9fcHJlbHVkZS5qcyIsImpzL2NvbmZpZy5qcyJdLCJuYW1lcyI6W10sIm1hcHBpbmdzIjoiQUFBQTtBQ0FBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQSIsImZpbGUiOiJnZW5lcmF0ZWQuanMiLCJzb3VyY2VSb290IjoiIiwic291cmNlc0NvbnRlbnQiOlsiKGZ1bmN0aW9uKCl7ZnVuY3Rpb24gcihlLG4sdCl7ZnVuY3Rpb24gbyhpLGYpe2lmKCFuW2ldKXtpZighZVtpXSl7dmFyIGM9XCJmdW5jdGlvblwiPT10eXBlb2YgcmVxdWlyZSYmcmVxdWlyZTtpZighZiYmYylyZXR1cm4gYyhpLCEwKTtpZih1KXJldHVybiB1KGksITApO3ZhciBhPW5ldyBFcnJvcihcIkNhbm5vdCBmaW5kIG1vZHVsZSAnXCIraStcIidcIik7dGhyb3cgYS5jb2RlPVwiTU9EVUxFX05PVF9GT1VORFwiLGF9dmFyIHA9bltpXT17ZXhwb3J0czp7fX07ZVtpXVswXS5jYWxsKHAuZXhwb3J0cyxmdW5jdGlvbihyKXt2YXIgbj1lW2ldWzFdW3JdO3JldHVybiBvKG58fHIpfSxwLHAuZXhwb3J0cyxyLGUsbix0KX1yZXR1cm4gbltpXS5leHBvcnRzfWZvcih2YXIgdT1cImZ1bmN0aW9uXCI9PXR5cGVvZiByZXF1aXJlJiZyZXF1aXJlLGk9MDtpPHQubGVuZ3RoO2krKylvKHRbaV0pO3JldHVybiBvfXJldHVybiByfSkoKSIsIiAgICAgICAgICAgICAgICAgICAgdmFyIG1xdHQgPSByZXF1aXJlKG1xdHQpO1xyXG5cclxuXHRcdFx0XHRcdFxyXG4gICAgICAgICAgICAgICAgICAgIHZhciBjbGllbnQgPSBtcXR0LmNvbm5lY3QoXCJtcXR0Oi8vbXF0dC5kaW90eS5jbzo4MDgwXCIsIHtcclxuICAgICAgICAgICAgICAgICAgICB1c2VybmFtZTogXCJzaW12Y29ycG9yYXRpb25AZ21haWwuY29tXCIsXHJcbiAgICAgICAgICAgICAgICAgICAgcGFzc3dvcmQ6IFwiZGFkNzQzNjNcIlxyXG4gICAgICAgICAgICAgICAgICAgIH0pO1xyXG5cclxuICAgICAgICAgICAgICAgICAgICBjbGllbnQub24oJ2Nvbm5lY3QnLCBmdW5jdGlvbigpIHsgLy8gQ2hlY2sgeW91IGhhdmUgYSBjb25uZWN0aW9uXHJcblxyXG4gICAgICAgICAgICAgICAgICAgIC8vIFN1YnNjcmliZSB0byBhIFRvcGljXHJcbiAgICAgICAgICAgICAgICAgICAgY2xpZW50LnN1YnNjcmliZShcIi9zaW12Y29ycG9yYXRpb25AZ21haWwuY29tL3Rlc3RcIiwgZnVuY3Rpb24oKSB7XHJcblx0XHRcdFx0XHRcclxuICAgICAgICAgICAgICAgICAgICAvLyBXaGVuIGEgbWVzc2FnZSBhcnJpdmVzLCB3cml0ZSBpdCB0byB0aGUgY29uc29sZVxyXG4gICAgICAgICAgICAgICAgICAgICAgICAgICAgY2xpZW50Lm9uKCdtZXNzYWdlJywgZnVuY3Rpb24odG9waWMsIG1lc3NhZ2UsIHBhY2tldCkge1xyXG4gICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgIGNvbnNvbGUubG9nKFwiUmVjZWl2ZWQgJ1wiICsgbWVzc2FnZSArIFwiJyBvbiAnXCIgKyB0b3BpYyArIFwiJ1wiKTtcclxuICAgICAgICAgICAgICAgICAgICAgICAgICAgIH0pO1xyXG4gICAgICAgICAgICAgICAgICAgICAgICB9KTtcclxuXHJcbiAgICAgICAgICAgICAgICAgICAgLy8gUHVibGlzaCBhIG1lc3NhZ2UgdG8gYSBUb3BpY1xyXG4gICAgICAgICAgICAgICAgICAgICAgICBjbGllbnQucHVibGlzaChcIi9zaW12Y29ycG9yYXRpb25AZ21haWwuY29tL3Rlc3RcIiwgJ1NlcnZpZG9yIE9OTElORScsIGZ1bmN0aW9uKCkge1xyXG4gICAgICAgICAgICAgICAgICAgICAgICAgICAgY29uc29sZS5sb2coXCJNZXNzYWdlIHBvc3RlZC4uLlwiKTtcclxuICAgICAgICAgICAgICAgICAgICAgICAgICAgIGNsaWVudC5lbmQoKTsgLy8gQ2xvc2UgdGhlIGNvbm5lY3Rpb24gYWZ0ZXIgcHVibGlzaFxyXG4gICAgICAgICAgICAgICAgICAgICAgICB9KTtcclxuICAgICAgICAgICAgICAgICAgICB9KTtcclxuICAgICAgICAgICAgICAgIFxyXG4gICAgICAgICAgICAiXX0=
