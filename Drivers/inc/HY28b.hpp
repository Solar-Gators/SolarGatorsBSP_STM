/*
 * LCD.h
 *
 *  Created on: Jan 19, 2021
 *      Author: John Carr
 */

#ifndef SOLARGATORSBSP_DRIVERS_INC_HY28b_HPP_
#define SOLARGATORSBSP_DRIVERS_INC_HY28b_HPP_

#include <stdbool.h>
#include <stdint.h>
#include "main.h"
/************************************ Defines *******************************************/

/* CS LCD*/
  #define SPI_CS_LOW HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET)
  #define SPI_CS_HIGH HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET)

/* CS Touchpanel */
#define SPI_CS_TP_LOW HAL_GPIO_WritePin(TP_CS_GPIO_Port, TP_CS_Pin, GPIO_PIN_RESET)
#define SPI_CS_TP_HIGH HAL_GPIO_WritePin(TP_CS_GPIO_Port, TP_CS_Pin, GPIO_PIN_SET)

/************************************ Defines *******************************************/

/********************************** Structures ******************************************/
typedef struct {
    uint16_t x;
    uint16_t y;
}point_t, dimension_t;
/********************************** Structures ******************************************/

/************************************ Public Functions  *******************************************/
class HY28b {

public:
	SPI_HandleTypeDef* spi;
	/*******************************************************************************
	 * Function Name  : HY28b
	 * Description    : Configures LCD Control lines, sets whole screen black
	 * Input          : bool usingTP: determines whether or not to enable TP interrupt
	 * Output         : None
	 * Return         : None
	 * Attention      : None
	 *******************************************************************************/
	HY28b(SPI_HandleTypeDef* hspi, bool usingTP);

	virtual ~HY28b();
	/*******************************************************************************
	 * Function Name  : DrawRectangle
	 * Description    : Draw a rectangle as the specified color
	 * Input          : xStart, xEnd, yStart, yEnd, Color
	 * Output         : None
	 * Return         : None
	 * Attention      : None
	 *******************************************************************************/
	void DrawRectangle(int16_t xStart, int16_t xEnd, int16_t yStart, int16_t yEnd, uint16_t Color);

	/******************************************************************************
	* Function Name  : PutChar
	* Description    : Lcd screen displays a character
	* Input          : - Xpos: Horizontal coordinate
	*                  - Ypos: Vertical coordinate
	*                  - ASCI: Displayed character
	*                  - charColor: Character color
	* Output         : None
	* Return         : None
	* Attention      : None
	*******************************************************************************/
	void PutChar( uint16_t Xpos, uint16_t Ypos, uint8_t ASCI, uint16_t charColor);

	/******************************************************************************
	* Function Name  : DrawText
	* Description    : Displays the string
	* Input          : - Xpos: Horizontal coordinate
	*                  - Ypos: Vertical coordinate
	*                  - str: Displayed string
	*                  - charColor: Character color
	* Output         : None
	* Return         : None
	* Attention      : None
	*******************************************************************************/
	void DrawText(uint16_t Xpos, uint16_t Ypos, uint8_t *str,uint16_t Color);

	/*******************************************************************************
	* Function Name  : WriteDataOnly
	* Description    : Data writing to the LCD controller
	* Input          : - data: data to be written
	* Output         : None
	* Return         : None
	* Attention      : None
	*******************************************************************************/
	void WriteDataOnly(uint16_t data);

	/*******************************************************************************
	* Function Name  : Clear
	* Description    : Fill the screen as the specified color
	* Input          : - Color: Screen Color
	* Output         : None
	* Return         : None
	* Attention      : None
	*******************************************************************************/
	void Clear(uint16_t Color);

	/******************************************************************************
	* Function Name  : SetPoint
	* Description    : Drawn at a specified point coordinates
	* Input          : - Xpos: Row Coordinate
	*                  - Ypos: Line Coordinate
	* Output         : None
	* Return         : None
	* Attention      : 18N Bytes Written
	*******************************************************************************/
	void SetPoint(uint16_t Xpos, uint16_t Ypos, uint16_t color);

	/*******************************************************************************
	* Function Name  : WriteData
	* Description    : LCD write register data
	* Input          : - data: register data
	* Output         : None
	* Return         : None
	* Attention      : None
	*******************************************************************************/
	void WriteData(uint16_t data);

	/*******************************************************************************
	* Function Name  : ReadReg
	* Description    : Reads the selected LCD Register.
	* Input          : None
	* Output         : None
	* Return         : LCD Register Value.
	* Attention      : None
	*******************************************************************************/
	uint16_t ReadReg(uint16_t LCD_reg);

	/*******************************************************************************
	* Function Name  : WriteIndex
	* Description    : LCD write register address
	* Input          : - index: register address
	* Output         : None
	* Return         : None
	* Attention      : None
	*******************************************************************************/
	void WriteIndex(uint16_t index);

	/*******************************************************************************
	 * Function Name  : SPISendRecvTPByte
	 * Description    : Send one byte then receive one byte of response from Touchpanel
	 * Input          : uint8_t: byte
	 * Output         : None
	 * Return         : None
	 * Attention      : None
	 *******************************************************************************/
	uint8_t SPISendRecvTPByte (uint8_t byte);

	/*******************************************************************************
	* Function Name  : SPISendRecvByte
	* Description    : Send one byte then recv one byte of response
	* Input          : uint8_t: byte
	* Output         : None
	* Return         : Recieved value
	* Attention      : None
	*******************************************************************************/
	uint8_t SPISendRecvByte(uint8_t byte);

	/*******************************************************************************
	* Function Name  : WriteDataStart
	* Description    : Start of data writing to the LCD controller
	* Input          : None
	* Output         : None
	* Return         : None
	* Attention      : None
	*******************************************************************************/
	void WriteDataStart(void);

	/*******************************************************************************
	* Function Name  : ReadData
	* Description    : LCD read data
	* Input          : None
	* Output         : None
	* Return         : return data
	* Attention  : None
	*******************************************************************************/
	uint16_t ReadData();

	/*******************************************************************************
	* Function Name  : WriteReg
	* Description    : Writes to the selected LCD register.
	* Input          : - LCD_Reg: address of the selected register.
	*                  - LCD_RegValue: value to write to the selected register.
	* Output         : None
	* Return         : None
	* Attention      : None
	*******************************************************************************/
	void WriteReg(uint16_t LCD_Reg, uint16_t LCD_RegValue);

	/*******************************************************************************
	* Function Name  : LCD_SetCursor
	* Description    : Sets the cursor position.
	* Input          : - Xpos: specifies the X position.
	*                  - Ypos: specifies the Y position.
	* Output         : None
	* Return         : None
	* Attention      : None
	*******************************************************************************/
	void SetCursor(uint16_t Xpos, uint16_t Ypos );

	/*******************************************************************************
	 * Function Name  : TP_ReadXY
	 * Description    : Obtain X and Y touch coordinates
	 * Input          : None
	 * Output         : None
	 * Return         : Point structure
	 * Attention      : None
	 *******************************************************************************/
	point_t TP_ReadXY();

	/*******************************************************************************
	 * Function Name  : TP_ReadX
	 * Description    : Obtain X touch coordinate
	 * Input          : None
	 * Output         : None
	 * Return         : X Coordinate
	 * Attention      : None
	 *******************************************************************************/
	uint16_t TP_ReadX();

	/*******************************************************************************
	 * Function Name  : TP_ReadY
	 * Description    : Obtain Y touch coordinate
	 * Input          : None
	 * Output         : None
	 * Return         : Y Coordinate
	 * Attention      : None
	 *******************************************************************************/
	uint16_t TP_ReadY();

  /*******************************************************************************
   * Function Name  : TP_ReadY
   * Description    : Obtain Y touch coordinate
   * Input          : None
   * Output         : None
   * Return         : Y Coordinate
   * Attention      : None
   *******************************************************************************/
	void SetSize(uint8_t size);

	/* Screen size */
	static constexpr uint32_t MAX_SCREEN_X = 320;
	static constexpr uint32_t MAX_SCREEN_Y = 240;
	static constexpr uint32_t MIN_SCREEN_X = 0;
	static constexpr uint32_t MIN_SCREEN_Y = 0;
	static constexpr uint32_t SCREEN_SIZE  = 76800;

	/* Register details */
	static constexpr uint32_t SPI_START = (0x70);     /* Start byte for SPI transfer        */
	static constexpr uint32_t SPI_RD    = (0x01);     /* WR bit 1 within start              */
	static constexpr uint32_t SPI_WR    = (0x00);     /* WR bit 0 within start              */
	static constexpr uint32_t SPI_DATA  = (0x02);     /* RS bit 1 within start byte         */
	static constexpr uint32_t SPI_INDEX = (0x00);     /* RS bit 0 within start byte         */

	/* XPT2046 registers definition for X and Y coordinate retrieval */
	static constexpr uint32_t CHX = 0x90;
	static constexpr uint32_t CHY = 0xD0;

	/* LCD colors */
	static constexpr uint32_t WHITE   = 0xFFFF;
	static constexpr uint32_t BLACK   = 0x0000;
	static constexpr uint32_t BLUE    = 0x0197;
	static constexpr uint32_t RED     = 0xF800;
	static constexpr uint32_t MAGENTA = 0xF81F;
	static constexpr uint32_t GREEN   = 0x07E0;
	static constexpr uint32_t CYAN    = 0x7FFF;
	static constexpr uint32_t YELLOW  = 0xFFE0;
	static constexpr uint32_t GRAY    = 0x2104;
	static constexpr uint32_t PURPLE  = 0xF11F;
	static constexpr uint32_t ORANGE  = 0xFD20;
	static constexpr uint32_t PINK    = 0xfdba;
	static constexpr uint32_t OLIVE   = 0xdfe4;

	/* ILI 9325 registers definition */
	static constexpr uint32_t READ_ID_CODE                    = 0x00;
	static constexpr uint32_t DRIVER_OUTPUT_CONTROL           = 0x01;
	static constexpr uint32_t DRIVING_WAVE_CONTROL            = 0x02;
	static constexpr uint32_t ENTRY_MODE                      = 0x03;
	static constexpr uint32_t RESIZING_CONTROL                = 0x04;
	static constexpr uint32_t DISPLAY_CONTROL_1               = 0x07;
	static constexpr uint32_t DISPLAY_CONTROL_2               = 0x08;
	static constexpr uint32_t DISPLAY_CONTROL_3               = 0x09;
	static constexpr uint32_t DISPLAY_CONTROL_4               = 0x0A;
	static constexpr uint32_t RGB_DISPLAY_INTERFACE_CONTROL_1 = 0x0C;
	static constexpr uint32_t FRAME_MARKER_POSITION           = 0x0D;
	static constexpr uint32_t RGB_DISPLAY_INTERFACE_CONTROL_2 = 0x0F;
	static constexpr uint32_t POWER_CONTROL_1                 = 0x10;
	static constexpr uint32_t POWER_CONTROL_2                 = 0x11;
	static constexpr uint32_t POWER_CONTROL_3                 = 0x12;
	static constexpr uint32_t POWER_CONTROL_4                 = 0x13;
	static constexpr uint32_t GRAM_HORIZONTAL_ADDRESS_SET     = 0x20;
	static constexpr uint32_t GRAM_VERTICAL_ADDRESS_SET       = 0x21;
	static constexpr uint32_t DATA_IN_GRAM                    = 0x22;
	static constexpr uint32_t POWER_CONTROL_7                 = 0x29;
	static constexpr uint32_t FRAME_RATE_AND_COLOR_CONTROL    = 0x2B;

	static constexpr uint32_t GAMMA_CONTROL_1                 = 0x30;
	static constexpr uint32_t GAMMA_CONTROL_2                 = 0x31;
	static constexpr uint32_t GAMMA_CONTROL_3                 = 0x32;
	static constexpr uint32_t GAMMA_CONTROL_4                 = 0x35;
	static constexpr uint32_t GAMMA_CONTROL_5                 = 0x36;
	static constexpr uint32_t GAMMA_CONTROL_6                 = 0x37;
	static constexpr uint32_t GAMMA_CONTROL_7                 = 0x38;
	static constexpr uint32_t GAMMA_CONTROL_8                 = 0x39;
	static constexpr uint32_t GAMMA_CONTROL_9                 = 0x3C;
	static constexpr uint32_t GAMMA_CONTROL_10                = 0x3D;

	static constexpr uint32_t HOR_ADDR_START_POS              = 0x50;
	static constexpr uint32_t HOR_ADDR_END_POS                = 0x51;
	static constexpr uint32_t VERT_ADDR_START_POS             = 0x52;
	static constexpr uint32_t VERT_ADDR_END_POS               = 0x53;
	static constexpr uint32_t GATE_SCAN_CONTROL_0X60          = 0x60;
	static constexpr uint32_t GATE_SCAN_CONTROL_0X61          = 0x61;
	static constexpr uint32_t GATE_SCAN_CONTROL_0X6A          = 0x6A;
	static constexpr uint32_t PART_IMAGE_1_DISPLAY_POS        = 0x80;
	static constexpr uint32_t PART_IMG_1_START_END_ADDR_0x81  = 0x81;
	static constexpr uint32_t PART_IMG_1_START_END_ADDR_0x82  = 0x81;
	static constexpr uint32_t PART_IMAGE_2_DISPLAY_POS        = 0x83;
	static constexpr uint32_t PART_IMG_2_START_END_ADDR_0x84  = 0x84;
	static constexpr uint32_t PART_IMG_2_START_END_ADDR_0x85  = 0x85;
	static constexpr uint32_t PANEL_ITERFACE_CONTROL_1        = 0x90;
	static constexpr uint32_t PANEL_ITERFACE_CONTROL_2        = 0x92;
	static constexpr uint32_t PANEL_ITERFACE_CONTROL_4        = 0x95;

	static constexpr uint32_t GRAM                            = 0x22;
	static constexpr uint32_t HORIZONTAL_GRAM_SET             = 0x20;
	static constexpr uint32_t VERTICAL_GRAM_SET               = 0x21;
private:
	inline uint16_t TP_ReadReg(uint8_t control_reg);
	uint8_t size_;
};
/************************************ Public Functions  *******************************************/




#endif /* SOLARGATORSBSP_DRIVERS_INC_HY28b_HPP_ */
