#include <Servo.h>// Inclui biblioteca de servos
 
Servo servoRotacao;// Cria variaveis para controlar servos
Servo servoPasso;// Cria variaveis para controlar servos
 
int ldrEsquerda = A3;// Ldr da esquerda pino 2
int ldrDireita  = A2;// Ldr da direita pino 3
int ldrCima     = A1;// Ldr de cima pino 4
int ldrBaixo    = A0;// Ldr de baixo pino 5
 
int valRotacao  = 90;// Posicao inicial dos servos
int valPasso    = 135;// Posicao inicial dos servos
 
int valEsquerda;// Variaveis para pegar valor analogico dos pinos
int valDireita;                                                      
int valCima;                                                      
int valBaixo;                                                        
 
int delayMovimento= 100;// Tempo de delay dos servos
 
void setup()
{
  servoRotacao.attach(6);// Atribui ao pino 6 o servo rotacao
  servoPasso.attach(7);// Atribui ao pino 9 o servo passo
}
 
void loop()
{
  valEsquerda = analogRead(ldrEsquerda);// Faz leitura analogica do ldr esquerdo de acordo com a incidencia de luz
  valDireita  = analogRead(ldrDireita);                          
  valCima     = analogRead(ldrCima);                                
  valBaixo    = analogRead(ldrBaixo);                                
 
  if (valEsquerda - valDireita > 2 || valEsquerda - valDireita < -2)  
  // Comparando os LDR's da esquerda e direita com threshold de "2" para evitar tremer os servos (jitter)
  {
    if (valEsquerda > valDireita && valRotacao > 0)                  
        // Luz vindo da direita, prepara para virar servo para direita (valor de travamento menor que 0)
    {
      valRotacao--;                                                  
          // Decrementa variavel
    }  
    if (valDireita > valEsquerda && valRotacao < 180)                
        // Luz vindo da esquerda, prepara para virar servo para esquerda (valor de travamento maior que 180)
    {
      valRotacao++;                                                  
          // Incrementa variavel
    }
  }
 
  if (valCima - valBaixo > 2 || valCima - valBaixo < -2)              
  // Comparando LDR's de Cima e Baixo com threshold de "2" para evitar tremer os servos (jitter)
  {
    if (valCima > valBaixo && valPasso > 90)                          
        // Luz vindo de Cima, prepara servo para virar para cima (valor de travamento menor que 90)
    {
      valPasso--;                                                    
          // Decrementa variavel
    }
    if (valBaixo > valCima && valPasso < 180)                        
        // Luz vindo de Baixo, prepara servo para ir para baixo (valor de travamento maior que 180)
    {
      valPasso++;                                                    
          // Incrementa variavel
    }  
  }
   /*
   dica: o servo de passo so precisa de um alcance de 90 graus em caso de luz vindo
   horizontalmente para o chao(nascer do sol)
   ou verticalmente (sol do meio dia)
   */
  servoRotacao.write(valRotacao);// Coloca a posicao do servo de acordo com valor calculado
  servoPasso.write(valPasso);// Coloca a posicao do servo de acordo com valor calculado
 
  delay(delayMovimento);// Espera o servo se mover até a posicao
}
