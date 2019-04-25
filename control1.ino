//<<<<<  AGV 1.1   PAC   >>>>>
//<<<<< SOFT 0.1         >>>>>

//             FRENTE
//        E0 --------- E1
//               |
//               |
//        X  --------- Y
//             

#define X_STEP_PIN         54
#define X_DIR_PIN          55
#define X_ENABLE_PIN       38

#define Y_STEP_PIN         60
#define Y_DIR_PIN          61
#define Y_ENABLE_PIN       56

#define E0_STEP_PIN        26
#define E0_DIR_PIN         28
#define E0_ENABLE_PIN      24

#define E1_STEP_PIN        36
#define E1_DIR_PIN         34
#define E1_ENABLE_PIN      30

int x;
int vx;
int vy;
int wz;
int wE0;
int wE1;
int wX;
int wY;
int ancho = 9;
int largo = 10;
int radio = 3.2;
int i = 0;
int delayX;
int delayY;
int delaywE0;
int delaywE1;

void setup() 
{
//Serial.begin(9600);
  
  pinMode(X_ENABLE_PIN,OUTPUT); 
  pinMode(Y_ENABLE_PIN,OUTPUT);
  pinMode(E0_ENABLE_PIN,OUTPUT);
  pinMode(E1_ENABLE_PIN,OUTPUT);
  
  pinMode(X_STEP_PIN,OUTPUT); 
  pinMode(X_DIR_PIN,OUTPUT); 

  pinMode(Y_STEP_PIN,OUTPUT); 
  pinMode(Y_DIR_PIN,OUTPUT); 
  
  pinMode(E0_STEP_PIN,OUTPUT);
  pinMode(E0_DIR_PIN,OUTPUT); 
  
  pinMode(E1_STEP_PIN,OUTPUT); 
  pinMode(E1_DIR_PIN,OUTPUT); 
  
}
void loop() {

//vx = analogRead(A0);
//vy = analogRead(A1);
//wz = analogRead(A2);
vx = 1/8 * radio;
vy = 2/8 * radio;
wz = 3/8 * radio;

cinematica();

delayX = map(wX,0,3/8 * radio,1,3);

delayY = map(wY,0,3/8 * radio,1,3);

delaywE0 = map(wE0,0,3/8 * radio,1,3);

delaywE1 = map(wE1,0,3/8 * radio,1,3);

// mandar wE0, wE1, wX, wY a cada motor correpondiente

if (i % (delayX*2) == 0){  
  digitalWrite(X_STEP_PIN,HIGH);
}
if (i % (delayY*2) == 0){
  digitalWrite(Y_STEP_PIN,HIGH);
}
if (i % (delaywE0*2) == 0){
  digitalWrite(E0_STEP_PIN,HIGH);
}
if (i % (delaywE1*2) == 0){
  digitalWrite(E1_STEP_PIN,HIGH);
}

delay(1);

if ( (i-delayX) % (delayX*2) == 0){
  digitalWrite(X_STEP_PIN,LOW);
}
if ( (i-delayY) % (delayY*2) == 0){
  digitalWrite(Y_STEP_PIN,LOW);
}
if ( (i-delaywE0) % (delaywE0*2) == 0){
  digitalWrite(E0_STEP_PIN,LOW);
}
if ( (i-delaywE1) % (delaywE1*2) == 0){
  digitalWrite(E1_STEP_PIN,LOW);
}

delay(1);

i = i + 1;

}

void cinematica(){

wE0 = (vx - vy - (ancho/2 + largo/2) * wz)/radio;

wE1 = (vx + vy + (ancho/2 + largo/2) * wz)/radio;

wX = (vx + vy - (ancho/2 + largo/2) * wz)/radio;

wY = (vx - vy + (ancho/2 + largo/2) * wz)/radio;
  
}
