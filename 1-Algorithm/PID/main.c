/*****************************************************************************
 * ͨ��PID�㷨
 *
 * ���������GPLЭ�鷢��
 *****************************************************************************/
#include <stdio.h>
#include <math.h>

#define PID_TYPE float

// PID����ģ�飨ÿ�����Ƶ�Ԫ��Ҫһ���˽ṹ��
struct pid_unit {
        PID_TYPE pid_sens[2];   // ������������3��������������
        PID_TYPE pid_cpid[3];   // ���������֡�΢��ϵ��
        PID_TYPE pid_dpid[3];   // PID����
};

// ��ʼ��PIDģ��Ĵ���
void pid_init(struct pid_unit *unit,  // PID����ģ��ָ��
              PID_TYPE p,             // ����ϵ��
              PID_TYPE i,             // ����ϵ��
              PID_TYPE d)             // ΢��ϵ��
{
        unit->pid_cpid[0] = p;
        unit->pid_cpid[1] = i;
        unit->pid_cpid[2] = d;

        unit->pid_dpid[0] = 0;
        unit->pid_dpid[1] = 0;
        unit->pid_dpid[2] = 0;

        unit->pid_sens[0] = 0;
        unit->pid_sens[1] = 0;
}

// PID�㷨���ƺ�����ͨ���˺���ʵ�ֶ������������е�PID����
// ����ֵ��PID��������ֵ
PID_TYPE pid_control(struct pid_unit *unit,   // PID����ģ��
                     PID_TYPE input,          // ��ǰ��������
                     PID_TYPE time)           // �����ϸ����ݵ�ʱ����
{
        // adjust the FIFO preserving the sensor data
        unit->pid_sens[1] = unit->pid_sens[0];
        unit->pid_sens[0] = input;

        // calculate each pid variable
        unit->pid_dpid[0]  =  unit->pid_sens[0] * unit->pid_cpid[0];
        unit->pid_dpid[1] +=  unit->pid_sens[0] * unit->pid_cpid[1] * time;
        unit->pid_dpid[2]  = (unit->pid_sens[0] - unit->pid_sens[1])/ time *
                              unit->pid_cpid[2];

        return unit->pid_dpid[0] + 
               unit->pid_dpid[1] +
               unit->pid_dpid[2];
}

// ʹ����ʾ
int main()
{
        struct pid_unit unit;        // ����һ��PID����ģ��
        pid_init(&unit, 0, 0, 1);    // �Ը�ģ����г�ʼ��

        int i;
        PID_TYPE input[1000];
        PID_TYPE output[1000];

        // ������������Ϊһ��ֵΪ10�����Ҳ�������Ǿ���PIDϵ�����д��������
        for(i=0; i<1000; i++) {
                input[i] = (PID_TYPE) 10 * sin((float)i/100);
                output[i] = pid_control(&unit, input[i], (float)1/100);
        }

        // ͨ����ӡ��ʽ�����롢����������������̨��ͨ���ܵ������ļ��󣬿�����gnuplot
        // ��������Ƴ�ͼ�����PID�������������Ӧ��ϵ
        for(i=0; i<1000; i++) {
                fprintf(stdout, "%8.4f\t%8.4f\t%8.4f\n", (float)i/100, input[i], output[i]);
        }

        return 0;
}
