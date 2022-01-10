int pin_ACS = 33; //definición del pin del sensor

void setup() {
  
  Serial.begin(115200);
}

void loop() {
  
  float voltajeSensor =get_voltage(10000);//obtenemos voltaje del sensor(10000 muestras) 
  Serial.print("Voltaje del sensor: ");
  Serial.println(voltajeSensor ,3);     
}


float get_voltage(int n_muestras)
{
  float voltage=0;
  
  for(int i=0;i<n_muestras;i++)
  {
    voltage =voltage+analogRead(pin_ACS) * (5.0 / 4095.0);    
  }
  voltage=voltage/n_muestras;
  return(voltage);
}
