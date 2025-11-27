const int RAIN_A0 = 35;  // analog
const int RAIN_D0 = 15;   // digital
const int DRY_RAW = 200;   // set by you after observing dry/wet
const int WET_RAW = 3500;  // set by you after observing fully wet

void setup(){
  Serial.begin(115200);
  analogSetPinAttenuation(RAIN_A0, ADC_11db);
  pinMode(RAIN_D0, INPUT);
  Serial.println("Rain sensor test (A0 + D0)");
}

int mapClamp(int val, int inMin, int inMax) {
  if (val <= inMin) return 0;
  if (val >= inMax) return 100;
  long v = map(val, inMin, inMax, 0, 100);
  return (int)v;
}

void loop(){
  int raw = analogRead(RAIN_A0); // 0..4095
  int d = digitalRead(RAIN_D0);
  int percent = mapClamp(raw, DRY_RAW, WET_RAW);
  Serial.printf("RAW=%d  PERC=%d%%  DIG=%d\n", raw, percent, d);
  delay(500);
}