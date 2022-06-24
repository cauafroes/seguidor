#define irEsquerda 2
#define irCentro 3
#define irDireita 4
#define pinMotorEn1 5 //en = enable
#define pinMotorEn2 6 //sao usadas para controlar a velocidade
#define pinMotorA1 7
#define pinMotorA2 8
#define pinMotorB1 9
#define pinMotorB2 10

int esquerda, centro, direita = 0;
int velMotorA, velMotorB = 0;
int somaConst = 0;
char direcao = "r";

void lerSensores(){
  esquerda = digitalRead(irEsquerda); 
  centro = digitalRead(irCentro); 
  direita = digitalRead(irDireita);

  Serial.print("esq = ");
  Serial.print(esquerda);
  Serial.print("    ");
  Serial.print("  centro = ");
  Serial.print(centro);
  Serial.print("    ");
  Serial.print("  dir = ");
  Serial.println(direita);

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
  if(centro == 0){
    if(esquerda == 1 && direita == 1){
      mover('f');
    }
    else if(esquerda == 0 && direita == 1){
      //curva 90 graus esquerda
      mover('e');
      delay(30);
      mover("f");
      delay(30);
      mover("r");
    }
    else if(esquerda == 1 && direita == 0){
      //curva 90 graus direita
      mover("d");
      delay(30);
      mover("f");
      delay(30);
      mover("r");
    }
    else if(esquerda == 0 && direita == 0){
      //array de sensores paralelo a linha
      //manda o robo seguir reto
      //tem mais trabalho a ser feito aqui
      mover("f");
      delay(50);
    }
  }
  else if(esquerda == 0){
    if(centro == 1 && direita == 1){
      mover('e');
    }
  }
  else if(direita == 0){
    if(esquerda == 1 && centro == 1){
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

  //como nao estamos usando pwm, botei os motores sempre na máxima caso a ponte h nao tenha os jumpers
  digitalWrite(pinMotorEn1, HIGH);
  digitalWrite(pinMotorEn2, HIGH);

  Serial.begin(115200);
}

void loop(){
  lerSensores();
  movimentos();
  delay(50);
}
