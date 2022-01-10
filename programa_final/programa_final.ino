/****************************************************************************************
 Amperimetro AC
   Se obtienen mediciones de corriente AC usando un sensor ACS712
   Los cálculos se realizan en función de corriente pico(Ip) y no se hace una medición directa del IRMS, 
   por esta razón el resultado es correcto siempre que la corriente tenga forma sinusoidal completa
 Conexiones:
  -----------------
  ACS712 -> Arduino
  -----------------    
  VCC    -> 5V  
  OUT    -> A0
  GND    -> GND    
  -----------------
  *Puede cambiar la conexión a otro pin analógico del arduino modificando la variable que define el pin
 Ejemplo desarrollado por Naylamp Mechatronics bajo licencia MIT (puede copiar, modificar, integrar o redistribuir)
 
 Última modificación el 04/09/2020
 
 Más información en:
   -https://naylampmechatronics.com/blog/48_tutorial-sensor-de-corriente-acs712.html
   -https://github.com/naylampmechatronics/Ejemplos_ACS712
   
**************************************************************************************************/
int pin_ACS = 33; //definición del pin del sensor
float Sensibilidad=0.32653; //sensibilidad en V/A para nuestro sensor
float offset=0.100; // Equivale a la amplitud del ruido
void setup() {
  
  Serial.begin(115200);
}

void loop() {
  
  float Ip=get_corriente();//obtenemos la corriente pico
  float Irms=Ip*0.707; //Intensidad RMS = Ipico/(2^1/2)
  float P=Irms*220.0; // P=IV watts
  Serial.print("Ip: ");
  Serial.print(Ip,3);
  Serial.print("A , Irms: ");
  Serial.print(Irms,3);
  Serial.print("A, Potencia: ");
  Serial.print(P,3);  
  Serial.println("W");
  delay(500);     
}

float get_corriente()
{
  float voltajeSensor;
  float corriente=0;
  long tiempo=millis();
  float Imax=0;
  float Imin=0;
  while(millis()-tiempo<500)//realizamos mediciones durante 0.5 segundos
  { 
    voltajeSensor = analogRead(pin_ACS) * (5.0 / 4095.0);//lectura del sensor
    corriente=0.9*corriente+0.1*((voltajeSensor-2.527)/Sensibilidad); //Ecuación  para obtener la corriente
    if(corriente>Imax)Imax=corriente;
    if(corriente<Imin)Imin=corriente;
  }
  return(((Imax-Imin)/2)-offset);
}
