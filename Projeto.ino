#include <VarSpeedServo.h>

//Cria objeto para controlar o servo direito
VarSpeedServo servo_direito;
//Cria objeto para controlar o servo esquerdo
VarSpeedServo servo_esquerdo;
 
int pino_x = A0; //Pino ligado ao X do joystick
int pino_y = A1; //Pino ligado ao Y do joystick
int val_x;   //Armazena o valor do eixo X
int val_y;   //Armazena o valor do eixo Y
int auxY = 90;
int auxX = 90;

int motorDireito = 7;
int motorEsquerdo = 8;
int botaoExterno = 6;
int cont = 0;
int ped = 0;

//Variáveis do debouncer
int UltimoBotao = 0;
int EstadoBotao = 0;

void setup(){
  //Define a porta a ser ligada ao servo direito
  servo_direito.attach(7, 1, 180);
  //Define a porta a ser ligada ao servo esquerdo
  servo_esquerdo.attach(8, 1, 180);
  //Define o Baud Rate
  Serial.begin(57600);
}
 
void loop(){
  EstadoBotao = digitalRead(botaoExterno);
  if (EstadoBotao != UltimoBotao){
    if (EstadoBotao == HIGH){
      delay(50);
      cont++;
      if (cont%2 == 0) ped = 0;
      else ped = 1;
    }
  }
  UltimoBotao = EstadoBotao;

  if (ped == 0){
    //Recebe o valor do joystick, eixo X
    val_x = analogRead(pino_x);
    //Converte o valor lido para um valor entre 1 e 180 graus
    val_x = map(val_x, 0, 1023, 1, 180);
    //Move o servo base para a posicao definida pelo joystick
    servo_direito.slowmove(val_x, 60);
    //Recebe o valor do joystick, eixo Y
    val_y = analogRead(pino_y);
    //Converte o valor lido para um valor entre 1 e 180 graus
    val_y = map(val_y, 0, 1023, 1, 180);
    //Move o servo inclinacao para a posicao definida pelo joystick
    servo_esquerdo.slowmove(val_y, 60);
  }
  else{
    int cmd;
    if (Serial.available()) {
      cmd = Serial.readString().toInt();
      Serial.print(cmd);
      if (cmd == 0){
        auxY -= 40;
        servo_esquerdo.slowmove(auxY, 60);
      }
      else if (cmd == 3){
        auxY += 40;      
        servo_esquerdo.slowmove(auxY, 60);
      }
      else if (cmd == 1){ //direita
        auxX += 40; 
        servo_direito.slowmove(auxX, 60);
      }
      else if (cmd == 2){
        auxX -= 40; 
        servo_direito.slowmove(auxX, 60);
      }
    }
  }
}