#ifndef NFC_H
#define NFC_H

#include "xil_io.h"
#include "sleep.h"

/**
 * @file    nfc.h
 * @brief   NFC ����������ͷ�ļ�
 *          �ṩ�� NFC ģ��Ĵ����Ĳ����ӿڣ�������
 *          - ���ò����루opcode��
 *          - �����߼����ַ��LBA��
 *          - �������ݳ���
 *          - ѡ��ͨ��/Plane
 *          - ��ѯ״̬�Ĵ������ȴ��������
 * 
 * @author  SCMI
 * @date    2025-09-26
 * @version 1.0
 * 
 * @note
 * 1. ������������ MicroBlaze + AXI4-Lite �ܹ��µ� NFC ģ�顣
 * 2. д��������RTL ����� opcode ������Ӧ�� NAND ������
 * 3. LBA Ϊ 48bit�����Ϊ�� 32bit �͸� 16bit �Ĵ�����
 * 4. ״̬�Ĵ������� busy��FIFO ���������ȴ������Ϣ��
 */

/* ------------------- NFC ����ַ ------------------- */
#define NFC_BASEADDR   0x40000000U  /**< NFC ģ�����ַ������ Address Editor ȷ�ϣ� */

/* ------------------- NFC �Ĵ���ƫ�� ------------------- */
#define NFC_OPCODE_REG       0x00  /**< [15:0] ������Ĵ��� */
#define NFC_LEN_REG          0x04  /**< [23:0] ���ݳ��ȼĴ��� */
#define NFC_LBALOW_REG       0x08  /**< [31:0] LBA �� 32 λ */
#define NFC_LBAHIGH_REG      0x0C  /**< [15:0] LBA �� 16 λ */
#define NFC_SEL_REG          0x10  /**< ͨ��/Plane ѡ��Ĵ��� */
#define NFC_STATUS_REG       0x14  /**< ״̬�Ĵ��� */

/* ------------------- �����붨�� ------------------- */
// NAND Flash �����루opcode����д�� NFC_OPCODE_REG
#define NFC_CMD_RESET        0x00FF  /**< FF, Reset */
#define NFC_CMD_SET_FEATURE1 0x01EF  /**< EF, Set Feature 1 */
#define NFC_CMD_SET_FEATURE2 0x02EF  /**< EF, Set Feature 2 */
#define NFC_CMD_GET_FEATURE  0x01EE  /**< EE, Get Feature */
#define NFC_CMD_READ_PARAM1  0x00EC  /**< EC, Read Parameter Page */
#define NFC_CMD_READ_PARAM2  0x2090  /**< 90, Read Parameter Page */
#define NFC_CMD_READ_PARAM3  0x0090  /**< 90, Read Parameter Page */
#define NFC_CMD_READ_UNIQUE  0x00ED  /**< ED, Read Unique ID */
#define NFC_CMD_BLOCK_ERASE  0xD060  /**< 60h + D0h, Block Erase */
#define NFC_CMD_PAGE_PROG    0x1080  /**< 80h + 10h, Page Program */
#define NFC_CMD_PAGE_READ    0x3000  /**< 00h + 30h, Page Read */

/* ------------------- ״̬�Ĵ���λ ------------------- */
#define NFC_STATUS_BUSY      (1 << 31) /**< Busy λ��0 = ���У�1 = æ */
#define NFC_STATUS_LENERR    (1 << 30) /**< ���ȴ����־ */
#define NFC_STATUS_RD_EMPTY  (1 << 5)  /**< �� FIFO �� */
#define NFC_STATUS_RD_FULL   (1 << 4)  /**< �� FIFO �� */
#define NFC_STATUS_WR_EMPTY  (1 << 3)  /**< д FIFO �� */
#define NFC_STATUS_WR_FULL   (1 << 2)  /**< д FIFO �� */

/* ------------------- NFC ���� API ------------------- */
/**
 * @brief ���� NFC ������
 * @param opcode �����루16bit�����ο� NFC_CMD_* �궨��
 */
void NFC_SetOpcode(u32 opcode);

/**
 * @brief ���� NFC ���������ݳ���
 * @param len ���ݳ��ȣ��ֽڣ����� 24 λ��Ч
 */
void NFC_SetLen(u32 len);

/**
 * @brief ���� NFC ���߼����ַ��LBA��
 * @param lba 48bit LBA
 */
void NFC_SetLBA(u64 lba);

/**
 * @brief ���� NFC ͨ��/Plane ѡ��
 * @param sel ѡ��ֵ��ͨ��Ϊ 0 �� 1��
 */
void NFC_SetSel(u32 sel);

/**
 * @brief ��ȡ NFC ״̬�Ĵ���
 * @return 32bit ״̬�Ĵ���ֵ
 */
u32  NFC_GetStatus(void);
//1111

/**
 * @brief �ȴ� NFC ����
 * @note ѭ����� busy λ��ֱ���������
 */
void NFC_WaitIdle(void);

#endif // NFC_H
