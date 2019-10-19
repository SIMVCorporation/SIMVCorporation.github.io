                    var mqtt = require('mqtt');

					
                    var client = mqtt.connect("mqtts://postman.cloudmqtt.com:30281", {
                    username: 'GitHub',
                    password: 'SIMVGithub'
                    });

                    client.on('connect', function() { // Check you have a connection

                    // Subscribe to a Topic
                    client.subscribe('SIMV/relatorio', function() {
					
                    // When a message arrives, write it to the console
                            client.on('message', function(topic, message, packet) {
                                console.log("Received '" + message + "' on '" + topic + "'");
									var RelatorioMessage = message;
									var span = document.querySelector('h3 span');
										span.innerHTML = RelatorioMessage;
                            });
                        });
						
						                    // Subscribe to a Topic
                    client.subscribe('SIMV/relatorio2', function() {
					
                    // When a message arrives, write it to the console
                            client.on('message', function(topic, message, packet) {
                                console.log("Received '" + message + "' on '" + topic + "'");
									var RelatorioMessage2 = message;
									var span2 = document.querySelector('h4 span');
										span2.innerHTML = RelatorioMessage2;
                            });
                        });
						



                    // Publish a message to a Topic
                        client.publish('SIMV/relatorio', 'Site ONLINE', function() {
                            console.log("Message posted...");
                        });
                    });
                
            