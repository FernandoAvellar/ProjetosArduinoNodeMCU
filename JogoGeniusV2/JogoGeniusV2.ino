
#define LED_AZUL 2
#define LED_VERMELHO 3
#define LED_AMARELO 4
#define LED_VERDE 5

#define BOTAO_AZUL 8
#define BOTAO_VERMELHO 9
#define BOTAO_AMARELO 10
#define BOTAO_VERDE 11

#define INDEFINIDO -1

#define UM_SEGUNDO 1000
#define MEIO_SEGUNDO 500
#define DUZENTOS_MILI_SEGUNDOS 200
#define CEM_MILI_SEGUNDOS 100

#define TAMANHO_SEQUENCIA 5

enum Estados{
  PRONTO_PARA_PROXIMA_RODADA,
  USUARIO_RESPONDENDO,
  JOGO_FINALIZADO_SUCESSO,
  JOGO_FINALIZADO_FALHA
};

int sequenciaLuzes[TAMANHO_SEQUENCIA];
int rodada = 0;
int leds_respondidos = 0;

void setup() {
  iniciaPortas();
  iniciaJogo();
}

void iniciaPortas() {
  pinMode(LED_AZUL,OUTPUT);
  pinMode(LED_VERMELHO,OUTPUT);
  pinMode(LED_AMARELO,OUTPUT);
  pinMode(LED_VERDE,OUTPUT);
  pinMode(BOTAO_AZUL,INPUT_PULLUP);
  pinMode(BOTAO_VERMELHO,INPUT_PULLUP);
  pinMode(BOTAO_AMARELO,INPUT_PULLUP);
  pinMode(BOTAO_VERDE,INPUT_PULLUP);
}

void iniciaJogo() { 
  int jogo = analogRead(0);
  randomSeed(jogo);
  for(int indice = 0; indice < TAMANHO_SEQUENCIA; indice++) {
    sequenciaLuzes[indice] = sorteiaCor();
  }
}

int sorteiaCor() {
  return random(LED_AZUL, LED_VERDE+1);
}

void loop() { 
  switch (estadoAtual()) {
    case PRONTO_PARA_PROXIMA_RODADA:
      preparaNovaRodada();
      break;
    case USUARIO_RESPONDENDO:
      processaRespostaUsuario();
      break;
    case JOGO_FINALIZADO_SUCESSO:
      jogoFinalizadoSucesso();
      break;
    case JOGO_FINALIZADO_FALHA:
      jogoFinalizadoFalha();
      break;
  }
  delay(DUZENTOS_MILI_SEGUNDOS);
}

void preparaNovaRodada() {
  rodada++;
  leds_respondidos = 0;
  if(rodada <= TAMANHO_SEQUENCIA) {
    tocaLedsRodada();
  }
}

void processaRespostaUsuario(){
  int resposta = checaRespostaJogador();
  if(resposta == INDEFINIDO) {
    return;
  }
  if(resposta == sequenciaLuzes[leds_respondidos]){
    leds_respondidos++;
    confirmaTecladoPressionado(resposta);
  }else {
    rodada = TAMANHO_SEQUENCIA+2; 
    confirmaTecladoPressionado(resposta); 
  }
}

int estadoAtual(){
  if(rodada <= TAMANHO_SEQUENCIA) {
    if(leds_respondidos == rodada) {
      return PRONTO_PARA_PROXIMA_RODADA;
    }else {
      return USUARIO_RESPONDENDO;
    }
  }else if(rodada == TAMANHO_SEQUENCIA+1) {
    return JOGO_FINALIZADO_SUCESSO;
  }else {
     return JOGO_FINALIZADO_FALHA;
  }
}

void tocaLedsRodada(){
  for(int i = 0; i < rodada; i++) {
    piscaLed(sequenciaLuzes[i]);
  }
}

int checaRespostaJogador() {
  if(digitalRead(BOTAO_VERDE) == LOW) {
    return LED_VERDE;
  }
  if(digitalRead(BOTAO_AMARELO) == LOW) {
    return LED_AMARELO;
  }
  if(digitalRead(BOTAO_VERMELHO) == LOW) {
    return LED_VERMELHO;
  }
  if(digitalRead(BOTAO_AZUL) == LOW) {
    return LED_AZUL;
  }
  return INDEFINIDO;
}

void confirmaTecladoPressionado(int resposta) {
  piscaLedRapidamente(resposta);
}

void piscaLed(int portaLed) {
  digitalWrite(portaLed,HIGH);
  delay(UM_SEGUNDO);
  digitalWrite(portaLed,LOW);
  delay(MEIO_SEGUNDO);
}

void piscaLedRapidamente(int portaLed) {
  digitalWrite(portaLed,HIGH);
  delay(DUZENTOS_MILI_SEGUNDOS);
  digitalWrite(portaLed,LOW);
  delay(DUZENTOS_MILI_SEGUNDOS);
}

void jogoFinalizadoSucesso() {
  piscaLedRapidamente(LED_VERDE);
  piscaLedRapidamente(LED_AMARELO);
  piscaLedRapidamente(LED_VERMELHO);
  piscaLedRapidamente(LED_AZUL);
}

void jogoFinalizadoFalha() {
  digitalWrite(LED_VERDE,HIGH);
  digitalWrite(LED_AMARELO,HIGH);
  digitalWrite(LED_VERMELHO,HIGH);
  digitalWrite(LED_AZUL,HIGH);
  delay(DUZENTOS_MILI_SEGUNDOS);
  digitalWrite(LED_VERDE,LOW);
  digitalWrite(LED_AMARELO,LOW);
  digitalWrite(LED_VERMELHO,LOW);
  digitalWrite(LED_AZUL,LOW);
  delay(CEM_MILI_SEGUNDOS);
}

