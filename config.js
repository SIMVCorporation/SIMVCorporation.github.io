                    var mqtt = require('mqtt');

					
                    var client = mqtt.connect("mqtts://postman.cloudmqtt.com:30281", {
                    username: 'GitHub',
                    password: 'SIMVGithub'
                    });

                    client.on('connect', function() { // Check you have a connection

                    // Subscribe to a Topic
                    client.subscribe('SIMV/message', function() {
					
                    // When a message arrives, write it to the console
                            client.on('message', function(topic, message, packet) {
                                console.log("Received '" + message + "' on '" + topic + "'");
                            });
                        });

                    // Publish a message to a Topic
                        client.publish('SIMV/status', 'Servidor ONLINE', function() {
                            console.log("Message posted...");
                            client.end(); // Close the connection after publish
                        });
                    });
                
            