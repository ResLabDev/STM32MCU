/** @file mcu_STM32F446xx.h
*
* @brief STM32F446xx MCU header file.
*
*/

#ifndef MCU_STM32F446XX_H_
#define MCU_STM32F446XX_H_

#include <stdint.h>

// =============================
// | NVIC Interrupt Controller |
// =============================
//
//=== NVIC Register Base Address ===
#define NVIC_ISER_BASE			0xE000E100U				// Interrupt set-enable register base
#define NVIC_ICER_BASE			0xE000E180U				// Interrupt clear-enable register base
#define NVIC_ISPR_BASE			0xE000E200U				// Interrupt set-pending register base
#define NVIC_ICPR_BASE			0xE000E280U				// Interrupt clear-pending register base
#define NVIC_IABR_BASE			0xE000E300U				// Interrupt active bit register base
#define NVIC_IPR_BASE			0xE000E400U				// Interrupt priority register base

// === NVIC Interrupt Generic Register ===
//
typedef struct NVIC_GEN_Reg_Def
{
	volatile uint32_t reg[8];
} NVIC_GEN_Reg_Def_t;

// === NVIC Interrupt IPR Register ===
//
typedef struct NVIC_IPR_Reg_Def
{
	volatile uint32_t reg[60];
} NVIC_IPR_Reg_Def_t;

// === NVIC Interrupt Register Definition ===
//
#define NVIC_ISER				((NVIC_GEN_Reg_Def_t *) NVIC_ISER_BASE)
#define NVIC_ICER				((NVIC_GEN_Reg_Def_t *) NVIC_ICER_BASE)
#define NVIC_ISPR				((NVIC_GEN_Reg_Def_t *) NVIC_ISPR_BASE)
#define NVIC_ICPR				((NVIC_GEN_Reg_Def_t *) NVIC_ICPR_BASE)
#define NVIC_IABR				((NVIC_GEN_Reg_Def_t *) NVIC_IABR_BASE)
#define NVIC_IPR				((NVIC_IPR_Reg_Def_t *) NVIC_IABR_BASE)


// ================
// | BASE Address |
// ================
//
//=== Flash and SRAM Base Address ===
//
#define FLASH_BASE				0x08000000U
#define SRAM1_BASE				0x20000000U
#define SRAM2_BASE				0x2001C000U
#define ROM						0x1FFF0000U
#define SRAM					SRAM1_BASE

//=== APBx and AHBx Peripheral Base Address ===
//
#define PERIPH_BASE				0x40000000U
#define APB1_PERIPH_BASE		PERIPH_BASE
#define APB2_PERIPH_BASE		0x40010000U
#define AHB1_PERIPH_BASE		0x40020000U
#define AHB2_PERIPH_BASE		0x50000000U

//=== APB1 Peripherals Base Address ===
//
#define I2C1_BASE				(APB1_PERIPH_BASE + 0x5400)
#define I2C2_BASE				(APB1_PERIPH_BASE + 0x5800)
#define I2C3_BASE				(APB1_PERIPH_BASE + 0x5C00)
#define SPI2_BASE				(APB1_PERIPH_BASE + 0x3800)
#define SPI3_BASE				(APB1_PERIPH_BASE + 0x3C00)
#define USART2_BASE				(APB1_PERIPH_BASE + 0x4400)
#define USART3_BASE				(APB1_PERIPH_BASE + 0x4800)
#define UART4_BASE				(APB1_PERIPH_BASE + 0x4C00)
#define UART5_BASE				(APB1_PERIPH_BASE + 0x5000)

//=== APB2 Peripherals Base Address ===
//
#define USART1_BASE				(APB2_PERIPH_BASE + 0x1000)
#define USART6_BASE				(APB2_PERIPH_BASE + 0x1400)
#define SPI1_BASE				(APB2_PERIPH_BASE + 0x3000)
#define SPI4_BASE				(APB2_PERIPH_BASE + 0x37FF)
#define SYSCFG_BASE				(APB2_PERIPH_BASE + 0x3800)
#define EXTI_BASE				(APB2_PERIPH_BASE + 0x3C00)

//=== AHB1 Peripherals Base Address ===
//
#define GPIOA_BASE				(AHB1_PERIPH_BASE + 0x0000)
#define GPIOB_BASE				(AHB1_PERIPH_BASE + 0x0400)
#define GPIOC_BASE				(AHB1_PERIPH_BASE + 0x0800)
#define GPIOD_BASE				(AHB1_PERIPH_BASE + 0x0C00)
#define GPIOE_BASE				(AHB1_PERIPH_BASE + 0x1000)
#define GPIOF_BASE				(AHB1_PERIPH_BASE + 0x1400)
#define GPIOG_BASE				(AHB1_PERIPH_BASE + 0x1800)
#define GPIOH_BASE				(AHB1_PERIPH_BASE + 0x1C00)
#define RCC_BASE				(AHB1_PERIPH_BASE + 0x3800)


// =======================
// | Peripheral Register |
// =======================
//
// === GPIO Peripheral Register ===
//
typedef struct GPIO_RegDef
{
	volatile uint32_t MODER;		// GPIO port mode register
	volatile uint32_t OTYPER;		// GPIO port output type register
	volatile uint32_t OSPEEDR;		// GPIO port output speed register
	volatile uint32_t PUPDR;		// GPIO port pull-up/pull-down register
	volatile uint32_t IDR;			// GPIO port input data register
	volatile uint32_t ODR;			// GPIO port output data register
	volatile uint32_t BSRR;			// GPIO port bit set/reset register
	volatile uint32_t LCKR;			// GPIO port configuration lock register
	volatile uint32_t AFR[2];		// GPIO alternate function AFR[0]:  low  / AFR[1]: high register
} GPIO_RegDef_t;

// === SPI Peripheral Register ===
//
typedef struct SPI_RegDef
{
	volatile uint32_t CR1;			// SPI control register 1
	volatile uint32_t CR2;			// SPI control register 2
	volatile uint32_t SR;			// SPI status register
	volatile uint32_t DR;			// SPI data register
	volatile uint32_t CRCPR;		// SPI CRC polynomal register
	volatile uint32_t RXCRCR;		// SPI RX CRC register
	volatile uint32_t TXCRCR;		// SPI TX CRC register
	volatile uint32_t I2SCFGR;		// SPI_I2S configuration register
	volatile uint32_t SPI_I2SPR;	// SPI_I2S prescaler register
} SPI_RegDef_t;

// === RCC (Reset-Clock Control) Peripheral Register ===
//
typedef struct RCC_RegDef
{
	volatile uint32_t CR;			// RCC clock control register
	volatile uint32_t PLLCFGR;		// RCC PLL configuration register
	volatile uint32_t CFGR;			// RCC clock configuration register
	volatile uint32_t CIR;			// RCC clock interrupt register
	volatile uint32_t AHB1RSTR;		// RCC AHB1 peripheral reset register
	volatile uint32_t AHB2RSTR;		// RCC AHB2 peripheral reset register
	volatile uint32_t AHB3RSTR;		// RCC AHB3 peripheral reset register
	uint32_t 	  	  RESERVED0;	// 0x1C
	volatile uint32_t APB1RSTR;		// RCC APB1 peripheral reset register
	volatile uint32_t APB2RSTR;		// RCC APB2 peripheral reset register
	uint32_t 	  	  RESERVED1[2];	// 0x28 - 0x2C
	volatile uint32_t AHB1ENR;		// RCC AHB1 peripheral clock enable register
	volatile uint32_t AHB2ENR;		// RCC AHB2 peripheral clock enable register
	volatile uint32_t AHB3ENR;		// RCC AHB3 peripheral clock enable register
	uint32_t 	  	  RESERVED2;	// 0x3C
	volatile uint32_t APB1ENR;		// RCC APB1 peripheral clock enable register
	volatile uint32_t APB2ENR;		// RCC APB2 peripheral clock enable register
	uint32_t 	  	  RESERVED3[2];	// 0x48 - 0x4C
	volatile uint32_t AHB1LPENR;	// RCC AHB1 peripheral clock enable in low power mode register
	volatile uint32_t AHB2LPENR;	// RCC AHB2 peripheral clock enable in low power mode register
	volatile uint32_t AHB3LPENR;	// RCC AHB3 peripheral clock enable in low power mode register
	uint32_t 	  	  RESERVED4;	// 0x5C
	volatile uint32_t APB1LPENR;	// RCC APB1 peripheral clock enable in low power mode register
	volatile uint32_t APB2LPENR;	// RCC APB2 peripheral clock enable in low power mode register
	uint32_t 	  	  RESERVED5[2];	// 0x68 - 0x6C
	volatile uint32_t BDCR;			// RCC Backup domain control register
	volatile uint32_t CSR;			// RCC clock control & status register
	uint32_t 	  	 RESERVED6[2];	// 0x78 - 0x7C
	volatile uint32_t SSCGR;		// RCC spread spectrum clock generation register
	volatile uint32_t PLLI2SCFGR;	// RCC PLLI2S configuration register
	volatile uint32_t PLLSAICFGR;	// RCC PLL configuration register
	volatile uint32_t DCKCFGR;		// RCC Dedicated Clock Configuration Register
	volatile uint32_t CKGATENR;		// RCC clocks gated enable register
	volatile uint32_t DCKCFGR2;		// RCC dedicated clocks configuration register 2
} RCC_RegDef_t;

// === EXTI Peripheral Register ===
//
typedef struct EXTI_RegDef
{
	volatile uint32_t IMR;			// EXTI interrupt mask register
	volatile uint32_t EMR;			// EXTI event mask register
	volatile uint32_t RTSR;			// EXTI rising trigger selection register
	volatile uint32_t FTSR;			// EXTI falling trigger selection register
	volatile uint32_t SWIER;		// EXTI software interrupt event register
	volatile uint32_t PR;			// EXTI pending register
} EXTI_RegDef_t;

// === SysConfig Register ===
//
typedef struct SYSCFG_RegDef
{
	volatile uint32_t MEMRMP;		// SYSCFG memory remap register
	volatile uint32_t PMC;			// SYSCFG peripheral mode configuration register
	volatile uint32_t EXTICR[4];	// SYSCFG external interrupt configuration registers
	uint32_t 		  RESERVED1[2];	// RESERVED
	volatile uint32_t CMPCR;		// SYSCFG Compensation cell control register
	uint32_t 		  RESERVED2[2];	// RESERVED
	volatile uint32_t CFGR;			// SYSCFG configuration register
} SYSCFG_RegDef_t;


// =========================
// | Peripheral Definition |
// =========================
//
// === GPIO Port Definition ===
//
#define GPIOA					((GPIO_RegDef_t *) GPIOA_BASE)
#define GPIOB					((GPIO_RegDef_t *) GPIOB_BASE)
#define GPIOC					((GPIO_RegDef_t *) GPIOC_BASE)
#define GPIOD					((GPIO_RegDef_t *) GPIOD_BASE)
#define GPIOE					((GPIO_RegDef_t *) GPIOE_BASE)
#define GPIOF					((GPIO_RegDef_t *) GPIOF_BASE)
#define GPIOG					((GPIO_RegDef_t *) GPIOG_BASE)
#define GPIOH					((GPIO_RegDef_t *) GPIOH_BASE)

// === SPI Interface Definition ===
//
#define SPI1					((SPI_RegDef_t *) SPI1_BASE)
#define SPI2					((SPI_RegDef_t *) SPI2_BASE)
#define SPI3					((SPI_RegDef_t *) SPI3_BASE)
#define SPI4					((SPI_RegDef_t *) SPI4_BASE)

// === SPI Register Definition ===
//
#define SPI_CR1REG_CPHA			0		// Clock phase
#define SPI_CR1REG_CPOL			1		// Clock polarity
#define SPI_CR1REG_MSTR			2		// Master selection
#define SPI_CR1REG_BR			3		// 5:3 Baud rate Control
#define SPI_CR1REG_SPE			6		// SPI enable
#define SPI_CR1REG_SSI			8		// Internal slave select
#define SPI_CR1REG_SSM			9		// Software slave management
#define SPI_CR1REG_RXONLY		10		// Receive only mode enable
#define SPI_CR1REG_DFF			11		// Data frame format
#define SPI_CR1REG_BIDIMODE		15		// Bidirectional data mode enable
#define SPI_SR_RXNE				0		// Receive buffer not empty flag
#define SPI_SR_TXE				1		// Transmit buffer empty flag
#define SPI_SR_BSY				7		// Busy flag

// === SPI Generic Definition ===
//
#define SPI_FLAG_RXNE			(1 << SPI_SR_RXNE)
#define SPI_FLAG_TXE			(1 << SPI_SR_TXE)
#define SPI_FLAG_BUSY			(1 << SPI_SR_BSY)

// === RCC Register Definition ===
//
#define RCC						((RCC_RegDef_t *) RCC_BASE)

// === EXTI Register Definition ===
//
#define EXTI					((EXTI_RegDef_t *) EXTI_BASE)

// === SYSCFG Register Definition ===
//
#define SYSCFG					((SYSCFG_RegDef_t *) SYSCFG_BASE)


// ======================
// | Clock Enable Macro |
// ======================
//
//=== GPIOx Clock Enable Macro ===
//
#define GPIOA_PCLK_EN()			(RCC->AHB1ENR |= (1 << 0))
#define GPIOB_PCLK_EN()			(RCC->AHB1ENR |= (1 << 1))
#define GPIOC_PCLK_EN()			(RCC->AHB1ENR |= (1 << 2))
#define GPIOD_PCLK_EN()			(RCC->AHB1ENR |= (1 << 3))
#define GPIOE_PCLK_EN()			(RCC->AHB1ENR |= (1 << 4))
#define GPIOF_PCLK_EN()			(RCC->AHB1ENR |= (1 << 5))
#define GPIOG_PCLK_EN()			(RCC->AHB1ENR |= (1 << 6))
#define GPIOH_PCLK_EN()			(RCC->AHB1ENR |= (1 << 7))

//=== SPIx Clock Enable Macro ===
//
#define SPI1_PCLK_EN()			(RCC->APB2ENR |= (1 << 12))
#define SPI2_PCLK_EN()			(RCC->APB1ENR |= (1 << 14))
#define SPI3_PCLK_EN()			(RCC->APB1ENR |= (1 << 15))
#define SPI4_PCLK_EN()			(RCC->APB2ENR |= (1 << 13))

//=== SYSCFG Clock Enable Macro ===
//
#define SYSCFG_PCLK_EN()		(RCC->APB2ENR |= (1 << 14))

//=== I2Cx Clock Enable Macro ===
//
#define I2C1_PCLK_EN()			(RCC->APB1ENR |= (1 << 21))


// =======================
// | Clock Disable Macro |
// =======================
//
//=== GPIOx Clock Disable Macro ===
//
#define GPIOA_PCLK_DI()			(RCC->AHB1ENR &= ~(1 << 0))
#define GPIOB_PCLK_DI()			(RCC->AHB1ENR &= ~(1 << 1))
#define GPIOC_PCLK_DI()			(RCC->AHB1ENR &= ~(1 << 2))
#define GPIOD_PCLK_DI()			(RCC->AHB1ENR &= ~(1 << 3))
#define GPIOE_PCLK_DI()			(RCC->AHB1ENR &= ~(1 << 4))
#define GPIOF_PCLK_DI()			(RCC->AHB1ENR &= ~(1 << 5))
#define GPIOG_PCLK_DI()			(RCC->AHB1ENR &= ~(1 << 6))
#define GPIOH_PCLK_DI()			(RCC->AHB1ENR &= ~(1 << 7))

//=== SPIx Clock Disable Macro ===
//
#define SPI1_PCLK_DI()			(RCC->APB2ENR &= ~(1 << 12))
#define SPI2_PCLK_DI()			(RCC->APB1ENR &= ~(1 << 14))
#define SPI3_PCLK_DI()			(RCC->APB1ENR &= ~(1 << 15))
#define SPI4_PCLK_DI()			(RCC->APB2ENR &= ~(1 << 13))

//=== I2Cx Clock Disable Macro ===
//
#define I2C1_PCLK_DI()			(RCC->APB1ENR &= ~(1 << 21))

//=== SYSCFG Clock Disable Macro ===
//
#define SYSCFG_PCLK_DI()		(RCC->APB2ENR &= ~(1 << 14))


// ====================
// | Peripheral Reset |
// ====================
//
//=== GPIO Peripheral Reset ===
//
#define GPIOA_REG_RESET() 		do { RCC->AHB1RSTR |= (1 << 0); RCC->AHB1RSTR &= ~(1 << 0); } while(0)
#define GPIOB_REG_RESET() 		do { RCC->AHB1RSTR |= (1 << 1); RCC->AHB1RSTR &= ~(1 << 1); } while(0)
#define GPIOC_REG_RESET() 		do { RCC->AHB1RSTR |= (1 << 2); RCC->AHB1RSTR &= ~(1 << 2); } while(0)
#define GPIOD_REG_RESET() 		do { RCC->AHB1RSTR |= (1 << 3); RCC->AHB1RSTR &= ~(1 << 3); } while(0)
#define GPIOE_REG_RESET() 		do { RCC->AHB1RSTR |= (1 << 4); RCC->AHB1RSTR &= ~(1 << 4); } while(0)
#define GPIOF_REG_RESET() 		do { RCC->AHB1RSTR |= (1 << 5); RCC->AHB1RSTR &= ~(1 << 5); } while(0)
#define GPIOG_REG_RESET() 		do { RCC->AHB1RSTR |= (1 << 6); RCC->AHB1RSTR &= ~(1 << 6); } while(0)
#define GPIOH_REG_RESET() 		do { RCC->AHB1RSTR |= (1 << 7); RCC->AHB1RSTR &= ~(1 << 7); } while(0)

//=== SPI Peripheral Reset ===
//
#define SPI1_REG_RESET()		do { RCC->APB2RSTR |= (1 << 12); RCC->AHB2RSTR &= ~(1 << 12); } while(0)
#define SPI2_REG_RESET()		do { RCC->APB1RSTR |= (1 << 14); RCC->AHB1RSTR &= ~(1 << 14); } while(0)
#define SPI3_REG_RESET()		do { RCC->APB1RSTR |= (1 << 15); RCC->AHB1RSTR &= ~(1 << 15); } while(0)
#define SPI4_REG_RESET()		do { RCC->APB2RSTR |= (1 << 13); RCC->AHB2RSTR &= ~(1 << 12); } while(0)

// ==========================
// | Interrupt Vector Table |
// ==========================
//
// === EXTI IRQ Numbers ===
//
#define IRQ_NO_EXTI0			6
#define IRQ_NO_EXTI1			7
#define IRQ_NO_EXTI2			8
#define IRQ_NO_EXTI3			9
#define IRQ_NO_EXTI4			10
#define IRQ_NO_EXTI9_5			23
#define IRQ_NO_EXTI15_10		40

// === EXTI IRQ Priorities ===
//
#define NVIC_IRQ_PRI0			0
#define NVIC_IRQ_PRI1			1
#define NVIC_IRQ_PRI2			2
#define NVIC_IRQ_PRI3			3
#define NVIC_IRQ_PRI4			4
#define NVIC_IRQ_PRI5			5
#define NVIC_IRQ_PRI6			6
#define NVIC_IRQ_PRI7			7
#define NVIC_IRQ_PRI8			8
#define NVIC_IRQ_PRI9			9
#define NVIC_IRQ_PRI10			10
#define NVIC_IRQ_PRI11			11
#define NVIC_IRQ_PRI12			12
#define NVIC_IRQ_PRI13			13
#define NVIC_IRQ_PRI14			14
#define NVIC_IRQ_PRI15			15

// === EXTI IRQ Special Config ===
//
#define NO_IPR_BITS				4	// CPU specific, lower nibbles are might not be implemented in the IPR


// ======================
// | Generic Definition |
// ======================
//
#define ENABLE			1
#define DISABLE			0
#define SET				ENABLE
#define RESET			DISABLE
#define FLAG_SET		SET
#define FLAG_RESET		RESET

// ========================
// | Public API Functions |
// ========================
//
void IRQInterruptConfig (uint8_t IRQNumber,  uint8_t enable);
void IRQPriorityConfig (uint8_t IRQNumber, uint8_t IRQPriority);


#endif /* MCU_STM32F446XX_H_ */

/* EOF */
