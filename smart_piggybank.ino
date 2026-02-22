#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <AccelStepper.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

//IN1->11, IN2->10, IN3->9, IN4->8
AccelStepper stepper(4, 11, 9, 10, 8); 

float sumaTotala = 0.00;

void setup() {
  lcd.init();
  lcd.backlight();
  
  stepper.setMaxSpeed(800.0); // setam viteza maxima
  stepper.setSpeed(-500.0); //in sensul invers a acelor de ceasornic

  pinMode(2, INPUT); 
  pinMode(3, INPUT);
  pinMode(4, INPUT); 
  pinMode(5, INPUT);

  lcd.setCursor(0, 0);
  lcd.print("Pusculita SMART");
}

void loop() {
  stepper.runSpeed();

  verificareSenzori();
}

void verificareSenzori() {
  static unsigned long lastCheck = 0;
  if (millis() - lastCheck > 35) { 
    if (digitalRead(2) == LOW) { proceseaza(0.50, "50 Bani"); }
    else if (digitalRead(3) == LOW) { proceseaza(0.10, "10 Bani"); }
    else if (digitalRead(4) == LOW) { proceseaza(0.05, "5 Bani"); }
    else if (digitalRead(5) == LOW) { proceseaza(0.01, "1 Ban"); }
    lastCheck = millis();
  }
}

void proceseaza(float val, String nume) {
  sumaTotala += val;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Bani: " + nume);
  lcd.setCursor(0, 1);
  lcd.print("Total: "); lcd.print(sumaTotala);
}