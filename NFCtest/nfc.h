#ifndef NFC_H
#define NFC_H

#include "xil_types.h"   // �ṩ u8/u16/u32/u64 ����

/**
 * @file    nfc.h
 * @brief   NFC ����������ͷ�ļ�
 * 
 * �ṩ�� NAND Flash �Ļ�������������װ��������
 * - Reset
 * - Feature ����/��ȡ
 * - ����ҳ��ȡ
 * - ���� / ��� / ��ȡ
 * 
 * @author  SCMI
 * @date    2025-09-26
 * @version 1.1
 */

/* ------------------- �������� ------------------- */

/**
 * @brief NAND Flash ��λ (FFh)
 */
void NFC_Reset(void);

/**
 * @brief ���� Timing Mode (01EFh)
 */
void NFC_SetTimingMode(void);

/**
 * @brief ���� Configuration (02EFh)
 */
void NFC_SetConfiguration(void);

/**
 * @brief ��ȡ Features (01EEh)
 */
void NFC_GetFeatures(void);

/**
 * @brief ��ȡ����ҳ (00ECh)
 */
void NFC_ReadParameter(void);

/* ------------------- ��ѡ��չ���� ------------------- */
// TODO: ������Ҫ����
// void NFC_ReadONFISignature(void);  /**< 2090h: ONFI Signature ID Read */
// void NFC_ReadManufacturerID(void); /**< 0090h: Manufacturer ID Read    */
// void NFC_ReadUniqueID(void);       /**< 00EDh: Unique ID Read          */

/* ------------------- ���Ĳ������� ------------------- */

/**
 * @brief ����һ�� Block
 * 
 * @param lba  Ҫ�������߼����ַ (Block ��ַ)
 */
void NFC_Erase(u64 lba, u32 len);

/**
 * @brief ���һ�� Page
 * 
 * @param lba   Page ���߼����ַ
 * @param len   Ҫд����ֽڳ���
 */
void NFC_Program(u64 lba, u32 len);

/**
 * @brief ��ȡһ�� Page
 * 
 * @param lba   Page ���߼����ַ
 * @param len   Ҫ��ȡ���ֽڳ���
 */
void NFC_Read(u64 lba, u32 len);

#endif // NFC_H
