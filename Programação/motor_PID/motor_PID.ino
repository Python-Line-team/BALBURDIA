#include <SparkFun_TB6612.h>

#define AIN1 36 // 32 //
#define BIN1 32 // 36 //
#define AIN2 30 // 38 //
#define BIN2 38 // 30 //
#define PWMA 9 // 10 //
#define PWMB 10 // 9 //
#define STBY 34

const int offsetA = 1;
const int offsetB = 1;

byte velocidade = 200;

Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);
//==============================================
#include <QTRSensors.h>

QTRSensors qtr;

const uint8_t SensorCount = 8;
uint16_t sensorValues[SensorCount];

//float  KP = 20, KI = 0.5, KD = 15;
float  KP = 7, KI = 0.5, KD = 6;
int ERRO, erroAnterior = 0, setPoint = 3500;
int velocidadeMotor1 = velocidade;
int velocidadeMotor2 = velocidade;
//==============================================
byte seguirLinha = 1;
void setup(){
  // configure the sensors
  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){A7, A6, A5, A4, A3, A2, A1, A0}, SensorCount);

  delay(500);

  for (uint16_t i = 0; i < 200; i++){
    
      if (i < 25 || (i > 50 && i < 75)|| (i > 100 && i < 125)|| (i > 150 && i < 175)){
        forward(motor1, motor2, 150);
      }else{
        back(motor1, motor2, -150);
      }
    qtr.calibrate();
  }
  brake(motor1, motor2);
  Serial.begin(9600);
  delay(5000);  
}

void loop(){
  while(seguirLinha == 1){
    int ERRO = qtr.readLineBlack(sensorValues) - setPoint;
    ERRO = map(ERRO, -3500, 3500, -velocidade, velocidade);
    int sinalControlador = KP * ERRO + KI* ERRO + KD * (ERRO - erroAnterior);
    erroAnterior = ERRO;
  
    int novaVelocidadeMotor1 = velocidadeMotor1 - sinalControlador;
    int novaVelocidadeMotor2 = velocidadeMotor2 + sinalControlador;
  
    if (novaVelocidadeMotor1 < 0)
      novaVelocidadeMotor1 = 0;
    if (novaVelocidadeMotor2 < 0)
      novaVelocidadeMotor2 = 0;
   
    if (novaVelocidadeMotor1 > 255)
      novaVelocidadeMotor1 = 255;
    if (novaVelocidadeMotor2 > 255)
      novaVelocidadeMotor2 = 255;
  
    motor1.drive(novaVelocidadeMotor1);
    motor2.drive(novaVelocidadeMotor2);
 
    qtr.readCalibrated(sensorValues);
  
    for(int aux = 0;aux <= 5; aux++){
       if (sensorValues[aux]> 800 && sensorValues[aux+1]> 800 &&
       sensorValues[aux+2]> 800 && sensorValues[aux+3]> 800){
          brake(motor1, motor2);
          seguirLinha = 0;
       }
    }
  }
}
