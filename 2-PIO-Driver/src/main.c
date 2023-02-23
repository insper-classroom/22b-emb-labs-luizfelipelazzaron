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

/*  Default pin configuration (no attribute). */
#define _PIO_DEFAULT (0u << 0)
/*  The internal pin pull-up is active. */
#define _PIO_PULLUP (1u << 0)
/*  The internal glitch filter is active. */
#define _PIO_DEGLITCH (1u << 1)
/*  The internal debouncing filter is active. */
#define _PIO_DEBOUNCE (1u << 3)

/**

\brief Define um nível de saída alto em todos os PIOs definidos em ul_mask.
Isso não tem efeito imediato em PIOs que não são saídas, mas o controlador de PIO
salvará o valor se eles forem alterados para saídas.
\param p_pio Ponteiro para uma instância de PIO.
\param ul_mask Máscara de bits de um ou mais pinos a serem configurados.
*/
void _pio_set(Pio *p_pio, const uint32_t ul_mask)
{
	p_pio->PIO_SODR = ul_mask;
}

/**
\brief Essa função chamada _pio_set é usada para definir o nível lógico de saída de um ou mais pinos de um periférico de entrada/saída programável (PIO) como alto (nível lógico 1).
O parâmetro p_pio é um ponteiro para a estrutura de dados do periférico que representa o conjunto de PIOs que serão configurados. O parâmetro ul_mask é uma máscara de bits que indica quais pinos serão configurados para o nível lógico alto.
Dentro da função, o registrador PIO_SODR do periférico é utilizado para setar o nível lógico alto (1) em todos os pinos definidos na máscara ul_mask. Ou seja, essa função vai definir que todos os pinos especificados na máscara devem ter o valor lógico 1, fazendo com que esses pinos, se conectados a algum dispositivo, tenham uma tensão elétrica correspondente a esse valor.
Configura um nível de saída baixo em todos os PIOs definidos em ul_mask.
Isso não tem efeitos imediatos em PIOs que não são de saída, mas o controlador de PIO
salvará o valor se eles forem alterados para saída.
\param p_pio Ponteiro para uma instância de PIO.
\param ul_mask Máscara de bits de um ou mais pinos para configurar.
*/
void _pio_clear(Pio *p_pio, const uint32_t ul_mask)
{
	p_pio->PIO_CODR = ul_mask;
}

/**
 * \brief A função é responsável por configurar o resistor de pull-up interno em um ou mais pinos de um componente chamado PIO (Input/Output Programável). O resistor de pull-up é um componente eletrônico que, quando ativado, faz com que o nível de tensão do pino seja "puxado" para um valor alto (geralmente 3,3V ou 5V), mesmo quando nenhum dispositivo externo estiver conectado a ele. Isso pode ser útil em alguns casos, como por exemplo, para evitar que um pino flutue (fique oscilando) em situações onde não há dispositivo externo conectado.
Na função, o parâmetro "ul_mask" é um bitmask (máscara de bits) que representa quais pinos serão configurados. O parâmetro "ul_pull_up_enable" é um valor booleano que indica se o resistor de pull-up interno deve ser ativado ou desativado nos pinos selecionados. Se ele for definido como "true", o resistor de pull-up será ativado e, se for definido como "false", será desativado. Configura a resistência interna de pull-up dos PIOs especificados em ul_mask em um determinado pino.
 *
 * \param p_pio Pointer to a PIO instance.
 * \param ul_mask Bitmask of one or more pin(s) to configure.
 * \param ul_pull_up_enable indica se a resistência de pull-up interna do(s) pino(s) deve ser configurada.
 */
void _pio_pull_up(Pio *p_pio, const uint32_t ul_mask,
				  const uint32_t ul_pull_up_enable)
{
	/**
	 * Essa função configura os pull-ups internos dos pinos do PIO. Se o parâmetro ul_pull_up_enable for 1, a função ativa o pull-up dos pinos especificados em ul_mask.
	 * Se for 0, a função desativa o pull-up.
	 * Para fazer isso, a função usa os registradores PIO_PUER e PIO_PUDR, que são responsáveis por ativar e desativar os pull-ups internos dos pinos, respectivamente.
	 * Se ul_pull_up_enable for 1, a função escreve o valor de ul_mask no registrador PIO_PUER, ativando os pull-ups dos pinos especificados.
	 * Caso contrário, a função escreve o valor de ul_mask no registrador PIO_PUDR, desativando os pull-ups dos pinos especificados.
	 *
	 */
	if (ul_pull_up_enable)
	{
		p_pio->PIO_PUER = ul_mask; // ativa o pull-up
	}
	else
	{
		p_pio->PIO_PUDR = ul_mask; // desativa o pull-up
	}
}

/**
 * \brief Configure um ou mais pinos ou um controlador PIO como entradas.
 * Opcionalmente, as correspondentes resistências pull-up internas e filtros de glitches podem ser ativados.
 *
 * \param p_pio Pointer to a PIO instance.
 * \param ul_mask Bitmask indicating which pin(s) to configure as input(s).
 * \param ul_attribute PIO attribute(s).
 */
void _pio_set_input(Pio *p_pio, const uint32_t ul_mask,
					const uint32_t ul_attribute)
{
	_pio_pull_up(p_pio, ul_mask, ul_attribute & _PIO_PULLUP);

	if (ul_attribute & (PIO_DEGLITCH | PIO_DEBOUNCE))
	{
		p_pio->PIO_IFER = ul_mask;
	}
	else
	{
		p_pio->PIO_IFDR = ul_mask;
	}
}

/**
 * \brief Configure one or more pin(s) of a PIO controller as outputs, with
 * the given default value. Optionally, the multi-drive feature can be enabled
 * on the pin(s).
 *
 * \param p_pio Pointer to a PIO instance.
 * \param ul_mask Bitmask indicating which pin(s) to configure.
 * \param ul_default_level Default level on the pin(s).
 * \param ul_multidrive_enable Indicates if the pin(s) shall be configured as
 * open-drain.
 * \param ul_pull_up_enable Indicates if the pin shall have its pull-up
 * activated.
 */
void _pio_set_output(Pio *p_pio, const uint32_t ul_mask,
					 const uint32_t ul_default_level,
					 const uint32_t ul_multidrive_enable,
					 const uint32_t ul_pull_up_enable)
{
	/* Ativa o controlador PIO para o(s) pino(s) especificado(s)  */
	p_pio->PIO_PER |= ul_mask;

	/* Define a direção do(s) pino(s) especificado(s) como saída */
	p_pio->PIO_OER |= ul_mask;

	/* Define o nível de saída padrão do(s) pino(s) especificado(s) */
	_pio_set(p_pio, ul_default_level);

	/* Ativa/desativa a função de multi-drive para o(s) pino(s) especificado(s) */
	if (ul_multidrive_enable)
	{
		p_pio->PIO_MDER |= ul_mask;
	}
	else
	{
		p_pio->PIO_MDDR |= ul_mask;
	}

	/* Ativa/desativa o pull-up para o(s) pino(s) especificado(s)  */
	_pio_pull_up(p_pio, ul_mask, ul_pull_up_enable);
}

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

	// Setando os inputs, os Botões
	_pio_set_input(BUTTON1_PIO, BUTTON1_PIO_IDX_MASK, _PIO_PULLUP | _PIO_DEBOUNCE);
	_pio_set_input(BUTTON2_PIO, BUTTON2_PIO_IDX_MASK, _PIO_PULLUP | _PIO_DEBOUNCE);
	_pio_set_input(BUTTON3_PIO, BUTTON3_PIO_IDX_MASK, _PIO_PULLUP | _PIO_DEBOUNCE);

	// Configura Pinos dos LEDS
	_pio_set_output(LED1_PIO, LED1_PIO_IDX_MASK, 0, 1, 0);
	_pio_set_output(LED2_PIO, LED2_PIO_IDX_MASK, 0, 1, 0);
	_pio_set_output(LED3_PIO, LED3_PIO_IDX_MASK, 0, 1, 0);

	// SUPER LOOP
	// aplicacoes embarcadas no devem sair do while(1).
	while (1)
	{
		// Ligando o LED1 quando o botão 1 é apertado:
		if (!pio_get(BUTTON1_PIO, PIO_INPUT, BUTTON1_PIO_IDX_MASK))
		{
			// Limpa o pino LED1_IDX (setando para nível lógico baixo)
			_pio_clear(LED1_PIO, LED1_PIO_IDX_MASK);
		}
		else
		{
			// Ativa o pino LED1_IDX (setando para nível lógico alto, apagando o LED)
			_pio_set(LED1_PIO, LED1_PIO_IDX_MASK);
		}
		// ------------------------------------------
		// Ligando o LED2 quando o botão 2 é apertado:
		if (!pio_get(BUTTON2_PIO, PIO_INPUT, BUTTON2_PIO_IDX_MASK))
		{
			// Limpa o pino LED2_IDX (setando para nível lógico baixo)
			_pio_clear(LED2_PIO, LED2_PIO_IDX_MASK);
		}
		else
		{
			// Ativa o pino LED2_IDX (setando para nível lógico alto, apagando o LED)
			_pio_set(LED2_PIO, LED2_PIO_IDX_MASK);
		}

		// ------------------------------------------
		// Ligando o LED3 quando o botão 3 é apertado:
		if (!pio_get(BUTTON3_PIO, PIO_INPUT, BUTTON3_PIO_IDX_MASK))
		{
			// Limpa o pino LED3_IDX (setando para nível lógico baixo)
			_pio_clear(LED3_PIO, LED3_PIO_IDX_MASK);
		}
		else
		{
			// Ativa o pino LED3_IDX (setando para nível lógico alto, apagando o LED)
			_pio_set(LED3_PIO, LED3_PIO_IDX_MASK);
		}
	}
	// Nunca devemos chegar aqui!
	return 0;
}