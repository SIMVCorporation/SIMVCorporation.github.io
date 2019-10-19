                    var mqtt = require('mqtt');

					
                    var client = mqtt.connect("mqtts://postman.cloudmqtt.com:10281", {
                    username: 'fdbljoqc',
                    password: 'nVpPA7ekAFeW'
                    });

                    client.on('connect', function() { // Check you have a connection

                    // Subscribe to a Topic
                    client.subscribe('SIMV/testes', function() {
					
                    // When a message arrives, write it to the console
                            client.on('message', function(topic, message, packet) {
                                console.log("Received '" + message + "' on '" + topic + "'");
                            });
                        });

                    // Publish a message to a Topic
                        client.publish('SIMV/testes', 'Servidor ONLINE', function() {
                            console.log("Message posted...");
                            client.end(); // Close the connection after publish
                        });
                    });
                
            