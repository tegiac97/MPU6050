#include"MPU6050.h"

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
    //printf("MPU init stpep 1\n\r");
	__delay_ms(100);
	MPU6050_Write(PWR_MGMT_1, 0x00);   // Thanh ghi thu 107 cua MPU6050 duoc set
    __delay_ms(100);                             //      Dung xung noi 8Mhz,bat sensor nhiet do,...
	//printf("MPU init stpep 2\n\r");
	__delay_ms(100);
    MPU6050_Write(SMPLRT_DIV, 0x07);   // Thanh ghi thu 25 cua MPU6050 duoc set
    //printf("MPU init stpep 3\n\r");
	__delay_ms(100);                               //  sao cho du lieu xuat ra o tan so 1kHz // Set the sample rate to 1000Hz - 8kHz/(7+1) = 1000Hz
	MPU6050_Write(CONFIG, 0x00);       // Thanh ghi thu 26 cua MPU6050 duoc set
    //printf("MPU init stpep 4\n\r");
	__delay_ms(100);                                 // Disable FSYNC and set 260 Hz Acc filtering, 256 Hz Gyro filtering, 8 KHz sampling
	MPU6050_Write(GYRO_CONFIG, 0x00);  // Thanh ghi thu 27 cua MPU6050 duoc set
    //printf("MPU init stpep 5\n\r");
	__delay_ms(100);                                 //      Detect goc xoay +_ 250degree/s
 	MPU6050_Write(ACCEL_CONFIG, 0x08); // Thanh ghi thu 28 cua MPU6050 duoc set
    //printf("MPU init stpep 6\n\r");
	__delay_ms(100);                                 //      Detect gia toc +_ 4.g , Sensitivity Scale Factor = 8192 LSB/g.
	MPU6050_Write(USER_CTRL, 0x00);    // 0X6A disable FIFO, disable master mode
	//printf("MPU init stpep 7\n\r");
	__delay_ms(100);   
	MPU6050_Write(PWR_MGMT_1, 0x01);   // PLL with X axis gyroscope reference and disable sleep mode
    //printf("MPU init stpep 8\n\r");
	__delay_ms(100);
}

// int main(){
//     float x_ac = 0, y_ac = 0, z_ac = 0;
// 	int im = 0, x_acc = 0, y_acc = 0, z_acc = 0;
// 	int  x_accL = 0, x_accH = 0, y_accL = 0, y_accH = 0, z_accL = 0, z_accH = 0;
//     UART_Init();
//     printf("UART init done \n\r");
//     __delay_ms(200);
//     I2C_Init();
//     printf("I2C init done. \n\r");
//      __delay_ms(200);
//     MPU6050_Init();
//     printf("MPU init done \n\r");
//      __delay_ms(200);
// 	im = MPU6050_Read(WHO_AM_I);
// 	printf("I AM: %d\t", im);
    
// 	while (1){
//         x_accH = MPU6050_Read(ACCEL_XOUT_H);
// 		x_accL = MPU6050_Read(ACCEL_XOUT_L);
// 		x_acc = x_accH << 8 | x_accL;

// 		y_accH = MPU6050_Read(ACCEL_YOUT_H);
// 		y_accL = MPU6050_Read(ACCEL_YOUT_L);
// 		y_acc = y_accH << 8 | y_accL;

// 		z_accH = MPU6050_Read(ACCEL_ZOUT_H);
// 		z_accL = MPU6050_Read(ACCEL_ZOUT_L);
//         z_acc = z_accH << 8 | z_accL;
        
//         //printf("x: %d \t y: %d \t z:%d \n\r", x_acc,y_acc,z_acc);
// 		// convert to (g) +-4g, S = 8192 B/g
// 		//x_ac = (float)x_acc / 8192; 
// 		//y_ac = (float)y_acc / 8192;
// 		//z_ac = (float)z_acc / 8192;
// 		//printf("%d:%d:%d\r\n ", (int)(x_ac * 1000), (int)(y_ac * 1000), (int)(z_ac * 1000));
// 		//__delay_ms(100);
      
// 	}
// }
