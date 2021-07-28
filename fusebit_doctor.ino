
#define  HFUSE_8  0xD9  // дефолтные фьюзы для ATmega 8
#define  LFUSE_8  0xE1  // дефолтные фьюзы для ATmega 8
#define  HFUSE_168  0xDF  // дефолтные фьюзы для ATmega 168
#define  LFUSE_168  0x62  // дефолтные фьюзы для ATmega 168
#define  HFUSE_328  0xD9  // дефолтные фьюзы для ATmega 328
#define  LFUSE_328  0x62  // дефолтные фьюзы для ATmega 328

// Назначение пинов
#define  DATA  PORTD // PORTD порт данных
#define  DATAD  DDRD
#define  VCC  8
#define  RDY  12  // RDY/!BSY сигнал от МК
#define  OE  11
#define  WR  10
#define  BS1  9
#define  XA0  13
#define  XA1  18
#define  PAGEL  19
#define  RST  14  // Выход подачи 12 вольт на RESET
#define  BS2  16
#define  XTAL1  17
#define  JUMPER  15

void setup()  // запускается разово
{
  // Установим линии для HV программирования как надо
  DATA = 0x00;  // линия данных
  DATAD = 0xFF;
  pinMode(VCC, OUTPUT);
  pinMode(RDY, INPUT);
  pinMode(OE, OUTPUT);
  pinMode(WR, OUTPUT);
  pinMode(BS1, OUTPUT);
  pinMode(XA0, OUTPUT);
  pinMode(XA1, OUTPUT);
  pinMode(PAGEL, OUTPUT);
  pinMode(RST, OUTPUT);  // Выход подачи 12 вольт на RESET
  pinMode(BS2, OUTPUT);
  pinMode(XTAL1, OUTPUT);
  pinMode(JUMPER, INPUT);
  
  // инициализируем пины
  int jumperValue = analogRead(A1);
  digitalWrite(RST, HIGH);  // выключим пока +12V
  delay(500);  // ждём пока всё устаканиться
  //и погнали!
  // приводим пины в режим программирования
  digitalWrite(PAGEL, LOW);
  digitalWrite(XA1, LOW);
  digitalWrite(XA0, LOW);
  digitalWrite(BS1, LOW);
  digitalWrite(BS2, LOW);
  // переходим в режим программирования
  digitalWrite(VCC, HIGH);  // подаём питание
  digitalWrite(WR, HIGH);  // и единицы на OE и WR
  digitalWrite(OE, HIGH);
  delay(1);
  digitalWrite(RST, LOW);  //  подаём +12V на RESET
  delay(1);
  // сначала пишем HFUSE
  //sendcmd(B01000000);  // отправляем команду на запись фьюза
  digitalWrite(XA1, HIGH);
  digitalWrite(XA0, LOW);
  digitalWrite(BS1, LOW);
  DATA = B01000000;
  digitalWrite(XTAL1, HIGH);  // дрыгнем XTAL чтоб передать команду в чип
  delay(1);
  digitalWrite(XTAL1, LOW);
  delay(1);
  //writefuse(HFUSE);
  digitalWrite(XA1, LOW);
  digitalWrite(XA0, HIGH);
  delay(1);
  // Write fuse
  if (jumperValue > 800){
    DATA = HFUSE_8;
  }
  else if(jumperValue > 600 && jumperValue < 799){
    DATA = HFUSE_168;
  }
  else if(jumperValue < 599){
    DATA = HFUSE_328;
  }
  digitalWrite(XTAL1, HIGH);  // дрыгнем XTAL чтоб передать команду в чип
  delay(1);
  digitalWrite(XTAL1, LOW);
  digitalWrite(BS1, HIGH);  // пишем HFUSE
  digitalWrite(WR, LOW);  //записано!
  delay(1);
  digitalWrite(WR, HIGH);
  delay(500);  // ждёмс
  // пишем LFUSE
  //sendcmd(B01000000);
  digitalWrite(XA1, HIGH);
  digitalWrite(XA0, LOW);
  digitalWrite(BS1, LOW);
  DATA = B01000000;
  digitalWrite(XTAL1, HIGH);  // дрыгнем XTAL чтоб передать команду в чип
  delay(1);
  digitalWrite(XTAL1, LOW);
  delay(1);
  //writefuse(LFUSE);
  digitalWrite(XA1, LOW);
  digitalWrite(XA0, HIGH);
  delay(1);
  // Write fuse
    if (jumperValue > 800){
    DATA = LFUSE_8;
  }
  else if(jumperValue > 600 && jumperValue < 799){
    DATA = LFUSE_168;
  }
  else if(jumperValue < 599){
    DATA = LFUSE_328;
  }
  digitalWrite(XTAL1, HIGH); // дрыгнем XTAL чтоб передать команду в чип
  delay(1);
  digitalWrite(XTAL1, LOW);
  digitalWrite(BS1, LOW);  // пишем LFUSE
  digitalWrite(WR, LOW);  //записано!
  delay(1);
  digitalWrite(WR, HIGH);
  delay(500);  // ждёмс
  // и выходим из режима программирования
  digitalWrite(RST, HIGH);  // выключим +12V
  // обнуляем все пины
  DATA = 0x00;
  digitalWrite(OE, LOW);
  digitalWrite(WR, LOW);
  digitalWrite(PAGEL, LOW);
  digitalWrite(XA1, LOW);
  digitalWrite(XA0, LOW);
  digitalWrite(BS1, LOW);
  digitalWrite(BS2, LOW);
  }
void loop() //дело сделано весело мигаем
{
  digitalWrite(XA0, HIGH);
  delay(1000);
  digitalWrite(XA0, LOW);
  delay(1000);
}
