#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

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

/* Definição - aceleração da gravidade */
#define VALOR_GRAVIDADE    9.80665  // m/s²

/* Definição - número de leituras para calibração da IMU */
#define NUM_LEITURAS_CALIBRACAO    100

/* Variaveis globais */
char linha_str[OLED_LINE_MAX_SIZE];
int estado_led;
float offset_ax = 0.0;
float offset_ay = 0.0;
float offset_az = 0.0;
float offset_gx = 0.0;
float offset_gy = 0.0;
float offset_gz = 0.0;
float ax, ay, az, gx, gy, gz;
Adafruit_MPU6050 mpu;
Adafruit_SSD1306 display(OLED_SCREEN_WIDTH, 
                         OLED_SCREEN_HEIGHT, 
                         &Wire, 
                         OLED_RESET, 
                         100000UL, 
                         100000UL);

/* Protótipos */
void calibra_acc_giroscopio(void); 
                         
/*
 * Implementações
 */
/* Função: faz calibração do acelerometro e giroscopio
 * Parametros: nenhum 
 * Retorno: nenhum
 */
void calibra_acc_giroscopio(void)
{
    int i;
    sensors_event_t a, g, temp;
    float soma_ax = 0;
    float soma_ay = 0;
    float soma_az = 0;
    float soma_gx = 0;
    float soma_gy = 0;
    float soma_gz = 0;

    for (i=0; i<NUM_LEITURAS_CALIBRACAO; i++)
    {
        mpu.getEvent(&a, &g, &temp);
        
        soma_ax = soma_ax + a.acceleration.x;
        soma_ay = soma_ay + a.acceleration.y;
        soma_az = soma_az + a.acceleration.z;

        soma_gx = soma_gx + g.gyro.x;
        soma_gy = soma_gy + g.gyro.y;
        soma_gz = soma_gz + g.gyro.z;        
    }

    offset_ax = (float)soma_ax/NUM_LEITURAS_CALIBRACAO;
    offset_ay = (float)soma_ay/NUM_LEITURAS_CALIBRACAO;
    offset_az = (float)(soma_az / NUM_LEITURAS_CALIBRACAO) - VALOR_GRAVIDADE;

    offset_gx = soma_gx/NUM_LEITURAS_CALIBRACAO;
    offset_gy = soma_gy/NUM_LEITURAS_CALIBRACAO;
    offset_gz = soma_gz/NUM_LEITURAS_CALIBRACAO;    
}

void setup() 
{
    Serial.begin(115200);
      
    /* Inicializa I²C (para comunicação com OLED e MPU6050)*/
    Wire.begin(OLED_SDA_PIN, OLED_SCL_PIN);

    /* Inicializa MPU6050 */
    if (!mpu.begin()) 
    {
        Serial.println("ERRO: falha ao inicializar MPU6050. O ESP32 reiniciará em 1s...");
        delay(1000);
        ESP.restart();
    }
    else
    {
        /* Configura MPU6050 */
        mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
        mpu.setGyroRange(MPU6050_RANGE_500_DEG);
        mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
        calibra_acc_giroscopio();
    }

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
        display.println(" Monitoramento");
        display.setCursor(0,OLED_LINHA_2);
        display.println(" LoRaWAN");
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
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    

    /* Aplica offset às acelerações e componentes do giroscópios */
    ax = a.acceleration.x - offset_ax;
    ay = a.acceleration.y - offset_ay;
    az = a.acceleration.z - offset_az;
    gx = g.gyro.x - offset_gx;
    gy = g.gyro.y - offset_gy;
    gz = g.gyro.z - offset_gz;

    Serial.println(offset_az);
   
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setCursor(0,OLED_LINHA_1);
    display.println("   Dados - MPU6050");
    display.setCursor(0,OLED_LINHA_2);
    display.println("_____________________");
    display.setTextSize(1);
    display.setCursor(0,OLED_LINHA_3);
   
    sprintf(linha_str,"A: %.1f, %.1f, %.1f", ax, ay, az); 
    display.println(linha_str);

    display.setCursor(0,OLED_LINHA_4);
    display.println("m/s^2");
    
    display.setCursor(0,OLED_LINHA_5);
    sprintf(linha_str,"G: %.1f, %.1f, %.1f", gx, gy, gz); 
    display.println(linha_str);

    display.setCursor(0,OLED_LINHA_6);
    sprintf(linha_str,"rad/s  T: %.1fC", temp.temperature); 
    display.println(linha_str);
    display.display();

    /* Aguarda 1 segundo para próxima leitura */
    delay(1000);
}
