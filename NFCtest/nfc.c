#include "nfc.h"
#include "nfc_reg.h"

/**
 * @brief  复位 NAND Flash
 */
void NFC_Reset(void) {
    NFC_SetOpcode(NFC_CMD_RESET);   // Reset command
    NFC_WaitIdle();
}

/**
 * @brief  设置 Timing 模式
 */
void NFC_SetTimingMode(void) {
    NFC_SetOpcode(NFC_CMD_SET_FEATURE1);   // Set Features - Timing
    NFC_WaitIdle();
}

/**
 * @brief  设置配置
 */
void NFC_SetConfiguration(void) {
    NFC_SetOpcode(NFC_CMD_SET_FEATURE2);   // Set Features - Configuration
    NFC_WaitIdle();
}

/**
 * @brief  读取 Feature
 */
void NFC_GetFeatures(void) {
    NFC_SetOpcode(NFC_CMD_GET_FEATURE);   // Get Features
    NFC_WaitIdle();
}

/**
 * @brief  读取 Parameter Page
 */
void NFC_ReadParameter(void) {
    NFC_SetOpcode(NFC_CMD_READ_PARAM1);   // Read Parameter Page
    NFC_WaitIdle();
}

/**
 * @brief  擦除块
 * @param  lba  逻辑块地址
 */
void NFC_Erase(u64 lba) {
    NFC_SetLBA(lba);
    NFC_SetOpcode(NFC_CMD_BLOCK_ERASE);   // Block Erase
    NFC_WaitIdle();
}

/**
 * @brief  页编程
 * @param  lba  逻辑块地址
 * @param  len  数据长度（单位：字节）
 */
void NFC_Program(u64 lba, u32 len) {
    NFC_WaitWrfifoNotFull();////有一些问题，当正在进行的读写操作无法检测FIFO的空满
    NFC_SetLBA(lba);
    NFC_SetLen(len);
    NFC_SetOpcode(NFC_CMD_PAGE_PROG);   // Program Page
    NFC_WaitIdle();
}

/**
 * @brief  页读取
 * @param  lba  逻辑块地址
 * @param  len  数据长度（单位：字节）
 */
void NFC_Read(u64 lba, u32 len) {
    NFC_WaitRdfifoNotEmpty();////有一些问题，当正在进行的读写操作无法检测FIFO的空满
    NFC_SetLBA(lba);
    NFC_SetLen(len);
    NFC_SetOpcode(NFC_CMD_PAGE_READ);   // Read Page
    NFC_WaitIdle();
}
