// C++ code
//
int TRIG = 13;
int ECHO = 10;
int BUZZ = 2;
long duracion = 0;
long distancia = 0;

void setup()
{
  pinMode(TRIG, OUTPUT);//pin de salida del diparador
  pinMode(ECHO, INPUT);//pin de entrada del pulso sonoro
  pinMode(BUZZ, OUTPUT);// pin de salida del buzzer
  Serial.begin(9600);//se inicializa la comunicación serie
}

void loop()
{
    digitalWrite (TRIG, LOW);
    delay(10);
    digitalWrite (TRIG, HIGH);
      delay(10);
      digitalWrite (TRIG, LOW);

      duracion = pulseIn (ECHO, HIGH);

      distancia = duracion / 58;
      Serial.println (distancia);

      if (distancia <= 60)
    {
    	tone (BUZZ, 1400, 600);//suena el buzzer (frecuencia=1400) 
                               
    } 
       else if(distancia > 60 && distancia <= 150)
    {
             tone (BUZZ, 900, 400);//suena el buzzer (frecuencia=400)	
    }
        else
    {
             noTone(BUZZ);//buzzer apagado
    }
    delay (100);
} 
