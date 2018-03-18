#include <Servo.h>

Servo motorInclinacao;

// Sensores de luminosidade para a Inclinacao
int sensorInclinacaoA = A0,
    sensorInclinacaoB = A1; 
    
// Valor da leitura dos sensores de Inclinacao
int valorInclinacaoA, 
    valorInclinacaoB; 

// Ajuste da velocidade de reacao dos motores, quando menor mais rapido
int deslocamento, 
    reacao = 20; 

// Diferenca entre a leitura dos sensores de Rotacao e Inclinacao
int diferencaLeitura; 

// Controle da posicao dos motores em graus
int posicaoAtual, 
    posicaoNova; 

// Valor toleravel entre as diferencas nas leituras dos sensores
int tolerancia = 10; 
    
// Calibracao dos motores, estado inicial em graus
int posicaoInicial = 90;     

// Debugging
boolean debugging = true; 

void setup() {
  // Definindo o sensor de Inclinacao  
  pinMode(sensorInclinacaoA, INPUT);
  pinMode(sensorInclinacaoB, INPUT);
  
  // Atribuindo os motores
  motorInclinacao.attach(8);
  
  // Calibrando os motores
  motorInclinacao.write(posicaoInicial);    
  
  if ( debugging ) Serial.begin(9600);
}
void loop() 
{ 
  valorInclinacaoA = analogRead(sensorInclinacaoA);
  valorInclinacaoB = analogRead(sensorInclinacaoB);
  
  diferencaLeitura = abs(valorInclinacaoA - valorInclinacaoB);
  deslocamento = max((diferencaLeitura / reacao), 1);
  
  posicaoAtual = motorInclinacao.read();

  if(motorInclinacao.read() > 130) {posicaoAtual = 130;}
  if(motorInclinacao.read() < 50) {posicaoAtual = 50;}
  
  if ( diferencaLeitura > tolerancia ) { 
    if ( valorInclinacaoA > valorInclinacaoB ) {    
      posicaoNova = posicaoAtual - deslocamento;
     }
    else {
      posicaoNova = posicaoAtual + deslocamento;
    }
  
    motorInclinacao.write(posicaoNova);
    
    if ( debugging ) {
      Serial.print("Inclinando:   ");
      Serial.print("Grau:("); Serial.print(posicaoNova); Serial.print(") A:");
      Serial.print(analogRead(sensorInclinacaoA)); Serial.print(" | B:"); Serial.println(analogRead(sensorInclinacaoB));
    }
  }
} 

