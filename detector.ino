//LINUXDAY Update

int schermo1=1;
int schermo2=2;
int schermo3=3;
int schermo4=4;

int decine;
int unita;
int decimi;
int centim;
int temp;
int val_Adc;
int centinaia;
String tempStr;
int buff;


int mill;
int cent;
int dec;
int uni;

// Definisco i pin delle cifre
int digit1 = 2;
int digit2 = 3;
int digit3 = 4;
int digit4 = 5;

// Definisco la mappatura tra pin e segmenti
int c=6;
int d=7;
int dp=8;
int a=9;
int g=10;
int f=11;
int b=12;
int e=13;



int count;

void tube_impulse(){
  count=count+1;
}


// Setup. Imposto ogni cifra e segmento come OUTPUT
void setup(){
  Serial.begin(115200);
  // Imposto le cifre come OUTPUT
  pinMode(digit1, OUTPUT);
  pinMode(digit2, OUTPUT);
  pinMode(digit3, OUTPUT);
  pinMode(digit4, OUTPUT);
  // Imposto i segmenti come OUTPUT
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(dp, OUTPUT);
     
   mill = 0;
   cent = 0;
   dec = 0;
   uni = 0;
}



void loop() { 
  
  uni=uni+1;  
  
  if (uni == 9){
   uni = 0;
   dec = dec + 1; 
  }
  
  if (dec == 9) {
   dec = 0;
   cent = cent + 1; 
  }
  
  if (cent == 9) {
   cent = 0;
   cent = cent + 1; 
  }
  
  if (mill == 9) {
   mill = 0;
   cent = 0;
   dec = 0;
   uni = 0; 
  }
 
   
   StampaMille(mill);
   //delay(0.5);
   StampaCento(cent);
  // delay(0.5);
   StampaDecina(dec);
   //delay(0.5);
   StampaUnita(uni);
   //delay(0.5);

   
   
}

void StampaDecina(int dec)
{
  
   digitalWrite(digit1, LOW);
   digitalWrite(digit2, LOW);
   digitalWrite(digit3, HIGH);
   digitalWrite(digit4, LOW);
   StampaNumero(dec);
   digitalWrite(dp, LOW);
   delayMicroseconds(5000);
 }
 
 
 void StampaUnita(int un)
{
  
   digitalWrite(digit1, LOW);
   digitalWrite(digit2, LOW);
   digitalWrite(digit3, LOW);
   digitalWrite(digit4, HIGH);
   StampaNumero(un);
   digitalWrite(dp, LOW);
   delayMicroseconds(5000);
 }

void StampaMille(int decim)
{
  
   digitalWrite(digit1, HIGH);
   digitalWrite(digit2, LOW);
   digitalWrite(digit3, LOW);
   digitalWrite(digit4, LOW);
   StampaNumero(decim);
   digitalWrite(dp, LOW);
   delayMicroseconds(5000);
 }

void StampaCento(int centim)
{
  
   digitalWrite(digit1, LOW);
   digitalWrite(digit2, HIGH);
   digitalWrite(digit3, LOW);
   digitalWrite(digit4, LOW);
   StampaNumero(centim);
   digitalWrite(dp, LOW);
   delayMicroseconds(5000);
 }




void StampaNumero(char n)  

{  
   
  if(n==0){
    
      
    digitalWrite(a, LOW);  
    digitalWrite(b, LOW);  
    digitalWrite(c, LOW);   
    digitalWrite(d, LOW);   
    digitalWrite(e, LOW);  
    digitalWrite(f, LOW);  
    digitalWrite(g, HIGH);
    digitalWrite(dp, HIGH);  
    
  }  
  
  if(n==1){  
    digitalWrite(a, HIGH);  
    digitalWrite(b, HIGH);  
    digitalWrite(c, HIGH);   
    digitalWrite(d, HIGH);   
    digitalWrite(e, LOW);  
    digitalWrite(f, LOW);  
    digitalWrite(g, HIGH);
    digitalWrite(dp, HIGH);  
     
   } 
  
  if(n==2){  
    digitalWrite(a, LOW);  
    digitalWrite(b, LOW);  
    digitalWrite(c, HIGH);   
    digitalWrite(d, LOW);   
    digitalWrite(e, LOW);  
    digitalWrite(f, HIGH);  
    digitalWrite(g, LOW);
    digitalWrite(dp, HIGH);

      
 } 
 
 
  if(n==3){  
    digitalWrite(a, LOW);  
    digitalWrite(b, LOW);  
    digitalWrite(c,LOW);   
    digitalWrite(d, LOW);   
    digitalWrite(e, HIGH);  
    digitalWrite(f, HIGH);  
    digitalWrite(g, LOW);
    digitalWrite(dp, LOW);  
     
   } 
  
  if(n==4){  
    digitalWrite(a, HIGH);  
    digitalWrite(b, LOW);  
    digitalWrite(c, LOW);   
    digitalWrite(d, HIGH);   
    digitalWrite(e, HIGH);  
    digitalWrite(f, LOW);  
    digitalWrite(g, LOW);
    digitalWrite(dp, LOW);  
    
   } 
  
  if(n==5){  
    digitalWrite(a, LOW);  
    digitalWrite(b, HIGH);  
    digitalWrite(c, LOW);   
    digitalWrite(d, LOW);   
    digitalWrite(e, HIGH);  
    digitalWrite(f, LOW);  
    digitalWrite(g, LOW);
    digitalWrite(dp, LOW);  
     
   } 
  
  if(n==6){  
    digitalWrite(a, LOW);  
    digitalWrite(b, HIGH);  
    digitalWrite(c, LOW);   
    digitalWrite(d, LOW);   
    digitalWrite(e, LOW);  
    digitalWrite(f, LOW);  
    digitalWrite(g, LOW);
    digitalWrite(dp, LOW);  
     
   } 
  
  if(n==7){  
    digitalWrite(a, LOW);  
    digitalWrite(b, LOW);  
    digitalWrite(c, LOW);   
    digitalWrite(d, HIGH);   
    digitalWrite(e, HIGH);  
    digitalWrite(f, HIGH);  
    digitalWrite(g, HIGH);
    digitalWrite(dp, LOW);  
      
    }
  
  if(n==8){   
    digitalWrite(a, LOW);  
    digitalWrite(b, LOW);  
    digitalWrite(c, LOW);   
    digitalWrite(d, LOW);   
    digitalWrite(e, LOW);  
    digitalWrite(f, LOW);  
    digitalWrite(g, LOW); 
    digitalWrite(dp, LOW); 
      
    }
  
  if(n==9){  
    digitalWrite(a, LOW);  
    digitalWrite(b, LOW);  
    digitalWrite(c, LOW);   
    digitalWrite(d, LOW);   
    digitalWrite(e, HIGH);  
    digitalWrite(f, LOW);  
    digitalWrite(g, LOW);
    digitalWrite(dp, LOW);  

    }
}  
     
