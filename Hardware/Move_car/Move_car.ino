#include <SoftwareSerial.h>   // Incluimos la librería  SoftwareSerial 
#include <Servo.h>

Servo myservo;

#define PWMA 3
#define AIN1 4
#define AIN2 5
#define PWMB 6
#define BIN1 7
#define BIN2 8


SoftwareSerial BT(12,13);                         // Definimos los pines RX y TX del Arduino conectados al Bluetooth

int vel=255; // Velocidad de los motores
bool activate = false;

void forward() {
  analogWrite(PWMA, vel);
  analogWrite(PWMB, vel);
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
}
void backward() {
  analogWrite(PWMA, vel);
  analogWrite(PWMB, vel);
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
}
void left() {
  analogWrite(PWMA, vel);
  analogWrite(PWMB, vel);
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
}
void right() {
  analogWrite(PWMA, vel);
  analogWrite(PWMB, vel);
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
}
void stop() {
  analogWrite(PWMA, _ );
  analogWrite(PWMB, _ ); //Que valores tendrian los motores para que paren ?
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);
}

void setup()
{
  BT.begin(9600);       // Inicializamos el puerto serie BT que hemos creado
  Serial.begin(115200);   // Inicializamos  el puerto serie  
    pinMode(PWMA, OUTPUT);
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(PWMB, OUTPUT);
    pinMode(BIN1, OUTPUT);
    pinMode(BIN2, OUTPUT);
    stop();
    myservo.attach(9);
    
}
 
void loop()
{
  if(BT.available())    // Si llega un dato por el puerto BT se envía al monitor serial
  {
    char c = BT.read();
    if(c == 'z'){
        activate = true;
    }
    if(c == 'x'){
        activate = false;
        stop();
    }

    if(activate){
        switch(c) {
        case 'G':
            forward();
            break;
        case '_':
            backward();
            break;
          //Movimiento para izquierda y derecha ???
        case 'K':
            stop();
            break;
        case 'L':
            myservo.write(0);
            break;
        case 'M':
            myservo.write(90);
            break;
        }
    }
    
    Serial.write(c);
  }
 
}
