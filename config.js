                    var mqtt = require('mqtt');

					
                    var client = mqtt.connect("mqtts://postman.cloudmqtt.com:30281", {
                    username: 'GitHub',
                    password: 'SIMVGithub'
                    });

                    client.on('connect', function() { // Check you have a connection

                    // Subscribe to a Topic
                    client.subscribe('SIMV/relatorio', function() {
					
                    // When a message arrives, write it to the console
                            client.on('RelatorioMessage', function(topic, message, packet) {
                                console.log("Received '" + RelatorioMessage + "' on '" + topic + "'");
									var message = RelatorioMessage;
									var span = document.querySelector('h3 span');
										span.innerHTML = message;
                            });
                        });
						



                    // Publish a message to a Topic
                        client.publish('SIMV/relatorio', 'Site ONLINE', function() {
                            console.log("Message posted...");
                        });
                    });
                
            