#define irEsquerda A0
#define irCentro A1
#define irDireita A3
#define pinMotorEn1 5 //en = enable
#define pinMotorEn2 6 //sao usadas para controlar a velocidade
#define pinMotorA1 7
#define pinMotorA2 8
#define pinMotorB1
#define pinMotorB2 10

int esquerda, centro, direita = 0;
int velMotorA, velMotorB = 0;
int somaConst = 0;
char direcao = "r";

void lerSensores(){
  esquerda = analogRead(irEsquerda); 
  centro = analogRead(irCentro); 
  direita = analogRead(irDireita);

  /*      debug
  Serial.println("esq = ");
  Serial.print(esquerda);
  Serial.print("    ");
  Serial.print("centro = ");
  Serial.print(centro);
  Serial.print("    ");
  Serial.print("dir = ");
  Serial.print(direita);
  */
}

void mover(char direcao){
  switch (direcao){
    case 'f':
      digitalWrite(pinMotorA1, HIGH);
      digitalWrite(pinMotorA2, LOW);
      digitalWrite(pinMotorB1, HIGH);
      digitalWrite(pinMotorB2, LOW);
      break;
    case 'd':
      digitalWrite(pinMotorA1, HIGH);
      digitalWrite(pinMotorA2, LOW);
      digitalWrite(pinMotorB1, LOW);
      digitalWrite(pinMotorB2, HIGH);
      break;
    case 'e':
      digitalWrite(pinMotorA1, LOW);
      digitalWrite(pinMotorA2, HIGH);
      digitalWrite(pinMotorB1, HIGH);
      digitalWrite(pinMotorB2, LOW);
      break;
    case 't':
      digitalWrite(pinMotorA1, LOW);
      digitalWrite(pinMotorA2, HIGH);
      digitalWrite(pinMotorB1, LOW);
      digitalWrite(pinMotorB2, HIGH);
      break;
    case 'r':
      digitalWrite(pinMotorA1, LOW);
      digitalWrite(pinMotorA2, LOW);
      digitalWrite(pinMotorB1, LOW);
      digitalWrite(pinMotorB2, LOW);
      break;
  }
}

void movimentos(){
  if(sensor2 == 0){
    if(sensor1 == 1 && sensor3 == 1){
      mover('f');
    }
    else if(sensor1 == 0 && sensor3 == 1){
      //curva 90 graus esquerda
      mover('e');
      delay(30);
      mover("f");
      delay(30);
      mover("r");
    }
    else if(sensor1 == 1 && sensor3 == 0){
      //curva 90 graus direita
      mover("d");
      delay(30);
      mover("f");
      delay(30);
      mover("r");
    }
    else if(sensor1 == 0 && sensor3 == 0){
      //array de sensores paralelo a linha
      //manda o robo seguir reto
      //tem mais trabalho a ser feito aqui
      mover("f");
      delay(50);
    }
  }
  else if(sensor1 == 0){
    if(sensor2 == 1 && sensor3 == 1){
      mover('e');
    }
  }
  else if(sensor3 == 0){
    if(sensor1 == 1 && sensor2 == 1){
      mover('d');
    }
  }
}

void setup(){
  pinMode(irEsquerda, INPUT);
  pinMode(irCentro, INPUT);
  pinMode(irDireita, INPUT);
  pinMode(pinMotorA1, OUTPUT);
  pinMode(pinMotorA2, OUTPUT);
  pinMode(pinMotorB1, OUTPUT);
  pinMode(pinMotorB2, OUTPUT);
  pinMode(pinMotorEn1, OUTPUT);
  pinMode(pinMotorEn2, OUTPUT);

  //como nao estamos usando pwm, botei os motores sempre na máxima
  digitalWrite(pinMotorEn1, HIGH);
  digitalWrite(pinMotorEn2, HIGH);

  Serial.begin(9600);
}

void loop(){
  lerSensores();
  movimentos();
}
