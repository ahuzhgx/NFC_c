#include "nfc.h"

/**
 ******************************************************************************
 * @file    nfc.c
 * @brief   NFC ��������������ʵ��
 *          ͨ�� AXI4-Lite �ӿڲ��� NFC ģ��Ĵ�����֧�֣�
 *          - ���ò����루opcode��
 *          - �����߼����ַ��LBA��
 *          - ���ò�������
 *          - ͨ��/Plane ѡ��
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
 *
 * @usage ʾ��:
 *      NFC_SetLBA(0x123456789ULL);
 *      NFC_SetLen(2048);
 *      NFC_SetOpcode(NFC_CMD_PAGE_READ);
 *      NFC_WaitIdle();
 *
 ******************************************************************************
 */



/**
 * @brief ���� NFC ������Ĵ���
 * @param opcode 16λ�����룬���� 0x00FF��0x1080 ��
 * @note д��������RTL ����� opcode ������Ӧ�� NAND ����
 */
void NFC_SetOpcode(u32 opcode) {
    Xil_Out32(NFC_BASEADDR + NFC_OPCODE_REG, opcode & 0xFFFF);
}

/**
 * @brief ���� NFC �����ĳ��ȼĴ���
 * @param len Ҫ���������ݳ��ȣ���λ�ֽڣ�
 * @note ֻʹ�õ� 24 λ����Ϊ RTL �ĳ��ȼĴ����� 24bit
 */
void NFC_SetLen(u32 len) {
    Xil_Out32(NFC_BASEADDR + NFC_LEN_REG, len & 0xFFFFFF);
}

/**
 * @brief ���� NFC ���߼����ַ��LBA��
 * @param lba 48λ�߼����ַ
 * @note LBA ��ɵ� 32 λ�͸� 16 λ���ֱ�д�������Ĵ���
 */
void NFC_SetLBA(u64 lba) {
    u32 lba_low  = (u32)(lba & 0xFFFFFFFF);     // �� 32 λ
    u32 lba_high = (u32)((lba >> 32) & 0xFFFF); // �� 16 λ
    Xil_Out32(NFC_BASEADDR + NFC_LBALOW_REG, lba_low);
    Xil_Out32(NFC_BASEADDR + NFC_LBAHIGH_REG, lba_high);
}

/**
 * @brief ���� NFC ͨ��/Plane ѡ��Ĵ���
 * @param sel ѡ��ֵ��ͨ��Ϊ 0 �� 1
 * @note RTL �� slv_reg[4][1:0] ��������ͨ��
 */
void NFC_SetSel(u32 sel) {
    Xil_Out32(NFC_BASEADDR + NFC_SEL_REG, sel);
}

/**
 * @brief ��ȡ NFC ״̬�Ĵ���
 * @return 32λ״̬�Ĵ���ֵ
 * @note �������ж� busy��fifo ������len error ��
 */
u32 NFC_GetStatus(void) {
    return Xil_In32(NFC_BASEADDR + NFC_STATUS_REG);
}

/**
 * @brief �ȴ� NFC ����
 * @note ��� status �Ĵ��� busy λ���� busy = 1����ѭ���ȴ�
 *       ��ֹ CPU æ�ȣ��ɼ� usleep ������ѯ
 */
void NFC_WaitIdle(void) {
    while (NFC_GetStatus() & NFC_STATUS_BUSY) {
        usleep(10); // �ӳ� 10 ΢�룬����æ��ռ�� CPU
    }
}
