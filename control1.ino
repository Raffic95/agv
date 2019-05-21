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


//definicion de variables que se van a utilizar
float x;
float vx;
float vy;
float wz;
float wE0;
float wE1;
float wX;
float wY;
float ancho = 25;
float largo = 24;
float radio = 3.2;
int i = 0;
int delayX;
int delayY;
int delaywE0;
int delaywE1;
float vxactual = 0;
float vyactual = 0;
float wzactual = 0;
float wXaux;
float wYaux;
float wE0aux;
float wE1aux;

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
/*asignar los valores de vx(velocidad para adelante), vy(velocidad para el costado), wz(velocidad angular con la 
que rota el autito. para mas detalles sobre estos parametros buscar el pdf que subio flavio.
se pueden definir con un potenciometro como hago aca, pero para fines de prueba le damos un valor manualmente.
vx = analogRead(A0);
vy = analogRead(A1);
wz = analogRead(A2);
*/
vx = 0;  //0 a 1 (Surge de algunos calculos)
vy = 0;  // 0 a 1
wz = 0.04 ; // 0 a 0.04

//para mover el autito voy a  necesitar que esas velocidades se transformen en velocidades angulares para cada unad de las
//4 ruedas.
/*
 antes de realizar los calculos de las velocidades de las ruedas pregunto 
 si la velocidad del auto cambio con respecto a la iteracion anterior
*/
if ((vx != vxactual) || (vy != vyactual) || (wz != wzactual)) {

/*
 Funcion Cinematica(): toma los 3 valores vx, vy y wz, y mediante una serie de calculos que provienen de deducciones
 que se encuentran en el pdf subido por flavio(buscar nombre del pdf) devuelve la velocidad angular correspondiente
 a cada una de las ruedas X, Y, E0, E1,  wX, wY, wE0, wE1 correspondientemente.
 */
 
cinematica();

//redefino mis velocidades actuales para despues comparar

vxactual = vx;

vyactual = vy;

wzactual = wz;


/*
 en este segmento le doy un valor al pin de direccion, pregunto si la velocidad angular que le quiero pasar
 a la rueda es negativa, en ese caso activo el pin que significa que vaya para atras, luego genero una variable
 con el modulo de la velocidad para despues poder pasarselo a la rueda.
 En el caso que sea positivo pongo el pin en low y mi variable auxiliar queda igual a la velocidad.

 Lo ultimo que hago es calcular la frecuencia con la que le voy a mandar pulsos al motor de cada rueda en la 
 variable delay, esto se hace con la funcion map que toma mi velocidad y la transforma en un tiempo de delay
 proporcional, los valores dentro de la funcion map son los valores maximos y minimos que pueden tomar
 el delay y las velocidades
 */
if (wX < 0 ){
  digitalWrite(X_DIR_PIN,HIGH);
  wXaux = -wX;
}
else{
  digitalWrite(X_DIR_PIN,LOW);
  wXaux = wX;
}
delayX = map(wXaux,0,1000,10,5);

if (wY < 0 ){
  digitalWrite(Y_DIR_PIN,HIGH);
  wYaux = -wY;
}
else{
  digitalWrite(Y_DIR_PIN,LOW);
  wYaux = wY;
}
delayY = map(wYaux,0,1000,10,5);

if (wE0 < 0 ){
  digitalWrite(E0_DIR_PIN,HIGH);
  wE0aux = -wE0;
}
else{
  digitalWrite(E0_DIR_PIN,LOW);
  wE0aux = wE0;
}

delaywE0 = map(wE0aux,0,1000,10,5);

if (wE1 < 0 ){
  digitalWrite(E1_DIR_PIN,HIGH);
  wE1aux = -wE1;
}
else{
  digitalWrite(E1_DIR_PIN,LOW);
  wE1aux = wE1;
}

delaywE1 = map(wE1aux,0,1000,10,5);

}

/*
 una vez que tenemos el delay para cada motor, lo que hacemos es activar y desactivar el motor con esta frecuencia para
 que la rueda se mueva a la velocidad deseada(esto tiene teoria atras preguntarselo a jose).
 lo hacemos utilizando un contador i que indica cuantas veces pasamos por un delay(1) que es un delay de 1 ms, la funcion %
 es la funcion resto y esta funcion va a dar 0 siempre que el contador i tenga como valor un multiplo del delay con el 
 que estoy comparando, lo que va a significar que pasaron delay ms desde la ultima vez que fue 0, se multiplica x 2 para 
 que este la mitad del tiempo en high y la mitad del tiempo en low
 */


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

wE0 = 1000*(vx - vy - (ancho/2 + largo/2) * wz)/radio;

wE1 = 1000*(vx + vy + (ancho/2 + largo/2) * wz)/radio;

wX = 1000*(vx + vy - (ancho/2 + largo/2) * wz)/radio;

wY = 1000*(vx - vy + (ancho/2 + largo/2) * wz)/radio;
  
}
