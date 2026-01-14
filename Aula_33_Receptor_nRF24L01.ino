/*****************************************************/
/*    Aula 33 – Módulo nRF24L01 - RECEPTOR           */
/* Programação do Módulo nRF24L01 - Receptor. O      */
/* código permite que o receptor receba uma informa_ */
/* ção (palavra: pressionado) para controlar o       */
/* acionamento do LED.                               */
/*****************************************************/
/* Links da biblioteca "RF24" by TMRh20 Avamander.   */
/* http://librarymanager/All#RF24#OFFERS             */
/* https://github.com/nRF24/RF24/                    */
/*****************************************************/
/* Define a palavra esperada do transmissor como     */
/* comando para acionar o LED.                       */
String mensagem_esperada = "pressionado";
/* Inclui a biblioteca de controle do módulo rádio.  */
#include <RF24.h>
/* Define o pino de controle do LED.                 */
#define pinoLED 2
/* Define os pinos de comunicação do módulo nRF24L01.*/
#define pinoCE 9
#define pinoCSN 10
/* Define o endereço de comunicação entre transmissor*/
/* e receptor.                                       */
#define endereco 5995
/* Cria o objeto de controle do módulo rádio.        */
RF24 radio(pinoCE, pinoCSN);
/* Variável que receberá a menssagem.                */
char msg_recebida[32] = "";

void setup() {
  /* Inicia o monitor serial.                        */
  Serial.begin(9600);
  /* Configura o pino do LED como saída.             */
  pinMode(pinoLED, OUTPUT);
  pinMode(7,OUTPUT);
  /* Inicializa o módulo rádio.                      */
  radio.begin();
  /* Abre canal de recebimento de dados no canal 0 (0-6).*/
  radio.openReadingPipe(0, endereco);
  /* Configura o nível de potência do módulo rádio.   */
  /* RF24_PA_MIN: Nível mínimo de potência.           */
  /* RF24_PA_LOW: Nível de potência baixo.            */
  /* RF24_PA_HIGH: Nível de potência alto.            */
  /* RF24_PA_MAX: Nível máximo de potência.           */
  radio.setPALevel(RF24_PA_MIN);
  /* Ativa o recebimento de dados.                    */
  radio.startListening();
}

void loop() {
  /* Se receber dados do transmissor, faça...         */
  if (radio.available()) {
    /* Lê os dados recebidos e armazena na variável   */
    /* msg_recebida.                                  */
    radio.read(&msg_recebida, sizeof(msg_recebida));
    /* Imprime no monitor serial a menssagem.         */
    Serial.println(msg_recebida);
    /* Se a menssagem recebida for igual a palavra    */
    /* pressionado, faça...                           */
    if (String(msg_recebida) == mensagem_esperada) {
      /* Altere o estado lógico do LED (Ligado/Desli_ */
      /* gado).                                       */
      digitalWrite(pinoLED, !digitalRead(pinoLED));
    }
  }
}
