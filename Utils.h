#pragma once

#include <stdint.h>
#include <tchar.h>
#include <iostream>
#include <string>


//#define BigtoLittle16(A)   (( ((uint16)(A) & 0xff00) >> 8)    | \  
//(((uint16)(A) & 0x00ff) << 8))
//
//#define BigtoLittle32(A)   ((( (uint32)(A) & 0xff000000) >> 24) | \  
//(((uint32)(A) & 0x00ff0000) >> 8) | \
//(((uint32)(A) & 0x0000ff00) << 8) | \
//(((uint32)(A) & 0x000000ff) << 24))

namespace Utils {

	//union�ж��Ǵ�С��
	union ud
	{
		int a;
		char b;
	};
	bool ceshi()
	{
		ud c;
		c.a = 1;
		return (c.b == 1);
	}

	
	bool IsBig_Endian()
		//����ֽ���Ϊbig-endian������true;
		//��֮Ϊlittle-endian������false
	{
		unsigned short test = 0x1122;
		if (*((unsigned char*)&test) == 0x11)
			return true;
		else
			return false;

	}//IsBig_Endian()

	//16λ�ֽ���ת��
	uint16_t Swap16Endian(uint16_t val)
	{
		return (((uint16_t)(val) & 0xff00) >> 8) | ((uint16_t)(val) & 0x00ff) << 8;
	}

	//ת����С���ֽ���
	uint32_t SwapEndian(uint32_t val) {

		uint32_t  l_8 = val << 8;
		uint32_t  l_8_and = l_8 & 0xFF00FF00;

		uint32_t  r_8 = val >> 8;
		uint32_t  r_8_and = r_8 & 0xFF00FF;

		val = l_8_and | r_8_and;
		//val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
		return (val << 16) | (val >> 16);
	}

	//�ж�һ������1�ĸ���
	int Num1(uint32_t val) {
		int size = val & 0xffffffff;
		return size;
	}

	void GetProjectExecuteDir(std::string &path)
	{
		TCHAR szFilePath[MAX_PATH + 1] = { 0 };
		GetModuleFileName(NULL, szFilePath, MAX_PATH);
		(_tcsrchr(szFilePath, _T('\\')))[1] = 0; // ɾ���ļ�����ֻ���·���ִ�

		path = std::string(szFilePath);
	}
};
