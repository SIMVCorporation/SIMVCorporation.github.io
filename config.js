                    var mqtt = require('mqtt');
					var includes = require('array-includes');
					var assert = require('assert');
					
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
										if(assert.equal(includes(RelatorioMessage, 'ONLINE'), true)){
										var span = document.querySelector('h3 span');
										span.innerHTML = RelatorioMessage;
}
									if(assert.equal(includes(RelatorioMessage, 'teste'), true)){
										var span = document.querySelector('h4 span');
										span.innerHTML = RelatorioMessage;
}
										
										
                            });
                        });


                    // Publish a message to a Topic
                        client.publish('SIMV/relatorio', 'Site ONLINE', function() {
                            console.log("Message posted...");
                        });
                    });
                
            