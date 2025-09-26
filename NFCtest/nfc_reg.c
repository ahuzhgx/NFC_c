#include "nfc.h"

/**
 ******************************************************************************
 * @file    nfc.c
 * @brief   NFC 控制器驱动函数实现
 *          通过 AXI4-Lite 接口操作 NFC 模块寄存器，支持：
 *          - 设置操作码（opcode）
 *          - 设置逻辑块地址（LBA）
 *          - 设置操作长度
 *          - 通道/Plane 选择
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
 *
 * @usage 示例:
 *      NFC_SetLBA(0x123456789ULL);
 *      NFC_SetLen(2048);
 *      NFC_SetOpcode(NFC_CMD_PAGE_READ);
 *      NFC_WaitIdle();
 *
 ******************************************************************************
 */



/**
 * @brief 设置 NFC 操作码寄存器
 * @param opcode 16位操作码，例如 0x00FF、0x1080 等
 * @note 写入操作码后，RTL 会根据 opcode 启动对应的 NAND 操作
 */
void NFC_SetOpcode(u32 opcode) {
    Xil_Out32(NFC_BASEADDR + NFC_OPCODE_REG, opcode & 0xFFFF);
}

/**
 * @brief 设置 NFC 操作的长度寄存器
 * @param len 要操作的数据长度（单位字节）
 * @note 只使用低 24 位，因为 RTL 的长度寄存器是 24bit
 */
void NFC_SetLen(u32 len) {
    Xil_Out32(NFC_BASEADDR + NFC_LEN_REG, len & 0xFFFFFF);
}

/**
 * @brief 设置 NFC 的逻辑块地址（LBA）
 * @param lba 48位逻辑块地址
 * @note LBA 拆成低 32 位和高 16 位，分别写入两个寄存器
 */
void NFC_SetLBA(u64 lba) {
    u32 lba_low  = (u32)(lba & 0xFFFFFFFF);     // 低 32 位
    u32 lba_high = (u32)((lba >> 32) & 0xFFFF); // 高 16 位
    Xil_Out32(NFC_BASEADDR + NFC_LBALOW_REG, lba_low);
    Xil_Out32(NFC_BASEADDR + NFC_LBAHIGH_REG, lba_high);
}

/**
 * @brief 设置 NFC 通道/Plane 选择寄存器
 * @param sel 选择值，通常为 0 或 1
 * @note RTL 的 slv_reg[4][1:0] 控制两条通道
 */
void NFC_SetSel(u32 sel) {
    Xil_Out32(NFC_BASEADDR + NFC_SEL_REG, sel);
}

/**
 * @brief 读取 NFC 状态寄存器
 * @return 32位状态寄存器值
 * @note 可用来判断 busy、fifo 空满、len error 等
 */
u32 NFC_GetStatus(void) {
    return Xil_In32(NFC_BASEADDR + NFC_STATUS_REG);
}

/**
 * @brief 等待 NFC 空闲
 * @note 检查 status 寄存器 busy 位，若 busy = 1，则循环等待
 *       防止 CPU 忙等，可加 usleep 轻松轮询
 */
void NFC_WaitIdle(void) {
    while (NFC_GetStatus() & NFC_STATUS_BUSY) {
        usleep(10); // 延迟 10 微秒，避免忙等占满 CPU
    }
}
