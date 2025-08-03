#include "App_Car.h"


short gx,gy,gz;
short ax,ay,az; 
float accel_angle;//通过加速度计算的角度
float gyro_y;//y轴角速度，根据量程转换成角度
extern float angle;

void App_Car_GetAngle(void)
{
   

    /* 1. 读取MPU6050的数据 */
    Int_MPU6050_Get_Accel(&ax, &ay, &az);
    Int_MPU6050_Get_Gyro(&gx, &gy, &gz);

    /* 2. 通过加速度计算倾角 */
    /* atan2得到的是弧度， 角度 = 弧度 * 180/PI */
    accel_angle = atan2(ax, az) * 180 / PAI;

    /* 3. 角速度：量程是+-2000°/s ，65536/4000=16.4  */
    /* 注意，角速度的符号要和加速度计算的角度符号方向一致 */
    gyro_y = -gy / 16.4;

    /* 4. 计算的倾角和角速度，进行卡尔曼滤波 */
    Com_Filter_Kalman(accel_angle, gyro_y);

    printf("accel_angle=%.1f\r\n", accel_angle);
    printf("gyro_y=%.1f\r\n", gyro_y);
    printf("angle=%.1f\r\n", angle);


}
