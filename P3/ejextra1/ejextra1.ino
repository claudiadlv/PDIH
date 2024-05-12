// C++ code
//
void setup()
{
  pinMode(LED_BUILTIN, OUTPUT); // Configurar el pin del LED integrado como salida
  pinMode(10, OUTPUT); // Configurar pin 10 como salida
  pinMode(11, OUTPUT); // Configurar pin 11 como salida
  pinMode(12, OUTPUT); // Configurar pin 12 como salida
  pinMode(13, OUTPUT); // Configurar pin 13 como salida
}

int primerLED = 2; // Variable para controlar el primer LED

void loop()
{
  // Controlar la secuencia de encendido de los LEDs
  digitalWrite(13, HIGH);
  delay(250);
  digitalWrite(13, LOW);
  delay(100);

  digitalWrite(12, HIGH);
  delay(100);
  digitalWrite(12, LOW);
  delay(100);

  digitalWrite(11, HIGH);
  delay(100);
  digitalWrite(11, LOW);
  delay(100);

  digitalWrite(10, HIGH);
  delay(100);
  digitalWrite(10, LOW);
  delay(100);

  // Repetir la secuencia en orden inverso
  digitalWrite(10, HIGH);
  delay(100);
  digitalWrite(10, LOW);
  delay(100);

  digitalWrite(11, HIGH);
  delay(100);
  digitalWrite(11, LOW);
  delay(100);

  digitalWrite(12, HIGH);
  delay(100);
  digitalWrite(12, LOW);
  delay(100);

  // Controlar la secuencia de encendido de los LEDs según la variable primerLED
  if (primerLED % 2 == 0) {
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(100);
  } else {
    digitalWrite(13, LOW);
    delay(100);
  }

  // Incrementar la variable primerLED
  primerLED++;
}
