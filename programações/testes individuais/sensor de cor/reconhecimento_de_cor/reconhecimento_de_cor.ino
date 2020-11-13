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
#define sensorOut_1 2
#define s2_1 3
#define s3_1 4

SensorCor esquerda;
void setup() {
  Serial.begin(9600);

  esquerda.declarar(sensorOut_1, s2_1, s3_1);
  for(int i = 0; i < 1000; i++) {
   Serial.println(i);
  esquerda.calibrarCor();
  }
}

void loop() {
  esquerda.lerCor();
  Serial.print("esquerda    ");
  Serial.print(esquerda.retornaCor());
  Serial.print("    ");
  esquerda.printarCor();
  
  delay(500);

//  Serial.println(esquerda.interpretarCor());
}
