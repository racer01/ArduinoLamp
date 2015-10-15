#include <IRremote.h>
/*
LACI TAVIRANYITO GOMBOK
1FE48B7 MUTE
1FE58A7 REPEAT
1FE7887 ON/OFF
1FE807F PHOTO
1FE40BF MUSIC
1FEC03F MOVIE
1FE20DF PLAY/PAUSE
1FEA05F UP
1FE609F MENU
1FEE01F LEFT
1FE10EF MENU
1FE906F RIGHT
1FE50AF ZOOM
1FED827 DOWN
1FEF807 BACK MUSIC
1FE30CF VOL+
1FEB04F BALRA TEKER
1FE708F BALRA LEPTET
1FE00FF VOL-
1FEF00F JOBBRA TEKER
1FE9867 JOBBRA LEPTET
*/
//0:R
//1:G
//2:B

// ---------------- CONFIG ----------------
int pin[] = {9, 10, 5};				// tű kiosztás
int RECV_PIN = 2;					//Infraport beallitasa
IRrecv irrecv(RECV_PIN);
decode_results results;
// ---------------- \CONFIG ----------------


int color[] = {0, 0, 0};			// jelenlegi érték
byte max = 255;						// 0-255 Fenyerosseg
double dly = 0.2;

int red[] = {255, 0, 0};
int green[] = {0, 255, 0};
int black[] = {0, 0, 0};

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
		switch(results.value)
		{
			case 0x1FE7887:		//ON/OFF - Laci
			case 0xFD00FF:	//ON-OFF -

			break;

			case 0x1FE807F:
			changeColor(red);
			break;

			case 0x1FE40BF:
			changeColor(black);
			break;

		}
		irrecv.resume();
	}
}

void changeColor(int newcolor[])
{
	//if(pf == 0 && zf == 0 && kf == 0) { for (int i = 0; i < pwr; i++){ analogWrite(piros,i); analogWrite(zold,i); analogWrite(kek,i); delay(dly); } pf=1; zf=1; kf=1; on=1; }
	for(int i = 0; i < 3; i++)
	{
		color[i] = newcolor[i];
		analogWrite(pin[i], color[i]);
	}
}

boolean closeEnough(int a[], int b[], int length)
{
	boolean r = false;
	for(int i = 0; i < length; i++)
	{
		if( ( (int)abs(a[i]-b[i]) ) < 2)
		{
			r = true;
		}
	}
	return r;
}

void animate()
{

}
