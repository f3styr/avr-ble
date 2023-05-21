#include "mcp9844.h"
#include <i2c_simple_master.h>


// 2 byte registers
int16_t  mcp9844_get_temperature() 
{
		
		int16_t register_value = i2c_read2ByteRegister(MCP9844_I2C_ADDR, MCP9844_TA_REG);
		
		int16_t upper_byte = (register_value >> 8) & 0x001F;
		int16_t lower_byte = (register_value) & 0x00FF;
		
		int16_t temperature;
		
		if ((upper_byte & 0x10) == 0x10){ //TA  0°C
			upper_byte = upper_byte & 0x0F; //Clear SIGN
			temperature = (upper_byte * 16 + lower_byte / 16) - 256;
		}
		else 
			temperature = (upper_byte * 16 + lower_byte / 16);
		
		
		return temperature;
				

}

