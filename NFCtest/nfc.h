#ifndef NFC_H
#define NFC_H


/**
 * @file    nfc.h
 * @brief   NFC 控制器驱动头文件
 *          提供对 NFC 模块寄存器的操作接口，包括：
 *          - 设置操作码（opcode）
 *          - 设置逻辑块地址（LBA）
 *          - 设置数据长度
 *          - 选择通道/Plane
 *          - 查询状态寄存器并等待操作完成
 * 
 * @author  SCMI
 * @date    2025-09-26
 * @version 1.0
 * 
 * @note
 * 1. 本驱动适用于 MicroBlaze + AXI4-Lite 架构下的 NFC 模块。
 * 2. 写入操作码后，RTL 会根据 opcode 启动对应的 NAND 操作。
 * 3. LBA 为 48bit，拆分为低 32bit 和高 16bit 寄存器。
 * 4. 状态寄存器包含 busy、FIFO 空满、长度错误等信息。
 */

/* ------------------- NFC 基地址 ------------------- */









#endif // NFC_H