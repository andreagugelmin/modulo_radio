/*******************************************************/
/*      Código Receptor - nRF24L01 + Joystick Shield   */
/*******************************************************/

#include <RF24.h>

/* Define os pinos para os LEDs */
#define ledA 4
#define ledB 3
#define ledC 5
#define ledD 6

/* Define o pino 7, que precisa estar em LOW */
#define pinoControle 7

/* Define os pinos de comunicação do módulo nRF24L01 */
#define pinoCE 9
#define pinoCSN 10

/* Define o endereço de comunicação entre transmissor e receptor */
const uint64_t endereco = 0x1234LL;

/* Cria o objeto de controle do módulo rádio */
RF24 radio(pinoCE, pinoCSN);

/* Variável para armazenar a mensagem recebida */
char mensagem_recebida[32];

void setup() {
  /* Configura os pinos dos LEDs como saída */
  pinMode(ledA, OUTPUT);
  pinMode(ledB, OUTPUT);
  pinMode(ledC, OUTPUT);
  pinMode(ledD, OUTPUT);

  /* Configura o pino 7 como entrada */
  pinMode(pinoControle, OUTPUT);

  /* Inicializa o módulo rádio */
  radio.begin();

  /* Abre canal de recebimento de dados */
  radio.openReadingPipe(0, endereco);

  /* Configura o nível de potência do módulo rádio */
  radio.setPALevel(RF24_PA_MIN);

  /* Inicia o recebimento de dados */
  radio.startListening();
}

void loop() {
  /* Verifica se o pino 7 está em LOW */
  if (digitalRead(pinoControle) == LOW) {
    /* Verifica se há dados disponíveis para receber */
    if (radio.available()) {
      /* Lê os dados recebidos */
      radio.read(&mensagem_recebida, sizeof(mensagem_recebida));

      /* Verifica qual mensagem foi recebida e aciona o LED correspondente */
      if (strcmp(mensagem_recebida, "A") == 0) {
        digitalWrite(ledA, HIGH);  // Acende LED na porta 2
        delay(2);
        digitalWrite(ledA, LOW);   // Apaga LED após o delay
      } else if (strcmp(mensagem_recebida, "B") == 0) {
        digitalWrite(ledB, HIGH);  // Acende LED na porta 3
        delay(2);
        digitalWrite(ledB, LOW);
      } else if (strcmp(mensagem_recebida, "C") == 0) {
        digitalWrite(ledC, HIGH);  // Acende LED na porta 4
        delay(2);
        digitalWrite(ledC, LOW);
      } else if (strcmp(mensagem_recebida, "D") == 0) {
        digitalWrite(ledD, HIGH);  // Acende LED na porta 5
        delay(2);
        digitalWrite(ledD, LOW);
      }
    }
  }
}
