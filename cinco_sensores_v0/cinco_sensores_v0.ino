#include "DHT.h"
#define dht_type DHT11 //define qual o tipo de sensor DHTxx que se está utilizando
 

/**
 * Configurações iniciais sobre os sensores
 * DHT11, LM35, LDR5 e TCRT5000
 */

 
int dht_pin = A2;
DHT dht_11 = DHT(dht_pin, dht_type); //pode-se configurar diversos sensores DHTxx

int lm35_pin = A0, leitura_lm35 = 0;
float temperatura;

int ldr_pin = A5;
int ldr_read = 0;
float vin = 5.00;
float valor_ADC = 0.00488758, r_ohms = 10000;

int switch_pin = 7;

void setup() 
{
  Serial.begin(9600);
  dht_11.begin();
  pinMode(switch_pin, INPUT);
}
 
void loop() 
{
  /**
   * Bloco do DHT11
   */
  float umidade = dht_11.readHumidity();
  float temperatura = dht_11.readTemperature();
  if (isnan(temperatura) or isnan(umidade)) 
  {
    Serial.print("Não foi possivel ler dht11");
  }else
  {
    Serial.print(umidade);
    Serial.print(";");
    Serial.print(temperatura);
    Serial.print(";");
   }
  /**
   * Bloco do LM35
   */
  leitura_lm35 = analogRead(lm35_pin);
  temperatura = leitura_lm35 * (5.0/1023) * 100;
  Serial.print(temperatura);
  Serial.print(";");

  /**
   * Bloco do LDR5
   */
  if(isnan(ldr_read)){
    Serial.println("Erro ao ler o sensor");
  }
  else{
    ldr_read = analogRead(ldr_pin);
    float vout = valor_ADC * ldr_read;
    float res_ldr = (r_ohms * (vin - vout))/vout; 
    float lux = 500/(res_ldr/1000);
    /*
     * Checando a voltagem
     * Quanto maior a incidência de luz menor a resistência do sensor
     */
    if(ldr_read > 750){
      Serial.print(ldr_read);
      Serial.print(" Vout: ");
      Serial.print(vout);
      Serial.print(" R_ldr: ");
      Serial.print(res_ldr);
      Serial.print(" Lux: ");
      Serial.print(lux);
      Serial.println(" Claro");
    }
    else{
      Serial.print(ldr_read);
      Serial.print(" Vout: ");
      Serial.print(vout); //imprime na tela a tensão de saída
      Serial.print(" R_ldr: ");
      Serial.print(res_ldr); //imprime na tela a resistência do ldr
      Serial.print(" Lux: ");
      Serial.print(lux); //imprime na tela o valor de lux
      Serial.println(" Escuro");
    }
  }
   
  /**
   * Bloco do TCRT5000
   */
  if(digitalRead(switch_pin) == LOW){
    Serial.println(0);
  }
  else {
    Serial.println(1);
  }
 delay(2000);
}
