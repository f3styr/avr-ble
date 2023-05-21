// https://ww1.microchip.com/downloads/aemDocuments/documents/OTH/ProductDocuments/DataSheets/20005192B.pdf


#ifndef mcp9844_H
#define	mcp9844_H

#include <stdint.h>


#define MCP9844_I2C_ADDR  (0x18)

//0000 = Capability register
#define MCP9844_CAPACITY_REG  (0x00)

//0001 = Configuration register (CONFIG)
#define MCP9844_CONFIG_REG  (0x01)

//0010 = Event Temperature Upper-Boundary Trip register (TUPPER)
#define MCP9844_TUPPER_REG  (0x02)

//0011 = Event Temperature Lower-Boundary Trip register (TLOWER)
#define MCP9844_TLOWER_REG  (0x03)

//0100 = Critical Temperature Trip register (TCRIT)
#define MCP9844_TCRIT_REG  (0x04)

//0101 = Temperature register (TA)
#define MCP9844_TA_REG  (0x05)

//0110 = Manufacturer ID register
#define MCP9844_MID_REG  (0x06)

//0111 = Device ID/Revision register
#define MCP9844_DID_REG  (0x07)

//1000 = Reserved
#define MCP9844_RESERVED_REG  (0x08)

//1001 = Resolution register
#define MCP9844_RESOLUTION_REG  (0x08)

int16_t mcp9844_get_temperature();


#endif