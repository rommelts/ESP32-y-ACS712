float Sensibilidad=0.524; //sensibilidad en Voltios/Amperio para sensor de 5A

void setup() {
  
  Serial.begin(115200);
}

void loop() {
  
  float I=get_corriente(200);//obtenemos la corriente promedio de 500 muestras 
  Serial.print("Corriente: ");
  Serial.println(I,3); 
  delay(100);     
}

float get_corriente(int n_muestras)
{
  float voltajeSensor;
  float corriente=0;
  for(int i=0;i<n_muestras;i++)
  {
    voltajeSensor = analogRead(33) * (5.0 / 4095.0);////lectura del sensor
    corriente=corriente+(voltajeSensor-3.646)/Sensibilidad; //Ecuación  para obtener la corriente
  }
  corriente=corriente/n_muestras;
  return(corriente);
}
