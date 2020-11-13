class SensorCor{
  private:
  byte out, s2, s3; //portas do sensor
  byte Redv, Greenv, Bluev, Lightv; //valor atual lido
  int whitep[4] = {1000, 1000, 1000, 1000};
  int Blackp[4] = {0, 0, 0, 0};
  byte laststate, state, cont;
  public:
  
  void declarar(byte outpin, byte s2pin, byte s3pin){
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
      if (aux3 > Blackp[aux2]){
        Blackp[aux2] = (Blackp[aux2]+ aux3)/2;
      }
      if (aux3 <= whitep[aux2]){
        whitep[aux2] = (whitep[aux2]+ aux3)/2;
      }
    }
  
    for (byte aux2 = 0; aux2 < 4; aux2++){
    //    Blackp[aux2] += (Blackp[aux2]/100)*10;
    }
  }

  void lerCor(){
    //lê o valor 
    int Sensretun;
    
    digitalWrite(s2, LOW);
    digitalWrite(s3, LOW);
    Sensretun = map(pulseIn(out, LOW), whitep[0], Blackp[0], 0, 255);
    if (Sensretun >= 255){Redv = 255;}
    else if(Sensretun <= 0){Redv = 0;}
    else{Redv = Sensretun;}
    
    digitalWrite(s2, HIGH);
    digitalWrite(s3, HIGH);
    Sensretun = map(pulseIn(out, LOW), whitep[1], Blackp[1], 0, 255);
    if (Sensretun >= 255){Greenv = 255;}
    else if(Sensretun <= 0){Greenv = 0;}
    else{Greenv = Sensretun;}
  
    digitalWrite(s2, LOW);
    digitalWrite(s3, HIGH);
    Sensretun = map(pulseIn(out, LOW), whitep[2], Blackp[2], 0, 255);
    if (Sensretun >= 255){Bluev = 255;}
    else if(Sensretun <= 0){Bluev = 0;}
    else{Bluev = Sensretun;}

    digitalWrite(s2, HIGH);
    digitalWrite(s3, LOW);
    Sensretun = map(pulseIn(out, LOW), whitep[3], Blackp[3], 0, 255); 
    if (Sensretun >= 255){Lightv = 255;}
    else if(Sensretun <= 0){Lightv = 0;}
    else{Lightv = Sensretun;}
  }

};
