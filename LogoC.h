//--------------------------defining new characters
byte solid[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
};
byte t_right[8] = {
  B00000,
  B10000,
  B11000,
  B11100,
  B11110,
  B11111,
  B11111,
};
byte t_left[8] = {
  B00000,
  B00001,
  B00011,
  B00111,
  B01111,
  B11111,
  B11111,
};
byte b_right[8] = {
  B11111,
  B11111,
  B11110,
  B11100,
  B11000,
  B10000,
  B00000,
};
byte b_left[8] = {
  B11111,
  B11111,
  B01111,
  B00111,
  B00011,
  B00001,
  B00000,
};
byte blank[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
};
byte que[8] = {
  B11000,
  B11100,
  B11110,
  B11111,
  B01111,
  B00111,
  B00011,
};

//--------------------------function to display the QFCT logo
void displayLogo(){
  lcd.setCursor(0,0);
  delay(50);
   
  //row 1----------------
  lcd.write(byte(5));
  lcd.write(byte(2));
  lcd.write(byte(0));
  lcd.write(byte(0));
  lcd.write(byte(1));
  lcd.write(byte(5));
  
  lcd.write(byte(2));
  lcd.write(byte(0));
  lcd.write(byte(0));  
  lcd.write(byte(1));
  
  lcd.write(byte(2));
  lcd.write(byte(0));
  lcd.write(byte(0));
  lcd.write(byte(1));
  
  lcd.write(byte(2));
  lcd.write(byte(0));
  lcd.write(byte(0));  
  lcd.write(byte(0));
  lcd.write(byte(1));
  lcd.write(byte(5));

  // row 2------------------
  lcd.setCursor(0,1);
  delay(50);
  lcd.write(byte(5));
  lcd.write(byte(0));
  lcd.write(byte(5));
  lcd.write(byte(5));
  lcd.write(byte(0));
  lcd.write(byte(5));
  
  lcd.write(byte(0));
  lcd.write(byte(5));
  lcd.write(byte(5));  
  lcd.write(byte(5));
  
  lcd.write(byte(0));
  lcd.write(byte(5));
  lcd.write(byte(5));
  lcd.write(byte(5));
  
  lcd.write(byte(5));
  lcd.write(byte(5));
  lcd.write(byte(0));  
  lcd.write(byte(5));
  lcd.write(byte(5));
  lcd.write(byte(5));
  
  //row 3-----------------
  lcd.setCursor(0,2);
  delay(50);
  lcd.write(byte(5));
  lcd.write(byte(0));
  lcd.write(byte(5));
  lcd.write(byte(6));
  lcd.write(byte(0));
  lcd.write(byte(5));
  
  lcd.write(byte(0));
  lcd.write(byte(3));
  lcd.write(byte(5));  
  lcd.write(byte(5));

  lcd.write(byte(0));
  lcd.write(byte(5));
  lcd.write(byte(5));
  lcd.write(byte(5)); 
  
  lcd.write(byte(5));
  lcd.write(byte(5));
  lcd.write(byte(0));  
  lcd.write(byte(5));
  lcd.write(byte(5));
  lcd.write(byte(5));

  
  //row 4----------------
  lcd.setCursor(0,3);
  delay(50);
  lcd.write(byte(5));  
  lcd.write(byte(4));
  lcd.write(byte(0));
  lcd.write(byte(0));
  lcd.write(byte(6));
  lcd.write(byte(5));
  
  lcd.write(byte(0));
  lcd.write(byte(5));
  lcd.write(byte(5));  
  lcd.write(byte(5));
  
  lcd.write(byte(4));
  lcd.write(byte(0));
  lcd.write(byte(0));
  lcd.write(byte(3));
  
  lcd.write(byte(5));
  lcd.write(byte(5));
  lcd.write(byte(0));  
  lcd.write(byte(5));
  lcd.write(byte(5));
  lcd.write(byte(5));
  
  delay(1500);
  lcd.clear();  
}

//--------------------------function for logo initialization
void initializeLogo(){
  lcd.createChar(0, solid);
  lcd.createChar(1, t_right);
  lcd.createChar(2, t_left);
  lcd.createChar(3, b_right);
  lcd.createChar(4, b_left);
  lcd.createChar(5, blank);
  lcd.createChar(6, que);
}

//---------------------------------------------INITIALIZES THE LCD DISPLAY
void initializeLCD(){
  lcd.init();
  lcd.backlight();
  lcd.begin(20,4);
}

//---------------------------------------------DISPLAYS STATIC UNITS ON THE LCD DISPLAY
void displayTemplate(){
  //line 0
  lcd.setCursor(0,0);
  lcd.print("  . V    . A       W");
  
  //line 1
  lcd.setCursor(0,1);
  lcd.print("A   .   FC   .     %");
  lcd.setCursor(6,1);
  lcd.print((char)223);     //celcius sign
  lcd.setCursor(15,1);
  lcd.print((char)223);

  //line 2
  lcd.setCursor(0,2);
  lcd.print("  km/h      m    :  ");

  //line 3
  lcd.setCursor(0,3);
  lcd.print("Error:");
}

//---------------------------------------------CONVERT CONTROLLER DATA TO LCD FRIENDSLY FORMAT
Arr2 prep_data(int voltage_in, int current_in, int amb_temp_in, int fc_temp_in, int hydrogen_in){
  Arr2 a;
  a.concat_disp[2][5];
  //----------------------------------------LINE 0
  //voltage
  a.concat_disp[0][0] = (int)voltage_in;
  a.concat_disp[0][1] = (voltage_in - (float)a.concat_disp[0][0]) * 10;

  //current
  a.concat_disp[0][2] = (int)current_in;
  a.concat_disp[0][3] = (float)(current_in - (float)a.concat_disp[0][2]) * 10;

  //power
  a.concat_disp[0][4] = (int)voltage_in*current_in;

  //----------------------------------------LINE 1
  //ambient temperature
  a.concat_disp[1][0] = (int)amb_temp_in;
  a.concat_disp[1][1] = ((amb_temp_in - a.concat_disp[1][0]) * 10);

  //fc temperature
  a.concat_disp[1][2] = (int)fc_temp_in;
  a.concat_disp[1][3] = (fc_temp_in - a.concat_disp[1][2] ) * 10;

  //hydrogen level
  a.concat_disp[1][4] = (int)hydrogen_in;

  //----------------------------------------LINE 2
  //speed
  //disp2_values[0] = (int)currentSpeedKMPH;
  
  //distance
  //disp2_values[1] = (int)tripDistanceM;

  //time
  //seconds = millis()/1000;
  //disp2_values[2] = (int)(seconds / 60);    //get minutes
  //disp2_values[3] = (int)(seconds - disp2_values[2]*60);    //get seconds
  
  return a;
}

//---------------------------------------------DISPLAY NUMBERS CORRECTLY BASED ON TENS/ONES
int checkLTTen(int n){
  if(n < 10){
    return 1;
  }else{
    return 0;
  }
}
int checkLTThous(int n){
  if(n < 10){
    return 3;
  }else if(n < 100){
    return 2;
  }else if(n < 1000){
    return 1;
  }else{
    return 0;
  }
}


//---------------------------------------------WRITE DATA TO LCD DISPLAY
void displayRefresh(LiquidCrystal_I2C lcd, Arr2 structarray){
  //----------------------------------------LINE 0
  //voltage
  lcd.setCursor(0+checkLTTen(structarray.concat_disp[0][0]),0);
  lcd.print(structarray.concat_disp[0][0]);
  lcd.setCursor(3,0);
  lcd.print(structarray.concat_disp[0][1]);

  //current
  lcd.setCursor(7+checkLTTen(structarray.concat_disp[0][2]),0);
  lcd.print(structarray.concat_disp[0][2]);
  lcd.setCursor(10,0);
  lcd.print(structarray.concat_disp[0][3]);

  //power
  lcd.setCursor(15+checkLTThous(structarray.concat_disp[0][4]),0);
  lcd.print(structarray.concat_disp[0][4]);

  //----------------------------------------LINE 1
  //ambient temperature
  lcd.setCursor(2+checkLTTen(structarray.concat_disp[1][0]),1);
  lcd.print(structarray.concat_disp[1][0]);
  lcd.setCursor(5,1);
  lcd.print(structarray.concat_disp[1][1]);

  //fc temperature
  lcd.setCursor(11+checkLTTen(structarray.concat_disp[1][2]),1);
  lcd.print(structarray.concat_disp[1][2]);
  lcd.setCursor(14,1);
  lcd.print(structarray.concat_disp[1][3]);

  //hydrogen
  lcd.setCursor(17+checkLTTen(structarray.concat_disp[1][4]),1);
  lcd.print(structarray.concat_disp[1][4]);

  //----------------------------------------LINE 2
  //speed
  //lcd.setCursor(0+checkLTTen(disp2_values[0]),2);
  //lcd.print(disp2_values[0]);

  //distance
  //lcd.setCursor(8+checkLTThous(disp2_values[1]),2);
  //lcd.print(disp2_values[1]);

  //trip time
 // lcd.setCursor(15+checkLTTen(disp2_values[2]),2);
  //lcd.print(disp2_values[2]);

//  if(checkLTTen(disp2_values[2])){
//    lcd.setCursor(15,2);
//    lcd.print("0");
//    lcd.setCursor(16,2);
//    lcd.print(disp2_values[2]);
//  }else{
//    lcd.setCursor(15,2);
//    lcd.print(disp2_values[2]);
//  }
//  
//  if(checkLTTen(disp2_values[3])){
//    lcd.setCursor(18,2);
//    lcd.print("0");
//    lcd.setCursor(19,2);
//    lcd.print(disp2_values[3]);
//  }else{
//    lcd.setCursor(18,2);
//    lcd.print(disp2_values[3]);
//  }
}
