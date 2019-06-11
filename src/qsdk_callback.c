/*
 * File      : qsdk_callback.c
 * This file is part of callback in qsdk
 * Copyright (c) 2018-2030, longmain Development Team
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-14     longmain     first version
 * 2018-12-13     longmain     update fun
 */

#include "qsdk.h"
#include "stdio.h"
#include "stdlib.h"

#define LOG_TAG              "[QSDK/CALLBACK]"
#ifdef QSDK_USING_LOG
#define LOG_LVL              LOG_LVL_DBG
#else
#define LOG_LVL              LOG_LVL_INFO
#endif
#include <ulog.h>

#ifdef QSDK_USING_NET
extern qsdk_net_client_t udp_client;
#endif

#ifdef QSDK_USING_ONENET
//���� object
extern qsdk_onenet_stream_t temp_object;
extern qsdk_onenet_stream_t hump_object;
extern qsdk_onenet_stream_t light0_object;
extern qsdk_onenet_stream_t light1_object;
extern qsdk_onenet_stream_t light2_object;
extern qsdk_onenet_stream_t gps_lat_object;
extern qsdk_onenet_stream_t gps_lon_object;
#endif



//���ó���
extern int beep_status;
/****************************************************
* �������ƣ� qsdk_rtc_set_time_callback
*
* �������ã� RTC���ûص�����
*
* ��ڲ����� year�����		month: �·�		day: ����
*
*							hour: Сʱ		min: ����		sec: ��		week: ����
*
* ����ֵ�� 0 �����ɹ�	1 ����ʧ��
*****************************************************/
void qsdk_rtc_set_time_callback(int year,char month,char day,char hour,char min,char sec,char week)
{ 
	set_date(year,month,day);
	set_time(hour,min,sec);
}
/****************************************************
* �������ƣ� qsdk_net_data_callback
*
* �������ã� TCP/UDP �������·����ݻص�����
*
* ��ڲ�����	data: �����׵�ַ
*
*							len: ���ݳ���
*
* ����ֵ�� 0 �����ɹ�	1 ����ʧ��
*****************************************************/
int qsdk_net_data_callback(char *data,int len)
{
#ifdef QSDK_USING_NET
	LOG_D("enter net callback\r\n");
	if(qsdk_net_get_client_revice(udp_client)==RT_EOK)
	{
		LOG_D("udp client rev data=%d,%s\r\n",len,data);
	}
#endif
	return RT_EOK;
}

/****************************************************
* �������ƣ� qsdk_iot_data_callback
*
* �������ã� IOTƽ̨�·����ݻص�����
*
* ��ڲ����� data���·������׵�ַ
*
*							len	:	�·����ݳ���
*
* ����ֵ�� 0 �����ɹ�	1 ����ʧ��
*****************************************************/
int qsdk_iot_data_callback(char *data,int len)
{
	LOG_D("enter iot callback\r\n");
	LOG_D("rev data=%d,%s\r\n",len,data);
	return RT_EOK;
}	
/****************************************************
* �������ƣ� qsdk_onenet_close_callback
*
* �������ã� onenetƽ̨ǿ�ƶϿ����ӻص�����
*
* ��ڲ����� ��
*
* ����ֵ�� 0 �����ɹ�	1 ����ʧ��
*****************************************************/
int qsdk_onenet_close_callback()
{
	LOG_D("enter close onenent callback\r\n");

	return RT_EOK;
}
/****************************************************
* �������ƣ� qsdk_onenet_read_rsp_callback
*
* �������ã� onenetƽ̨ read�����ص�����
*
* ��ڲ����� msgid����ϢID	insid��instance id	resid: resource id
*
* ����ֵ�� 0 �����ɹ�	1 ����ʧ��
*****************************************************/
int qsdk_onenet_read_rsp_callback(int msgid,int insid,int resid)
{
	float temp=1000.12345;
	rt_kprintf("enter read dsp callback\r\n");
	if(qsdk_onenet_get_object_read(temp_object)==RT_EOK)
		qsdk_onenet_read_rsp(msgid,qsdk_onenet_status_result_read_success,temp_object,1,(qsdk_onenet_value_t)&temp,0,0);
		return RT_EOK;
}
/****************************************************
* �������ƣ� qsdk_onenet_write_rsp_callback
*
* �������ã� onenetƽ̨ write�����ص�����
*
* ��ڲ����� len:	��Ҫд������ݳ���
*
*						 value:	��Ҫд�����������
*
* ����ֵ�� 0 �����ɹ�	1 ����ʧ��
*****************************************************/
int qsdk_onenet_write_rsp_callback(int len,char* value)
{
	
	return RT_EOK;
}
/****************************************************
* �������ƣ� qsdk_onenet_exec_rsp_callback
*
* �������ã� onenetƽ̨ exec�����ص�����
*
* ��ڲ����� len:	ƽ̨exec�����·����ݳ���
*
*						 cmd:	ƽ̨exec�����·���������
*
* ����ֵ�� 0 �����ɹ�	1 ����ʧ��
*****************************************************/
int qsdk_onenet_exec_rsp_callback(int len,char* cmd)
{

	LOG_D("enter exec dsp callback\r\n");

	LOG_D("exec data len:%d   data=%s\r\n",len,cmd);
	return RT_EOK;

}



/****************************************************
* �������ƣ� qsdk_onenet_fota_callback
*
* �������ã� onenet ƽ̨FOTA�����ص�����
*
* ��ڲ����� ��
*
* ����ֵ�� 	 ��
*****************************************************/
void qsdk_onenet_fota_callback(void)
{
	LOG_D("enter fota callback\r\n");



}

/****************************************************
* �������ƣ� qsdk_mqtt_data_callback
*
* �������ã� MQTT �������·����ݻص�����
*
* ��ڲ�����topic������    mesg��ƽ̨�·���Ϣ    mesg_len���·���Ϣ����
*
* ����ֵ�� 	0 �����ɹ�	1 ����ʧ��
*****************************************************/


int qsdk_mqtt_data_callback(char *topic,char *mesg,int mesg_len)
{
	rt_kprintf("enter mqtt callback  mesg:%s,len:%d\r\n",mesg,mesg_len);

	return RT_EOK;
}


/****************************************************
* �������ƣ� qsdk_nb_reboot_callback
*
* �������ã� nb-iotģ�����⸴λ�ص�����
*
* ��ڲ�������
*
* ����ֵ��  ��
*****************************************************/
void qsdk_nb_reboot_callback(void)
{
	LOG_D("enter reboot callback\r\n");
	



}




