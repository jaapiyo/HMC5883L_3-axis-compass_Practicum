
// Practicum positiebepaling
// HMC5883L 3-axis MEMS compass
// 8-5-2017
//
// Jaap Elstgeest en Jelle Kampf

#include <HMC5883L.h>
#include <Wire.h>

HMC5883L compass;


void setup()
{

	Serial.begin(115200);
	Wire.begin();

	compass = HMC5883L();
	compass.SetScale(2.5);	// configure gain (1.3 is miss een beetje teveel?)
	compass.SetMeasurementMode(Measurement_Continuous);

}

void loop()
{

	MagnetometerRaw raw = compass.ReadRawAxis();
	MagnetometerScaled scaled = compass.ReadScaledAxis();

	float xHeading = atan2(scaled.YAxis, scaled.XAxis);
	float yHeading = atan2(scaled.ZAxis, scaled.XAxis);
	float zHeading = atan2(scaled.ZAxis, scaled.YAxis);

	if (xHeading < 0) xHeading += 2 * PI;
	if (xHeading > 2 * PI) xHeading -= 2 * PI;

	if (yHeading < 0) yHeading += 2 * PI;
	if (yHeading > 2 * PI) yHeading -= 2 * PI;

	if (zHeading < 0) zHeading += 2 * PI;
	if (zHeading > 2 * PI) zHeading -= 2 * PI;

	float xDeg = xHeading * 180 / M_PI;
	float yDeg = yHeading * 180 / M_PI;
	float zDeg = zHeading * 180 / M_PI;

	/*Serial.print(xDeg);
	Serial.print('\t');
	Serial.print(yDeg);
	Serial.print('\t');
	Serial.print(zDeg);
	Serial.print('\n');*/

	Serial.print(raw.XAxis);
	Serial.print('\t');
	Serial.print(raw.YAxis);
	Serial.print('\t');
	Serial.print(raw.ZAxis);
	Serial.print('\n');

	delay(100);
}
