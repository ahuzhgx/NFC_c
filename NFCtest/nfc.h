#ifndef NFC_H
#define NFC_H

#include "xil_types.h"   // 提供 u8/u16/u32/u64 类型

/**
 * @file    nfc.h
 * @brief   NFC 控制器驱动头文件
 * 
 * 提供对 NAND Flash 的基本操作函数封装，包括：
 * - Reset
 * - Feature 设置/获取
 * - 参数页读取
 * - 擦除 / 编程 / 读取
 * 
 * @author  SCMI
 * @date    2025-09-26
 * @version 1.1
 */

/* ------------------- 基本命令 ------------------- */

/**
 * @brief NAND Flash 复位 (FFh)
 */
void NFC_Reset(void);

/**
 * @brief 设置 Timing Mode (01EFh)
 */
void NFC_SetTimingMode(void);

/**
 * @brief 设置 Configuration (02EFh)
 */
void NFC_SetConfiguration(void);

/**
 * @brief 获取 Features (01EEh)
 */
void NFC_GetFeatures(void);

/**
 * @brief 读取参数页 (00ECh)
 */
void NFC_ReadParameter(void);

/* ------------------- 可选扩展命令 ------------------- */
// TODO: 根据需要启用
// void NFC_ReadONFISignature(void);  /**< 2090h: ONFI Signature ID Read */
// void NFC_ReadManufacturerID(void); /**< 0090h: Manufacturer ID Read    */
// void NFC_ReadUniqueID(void);       /**< 00EDh: Unique ID Read          */

/* ------------------- 核心操作命令 ------------------- */

/**
 * @brief 擦除一个 Block
 * 
 * @param lba  要擦除的逻辑块地址 (Block 地址)
 */
void NFC_Erase(u64 lba, u32 len);

/**
 * @brief 编程一个 Page
 * 
 * @param lba   Page 的逻辑块地址
 * @param len   要写入的字节长度
 */
void NFC_Program(u64 lba, u32 len);

/**
 * @brief 读取一个 Page
 * 
 * @param lba   Page 的逻辑块地址
 * @param len   要读取的字节长度
 */
void NFC_Read(u64 lba, u32 len);

#endif // NFC_H
