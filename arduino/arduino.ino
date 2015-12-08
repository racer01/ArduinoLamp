#include <IRremote.h>
#include <math.h>

// --------------------------- CONFIG -------------------------
const int pin[] = {9, 10, 5};				// tű kiosztás
const int RECV_PIN = 2;					//Infraport beallitasa
IRrecv irrecv(RECV_PIN);
decode_results results;
// ---------------------------\CONFIG -------------------------


byte color[] = {0, 0, 0};			// jelenlegi értékek
byte newColor[] = {0, 0, 0};			// leendő értékek
const byte max = 255;						// 0-255 fényerősség
double fadeRate = 0.001;					// késleltetés (3ms-enként)
bool animate = false;				// animáljon-e

const byte red[] = {255, 0, 0};
const byte green[] = {0, 255, 0};
const byte blue[] = {0, 0, 255};

const byte pink[] = {255, 20, 147};
const byte soCool[] = {204, 51, 0};

const byte cyan[] = {0, 255, 255};
const byte purple[] = {255, 0, 255};
const byte yellow[] = {255, 255, 0};

const byte black[] = {0, 0, 0};
const byte white[] = {255, 255, 255};

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
			changeColor(black);
			break;

			case 0x1FE48B7:			//MUTE		- LACI
			case 0xFD30CF:			//0 		- SZIKRA
			changeColor(white);
			break;

			case 0x1FE807F:			//PHOTO		- LACI
			case 0xFD08F7:			//1		- SZIKRA
			changeColor(red);
			break;

			case 0x1FE40BF:			//MUSIC		- LACI
			case 0xFD8877:			//2		- SZIKRA
			changeColor(green);
			break;

			case 0x1FEC03F:			//MOVIE		- LACI
			case 0xFD48B7:			//3		- SZIKRA
			changeColor(blue);
			break;

			case 0x1FE20DF:			//PLAY/PAUSE- LACI
			case 0xFD28D7:			//4		- SZIKRA
			changeColor(yellow);
			break;

			case 0x1FEA05F:			//UP		- LACI
			changeColor(soCool);
			break;

			case 0xFDA857:			//5		- SZIKRA
			changeColor(cyan);
			break;

			case 0x1FE609F:
			changeColor(pink);
			break;

			case 0xFD6897:			//6		- SZIKRA
			changeColor(purple);
			break;

		}
		irrecv.resume();
	}

	if (animate)
	{
		for (int i = 0; i < 3 ; i++)
		{
			color[i] += absCeil( (newColor[i] - color[i]) * fadeRate );
			analogWrite(pin[i], color[i]);
		}
		if ( (color[0] == newColor[0]) && (color[1] == newColor[1]) && (color[2] == newColor[2]) )
			animate = false;
		delay(3);
	}
}

int absCeil(double in)
{
	if (in >= 0)
		return (int)ceil(in);
	else if (in < 0)
		return (int)floor(in);
}

void changeColor(const byte nc[])
{
	animate = true;
	for(byte i = 0; i < 3; i++)
	{
		newColor[i] = nc[i];
	}
}
