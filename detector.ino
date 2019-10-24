int geiger = 2;
int counter=0;


void tube_impulse() {
 Serial.println(1);
 counter=counter+1;

//TODO: Display 7seg
  
}

void setup() {  
  Serial.begin(115200);  
  pinMode(geiger, INPUT);   
  digitalWrite(geiger, LOW);  
  
  attachInterrupt(0, tube_impulse, FALLING);
}


void loop() {

}
