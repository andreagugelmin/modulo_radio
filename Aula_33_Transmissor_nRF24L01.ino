/*******************************************************/
/*      Aula 33 – Módulo nRF24L01 - TRANSMISSOR        */
/* O código permite enviar uma informação (palavra:    */
/* pressionado) por meio do módulo nRF24L01 ao         */
/* pressionar o botão.                                 */
/*******************************************************/
/* Links da biblioteca "RF24" by TMRh20 Avamander.     */
/* http://librarymanager/All#RF24#OFFERS               */
/* https://github.com/nRF24/RF24/                      */
/*******************************************************/
/* Declara a variável mensagem do tipo char para       */
/* amazenar a palavra que será utilizada como comando  */
/* para acionar o LED.                                 */
char mensagem[] = "pressionado";
/* Inclui a biblioteca de controle do módulo rádio.    */
#include <RF24.h>
/* Define o pino de leitura do botão.                  */
#define pinoBotao 2
/* Define os pinos de comunicação do módulo nRF24L01.  */
#define pinoCE 9
#define pinoCSN 10
/* Define o endereço de comunicação entre transmissor  */
/* e receptor.                                         */
#define endereco 5995
/* Cria o objeto de controle do módulo rádio.          */
RF24 radio(pinoCE, pinoCSN);

void setup() {
  /* Configura o pino do botão como entrada ativando o */
  /* resistor interno.                                 */
  pinMode(pinoBotao, INPUT_PULLUP);
  /* Inicializa o módulo rádio.                        */
  radio.begin();
  /* Abre canal de envio de dados.                     */
  radio.openWritingPipe(endereco);
  /* Configura o nível de potência do módulo rádio.    */
  /* RF24_PA_MIN: Nível mínimo de potência.            */
  /* RF24_PA_LOW: Nível de potência baixo.             */
  /* RF24_PA_HIGH: Nível de potência alto.             */
  /* RF24_PA_MAX: Nível máximo de potência.            */
  radio.setPALevel(RF24_PA_MIN);
  /* Desativa o recebimento de dados, pois somente irá */
  /* enviar.                                           */
  radio.stopListening();
}

void loop() {
  /* Se o botão for pressionado, faz...                */
  if (digitalRead(pinoBotao) == LOW) {
    /* Envia a palavra para o receptor.                */
    radio.write(&mensagem, sizeof(mensagem));
    /* Intervalo para nova leitura do botão.           */
    delay(400);
  }
}
