                    var mqtt = require('mqtt');
					var includes = require('includes');
					
                    var client = mqtt.connect("mqtts://postman.cloudmqtt.com:30281", {
                    username: 'GitHub',
                    password: 'SIMVGithub'
                    });

                    client.on('connect', function() {

                    client.subscribe('SIMV/relatorio', function() {
					
                            client.on('message', function(topic, message, packet) {
                                console.log("Received '" + message + "' on '" + topic + "'");
									var result = message.includes('ONLINE');
									//N�O ESQUECER DE ARRUMAR OS ICONES OU RETIRA-LOS
	var SiteStatus = result;
	var img = document.getElementById("SiteStatus");
function trocaImg(SiteStatus){
  if (SiteStatus == true)
    {
      img.src = "/Media.Style/SiteOff.png";
    }
  else
    {
      img.src = "/Media.Style/SiteOn.png";
    }
};
									//N�O ESQUECER DE ARRUMAR OS ICONES OU RETIRA-LOS
									console.log(result);
										if(result == true){
											var span = document.querySelector('h3 span')
											span.innerHTML = message
										} else 	{
											var span = document.querySelector('h3 span2')
											span.innerHTML = message
										}								
                            });
                        });


                        client.publish('SIMV/relatorio', 'Site ONLINE', function() {
                            console.log("Message posted...");
                        });
                    });
                
            