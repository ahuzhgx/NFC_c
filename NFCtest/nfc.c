#include "nfc.h"
#include "nfc_reg.h"

/**
 * @brief  ��λ NAND Flash
 */
void NFC_Reset(void) {
    NFC_SetOpcode(0x00FF);   // Reset command
    NFC_WaitIdle();
}

/**
 * @brief  ���� Timing ģʽ
 */
void NFC_SetTimingMode(void) {
    NFC_SetOpcode(0x01EF);   // Set Features - Timing
    NFC_WaitIdle();
}

/**
 * @brief  ��������
 */
void NFC_SetConfiguration(void) {
    NFC_SetOpcode(0x02EF);   // Set Features - Configuration
    NFC_WaitIdle();
}

/**
 * @brief  ��ȡ Feature
 */
void NFC_GetFeatures(void) {
    NFC_SetOpcode(0x01EE);   // Get Features
    NFC_WaitIdle();
}

/**
 * @brief  ��ȡ Parameter Page
 */
void NFC_ReadParameter(void) {
    NFC_SetOpcode(0x00EC);   // Read Parameter Page
    NFC_WaitIdle();
}

/**
 * @brief  ������
 * @param  lba  �߼����ַ
 */
void NFC_Erase(u64 lba) {
    NFC_SetLBA(lba);
    NFC_SetOpcode(0xD060);   // Block Erase
    NFC_WaitIdle();
}

/**
 * @brief  ҳ���
 * @param  lba  �߼����ַ
 * @param  len  ���ݳ��ȣ���λ���ֽڣ�
 */
void NFC_Program(u64 lba, u32 len) {
    NFC_SetLBA(lba);
    NFC_SetLen(len);
    NFC_SetOpcode(0x1080);   // Program Page
    NFC_WaitIdle();
}

/**
 * @brief  ҳ��ȡ
 * @param  lba  �߼����ַ
 * @param  len  ���ݳ��ȣ���λ���ֽڣ�
 */
void NFC_Read(u64 lba, u32 len) {
    NFC_SetLBA(lba);
    NFC_SetLen(len);
    NFC_SetOpcode(0x3000);   // Read Page
    NFC_WaitIdle();
}
