#include "xil_io.h"
#include "xil_printf.h"
#include "sleep.h"

// NFC ����ַ���� Address Editor ��ȷ�Ϻ��滻����
#define NFC_BASEADDR   0x40000000U

// ���輸���Ĵ���ƫ��
#define NFC__REG   0x00  // 
#define NFC__REG   0x04  // 
#define NFC__REG   0x08  // 
#define NFC__REG    0x0C  // 

int main()
{
    u32 reg_val;

    xil_printf("NFC AXI4-Lite test start...\n\r");

    // д���ƼĴ���������bit0=1 ��ʹ��
    Xil_Out32(NFC_BASEADDR + NFC_CTRL_REG, 0x00000001);
    xil_printf("Write CTRL: 0x%08lx\n\r", Xil_In32(NFC_BASEADDR + NFC__REG));

    // д����Ĵ�����������һ���������� 0xA5
    Xil_Out32(NFC_BASEADDR + NFC_CMD_REG, 0x000000A5);
    xil_printf("Write CMD: 0x%08lx\n\r", Xil_In32(NFC_BASEADDR + NFC__REG));

    // д�����ݼĴ���
    Xil_Out32(NFC_BASEADDR + NFC_DATA_REG, 0x12345678);
    xil_printf("Write DATA: 0x%08lx\n\r", Xil_In32(NFC_BASEADDR + NFC__REG));

    // ��ѯ״̬�Ĵ���
    do {
        reg_val = Xil_In32(NFC_BASEADDR + NFC__REG);
        xil_printf("Status = 0x%08lx\n\r", reg_val);
        usleep(1000);  // ��ʱ 1ms
    } while ((reg_val & 0x1) == 0);  // ���� bit0 ��ʾ���

    xil_printf("NFC test done.\n\r");

    return 0;
}
