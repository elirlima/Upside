//Sistema de irrigacao automatico
//Colegio Santa Maria

//Define pino no qual o sensor está conectado
#define pino_sinal_analogico A0
#define ledVermelho 10
#define ledAmarelo 9
#define ledVerde 8

//Variaveis dos led`s
int Leitura_umidade, Bomba = 7;

void setup() {
 //Inicia comunicação serial
  Serial.begin(9600);
  
  //Configura o pino A0 como entrada para leitura do sensor
  pinMode(pino_sinal_analogico, INPUT);
  //Pino de acionamento da bomba
  pinMode(Bomba, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
}

void loop() {
  //Le o valor do pino A0 do sensor
  Leitura_umidade = analogRead(pino_sinal_analogico);
  
  //Converte o valor analogico para porcentagem. Valores do map() invertidos para uma leitura mais intuitiva.
  Leitura_umidade = map(Leitura_umidade, 0, 1024, 100, 0);
 
  //Mostra o valor da porta analogica no serial monitor
  Serial.print("Porta analogica: ");
  Serial.println(Leitura_umidade);

  //Solo seco. Se a leitura for abaixo de 20%, a bomba vai ficar ligada até que a leitura seja 80% e apos isso ela desliga.
  //Estes parametros podem ser alterados de acordo com o tipo e plantacao e suas necessidades.
  if(Leitura_umidade <= 10)
  {
   digitalWrite(Bomba, HIGH);
   //do{
   //digitalWrite(Bomba, HIGH);
   //}while(Leitura_umidade == 50); 
   nivel_umidade();
   for(int i=0; i<10; i++){
    delay(1000);
    }
  }

  else
  {
   digitalWrite(Bomba, LOW);
   nivel_umidade();
  }
  
  delay(100);
}

//Funcao para leitura do nivel de umidade atraves dos led`s
void nivel_umidade(){
  if(Leitura_umidade < 25){
    digitalWrite(ledVerde,LOW);
    digitalWrite(ledAmarelo,LOW);
    digitalWrite(ledVermelho,HIGH);
    }

  else if(Leitura_umidade >= 25 && Leitura_umidade <60){
    digitalWrite(ledVerde,LOW);
    digitalWrite(ledAmarelo,HIGH);
    digitalWrite(ledVermelho,LOW);
    }

  else if(60 <= Leitura_umidade){
    digitalWrite(ledVerde,HIGH);
    digitalWrite(ledAmarelo,LOW);
    digitalWrite(ledVermelho,LOW);
    } 
}

