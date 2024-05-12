// C++ code
//
int led = 9;
int intensidad;

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

void loop() {
  intensidad = analogRead(A0);
  
  Serial.print("El valor es de: ");
  Serial.println(intensidad);
  delay(100);
  
  // Mapear la intensidad de luz al rango de valores de brillo del LED
  int brillo = map(intensidad, 0, 1023, 0, 255);
  
  // Establecer el brillo del LED según la intensidad de luz
  analogWrite(led, brillo);
}
