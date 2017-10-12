#include"i2c.h"

void UART_Init(){
    U1MODEbits.STSEL=0;
    U1MODEbits.PDSEL=0;
    U1BRG=12;
    U1MODEbits.UARTEN=1;
   
}

//I2C_Start
void I2C_Start(){
    I2CCONbits.SEN=1;
    while (I2CCONbits.SEN);	//Wait for Start Condition
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
    TRISGbits.TRISG2 = 0;                       //Set G2 port to output
    TRISGbits.TRISG3 = 1;                       //Set G3 port to input
    
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

