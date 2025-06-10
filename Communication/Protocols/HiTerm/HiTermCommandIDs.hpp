#pragma once
#ifndef Communication__HiTerm_CommandIDs__hpp
#define Communication__HiTerm_CommandIDs__hpp

// #Kernel
#include "Types\BaseTypes.hpp"


namespace Communication::HiTerm::CommandID {

constexpr UInt8 BOOT_SEND_API      = 0x02; /*!< Send FLASH API @ boot time*/
constexpr UInt8 READ               = 0x10; /*!< Read single/multiple variables */
constexpr UInt8 READ_NEW           = 0x11; 
constexpr UInt8 WRITE_NEW          = 0x12; 
constexpr UInt8 BOOT_READ          = 0x16; /*!< Read single/multiple variables @ boot time*/
constexpr UInt8 BOOT_WRITE         = 0x20; /*!< Write single/multiple variables @ boot time*/
constexpr UInt8 WRITE              = 0x23; /*!< Write single/multiple variables */
constexpr UInt8 READ_BBX           = 0x24; /*!< read black box content */
constexpr UInt8 READ_BBX_NEW       = 0x25; 
constexpr UInt8 READ_MON_TAB0      = 0x40; /*!< Read the 0. tab descriptor*/
constexpr UInt8 READ_MON_TAB1      = 0x41; /*!< Read the 1. tab descriptor*/
constexpr UInt8 READ_MON_TAB2      = 0x42; /*!< Read the 2. tab descriptor*/
constexpr UInt8 READ_MON_TAB3      = 0x43; /*!< Read the 3. tab descriptor*/
constexpr UInt8 READ_MON_TAB4      = 0x44; /*!< Read the 4. tab descriptor*/
constexpr UInt8 READ_MON_TAB5      = 0x45; /*!< Read the 5. tab descriptor*/
constexpr UInt8 READ_MON_TAB6      = 0x46; /*!< Read the 6. tab descriptor*/
constexpr UInt8 READ_MON_TAB7      = 0x47; /*!< Read the 7. tab descriptor*/
constexpr UInt8 READ_MON_TAB8      = 0x48; /*!< Read the 8. tab descriptor*/
constexpr UInt8 READ_MON_TAB9      = 0x49; /*!< Read the 9. tab descriptor*/
constexpr UInt8 READ_ERROR_HISTORY = 0x51; /*!< read error history */
constexpr UInt8 BOOT_CLEAR_SECTOR  = 0x53; 
constexpr UInt8 READ_TABNAMES      = 0x55; /*!< Read the name of the tabs in user mode (only for 0th address DSP)*/
constexpr UInt8 CLEAR_EEPROM       = 0x58; 
constexpr UInt8 BOOT_READ_FLASH    = 0x5A; 
constexpr UInt8 BOOT_PROGRAM_FLASH = 0x5F; 
constexpr UInt8 MODBUS_READ        = 0x60; 
constexpr UInt8 MODBUS_WRITE       = 0x61; 
constexpr UInt8 READ_SPI_RAM       = 0x75; /*!< read spi ram (bbx, error history */
constexpr UInt8 READ_UNITS         = 0x79; /*!< read unit table */
constexpr UInt8 REBOOT             = 0x80; /*!< Reboot DSP */
constexpr UInt8 PING               = 0x99; /*!< ping DSP */
constexpr UInt8 READ_TAB0VALUES    = 0xA0; /*!< read all tabvalues in 0. tab */
constexpr UInt8 READ_TAB1VALUES    = 0xA1; /*!< read all tabvalues in 1. tab */
constexpr UInt8 READ_TAB2VALUES    = 0xA2; /*!< read all tabvalues in 2. tab */
constexpr UInt8 READ_TAB3VALUES    = 0xA3; /*!< read all tabvalues in 3. tab */
constexpr UInt8 READ_TAB4VALUES    = 0xA4; /*!< read all tabvalues in 4. tab */
constexpr UInt8 READ_TAB5VALUES    = 0xA5; /*!< read all tabvalues in 5. tab */
constexpr UInt8 READ_TAB6VALUES    = 0xA6; /*!< read all tabvalues in 6. tab */
constexpr UInt8 READ_TAB7VALUES    = 0xA7; /*!< read all tabvalues in 7. tab */
constexpr UInt8 READ_TAB8VALUES    = 0xA8; /*!< read all tabvalues in 8. tab */
constexpr UInt8 READ_TAB9VALUES    = 0xA9; /*!< read all tabvalues in 9. tab */

}


#endif