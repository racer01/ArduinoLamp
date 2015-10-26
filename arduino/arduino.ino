#include <IRremote.h>
#include <math.h>

// --------------------------- CONFIG -------------------------
int pin[] = {9, 10, 5};				// tű kiosztás
int RECV_PIN = 2;					//Infraport beallitasa
IRrecv irrecv(RECV_PIN);
decode_results results;
// ---------------------------\CONFIG -------------------------


int color[] = {0, 0, 0};			// jelenlegi érték
byte max = 255;						// 0-255 Fenyerosseg
double dly = 0.001;

int red[] = {255, 0, 0};
int green[] = {0, 255, 0};
int blue[] = {0, 0, 255};

int poop[] = {89, 48, 1};
int pink[] = {255, 20, 147};
int soCool[] = {204, 51, 0};

int black[] = {0, 0, 0};
int white[] = {255, 255, 255};

void setup()
{
	pinMode(pin[0], OUTPUT);		//Kimenetek beallitasa
	pinMode(pin[1], OUTPUT);
	pinMode(pin[2], OUTPUT);

	Serial.begin(9600);				//Soros monitor beallitasa
	irrecv.enableIRIn();			//Infra vevo engedelyezese
}

void loop()
{
	if (irrecv.decode(&results))
	{
		switch (results.value)
		{
			case 0x1FE7887:			//ON-OFF	- Laci
			case 0xFD00FF:			//ON-OFF	- Szikra
			animate(black, dly);
			break;

			case 0x1FE48B7:			//MUTE		- LACI
			case 0xFD40bF:			//PLAY/PAUSE- SZIKRA
			animate(white, dly);
			break;

			case 0x1FE807F:			//PHOTO		- LACI
			case 0xFD20DF:			//RPT		- SZIKRA
			animate(red, dly);
			break;

			case 0x1FE40BF:			//MUSIC		- LACI
			case 0xFDA05F:			//CH-		- SZIKRA
			animate(green, dly);
			break;

			case 0x1FEC03F:			//MOVIE		- LACI
			case 0xFD609F:			//CH+		- SZIKRA
			animate(blue, dly);
			break;

			case 0x1FE20DF:			//PLAY/PAUSE- LACI
			case 0xFD10EF:			//EQ		- SZIKRA
			animate(poop, dly);
			break;

			case 0x1FEA05F:			//UP		- LACI
			case 0xFD906F:			//VOL-		- SZIKRA
			animate(soCool, dly);
			break;

			case 0x1FE609F:
			case 0xFD50AF:
			animate(pink, dly);
			break;

		}
		irrecv.resume();
	}
}
// --------------------------- DEPRECATED ---------------------
void changeColor(int newcolor[])
{
	for (int i = 0; i < 3; i++)
	{
		color[i] = newcolor[i];
		analogWrite(pin[i], color[i]);
	}
}
// ---------------------------\DEPRECATED ---------------------

void animate(int newcolor[], double fadeRate)
{
	do
	{
		for (int i = 0; i < 3; i++)
		{
			int dist = newcolor[i] - color[i];	// a két érték közötti előjeles távolság

			if (dist >= 0)
			{
				color[i] += (int)ceil( dist * fadeRate);
			}
			else if (dist < 0)
			{
				color[i] += (int)floor( dist * fadeRate);
			}
			analogWrite(pin[i], color[i]);
		}
		delay(3);
	} while ( (color[0] != newcolor[0]) || (color[1] != newcolor[1]) || (color[2] != newcolor[2]) );
}
