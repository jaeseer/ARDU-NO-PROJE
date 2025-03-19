//Motor pinlerini tanımlıyoruz.
const int in1 = 6;
const int in2 = 9;
const int in3 = 10;
const int in4 = 11;
//Hız değişkeni atadık.
int hiz = 255;
//Mesafe için değişkenler atadık.
int sure;
unsigned int mesafe;
int sure2;
unsigned int mesafe2;
int sure3;
unsigned int mesafe3;
//Bluetooth verisi için değişken.
int state;
void setup() {
  //Motor çıkış pin modları
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  //Mosafe sensörleri pin modları tanımı.
  pinMode(2, OUTPUT);
  pinMode(3, INPUT);
  pinMode(A0, OUTPUT);
  pinMode(A1, INPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, INPUT);
  //Seri ekranı başlatıyoruz.
  Serial.begin(9600);
  //Led çıkışları
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  //Buzzer pini
  pinMode(A5, OUTPUT);
}

void loop() {

  if (digitalRead(state) == LOW) {
    state = 'S';
  }

  //Gelen veriyi 'state' değişkenine kaydet
  if (Serial.available() > 0) {
    state = Serial.read();
  }

//Mesafe hesaplaması yapılıyor.
  digitalWrite(2, HIGH);
  delayMicroseconds(20);
  digitalWrite(2, LOW);
  sure = pulseIn(3, HIGH);
  mesafe = (sure / 2) / 29.1;
  //ikici sensör verisi
  digitalWrite(A0, HIGH);
  delayMicroseconds(20);
  digitalWrite(A0, LOW);
  sure2 = pulseIn(A1, HIGH);
  mesafe2 = (sure2 / 2) / 29.1;
//Üçüncü sensör verisi
  digitalWrite(A2, HIGH);
  delayMicroseconds(20);
  digitalWrite(A2, LOW);
  sure3 = pulseIn(A3, HIGH);
  mesafe3 = (sure3 / 2) / 29.1;
//Araç hızını belirliyoruz.
  if (state == '0') {
    hiz = 0;
  }
  else if (state == '1') {
    hiz = 100;
  }
  else if (state == '2') {
    hiz = 180;
  }
  else if (state == '3') {
    hiz = 200;
  }
  else if (state == '4') {
    hiz = 255;
  }
  //Dönüşler için iç tekeri %50 yavaşlatıyoruz.
  int yavasteker = hiz * 50 / 100;
  //önde nesne var geri dön.
  if (mesafe < 30) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(8, HIGH);
    digitalWrite(7, HIGH);
    analogWrite(A5, 250);
    delay(100);
    analogWrite(A5, 2);
    delay(100);
  }
  //sağ tarafta nesne var sola git.
  else if (mesafe2 < 30) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
    digitalWrite(8, LOW);
    digitalWrite(7, HIGH);
  }
  //sol tarafta nesne var sağa git.
  else if (mesafe3 < 30) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(8, HIGH);
    digitalWrite(7, LOW);
  }
  /***********************İleri****************************/
  else if (state == 'F') {
    analogWrite(in1, hiz);
    analogWrite(in2, 0);
    analogWrite(in3, hiz);
    analogWrite(in4, 0);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(8, LOW);
    digitalWrite(7, LOW);

  }
  /***********************Geri****************************/
  //Gelen veri 'B' ise araba geri gider.
  else if (state == 'B') {
    analogWrite(in1, 0);
    analogWrite(in2, hiz);
    analogWrite(in3, 0 );
    analogWrite(in4, hiz);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(8, HIGH);
    digitalWrite(7, HIGH);
    analogWrite(A5, 250);
    delay(100);
    analogWrite(A5, 2);
    delay(100);
  }
  /***************************Sol*****************************/
  //Gelen veri 'L' ise araba sola gider.
  else if (state == 'L') {
    analogWrite(in1, hiz);
    analogWrite(in2, 0);
    analogWrite(in3, 0);
    analogWrite(in4, hiz);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(8, HIGH);
    digitalWrite(7, LOW);

  }

  /***************************Sağ*****************************/
  //Gelen veri 'R' ise araba sağa gider
  else if (state == 'R') {
    analogWrite(in1, 0);
    analogWrite(in2, hiz);
    analogWrite(in3, hiz);
    analogWrite(in4, 0);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
    digitalWrite(8, LOW);
    digitalWrite(7, HIGH);
  }

  /***************************Sol ileri*****************************/
  //Gelen veri 'G' ise araba sol ileriye gider
  else if (state == 'G') {
    analogWrite(in1, hiz);
    analogWrite(in2, 0);
    analogWrite(in3, yavasteker);
    analogWrite(in4, 0);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(8, HIGH);
    digitalWrite(7, LOW);
  }
  /***************************sağ ileri*****************************/
  //Gelen veri 'I' ise araba sağ ileriye gider
  else if (state == 'I') {
    analogWrite(in1, yavasteker);
    analogWrite(in2, 0 );
    analogWrite(in3, hiz);
    analogWrite(in4, 0);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
    digitalWrite(8, LOW);
    digitalWrite(7, HIGH);
  }

  /***************************Sol geri*****************************/
  //Gelen veri 'H' ise araba sol geri gider
  else if (state == 'H') {
    analogWrite(in1, 0);
    analogWrite(in2, hiz);
    analogWrite(in3, 0);
    analogWrite(in4, yavasteker);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(8, HIGH);
    digitalWrite(7, LOW);
  }
  /***************************sağ geri*****************************/
  //Gelen veri 'J' ise araba sağ geri gider
  else if (state == 'J') {
    analogWrite(in1, 0);
    analogWrite(in2, yavasteker);
    analogWrite(in3, 0);
    analogWrite(in4, hiz);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
    digitalWrite(8, LOW);
    digitalWrite(7, HIGH);
  }
  /***************************korna çal*****************************/
  //Gelen veri 'V' ise korna çal
  else if (state == 'V') {
    analogWrite(A5, 250);
  }
  /***************************korna sustur*****************************/
  //Gelen veri 'v' ise korna sustur
  else if (state == 'v') {
    analogWrite(A5, 0);
  }

  /***************************Ön farları aç*****************************/
  //Gelen veri 'W' ise ön farları aç
  else if (state == 'W') {
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);

  }
  /***************************Ön farları kapat*****************************/
  //Gelen veri 'w' ise ön farları kapat
  else if (state == 'w') {
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
  }
  /***************************Arka farları aç*****************************/
  //Gelen veri 'U' ise arka farları aç
  else if (state == 'U') {
    digitalWrite(8, HIGH);
    digitalWrite(7, HIGH);

  }
  /***************************Arka farları kapat*****************************/
  //Gelen veri 'u' ise arka farları kapat
  else if (state == 'u') {
    digitalWrite(8, LOW);
    digitalWrite(7, LOW);
  }

  /***************************Dörtlüyü aç*****************************/
  //Gelen veri 'X' ise dörtlüyü aç
  else if (state == 'X') {
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(7, HIGH);
    delay(500);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(8, LOW);
    digitalWrite(7, LOW);
    delay(500);
  }
  /***************************Dörtlüyü kapat*****************************/
  //Gelen veri 'x' ise dörtlüyü kapat
  else if (state == 'x') {
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(8, LOW);
    digitalWrite(7, LOW);
  }
  else {
    digitalWrite(in1, 0);
    digitalWrite(in2, 0);
    digitalWrite(in3, 0);
    digitalWrite(in4, 0);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(8, LOW);
    digitalWrite(7, LOW);
  }

}

