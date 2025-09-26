#include "nfc.h"
#include "nfc_reg.h"

/**
 * @brief  复位 NAND Flash
 */
void NFC_Reset(void) {
    NFC_SetOpcode(0x00FF);   // Reset command
    NFC_WaitIdle();
}

/**
 * @brief  设置 Timing 模式
 */
void NFC_SetTimingMode(void) {
    NFC_SetOpcode(0x01EF);   // Set Features - Timing
    NFC_WaitIdle();
}

/**
 * @brief  设置配置
 */
void NFC_SetConfiguration(void) {
    NFC_SetOpcode(0x02EF);   // Set Features - Configuration
    NFC_WaitIdle();
}

/**
 * @brief  读取 Feature
 */
void NFC_GetFeatures(void) {
    NFC_SetOpcode(0x01EE);   // Get Features
    NFC_WaitIdle();
}

/**
 * @brief  读取 Parameter Page
 */
void NFC_ReadParameter(void) {
    NFC_SetOpcode(0x00EC);   // Read Parameter Page
    NFC_WaitIdle();
}

/**
 * @brief  擦除块
 * @param  lba  逻辑块地址
 */
void NFC_Erase(u64 lba) {
    NFC_SetLBA(lba);
    NFC_SetOpcode(0xD060);   // Block Erase
    NFC_WaitIdle();
}

/**
 * @brief  页编程
 * @param  lba  逻辑块地址
 * @param  len  数据长度（单位：字节）
 */
void NFC_Program(u64 lba, u32 len) {
    NFC_SetLBA(lba);
    NFC_SetLen(len);
    NFC_SetOpcode(0x1080);   // Program Page
    NFC_WaitIdle();
}

/**
 * @brief  页读取
 * @param  lba  逻辑块地址
 * @param  len  数据长度（单位：字节）
 */
void NFC_Read(u64 lba, u32 len) {
    NFC_SetLBA(lba);
    NFC_SetLen(len);
    NFC_SetOpcode(0x3000);   // Read Page
    NFC_WaitIdle();
}
