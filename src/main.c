/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

/************************************************************************/
/* includes                                                             */
/************************************************************************/
#include <asf.h>

#include "gfx_mono_ug_2832hsweg04.h"
#include "gfx_mono_text.h"
#include "sysfont.h"

/************************************************************************/
/* defines                                                              */
/************************************************************************/

#define LED_PIO           PIOC                  // periferico que controla o LED
#define LED_PIO_ID        12                    // ID do periférico PIOC (controla LED)
#define LED_PIO_IDX       8u                    // ID do LED no PIO
#define LED_PIO_IDX_MASK  (1u << LED_PIO_IDX)   // Mascara para CONTROLARMOS o LED


#define BUT_PIO           PIOA
#define BUT_PIO_ID        10
#define BUT_PIO_IDX       11u
#define BUT_PIO_IDX_MASK (1u << BUT_PIO_IDX)

#define LED1_PIO           PIOA
#define LED1_PIO_ID        10
#define LED1_PIO_IDX       0u
#define LED1_PIO_IDX_MASK  (1u << LED1_PIO_IDX)

#define LED2_PIO           PIOC
#define LED2_PIO_ID        12
#define LED2_PIO_IDX       30u
#define LED2_PIO_IDX_MASK  (1u << LED2_PIO_IDX)

#define LED3_PIO           PIOB
#define LED3_PIO_ID        11
#define LED3_PIO_IDX       2u
#define LED3_PIO_IDX_MASK  (1u << LED3_PIO_IDX)

#define BUT1_PIO           PIOD
#define BUT1_PIO_ID        16
#define BUT1_PIO_IDX       28u
#define BUT1_PIO_IDX_MASK (1u << BUT1_PIO_IDX)

#define BUT2_PIO           PIOC
#define BUT2_PIO_ID        12
#define BUT2_PIO_IDX       31u
#define BUT2_PIO_IDX_MASK (1u << BUT2_PIO_IDX)

#define BUT3_PIO           PIOA
#define BUT3_PIO_ID        10
#define BUT3_PIO_IDX       19u
#define BUT3_PIO_IDX_MASK (1u << BUT3_PIO_IDX)

#define BUZ_PIO            PIOD
#define BUZ_PIO_ID         16
#define BUZ_PIO_IDX        30u
#define BUZ_PIO_IDX_MASK  (1u << BUZ_PIO_IDX)

/************************************************************************/
/* constants                                                            */
/************************************************************************/

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

/************************************************************************/
/* variaveis globais                                                    */
/************************************************************************/
int PausedTime = 0;


/************************************************************************/
/* prototypes                                                           */
/************************************************************************/

void init(void);

/************************************************************************/
/* interrupcoes                                                         */
/************************************************************************/

/************************************************************************/
/* funcoes                                                              */
/************************************************************************/

// Funcao Toca Buzzer

void Buzzer(int frequency, int lenght){
	
	pio_clear(LED_PIO, LED_PIO_IDX_MASK);
	
	long delay = 1000000 / frequency / 2;
	long ncycles = frequency * lenght / 1000;
	
	for(long i = 0; i < ncycles; i++){
		if(!pio_get (BUT3_PIO, PIO_INPUT, BUT3_PIO_IDX_MASK)){
			break;
		}
		pio_set(BUZ_PIO, BUZ_PIO_IDX_MASK);
		delay_us(delay);
		pio_clear(BUZ_PIO, BUZ_PIO_IDX_MASK);
		delay_us(delay);
	}
	
	pio_set(LED_PIO, LED_PIO_IDX_MASK);

}

// Funcao Musica

void Music(int melody[], int tempo[], int size, int pause){
	
	for(int i = pause; i < size; i++){
		
		int lenght = 1000 / tempo[i];
		
		Buzzer(melody[i], lenght);
		
		int notedelay = lenght * 1.3;
		delay_ms(notedelay);
		
		Buzzer(0, lenght);
		if(!pio_get (BUT3_PIO, PIO_INPUT, BUT3_PIO_IDX_MASK)){
			PausedTime = i;
			delay_ms(450);
			break;
		}
	}
}

// Fun??o de inicializa??o do uC
void init(void)
{
	// Initialize the board clock
	sysclk_init();
	
	// Desativa WatchDog Timer
	WDT->WDT_MR = WDT_MR_WDDIS;

	// Ativa o PIO na qual o LED foi conectado
	// para que possamos controlar o LED.
	pmc_enable_periph_clk(LED_PIO_ID);
	pmc_enable_periph_clk(LED1_PIO_ID);
	pmc_enable_periph_clk(LED2_PIO_ID);
	pmc_enable_periph_clk(LED3_PIO_ID);
	pmc_enable_periph_clk(BUZ_PIO_ID);

	// Inicializa PIO do botao
	pmc_enable_periph_clk(BUT_PIO_ID);
	pmc_enable_periph_clk(BUT1_PIO_ID);
	pmc_enable_periph_clk(BUT2_PIO_ID);
	pmc_enable_periph_clk(BUT3_PIO_ID);

	//Inicializa PC8 como saída
	pio_set_output(LED_PIO, LED_PIO_IDX_MASK, 0, 0, 0);
	pio_set_output(LED1_PIO, LED1_PIO_IDX_MASK, 0, 0, 0);
	pio_set_output(LED2_PIO, LED2_PIO_IDX_MASK, 0, 0, 0);
	pio_set_output(LED3_PIO, LED3_PIO_IDX_MASK, 0, 0, 0);
	pio_set_output(BUZ_PIO, BUZ_PIO_IDX_MASK, 0, 0, 0);

	// configura pino ligado ao botão como entrada com um pull-up.
	pio_set_input(BUT_PIO,BUT_PIO_IDX_MASK,PIO_DEFAULT);
	pio_set_input(BUT1_PIO,BUT1_PIO_IDX_MASK,PIO_DEFAULT);
	pio_set_input(BUT2_PIO,BUT2_PIO_IDX_MASK,PIO_DEFAULT);
	pio_set_input(BUT3_PIO,BUT3_PIO_IDX_MASK,PIO_DEFAULT);
	

	pio_pull_up(BUT_PIO, BUT_PIO_IDX_MASK, 1);
	pio_pull_up(BUT1_PIO, BUT1_PIO_IDX_MASK, 1);
	pio_pull_up(BUT2_PIO, BUT2_PIO_IDX_MASK, 1);
	pio_pull_up(BUT3_PIO, BUT3_PIO_IDX_MASK, 1);
	
	pio_set(LED_PIO, LED_PIO_IDX_MASK);
	pio_set(LED1_PIO, LED1_PIO_IDX_MASK);
	pio_set(LED2_PIO, LED2_PIO_IDX_MASK);
	pio_set(LED3_PIO, LED3_PIO_IDX_MASK);
}


int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */

	board_init();


	delay_init();
	pmc_enable_periph_clk(ID_PIOA);
	pmc_enable_periph_clk(ID_PIOB);
	pmc_enable_periph_clk(ID_PIOC);
	pmc_enable_periph_clk(ID_PIOD);
	pmc_enable_periph_clk(ID_SPI0);
	
	gfx_mono_ssd1306_init();
	
	init();
	int sel = 0;
	pio_clear(LED1_PIO, LED1_PIO_IDX_MASK);
	gfx_mono_draw_string("Musica:", 30,0, &sysfont);
	gfx_mono_draw_string("Mario     ", 30,16, &sysfont);
	
	
	int MarioMelody[] = {
		NOTE_E7, NOTE_E7, 0, NOTE_E7,
		0, NOTE_C7, NOTE_E7, 0,
		NOTE_G7, 0, 0,  0,
		NOTE_G6, 0, 0, 0,
		
		NOTE_C7, 0, 0, NOTE_G6,
		0, 0, NOTE_E6, 0,
		0, NOTE_A6, 0, NOTE_B6,
		0, NOTE_AS6, NOTE_A6, 0,
		
		NOTE_G6, NOTE_E7, NOTE_G7,
		NOTE_A7, 0, NOTE_F7, NOTE_G7,
		0, NOTE_E7, 0, NOTE_C7,
		NOTE_D7, NOTE_B6, 0, 0,
		
		NOTE_C7, 0, 0, NOTE_G6,
		0, 0, NOTE_E6, 0,
		0, NOTE_A6, 0, NOTE_B6,
		0, NOTE_AS6, NOTE_A6, 0,
		
		NOTE_G6, NOTE_E7, NOTE_G7,
		NOTE_A7, 0, NOTE_F7, NOTE_G7,
		0, NOTE_E7, 0, NOTE_C7,
		NOTE_D7, NOTE_B6, 0, 0
	};
	
	int MarioTime[] = {
		12, 12, 12, 12,
		12, 12, 12, 12,
		12, 12, 12, 12,
		12, 12, 12, 12,
		
		12, 12, 12, 12,
		12, 12, 12, 12,
		12, 12, 12, 12,
		12, 12, 12, 12,
		
		9, 9, 9,
		12, 12, 12, 12,
		12, 12, 12, 12,
		12, 12, 12, 12,
		
		12, 12, 12, 12,
		12, 12, 12, 12,
		12, 12, 12, 12,
		12, 12, 12, 12,
		
		9, 9, 9,
		12, 12, 12, 12,
		12, 12, 12, 12,
		12, 12, 12, 12,
	};
	
	int PiratesMelody[] = {       //Note of the song, 0 is a rest/pulse
		NOTE_E6, NOTE_G6, NOTE_A6, NOTE_A6, 0,
		NOTE_A6, NOTE_B6, NOTE_C7, NOTE_C7, 0,
		NOTE_C7, NOTE_D7, NOTE_B6, NOTE_B6, 0,
		NOTE_A6, NOTE_G6, NOTE_A6, 0,
		
		NOTE_E6, NOTE_G6, NOTE_A6, NOTE_A6, 0,
		NOTE_A6, NOTE_B6, NOTE_C7, NOTE_C7, 0,
		NOTE_C7, NOTE_D7, NOTE_B6, NOTE_B6, 0,
		NOTE_A6, NOTE_G6, NOTE_A6, 0,
		
		NOTE_E6, NOTE_G6, NOTE_A6, NOTE_A6, 0,
		NOTE_A6, NOTE_C7, NOTE_D7, NOTE_D7, 0,
		NOTE_D7, NOTE_E7, NOTE_F7, NOTE_F7, 0,
		NOTE_E7, NOTE_D7, NOTE_E7, NOTE_A6, 0,
		
		NOTE_A6, NOTE_B6, NOTE_C7, NOTE_C7, 0,
		NOTE_D7, NOTE_E7, NOTE_A6, 0,
		NOTE_A6, NOTE_C7, NOTE_B6, NOTE_B6, 0,
		NOTE_C7, NOTE_A6, NOTE_B6, 0,

		NOTE_A6, NOTE_A6,
		//Repeat of first part
		NOTE_A6, NOTE_B6, NOTE_C7, NOTE_C7, 0,
		NOTE_C7, NOTE_D7, NOTE_B6, NOTE_B6, 0,
		NOTE_A6, NOTE_G6, NOTE_A6, 0,

		NOTE_E6, NOTE_G6, NOTE_A6, NOTE_A6, 0,
		NOTE_A6, NOTE_B6, NOTE_C7, NOTE_C7, 0,
		NOTE_C7, NOTE_D7, NOTE_B6, NOTE_B6, 0,
		NOTE_A6, NOTE_G6, NOTE_A6, 0,
		
		NOTE_E6, NOTE_G6, NOTE_A6, NOTE_A6, 0,
		NOTE_A6, NOTE_C7, NOTE_D7, NOTE_D7, 0,
		NOTE_D7, NOTE_E7, NOTE_F7, NOTE_F7, 0,
		NOTE_E7, NOTE_D7, NOTE_E7, NOTE_A6, 0,
		
		NOTE_A6, NOTE_B6, NOTE_C7, NOTE_C7, 0,
		NOTE_D7, NOTE_E7, NOTE_A6, 0,
		NOTE_A6, NOTE_C7, NOTE_B6, NOTE_B6, 0,
		NOTE_C7, NOTE_A6, NOTE_B6, 0,
		//End of Repeat

		NOTE_E7, 0, 0, NOTE_F7, 0, 0,
		NOTE_E7, NOTE_E7, 0, NOTE_G7, 0, NOTE_E7, NOTE_D7, 0, 0,
		NOTE_D7, 0, 0, NOTE_C7, 0, 0,
		NOTE_B6, NOTE_C7, 0, NOTE_B6, 0, NOTE_A6,

		NOTE_E7, 0, 0, NOTE_F7, 0, 0,
		NOTE_E7, NOTE_E7, 0, NOTE_G7, 0, NOTE_E7, NOTE_D7, 0, 0,
		NOTE_D7, 0, 0, NOTE_C7, 0, 0,
		NOTE_B6, NOTE_C7, 0, NOTE_B6, 0, NOTE_A6
	};
	
	int PiratesTime[] = {
		8, 8, 4, 8, 8,
		8, 8, 4, 8, 8,
		8, 8, 4, 8, 8,
		8, 8, 2, 8,
		
		8, 8, 4, 8, 8,
		8, 8, 4, 8, 8,
		8, 8, 4, 8, 8,
		8, 8, 2, 8,
		
		8, 8, 4, 8, 8,
		8, 8, 4, 8, 8,
		8, 8, 4, 8, 8,
		8, 8, 8, 4, 8,

		8, 8, 4, 8, 8,
		4, 8, 4, 8,
		8, 8, 4, 8, 8,
		8, 8, 2, 2,

		4, 8,
		//Rpeat of First Part
		8, 8, 4, 8, 8,
		8, 8, 4, 8, 8,
		8, 8, 2, 8,
		
		8, 8, 4, 8, 8,
		8, 8, 4, 8, 8,
		8, 8, 4, 8, 8,
		8, 8, 2, 8,
		
		8, 8, 4, 8, 8,
		8, 8, 4, 8, 8,
		8, 8, 4, 8, 8,
		8, 8, 8, 4, 8,

		8, 8, 4, 8, 8,
		4, 8, 4, 8,
		8, 8, 4, 8, 8,
		8, 8, 2, 2,
		//End of Repeat
		
		4, 8, 2, 4, 8, 2,
		8, 8, 8, 8, 8, 8, 8, 8, 2,
		4, 8, 2, 4, 8, 2,
		8, 8, 8, 8, 8, 2,

		4, 8, 2, 4, 8, 2,
		8, 8, 8, 8, 8, 8, 8, 8, 2,
		4, 8, 2, 4, 8, 2,
		8, 8, 8, 8, 8, 2
	};
	
	int MegalovaniaMelody[] = {
		293*4, 293*4, 587*4,
		440*4, 415*4, 391*4,
		349*4, 293*4, 349*4,
		391*4, 261*4, 261*4,
		587*4, 440*4, 415*4,
		391*4, 349*4, 293*4,
		349*4, 391*4, 246*4,
		246*4, 587*4, 440*4,
		415*4, 391*4, 349*4,
		293*4, 349*4, 391*4,
		233*4, 233*4, 587*4,
		440*4, 415*4, 391*4,
		349*4, 293*4, 349*4,
		391*4, 293*4, 293*4,
		587*4, 440*4, 415*4,
		391*4, 349*4, 293*4,
		349*4, 391*4, 261*4,
		261*4, 587*4, 440*4,
		415*4, 391*4, 349*4,
		293*4, 349*4, 391*4,
		246*4, 246*4, 587*4,
		440*4, 415*4, 391*4,
		349*4, 293*4, 349*4,
		391*4, 233*4, 233*4,
		587*4, 440*4, 415*4,
		391*4, 349*4, 293*4,
		349*4, 391*4, 293*4,
		293*4, 587*4, 440*4,
		415*4, 391*4, 349*4,
		293*4, 349*4, 391*4,
		261*4, 261*4, 587*4,
		440*4, 415*4, 391
	};
	
	int MegalovaniaTime[] = {

		1000/125,

		1000/125,

		1000/250,

		1000/375,

		1000/250,

		1000/250,

		1000/250,

		1000/125,

		1000/125,

		1000/125,
		
		1000/62,
		
		1000/62,
		
		1000/62,
		
		1000/62,

		1000/250,

		1000/375,

		1000/250,

		1000/250,

		1000/250,

		1000/125,

		1000/125,

		1000/125,

		1000/125,

		1000/125,

		1000/250,

		1000/375,

		1000/250,

		1000/250,

		1000/250,

		1000/125,

		1000/125,

		1000/125,

		1000/62,

		1000/62,

		1000/62,

		1000/62,

		1000/250,

		1000/375,

		1000/250,

		1000/250,

		1000/250,

		1000/125,

		1000/125,

		1000/125,

		1000/125,

		1000/125,

		1000/250,

		1000/375,

		1000/250,

		1000/250,

		1000/250,

		1000/125,

		1000/125,

		1000/125,
		
		1000/62,
		
		1000/62,
		
		1000/62,
		
		1000/62,

		1000/250,

		1000/375,

		1000/250,

		1000/250,

		1000/250,

		1000/125,

		1000/125,

		1000/125,

		1000/125,

		1000/125,

		1000/250,

		1000/375,

		1000/250,

		1000/250,

		1000/250,

		1000/125,

		1000/125,

		1000/125,

		1000/62,

		1000/62,

		1000/62,

		1000/62,

		1000/250,

		1000/375,

		1000/250,

		1000/250,

		1000/250,

		1000/125,

		1000/125,

		1000/125,

		1000/125,

		1000/125,

		1000/250,

		1000/325,

		1000/250,

		1000/250,

		1000/250,

		1000/125,

		1000/125
	};
	
	while(1) {
		if(!pio_get (BUT1_PIO, PIO_INPUT, BUT1_PIO_IDX_MASK)){
			PausedTime = 0;
			if(sel == 0){
				Music(MarioMelody, MarioTime, 78,0);
			}
			else if(sel == 1){
				Music(MegalovaniaMelody, MegalovaniaTime, 100,0);
			}
			else if(sel == 2){
				Music(PiratesMelody, PiratesTime, 76,0);
			}


		}
		
		if(!pio_get (BUT2_PIO, PIO_INPUT, BUT2_PIO_IDX_MASK)){
			PausedTime = 0;
			if(sel == 0){
				pio_set(LED1_PIO, LED1_PIO_IDX_MASK);
				pio_clear(LED2_PIO, LED2_PIO_IDX_MASK);
				gfx_mono_draw_string("Undertale", 30,16, &sysfont);
				sel = 1;
				delay_ms(400);
			}
			else if(sel == 1){
				pio_set(LED2_PIO, LED2_PIO_IDX_MASK);
				pio_clear(LED3_PIO, LED3_PIO_IDX_MASK);
				gfx_mono_draw_string("Piratas  ", 30,16, &sysfont);
				sel = 2;
				delay_ms(400);
			}
			else if(sel == 2){
				pio_set(LED3_PIO, LED3_PIO_IDX_MASK);
				pio_clear(LED1_PIO, LED1_PIO_IDX_MASK);
				gfx_mono_draw_string("Mario    ", 30,16, &sysfont);
				sel = 0;
				delay_ms(400);
			}

		}

		if(!pio_get (BUT3_PIO, PIO_INPUT, BUT3_PIO_IDX_MASK)){
			if(sel == 0){
				Music(MarioMelody, MarioTime, 78,PausedTime);
			}
			else if(sel == 1){
				Music(MegalovaniaMelody, MegalovaniaTime, 100,PausedTime);
			}
			else if(sel == 2){
				Music(PiratesMelody, PiratesTime, 76,PausedTime);
			}
		}
	}
	/* Insert application code here, after the board has been initialized. */
}
