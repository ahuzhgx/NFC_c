#include "nfc.h"

void NFC_SetOpcode(u32 opcode) {
    Xil_Out32(NFC_BASEADDR + NFC_OPCODE_REG, opcode & 0xFFFF);
}

void NFC_SetLen(u32 len) {
    Xil_Out32(NFC_BASEADDR + NFC_LEN_REG, len & 0xFFFFFF);
}

void NFC_SetLBA(u64 lba) {
    u32 lba_low  = (u32)(lba & 0xFFFFFFFF);
    u32 lba_high = (u32)((lba >> 32) & 0xFFFF);
    Xil_Out32(NFC_BASEADDR + NFC_LBALOW_REG, lba_low);
    Xil_Out32(NFC_BASEADDR + NFC_LBAHIGH_REG, lba_high);
}

void NFC_SetSel(u32 sel) {
    Xil_Out32(NFC_BASEADDR + NFC_SEL_REG, sel);
}

u32 NFC_GetStatus(void) {
    return Xil_In32(NFC_BASEADDR + NFC_STATUS_REG);
}

void NFC_WaitIdle(void) {
    while (NFC_GetStatus() & NFC_STATUS_BUSY) {
        usleep(10);
    }
}