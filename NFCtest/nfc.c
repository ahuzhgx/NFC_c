#include "nfc.h"
#include "nfc_reg.h"

/**
 * @brief  ��λ NAND Flash
 */
void NFC_Reset(void) {
    NFC_SetOpcode(NFC_CMD_RESET);   // Reset command
    NFC_WaitIdle();
}

/**
 * @brief  ���� Timing ģʽ
 */
void NFC_SetTimingMode(void) {
    NFC_SetOpcode(NFC_CMD_SET_FEATURE1);   // Set Features - Timing
    NFC_WaitIdle();
}

/**
 * @brief  ��������
 */
void NFC_SetConfiguration(void) {
    NFC_SetOpcode(NFC_CMD_SET_FEATURE2);   // Set Features - Configuration
    NFC_WaitIdle();
}

/**
 * @brief  ��ȡ Feature
 */
void NFC_GetFeatures(void) {
    NFC_SetOpcode(NFC_CMD_GET_FEATURE);   // Get Features
    NFC_WaitIdle();
}

/**
 * @brief  ��ȡ Parameter Page
 */
void NFC_ReadParameter(void) {
    NFC_SetOpcode(NFC_CMD_READ_PARAM1);   // Read Parameter Page
    NFC_WaitIdle();
}

/**
 * @brief  ������
 * @param  lba  �߼����ַ
 */
void NFC_Erase(u64 lba) {
    NFC_SetLBA(lba);
    NFC_SetOpcode(NFC_CMD_BLOCK_ERASE);   // Block Erase
    NFC_WaitIdle();
}

/**
 * @brief  ҳ���
 * @param  lba  �߼����ַ
 * @param  len  ���ݳ��ȣ���λ���ֽڣ�
 */
void NFC_Program(u64 lba, u32 len) {
    NFC_WaitWrfifoNotFull();////��һЩ���⣬�����ڽ��еĶ�д�����޷����FIFO�Ŀ���
    NFC_SetLBA(lba);
    NFC_SetLen(len);
    NFC_SetOpcode(NFC_CMD_PAGE_PROG);   // Program Page
    NFC_WaitIdle();
}

/**
 * @brief  ҳ��ȡ
 * @param  lba  �߼����ַ
 * @param  len  ���ݳ��ȣ���λ���ֽڣ�
 */
void NFC_Read(u64 lba, u32 len) {
    NFC_WaitRdfifoNotEmpty();////��һЩ���⣬�����ڽ��еĶ�д�����޷����FIFO�Ŀ���
    NFC_SetLBA(lba);
    NFC_SetLen(len);
    NFC_SetOpcode(NFC_CMD_PAGE_READ);   // Read Page
    NFC_WaitIdle();
}
