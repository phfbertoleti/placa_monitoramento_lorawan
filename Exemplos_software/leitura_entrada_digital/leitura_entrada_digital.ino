#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/* Definições - OLED */
#define OLED_CLEAR_LINE      "                     "
#define OLED_LINE_MAX_SIZE   21
#define OLED_SDA_PIN         4
#define OLED_SCL_PIN         15
#define OLED_ADDRESS         0x3C
#define OLED_RESET           16 
#define OLED_SCREEN_HEIGHT   64
#define OLED_SCREEN_WIDTH    128
#define OLED_LINHA_1         0
#define OLED_LINHA_2         10
#define OLED_LINHA_3         20
#define OLED_LINHA_4         30
#define OLED_LINHA_5         40
#define OLED_LINHA_6         50

/* Definição - GPIO da entrada digital */
#define GPIO_ENTRADA_DIGITAL  34

/* Variaveis globais */
char linha_str[OLED_LINE_MAX_SIZE];
int estado_led;
Adafruit_SSD1306 display(OLED_SCREEN_WIDTH, 
                         OLED_SCREEN_HEIGHT, 
                         &Wire, 
                         OLED_RESET, 
                         100000UL, 
                         100000UL);
/*
 * Implementações
 */


void setup() 
{
    Serial.begin(115200);

    /* Configuração do GPIO de leitura da entrada digital */
    pinMode(GPIO_ENTRADA_DIGITAL, INPUT);
        
    /* Inicializa I²C (para comunicação com OLED)*/
    Wire.begin(OLED_SDA_PIN, OLED_SCL_PIN);

    /* Inicializa display */
    if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) 
    { 
        Serial.println("[ERRO] não foi possivel inicializar display. O NodeMCU será reiniciado em 1s...");
        delay(1000);
        ESP.restart();
    }
    else
    {
        Serial.println("Display inicializado.");
        display.clearDisplay();
        display.setTextColor(WHITE);
        display.setTextSize(1);
        display.setCursor(0,OLED_LINHA_1);
        display.println("Placa de manutencao");
        display.setCursor(0,OLED_LINHA_2);
        display.println("preventiva");
        display.setCursor(0,OLED_LINHA_3);
        display.println("_____________________");
        display.setCursor(0,OLED_LINHA_5);
        display.println("Pedro Bertoleti");
        display.setCursor(0,OLED_LINHA_6);
        display.println("pedrobertoleti.com.br");
        display.display();
        delay(500);
    }
}

void loop() 
{
    
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(4);
    display.setCursor(0,OLED_LINHA_3);
    
    if (digitalRead(GPIO_ENTRADA_DIGITAL) == LOW)
        display.println("Livre");
    else
        display.println("BLOQ");    
    
    display.display();

    delay(500);    
}
