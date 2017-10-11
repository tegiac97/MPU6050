// DSPIC30F6010A Configuration Bit Settings
// 'C' source line config statements
// FOSC
#pragma config FOSFPR = HS              // Oscillator (Internal Fast RC (No change to Primary Osc Mode bits))
#pragma config FCKSMEN = CSW_FSCM_OFF   // Clock Switching and Monitor (Sw Disabled, Mon Disabled)

// FWDT
#pragma config FWPSB = WDTPSB_16        // WDT Prescaler B (1:16)
#pragma config FWPSA = WDTPSA_512       // WDT Prescaler A (1:512)
#pragma config WDT = WDT_OFF            // Watchdog Timer (Disabled)

// FBORPOR
#pragma config FPWRT = PWRT_64          // POR Timer Value (64ms)
#pragma config BODENV = BORV20          // Brown Out Voltage (Reserved)
#pragma config BOREN = PBOR_ON          // PBOR Enable (Enabled)
#pragma config LPOL = PWMxL_ACT_HI      // Low-side PWM Output Polarity (Active High)
#pragma config HPOL = PWMxH_ACT_HI      // High-side PWM Output Polarity (Active High)
#pragma config PWMPIN = RST_IOPIN       // PWM Output Pin Reset (Control with PORT/TRIS regs)
#pragma config MCLRE = MCLR_EN          // Master Clear Enable (Disabled)

// FBS
#pragma config BWRP = WR_PROTECT_BOOT_OFF// Boot Segment Program Memory Write Protect (Boot Segment Program Memory may be written)
#pragma config BSS = NO_BOOT_CODE       // Boot Segment Program Flash Memory Code Protection (No Boot Segment)
#pragma config EBS = NO_BOOT_EEPROM     // Boot Segment Data EEPROM Protection (No Boot EEPROM)
#pragma config RBS = NO_BOOT_RAM        // Boot Segment Data RAM Protection (No Boot RAM)

// FSS
#pragma config SWRP = WR_PROT_SEC_OFF   // Secure Segment Program Write Protect (Disabled)
#pragma config SSS = NO_SEC_CODE        // Secure Segment Program Flash Memory Code Protection (No Secure Segment)
#pragma config ESS = NO_SEC_EEPROM      // Secure Segment Data EEPROM Protection (No Segment Data EEPROM)
#pragma config RSS = NO_SEC_RAM         // Secure Segment Data RAM Protection (No Secure RAM)

// FGS
#pragma config GWRP = GWRP_OFF          // General Code Segment Write Protect (Disabled)
#pragma config GCP = GSS_OFF            // General Segment Code Protection (Disabled)

// FICD
#pragma config ICS = ICS_PGD            // Comm Channel Select (Use PGC/EMUC and PGD/EMUD)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.


#define FCY 2000000UL
#define FSCL 400000

#include<p30F6010A.h>
#include<xc.h>
#include<stdio.h>
#include"MPUdefine.c"
#include<libpic30.h>

void UART_Init();
void I2C_Stop();
void I2C_Stop();
void I2C_Repeated_Start();
int I2C_Read();

void I2C_Write(int);
void I2C_Init();
void I2C_ACK();
void I2C_NACK();
void MPU6050_Init();
int MPU6050_Read();
void MPU6050_Write(int, int);

int main(){
    float x_ac = 0, y_ac = 0, z_ac = 0;
	int im = 0, x_acc = 0, y_acc = 0, z_acc = 0;
	int  x_accL = 0, x_accH = 0, y_accL = 0, y_accH = 0, z_accL = 0, z_accH = 0;
    UART_Init();
    printf("UART init done \n\r");
    __delay_ms(200);
    I2C_Init();
    printf("I2C init done. \n\r");
     __delay_ms(200);
    MPU6050_Init();
    printf("MPU init done \n\r");
     __delay_ms(200);
	im = MPU6050_Read(WHO_AM_I);
	printf("I AM: %d\t", im);
    
	while (1){
    //im = MPU6050_Read(WHO_AM_I);
	//printf("%d\t", im);
    //__delay_ms(200);
        //im = MPU6050_Read(WHO_AM_I);
        //printf("%d\t", im);
        x_accH = MPU6050_Read(ACCEL_XOUT_H);
		x_accL = MPU6050_Read(ACCEL_XOUT_L);
		x_acc = x_accH << 8 | x_accL;

		y_accH = MPU6050_Read(ACCEL_YOUT_H);
		y_accL = MPU6050_Read(ACCEL_YOUT_L);
		y_acc = y_accH << 8 | y_accL;

		z_accH = MPU6050_Read(ACCEL_ZOUT_H);
		z_accL = MPU6050_Read(ACCEL_ZOUT_L);
        z_acc = z_accH << 8 | z_accL;
        
        printf("x: %d \t y: %d \t z:%d \n\r", x_acc,y_acc,z_acc);
		// convert to (g) +-4g, S = 8192 B/g
		//x_ac = (float)x_acc / 8192; 
		//y_ac = (float)y_acc / 8192;
		//z_ac = (float)z_acc / 8192;
		//printf("%d:%d:%d\r\n ", (int)(x_ac * 1000), (int)(y_ac * 1000), (int)(z_ac * 1000));
		//__delay_ms(100);
      
	}
}


void UART_Init(){
    U1MODEbits.STSEL=0;
    U1MODEbits.PDSEL=0;
    U1BRG=12;
    U1MODEbits.UARTEN=1;
   
}

//I2C_Start
void I2C_Start(){
    I2CCONbits.SEN=1;
    while (I2CCONbits.SEN);	//Wait for Start COndition
     //printf("I2C Start!\n\r");
}

//I2C_Stop
void I2C_Stop(){
    I2CCONbits.PEN=1;
    //printf("I2C Stop!\n\r");
}

//I2C_Repeated_Start
void I2C_Repeated_Start(){
    I2CCONbits.RSEN=1;
    while (I2CCONbits.RSEN);	//Wait for restart
    //printf("I2C Repeat Start!\n\r");
}
void I2C_Wait(){
    while(I2CSTATbits.TRSTAT==1);// printf("Wait for and verify the ack from slave! \n\r");
}
//I2C_Write
void I2C_Write(int data){
    I2CTRN=data;
    while (I2CSTATbits.TBF);// printf("Wait for data transmission! \n\r");
   
}
void I2C_ENRecept(){
    I2CCONbits.RCEN=1;		//enable master data reception
	while (I2CCONbits.RCEN);		//wait for data reception
	//I2CCONbits.PEN = 1;		//Generate Start COndition
	//while (I2CCONbits.PEN);	//Wait for Start COndition
}
//I2C_Read
int I2C_Read(){  
    return I2CRCV;
}

void I2C_Init(){
    //I2CCON = 0x0000;
    I2CCON = 0x1200;
    I2CSTAT = 0x0000;
    I2CBRG=(FCY/FSCL-FCY/1111111)-1;                     ////////////////////////////////////////////////////////////
    //I2CCONbits.DISSLW=1;
    //I2CCONbits.I2CEN=1;
    I2CCON = 0x9200;
    TRISGbits.TRISG2 = 0;
    TRISGbits.TRISG3 = 1;
    
}


//ACK
void I2C_ACK(){
    //I2CCONbits.ACKEN=1;
    I2CCONbits.ACKDT=0;
}

//NACK
void I2C_NACK(){
    I2CCONbits.ACKDT=1;
    //printf("Master Send NACK! \n\r");
}


//Read of Serial EEPROM
void MPU6050_Write(int address, int data){
    //printf("In MPU6050_Write! \n\r");
    I2C_Start();
    I2C_Write(0xD0);
    I2C_Wait(); 
    I2C_Write(address);
    I2C_Wait(); 
    I2C_Write(data);
    I2C_Wait(); 
    I2C_Stop();
    __delay_ms(100);
}

//Transmission and Reception
// void I2C_Write(int address, int data){
//     I2C_Start();

// }

int MPU6050_Read(int address){
    int data;
    I2C_Wait(); 
    I2C_Start();
    I2C_Write(0xD0);
    I2C_Wait(); 
    I2C_Write(address);
    I2C_Wait(); 
    I2C_Repeated_Start();
    I2C_Write(0xD0|1);
    I2C_Wait(); 
    I2C_ENRecept();
    data=I2C_Read();
    I2C_NACK();
    I2C_Wait(); 
    I2C_Stop();
     return data;
}

void MPU6050_Init(){
	MPU6050_Write(PWR_MGMT_1,0X80); // resets all internal registers to their default values
    printf("MPU init stpep 1\n\r");
	__delay_ms(100);
	MPU6050_Write(PWR_MGMT_1, 0x00);   // Thanh ghi thu 107 cua MPU6050 duoc set
    __delay_ms(100);                             //      Dung xung noi 8Mhz,bat sensor nhiet do,...
	printf("MPU init stpep 2\n\r");
	__delay_ms(100);
    MPU6050_Write(SMPLRT_DIV, 0x07);   // Thanh ghi thu 25 cua MPU6050 duoc set
     printf("MPU init stpep 3\n\r");
	__delay_ms(100);                               //  sao cho du lieu xuat ra o tan so 1kHz // Set the sample rate to 1000Hz - 8kHz/(7+1) = 1000Hz
	MPU6050_Write(CONFIG, 0x00);       // Thanh ghi thu 26 cua MPU6050 duoc set
    printf("MPU init stpep 4\n\r");
	__delay_ms(100);                                 // Disable FSYNC and set 260 Hz Acc filtering, 256 Hz Gyro filtering, 8 KHz sampling
	MPU6050_Write(GYRO_CONFIG, 0x00);  // Thanh ghi thu 27 cua MPU6050 duoc set
     printf("MPU init stpep 5\n\r");
	__delay_ms(100);                                 //      Detect goc xoay +_ 250degree/s
 	MPU6050_Write(ACCEL_CONFIG, 0x08); // Thanh ghi thu 28 cua MPU6050 duoc set
     printf("MPU init stpep 6\n\r");
	__delay_ms(100);                                 //      Detect gia toc +_ 4.g , Sensitivity Scale Factor = 8192 LSB/g.
	MPU6050_Write(USER_CTRL, 0x00);    // 0X6A disable FIFO, disable master mode
	printf("MPU init stpep 7\n\r");
	__delay_ms(100);   
	MPU6050_Write(PWR_MGMT_1, 0x01);   // PLL with X axis gyroscope reference and disable sleep mode
   printf("MPU init stpep 8\n\r");
	__delay_ms(100);
}
