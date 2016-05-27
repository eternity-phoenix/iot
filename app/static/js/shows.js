
var y;
function get_data() {
	y = null;
    $.ajax({
        url: "/show_datas/",
        data: JSON.stringify({"sensor_id": "DHT11", "attribute": "temperature", "user_id": "18328504755"}),
        type: "POST",
        dataType: "json",
        contentType: "application/json",
        success: function(data) {
                y = parseFloat(data.data);
            },
        error: function(er) {
                alert(er);
                console.log(er);
            }
    });
}
get_data();


$(function () {                                                                     
$(document).ready(function() {                                                  
	Highcharts.setOptions({                                                     
		global: {                                                               
			useUTC: false                                                       
		}                                                                       
	});                                                                         
																				
	var chart;                                                                  
	$('#container').highcharts({                                                
		chart: {                                                                
			type: 'spline',                                                     
			animation: Highcharts.svg, // don't animate in old IE               
			marginRight: 10,                                                    
			events: {                                                           
				load: function() {                                              
																				
					// set up the updating of the chart each second             
					var series = this.series[0];                                
					setInterval(function() {                                    
						var x = (new Date()).getTime(); // current time
						series.addPoint([x, y], true, true); 
						get_data();                    
					}, 5000);//刷新速率
				}                                                               
			}                                                                   
		},                                                                      
		title: {                                                                
			text: 'CPU动态走势图--1秒'                                            
		},                                                                      
		xAxis: {                                                                
			type: 'datetime',                                                   
			tickPixelInterval: 100                                              
		},                                                                      
		yAxis: {                                                                
			title: {                                                            
				text: 'CPU动态走势图--1秒'                                                   
			},                                                                  
			plotLines: [{                                                       
				value: 0,                                                       
				width: 1,                                                       
				color: '#808080'                                                
			}]                                                                  
		},                                                                      
		tooltip: {                                                              
			formatter: function() {                                             
					return '<b>'+ this.series.name +'</b><br/>'+                
					Highcharts.dateFormat('%Y-%m-%d %H:%M:%S', this.x) +'<br/>'+
					Highcharts.numberFormat(this.y, 2);                         
			}                                                                   
		},                                                                      
		legend: {                                                               
			enabled: false                                                      
		},                                                                      
		exporting: {                                                            
			enabled: false                                                      
		},                                                                      
		series: [{                                                              
			name: 'Random data',                                                
			data: (function() {                                                 
				// generate an array of random data                             
				var data = [],                                                  
					time = (new Date()).getTime(),                              
					i;                                                          
																				
				for (i = -19; i <= 0; i++) {                                    
					data.push({                                                 
						x: time + i * 1000,                                     
						y: 1//Math.random() 初始化时前20个数据                                       
					});                                                         
				}                                                               
				return data;                                                    
			})()                                                                
		}]                                                                      
	});                                                                         
});                                                                             
																				
});      