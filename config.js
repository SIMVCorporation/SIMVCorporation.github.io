                    var mqtt = require('mqtt');

					
                    var client = mqtt.connect("mqtt://mqtt.dioty.co:8080", {
                    username: 'simvcorporation@gmail.com',
                    password: 'dad74363'
                    });

                    client.on('connect', function() { // Check you have a connection

                    // Subscribe to a Topic
                    client.subscribe('/simvcorporation@gmail.com/test', function() {
					
                    // When a message arrives, write it to the console
                            client.on('message', function(topic, message, packet) {
                                console.log("Received '" + message + "' on '" + topic + "'");
                            });
                        });

                    // Publish a message to a Topic
                        client.publish('/simvcorporation@gmail.com/test', 'Servidor ONLINE', function() {
                            console.log("Message posted...");
                            client.end(); // Close the connection after publish
                        });
                    });
                
            