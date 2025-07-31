#include "Int_MPU6050.h"

uint8_t Int_MPU6050_ReadByte(uint8_t reg_addr,uint8_t *receive_byte)
{
    Dri_I2C2_Start();
    Dri_I2C_SendAddr(MPU_IIC_ADDR << 1 | 0x00);
    Dri_I2C_SendAddr(reg_addr);
    Dri_I2C2_Start();
    Dri_I2C_SendAddr(MPU_IIC_ADDR << 1 | 0x01);
    /*先准备NACK，和停止信号*/
    Dri_I2C2_NAck();
    Dri_I2C2_Stop();
    *receive_byte = Dri_I2C_ReadByte();
    return 0;
}

uint8_t Int_MPU6050_ReadBytes(uint8_t reg_addr,uint8_t *receive_buff,uint8_t size)
{
    Dri_I2C2_Start();
    Dri_I2C_SendAddr(MPU_IIC_ADDR << 1 | 0x00);
    Dri_I2C_SendAddr(reg_addr);
    Dri_I2C2_Start();
    Dri_I2C_SendAddr(MPU_IIC_ADDR << 1 | 0x01);
    for (uint8_t i = 0; i < size; i++)
    {
        if (i < size - 1)
        {
            Dri_I2C2_Ack();
        }
        else
        {
            Dri_I2C2_NAck();
            Dri_I2C2_Stop();
        }
        receive_buff[i] = Dri_I2C_ReadByte();
    }
    
    /*先准备NACK，和停止信号*/
    Dri_I2C2_NAck();
    Dri_I2C2_Stop();
    *receive_buff = Dri_I2C_ReadByte();
    return 0;
}

uint8_t Int_MPU6050_WriteByte(uint8_t reg_addr,uint8_t write_byte)
{
    Dri_I2C2_Start();
    Dri_I2C_SendAddr(MPU_IIC_ADDR << 1 | 0x00);
    Dri_I2C_SendAddr(reg_addr);
    Dri_I2C_SendByte(write_byte);
    Dri_I2C2_Stop();
    return 0;
}

uint8_t Int_MPU6050_WriteBytes(uint8_t reg_addr,uint8_t *write_bytes,uint8_t size)
{
    Dri_I2C2_Start();
    Dri_I2C_SendAddr(MPU_IIC_ADDR << 1 | 0x00);
    Dri_I2C_SendAddr(reg_addr);
    for (uint8_t i = 0; i < size; i++)
    {
        Dri_I2C_SendByte(write_bytes[i]);
    } 
    Dri_I2C2_Stop();
    return 0;
}

void Int_MPU6050_Init(void)
{
    uint8_t dev_id;
    /*初始化I2C*/
    Dri_I2C2_Init();
    /*复位唤醒*/
    Int_MPU6050_WriteByte(MPU_PWR_MGMT1_REG,0x80);
    For_Delay_ms(300);
    Int_MPU6050_WriteByte(MPU_PWR_MGMT1_REG,0x00);
    /*陀螺仪量程配置*/
    Int_MPU6050_WriteByte(MPU_GYRO_CFG_REG,3 << 3);
    /*加速度量程*/
    Int_MPU6050_WriteByte(MPU_ACCEL_CFG_REG,0 << 3);

    /*系统时钟源，陀螺仪采样率，低通滤波的设置*/
    /*先确认正常工作，读一下id*/
    Int_MPU6050_ReadByte(MPU_DEVICE_ID_REG,&dev_id);
    if (dev_id == MPU_IIC_ADDR)
    {
        /*时钟源*/
        Int_MPU6050_WriteByte(MPU_PWR_MGMT1_REG,0x01);
        /*陀螺仪采样率*/
        /*低通滤波*/
    }
    
}
