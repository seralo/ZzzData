#include <ZzzData.h>

ZzzDataMinMax <int> data;

void setup() {
	Serial.begin(115200);
	delay(250); //to ensure correctly initialized

	Serial.print("Add value data=");
	Serial.println(data.add(120));

	Serial.print("Add value data=");
	Serial.println(data.add(100));

	Serial.print("Add value data=");
	Serial.println(data.add(0));

	Serial.print("Min: ");
	Serial.println(data.min());

	Serial.print("Max: ");
	Serial.println(data.max());
}

void loop() {
}
