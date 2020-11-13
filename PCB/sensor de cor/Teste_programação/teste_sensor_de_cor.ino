/* vcc - gnd - s3_2 - s2_2 - out_2 - s3 - s2 - out
 * TABELA DE LEITURA DE COR
 *            s2    s3
 * Vermelho  LOW    LOW
 * verde     LOW    HIGH
 * Azul      HIGH   LOW
 * Luz       HIGH   HIGH
 * 
 */
#include "sensor_de_cor.h"
 
//sensor de cor 1 
#define sensorOut_1 47
#define s2_1 49
#define s3_1 51

//sensor de cor 2
#define sensorOut_2 41
#define s2_2 43
#define s3_2 45

SensorCor esquerda;
SensorCor direita;
void setup() {
  Serial.begin(9600);

  esquerda.declarar(sensorOut_1, s2_1, s3_1);
  direita.declarar(sensorOut_2, s2_2, s3_2);
  esquerda.calibrarCor();
  direita.calibrarCor();
}

void loop() {
  esquerda.lerCor();
  Serial.print("esquerda    ");
  esquerda.printarCor();
  direita.lerCor();
  Serial.print("direita     ");
  direita.printarCor();
  delay(1000);

//  Serial.println(esquerda.interpretarCor());
}
