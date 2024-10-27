#include <Arduino.h>
#include <SharpIR.h>
#include "..\lib\measurateIMU.h"
#include "..\lib\motorController.h"

// OBS:
//   verificar se os pinos estão conecta dos da forma correta,
//   faça o teste de desvio mencionado à cima para fazer a ver
//   ificação.

// motores da esquerda e direita:2
motorController motorDireito(22, 23, 2);
motorController motorEsquerdo(24, 25, 3);

// pino do sensor de distancia:2222
// OBS:
//    em cima do sensor existe uma numeração indicando o model
//    o do sensor, verifique a numeração e deixe ele colocado 
//    corretamente.
SharpIR sensorDistancia(SharpIR::GP2Y0A21YK0F, A0);

// pinos dos infra vermelhos:
char IVermelhoDireito  = A1;
char IvermelhoEsquerdo = A2;

// a constante de rotação:
// - influencia no momento em que o sumo está sentindo os seus
//   sensores na circunferencia da arena.
const double constanteRotação = 0.9/1000; // k/1000

// variaveis:
// -  variaveis de distancia
int distancia = 0;            // cm
int distanciaInimigo = 60;    // cm
// -  variaveis de velocidade
int velocidadeDireita  = 0;   // PWM
int velocidadeEsquerda = 0;   // PWM
int velocidadeMedia = 128;    // PWM
// -  variaveis da arena
bool bordaEsquerda = false;   // true/false
bool bordaDireita  = false;   // true/false
// -  variaveis de tempo
double tempoSCorrente = 0;    // s
double tempoSPassado  = 0;    // s
double tempoSDireita  = 0;    // s
double tempoSEsquerda = 0;    // s



void setup() {
    // iniciando os sensores IR
    pinMode(IVermelhoDireito , INPUT);
    pinMode(IvermelhoEsquerdo, INPUT);

    // desligando inicialmente os motores
    motorDireito.turnOff();
    motorEsquerdo.turnOff();
}

void loop() {
    // adicionar distancia
    distancia = sensorDistancia.getDistance();
    // varificar os sensores IR em ambos os lados
    bordaEsquerda = digitalRead(IvermelhoEsquerdo);
    bordaDireita  = digitalRead(IVermelhoDireito );


    tempoSCorrente = millis(); // definir tempo

    // varificando se há algum possivel inimigo no raio
    if (distancia < distanciaInimigo) {
        attacar();
    }
    else {
        encontrar();
    }

    tempoSPassado = tempoSCorrente; // redefinir tempo passado


    // definir as velocidades nos enables e mudar a polaridade
    motorDireito.changeVelocitySensed(velocidadeDireita);   // definir na direita
    motorEsquerdo.changeVelocitySensed(velocidadeEsquerda); // definir da esquerda
    motorDireito.run();  // acelerar motor
    motorEsquerdo.run(); // acelerar motor
}



void encontrar() {
    // iniciar rotação do robô para encontrar os oponentes na arena
    velocidadeDireita  =  velocidadeMedia;
    velocidadeEsquerda = -velocidadeMedia;


    // caso o valor seja verdadeiro...
    if (bordaDireita)
    {
        velocidadeDireita  = -velocidadeMedia/4; // mover o robô para traz
        velocidadeEsquerda = -velocidadeMedia;   // mover o robô para traz
        delay(500);
    }
    // caso o valor seja verdadeiro...
    if (bordaEsquerda)
    {
        velocidadeDireita  = -velocidadeMedia;   // mover o robô para traz
        velocidadeEsquerda = -velocidadeMedia/4; // mover o robô para traz
        delay(500);
    }
}



void attacar() {
    // Verificar o sensor da esquerda
    if (bordaEsquerda) tempoSEsquerda += (tempoSPassado - tempoSCorrente); // adicionar o tempo
    else tempoSEsquerda = 0;                                               // resetar o tempo
    // Verificar o sensor da direita
    if (bordaDireita ) tempoSDireita  += (tempoSPassado - tempoSCorrente); // adicionar o tempo
    else tempoSDireita  = 0;                                               // resetar o tempo

    // calcular velocidade das rodas
    velocidadeDireita  = velocidadeMedia + (constanteRotação* (tempoSDireita  - tempoSEsquerda));
    velocidadeEsquerda = velocidadeMedia + (constanteRotação* (tempoSEsquerda - tempoSDireita ));
}