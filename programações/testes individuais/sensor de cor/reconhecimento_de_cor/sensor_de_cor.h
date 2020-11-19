class SensorCor{
  private:
  byte out, s2, s3; //portas do sensor
  byte Red, Green, Blue, Light; //valor atual lido
  int WhiteAverage[4] = {1000, 1000, 1000, 1000};
  int BlackAverage[4] = {0, 0, 0, 0};
  byte laststate, state, cont;
  public:
  
  void declarar(byte outpin, byte s2pin, byte s3pin){ //Declarção dos pinos
    out = outpin; s2 = s2pin; s3 = s3pin;
    pinMode(out, INPUT);
    pinMode(s2, OUTPUT);
    pinMode(s3, OUTPUT);
  }
  void calibrarCor(){
    delay(1);
    for (byte aux2 = 0; aux2 < 4; aux2++){
      switch (aux2){
      case 0: digitalWrite(s2, LOW); digitalWrite(s3, LOW);break;
      case 1: digitalWrite(s2, HIGH); digitalWrite(s3, HIGH);break;
      case 2: digitalWrite(s2, LOW); digitalWrite(s3, HIGH);break;
      case 3: digitalWrite(s2, HIGH); digitalWrite(s3, LOW);break;
      }
      int aux3 = pulseIn(out, LOW);
      if (aux3 > BlackAverage[aux2]){
        BlackAverage[aux2] = (BlackAverage[aux2]+ aux3)/2;
      }
      if (aux3 <= WhiteAverage[aux2]){
        WhiteAverage[aux2] = (WhiteAverage[aux2]+ aux3)/2;
      }
    }
  
    for (byte aux2 = 0; aux2 < 4; aux2++){
    //    BlackAverage[aux2] += (BlackAverage[aux2]/100)*10;
    }
  }

  void lerCor(){
    //lê o valor 
    int SensorReturn;
    
    digitalWrite(s2, LOW);
    digitalWrite(s3, LOW);
    SensorReturn = map(pulseIn(out, LOW), WhiteAverage[0], BlackAverage[0], 0, 255);
    if (SensorReturn >= 255){Red = 255;}
    else if(SensorReturn <= 0){Red = 0;}
    else{Red = SensorReturn;}
    
    digitalWrite(s2, HIGH);
    digitalWrite(s3, HIGH);
    SensorReturn = map(pulseIn(out, LOW), WhiteAverage[1], BlackAverage[1], 0, 255);
    if (SensorReturn >= 255){Green = 255;}
    else if(SensorReturn <= 0){Green = 0;}
    else{Green = SensorReturn;}
  
    digitalWrite(s2, LOW);
    digitalWrite(s3, HIGH);
    SensorReturn = map(pulseIn(out, LOW), WhiteAverage[2], BlackAverage[2], 0, 255);
    if (SensorReturn >= 255){Blue = 255;}
    else if(SensorReturn <= 0){Blue = 0;}
    else{Blue = SensorReturn;}

    digitalWrite(s2, HIGH);
    digitalWrite(s3, LOW);
    SensorReturn = map(pulseIn(out, LOW), WhiteAverage[3], BlackAverage[3], 0, 255); 
    if (SensorReturn >= 255){Light = 255;}
    else if(SensorReturn <= 0){Light = 0;}
    else{Light = SensorReturn;}
  }

  void printarCor() {
    Serial.print(Red);
    Serial.print(" ");
    Serial.print(Green);
    Serial.print(" ");
    Serial.print(Blue);
    Serial.print(" ");
    Serial.print(Light);
    Serial.println(" ");
  }

  byte retornaCor () { //Função que retorna a cor lida na função lerCor(), 1 para preto, 2 para verde e 3 para azul
    lerCor();
    
    if(Red < 50&& Green < 50&& Blue < 50&& Light < 50) {
      return 1; //branco
    }
    else if(Green < Red && Green < Blue){
      return 2;// verde
    }
    else if(Red < Green && Red < Blue) {
      return 3;//  vermelho
    }
    else if(Blue < Red && Blue < Green && Light < 180) {
      return 4;//  azul
    }
    return 5;
    }
  };
