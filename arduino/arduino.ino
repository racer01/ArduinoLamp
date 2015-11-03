#include <IRremote.h>
#include <math.h>

// --------------------------- CONFIG -------------------------
const int pin[] = {9, 10, 5};				// tű kiosztás
const int RECV_PIN = 2;					//Infraport beallitasa
IRrecv irrecv(RECV_PIN);
decode_results results;
// ---------------------------\CONFIG -------------------------


int color[] = {0, 0, 0};			// jelenlegi érték
const byte max = 255;						// 0-255 Fenyerosseg
double dly = 0.001;

const int red[] = {255, 0, 0};
const int green[] = {0, 255, 0};
const int blue[] = {0, 0, 255};

const int poop[] = {255, 255, 0};
const int pink[] = {255, 20, 147};
const int soCool[] = {204, 51, 0};

const int turkiz[] = {0, 255,255};
const int lila[] = {255, 0, 255};

const int black[] = {0, 0, 0};
const int white[] = {255, 255, 255};

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
			case 0xFD30CF:			//0 		- SZIKRA
			animate(white, dly);
			break;

			case 0x1FE807F:			//PHOTO		- LACI
			case 0xFD08F7:			//1		- SZIKRA
			animate(red, dly);
			break;

			case 0x1FE40BF:			//MUSIC		- LACI
			case 0xFD08F7:			//2		- SZIKRA
			animate(green, dly);
			break;

			case 0x1FEC03F:			//MOVIE		- LACI
			case 0xFD8877:			//3		- SZIKRA
			animate(blue, dly);
			break;

			case 0x1FE20DF:			//PLAY/PAUSE- LACI
			case 0xFD28D7:			//4		- SZIKRA
			animate(poop, dly);
			break;

			case 0x1FEA05F:			//UP		- LACI
			animate(soCool, dly);
			break;
			
			case 0xFDA857:			//5		- SZIKRA
			animate(turkiz, dly);
			break;

			case 0x1FE609F:
			animate(pink, dly);
			break;
			
			case 0xFD6897:			//6		- SZIKRA
			animate(lila, dly);
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
