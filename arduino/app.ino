/*
    Este código permite controlar el LED asociado al pin 13 del Arduino. A través
   del Monitor Serie, enviando un "1" encendemos un LED y con cualquier otro caracter
   apagamos el LED
   @author Antony Garcia Gonzalez, Panama Hitek
*/

const int led_rojo = 6;
const int led_azul = 5;
int currentSelectedLed = led_rojo;
const int pause = 1000;
int intensidad = 127;


void setup() {
  analogWrite(led_rojo, intensidad);
  analogWrite(led_azul, 0);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    int valor = input.toInt();

    if ( valor > 0 && valor <= 255) {
      delay(20);
      Serial.println("EL valor leido es " + String(valor));

      fadeLed(currentSelectedLed, intensidad, valor);
      intensidad = valor;

      delay(20);
      Serial.println("La intensidad actualizada es " + String(intensidad));
    }
    else if(valor == 300) {
      changeLeds();
    }
  }
}

void fadeLed(int led, int initValue, int endValue) {

  const int fadeDelay = 30;
  const int fadeSteps = 5;
  int dif =  endValue - initValue;
  int i = 0;
  int count = 0;

  if (dif > 0) {
    /* end value es mayor */
    i = initValue;
    count = endValue;
    for( i; i < count; i += fadeSteps)
    {
      analogWrite(led, i);
      delay(fadeDelay);
    }

  }
  else if(dif < 0)
  {
    /* init value es mayor */
    i = initValue;
    count = endValue; 
    for( i; i > count; i -= fadeSteps)
    {
      analogWrite(led, i);
      delay(fadeDelay);
    }
  }
}

void changeLeds(){
  int toggledLed;

  if (currentSelectedLed  == led_rojo) {
    delay(20);
    Serial.println("Cambiando LED a Azul");
    toggledLed = led_azul;
  } else {
    delay(20);
    Serial.println("Cambiando LED a Rojo");
    toggledLed = led_rojo;
  }

  analogWrite(currentSelectedLed, 0);
  currentSelectedLed = toggledLed;
  analogWrite(currentSelectedLed, intensidad);
}