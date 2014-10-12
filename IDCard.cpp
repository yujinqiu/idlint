#include <string>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#include "IDCard.h"

using namespace std;

// wi =2(n-1)(mod 11) 
int32_t IDCard::wi[18] = { 7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2, 1 }; 

// verify digit 
char IDCard::vi[11] = { '1', '0', 'X', '9', '8', '7', '6', '5', '4', '3', '2' }; 

//身份证号码校验 
int32_t IDCard::verify(string idcard, int32_t& gender/*0: 女 1::表示男*/) 
{ 
	//把15位身份证升级为18位
	if ( idcard.length() == 15) 
	{ 
		idcard = uptoeighteen(idcard); 
	} 

	if (idcard.length() != 18) 
	{ 
		return -1; 
	}

	//1-17必须是数字
	for(int32_t i = 0; i < 17; ++i)
	{
		if( idcard[i] < '0' || idcard[i] > '9')
		{
			return -2;
		}
	}

	//最后一位(第18位)为校验码，检查checksum值
	char verify = toupper(idcard[17]); 
	if (verify != checksum(idcard))
	{
		return -3; 
	} 

	//第1-2位为省级行政区划代码，[11, 65] (第一位华北区1，东北区2，华东区3，中南区4，西南区5，西北区6)
	string strProvince = idcard.substr(0, 2);
	int32_t nProvince = atoi(strProvince.c_str());
	if( nProvince < 11 || nProvince > 65 )
	{
		return -4;
	}

	//第3-4为为地级行政区划代码，第5-6位为县级行政区划代码因为经常有调整，这块就不做校验

	//第7-10位为出生年份；//第11-12位为出生月份 //第13-14为出生日期
	if( !checkdate(idcard.substr(6,8)) )
	{
		return -5;
	}

	//第15-17位为顺序码，表示在同一地址码所标识的区域范围内，对同年、同月、同日出生的人编定的顺序号，顺序码的奇数分配给男性，偶数分配给女性
	string strSeq = idcard.substr(14,3);
	int32_t nSeq = atoi(strSeq.c_str());
	gender = nSeq%2;

	return 0; 
}

bool IDCard::checkdate(const string& strDate)
{
	string strYear = strDate.substr(0, 4);
	int32_t nYear = atoi(strYear.c_str());

	time_t timep;
	time(&timep);
	struct tm *p = gmtime(&timep);
	if( p )
	{
		if( nYear < 1900 || nYear > 1900 + p->tm_year )
		{
			return false;
		}

		if( atoi(strDate.c_str()) > ( (1900 + p->tm_year)*10000 + p->tm_mon*100 + p->tm_mday ) )
		{
			return false;
		}
	}

	string strMon = strDate.substr(4, 2);
	int32_t nMon = atoi(strMon.c_str());
	if( nMon <= 0 || nMon > 12 )
	{
		return false;
	}

	//月份天数表
	int32_t days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	bool bLeapYear = (nYear % 4 == 0 && nYear % 100 != 0) || (nYear % 400 == 0);
	if( bLeapYear )
	{
		days[1] = 29;
	}
	string strDay = strDate.substr(6, 2);
	int32_t nDay = atoi(strDay.c_str());
	if( nDay > days[nMon - 1 ] || nDay <= 0 )
	{
		return false;
	}

	return true;
}

//计算校验码
char IDCard::checksum(string eightcardid) 
{ 
	int32_t remaining = 0; 
	int32_t ai[18]; 

	if ( eightcardid.length() == 18 ) 
	{ 
		eightcardid = eightcardid.substr(0, 17); 
	} 

	if ( eightcardid.length() == 17 ) 
	{ 
		int32_t sum = 0; 
		for (int32_t i = 0; i < 17; i++) 
		{ 
			string k = eightcardid.substr(i, 1); 
			ai[i] = atoi(k.c_str()); 
		}

		for (int32_t i = 0; i < 17; i++) 
		{ 
			sum = sum + wi[i] * ai[i]; 
		} 
		remaining = sum % 11; 
	}

	return vi[remaining];
} 

//把15位身份证升级到18位身份证号码 
string IDCard::uptoeighteen(const string& fifteencardid) 
{ 
	string eightcardid = fifteencardid.substr(0, 6); 
	//加上年月日
	eightcardid = eightcardid + "19"; 
	eightcardid = eightcardid + fifteencardid.substr(6) ;
	//加上校验码
	eightcardid.push_back(checksum(eightcardid)); 
	return eightcardid; 
} 

