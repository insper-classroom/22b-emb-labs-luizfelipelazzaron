#include "asf.h"

// -----------------------------

// Definindo os LEDS e os BUTTONS da placa
// Com base na cartilha oferecida em sala e doc Atmel OLED1 Xplained Pro

// LED 1
//  Segundo tabela 4.2.1, LED1 está no pino 7
//  Conforme cartilha, pino 7 equvale a PA0
//  Portanto, PIO = PIOA e PIO_IDX=0
#define LED1_PIO PIOA
#define LED1_PIO_ID ID_PIOA
#define LED1_PIO_IDX 0
#define LED1_PIO_IDX_MASK (1 << LED1_PIO_IDX)

// LED 2
//  tabela 4.2.1, LED1 está no pino 8
//  Cartilha, pino 7 equvale a PC30
//  Portanto, PIO = PIOC e PIO_IDX=30
#define LED2_PIO PIOC
#define LED2_PIO_ID ID_PIOC
#define LED2_PIO_IDX 30
#define LED2_PIO_IDX_MASK (1 << LED2_PIO_IDX)

// LED 3
//  tabela 4.2.1, LED3 está no pino 6
//  Cartilha, pino 6 equvale a PB2
//  Portanto, PIO = PIOB e PIO_IDX=2
#define LED3_PIO PIOB
#define LED3_PIO_ID ID_PIOB
#define LED3_PIO_IDX 2
#define LED3_PIO_IDX_MASK (1 << LED3_PIO_IDX)

// BUTTON1
// Segundo tabela 4.2.1, BUTTON1 está no pino 9
// Conforme cartilha, pino 9 equvale a PD28
// Portanto, PIO = PIOD e PIO_IDX=28
#define BUTTON1_PIO PIOD
#define BUTTON1_PIO_ID ID_PIOD
#define BUTTON1_PIO_IDX 28
#define BUTTON1_PIO_IDX_MASK (1 << BUTTON1_PIO_IDX)

// BUTTON2
// Segundo tabela 4.2.1, BUTTON2 está no pino 3
// Conforme cartilha, pino 3 equivale a PC31
// Portanto, PIO = PIOC e PIO_IDX=31
#define BUTTON2_PIO PIOC
#define BUTTON2_PIO_ID ID_PIOC
#define BUTTON2_PIO_IDX 31
#define BUTTON2_PIO_IDX_MASK (1 << BUTTON2_PIO_IDX)

// BUTTON3
// Segundo tabela 4.2.1, BUTTON3 está no pino 4
// Conforme cartilha, pino 4 equivale a PA19
// Portanto, PIO = PIOA e PIO_IDX=19
#define BUTTON3_PIO PIOA
#define BUTTON3_PIO_ID ID_PIOA
#define BUTTON3_PIO_IDX 19
#define BUTTON3_PIO_IDX_MASK (1 << BUTTON3_PIO_IDX)

int main(void)
{
	// Inicializa clock
	sysclk_init();

	// Desativa watchdog
	WDT->WDT_MR = WDT_MR_WDDIS;

	// Ativa PIOs dos LEDS
	pmc_enable_periph_clk(LED1_PIO_ID);
	pmc_enable_periph_clk(LED2_PIO_ID);
	pmc_enable_periph_clk(LED3_PIO_ID);

	// Ativa PIOs dos BUTTONS
	pmc_enable_periph_clk(BUTTON1_PIO_ID);
	pmc_enable_periph_clk(BUTTON2_PIO_ID);
	pmc_enable_periph_clk(BUTTON3_PIO_ID);

	// Configura Pinos dos LEDS
	pio_configure(LED1_PIO, PIO_OUTPUT_1, LED1_PIO_IDX_MASK, PIO_DEFAULT);
	pio_configure(LED2_PIO, PIO_OUTPUT_1, LED2_PIO_IDX_MASK, PIO_DEFAULT);
	pio_configure(LED3_PIO, PIO_OUTPUT_1, LED3_PIO_IDX_MASK, PIO_DEFAULT);

	// Configura Pinos dos Buttons
	pio_configure(BUTTON1_PIO, PIO_INPUT, BUTTON1_PIO_IDX_MASK, PIO_PULLUP);
	pio_configure(BUTTON2_PIO, PIO_INPUT, BUTTON2_PIO_IDX_MASK, PIO_PULLUP);
	pio_configure(BUTTON3_PIO, PIO_INPUT, BUTTON2_PIO_IDX_MASK, PIO_PULLUP);

	// SUPER LOOP
	// aplicacoes embarcadas no devem sair do while(1).
	while (1)
	{
		// Ligando o LED1 quando o botão 1 é apertado:
		if (!pio_get(BUTTON1_PIO, PIO_INPUT, BUTTON1_PIO_IDX_MASK))
		{
			// Limpa o pino LED1_IDX (setando para nível lógico baixo)
			pio_clear(LED1_PIO, LED1_PIO_IDX_MASK);
		}
		else
		{
			// Ativa o pino LED1_IDX (setando para nível lógico alto, apagando o LED)
			pio_set(LED1_PIO, LED1_PIO_IDX_MASK);
		}
		// ------------------------------------------
				// Ligando o LED2 quando o botão 2 é apertado:
		if (!pio_get(BUTTON2_PIO, PIO_INPUT, BUTTON2_PIO_IDX_MASK))
		{
			// Limpa o pino LED2_IDX (setando para nível lógico baixo)
			pio_clear(LED2_PIO, LED2_PIO_IDX_MASK);
		}
		else
		{
			// Ativa o pino LED2_IDX (setando para nível lógico alto, apagando o LED)
			pio_set(LED2_PIO, LED2_PIO_IDX_MASK);
		}

		// ------------------------------------------
				// Ligando o LED3 quando o botão 3 é apertado:
		if (!pio_get(BUTTON3_PIO, PIO_INPUT, BUTTON3_PIO_IDX_MASK))
		{
			// Limpa o pino LED3_IDX (setando para nível lógico baixo)
			pio_clear(LED3_PIO, LED3_PIO_IDX_MASK);
		}
		else
		{
			// Ativa o pino LED3_IDX (setando para nível lógico alto, apagando o LED)
			pio_set(LED3_PIO, LED3_PIO_IDX_MASK);
		}
	}
	// Nunca devemos chegar aqui!
	return 0;
}