/*******************************************************/
/*      Código Transmissor - nRF24L01 + Joystick Shield */
/*******************************************************/

#include <RF24.h>

/* Define os pinos dos botões do joystick shield */
#define buttonA 2  // Pino do botão A
#define buttonB 3  // Pino do botão B
#define buttonC 5  // Pino do botão C
#define buttonD 4  // Pino do botão D

/* Define os pinos de comunicação do módulo nRF24L01 */
#define pinoCE 9
#define pinoCSN 10

/* Define o endereço de comunicação entre transmissor e receptor */
const uint64_t endereco = 0x1234LL;

/* Cria o objeto de controle do módulo rádio */
RF24 radio(pinoCE, pinoCSN);

/* Declara as mensagens para cada botão */
char mensagemA[] = "A";
char mensagemB[] = "B";
char mensagemC[] = "C";
char mensagemD[] = "D";

void setup() {
  /* Configura os pinos dos botões como entrada com resistor interno ativado */
  pinMode(buttonA, INPUT_PULLUP);
  pinMode(buttonB, INPUT_PULLUP);
  pinMode(buttonC, INPUT_PULLUP);
  pinMode(buttonD, INPUT_PULLUP);

  /* Inicializa o módulo rádio */
  radio.begin();

  /* Abre canal de envio de dados */
  radio.openWritingPipe(endereco);

  /* Configura o nível de potência do módulo rádio */
  radio.setPALevel(RF24_PA_MIN);

  /* Desativa o recebimento de dados, pois será apenas transmissor */
  radio.stopListening();
}

void loop() {
  /* Verifica se o botão A foi pressionado */
  if (digitalRead(buttonA) == LOW) {
    /* Envia a mensagem "A" */
    radio.write(&mensagemA, sizeof(mensagemA));
    delay(2);  // Evita múltiplos envios
  }

  /* Verifica se o botão B foi pressionado */
  if (digitalRead(buttonB) == LOW) {
    /* Envia a mensagem "B" */
    radio.write(&mensagemB, sizeof(mensagemB));
    delay(2);
  }

  /* Verifica se o botão C foi pressionado */
  if (digitalRead(buttonC) == LOW) {
    /* Envia a mensagem "C" */
    radio.write(&mensagemC, sizeof(mensagemC));
    delay(2);
  }

  /* Verifica se o botão D foi pressionado */
  if (digitalRead(buttonD) == LOW) {
    /* Envia a mensagem "D" */
    radio.write(&mensagemD, sizeof(mensagemD));
    delay(2);
  }
}
