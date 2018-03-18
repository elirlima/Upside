//Projeto UPSIDE
//SISTEMA AUTOMATICO DE CAPTACAO DE AGUA DA CHUVA
/* 
 *  O sistema funciona com um sensor de vazao que ativa uma solenoide,
 *  para permitir a entrada de agua. A medicao do nivel eh feita por
 *  um sensor ultrassonico, que desativa a solenoide, impedindoa a passagem
 *  da agua para o reservatorio.
 */

// include the library´s code:
//#include <LiquidCrystal.h>

float vazao; //Variável para armazenar o valor em L/min
int contaPulso; //Variável para a quantidade de pulsos

const int ultrasonico = 10; //pino ECHO
const int pingTrigger = 11; //trigger do ultrasonico
const int rele = 12; //rele para acionamento da solenoide
const int ledVerde = 45; 
const int ledVermelho = 49;
const int ledAmarelo = 47;
int nivel_de_agua; //armazena o valor do nivel de agua em porcentagem
float cm;
long duration; //duracao do pulso do ultrasonico
float distance; //Ultrasonico
int k = 0; //cotador no if

//const int botton = 18; //Botão do attach do sistema

//volatile byte state = LOW; //Estado attach

// initialize the library with the numbers of the interface pins
//LiquidCrystal lcd(8, 7, 6, 5, 4, 3);

void setup()
{
  pinMode(pingTrigger, OUTPUT);
  pinMode(ultrasonico, INPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  //pinMode(botton, INPUT_PULLUP);
  pinMode(rele, OUTPUT);
  
  //Interrupção do sistema com a função bottonVariation.
  //attachInterrupt(digitalPinToInterrupt(botton), bottonVariation, RISING);
  
  Serial.begin(9600);
  
  //lcd.begin(16, 2);

  pinMode(2, INPUT);
  attachInterrupt(0, incpulso, RISING); //Configura o pino 3(Interrupção 1) interrupção
}

void loop() {

  ultra_sensor();

  vazao_sensor();
  
  delay(1000);

  if(vazao > 0.5 /*&& state == LOW*/ && cm > 5 ){ //AJUSTAR A CONFIGURACAO DESTE IF PARA O SENSOR DE VAZAO
    //lcd.clear();
    //lcd.setCursor(0, 0);
    Serial.println("COMPORTA ABERTA");
    //lcd.print("COMPORTA FECHADA"); 
    //lcd.setCursor(0, 1);
    //lcd.print("Nivel:");
    Serial.print("Vazao: ");
    //lcd.print(nivel_de_agua);
    Serial.println(vazao);
    Serial.println(cm);
    //do{
    digitalWrite(rele, LOW); //RELE EM LOW, POREM, LIGADO.
    //}while(k < 6);
    //k++;
    }

  else{
    //lcd.clear();
    //lcd.setCursor(0, 0);
    Serial.println("COMPORTA FECHADA");
    //lcd.print("COMPORTA FECHADA"); 
    //lcd.setCursor(0, 1);
    //lcd.print("Nivel:");
    Serial.print("vazao: ");
    //lcd.print(nivel_de_agua);
    Serial.println(vazao);
    Serial.println(cm);
    digitalWrite(rele, HIGH);
   }
}

void vazao_sensor(){

  contaPulso = 0;   //Zera a variável para contar os giros por segundos
  sei();      //Habilita interrupção
  delay (3000); //Aguarda  segundo AUMENTEI O TEMPO AQUI PRA ESTABILIZAR OS VALORES!!!!!!!!!
  cli();      //Desabilita interrupção
  
  vazao = contaPulso / 5.5; //Converte para L/min
  }

void ultra_sensor(){
 
  //ULTRASONICO
  digitalWrite(pingTrigger, LOW);
  delayMicroseconds(2);
  digitalWrite(pingTrigger, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingTrigger, LOW);

  duration = pulseIn(ultrasonico, HIGH);

  //Converte o tempo em distancia
  cm = microsecondsToCentimeters(duration);

  if(cm < 8.0){
    digitalWrite(ledVermelho, HIGH);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVerde, LOW);
    }

  else if(cm >= 8.0 && cm < 16.0){
    digitalWrite(ledVermelho, LOW);
    digitalWrite(ledAmarelo, HIGH);
    digitalWrite(ledVerde, LOW);
    }

  else if(cm >= 18.0){
    digitalWrite(ledVermelho, LOW);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVerde, HIGH);
    }
  
  //para eventuais testes
  //Serial.println("Ultrasonico");
  //Serial.print(cm);
  //Serial.println();
  }

float microsecondsToCentimeters(float microseconds){
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return (microseconds / 29) ;// 2;
}

/*void bottonVariation(){
  state = !state;
  if(state == HIGH){
  digitalWrite(led, HIGH);
  }
  else{
  digitalWrite(led, LOW);
  }
}*/

void incpulso (){ 
  contaPulso++; //Incrementa a variável de contagem dos pulsos
}


