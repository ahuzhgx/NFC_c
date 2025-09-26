#include "xil_io.h"
#include "xil_printf.h"
#include "sleep.h"

// NFC 基地址（在 Address Editor 里确认后替换掉）
#define NFC_BASEADDR   0x40000000U

// 假设几个寄存器偏移
#define NFC__REG   0x00  // 
#define NFC__REG   0x04  // 
#define NFC__REG   0x08  // 
#define NFC__REG    0x0C  // 

int main()
{
    u32 reg_val;

    xil_printf("NFC AXI4-Lite test start...\n\r");

    // 写控制寄存器，例：bit0=1 打开使能
    Xil_Out32(NFC_BASEADDR + NFC_CTRL_REG, 0x00000001);
    xil_printf("Write CTRL: 0x%08lx\n\r", Xil_In32(NFC_BASEADDR + NFC__REG));

    // 写命令寄存器，例：发一个测试命令 0xA5
    Xil_Out32(NFC_BASEADDR + NFC_CMD_REG, 0x000000A5);
    xil_printf("Write CMD: 0x%08lx\n\r", Xil_In32(NFC_BASEADDR + NFC__REG));

    // 写入数据寄存器
    Xil_Out32(NFC_BASEADDR + NFC_DATA_REG, 0x12345678);
    xil_printf("Write DATA: 0x%08lx\n\r", Xil_In32(NFC_BASEADDR + NFC__REG));

    // 轮询状态寄存器
    do {
        reg_val = Xil_In32(NFC_BASEADDR + NFC__REG);
        xil_printf("Status = 0x%08lx\n\r", reg_val);
        usleep(1000);  // 延时 1ms
    } while ((reg_val & 0x1) == 0);  // 假设 bit0 表示完成

    xil_printf("NFC test done.\n\r");

    return 0;
}
