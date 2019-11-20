var mqtt = require('mqtt');
var includes = require('includes');
var client = mqtt.connect("mqtts://postman.cloudmqtt.com:30281", {
	username: 'GitHub',
	password: 'SIMVGithub'
});

client.on('connect', function() {
	var result = message.includes('Temperatura');
	var umidade = message.includes('Umidade');
		client.subscribe('SIMV/relatorio', function() {
			client.on('message', function(topic, message, packet) {
				console.log("Received '" + message + "' on '" + topic + "'");
				console.log(result);
				console.log(umidade);
					if(result == true){
						var span = document.querySelector('span2')
						span.innerHTML = message
					} else if(umidade == true) 	{
						var span = document.querySelector('span3')
						span.innerHTML = message
					} else {
						var span = document.querySelector('span4')
						span.innerHTML = message	
					}							
			});
		});
	client.publish('SIMV/status', 'Site ONLINE', function() {
		console.log("Message posted...");	
		var img = document.getElementById("SiteStatus");
		img.src = "/images/SiteOn.png";
	});
});
                
            
