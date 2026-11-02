#define M1_dir 45
#define M1_Speed 44
#define M2_dir 47
#define M2_Speed 46

void setup() {

pinMode(M1_dir, OUTPUT);
pinMode(M1_Speed, OUTPUT);

pinMode(M2_dir, OUTPUT);
pinMode(M2_Speed, OUTPUT);

}

void loop() {
  
vpered(); 

}


void vpered(){
  digitalWrite(M1_dir, 1);

analogWrite(M1_Speed, 150);

digitalWrite(M2_dir, 1);

analogWrite(M2_Speed, 150);

}