#pragma once

#include <string>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

using namespace std;


class IDCard 
{
	public:
		//身份证号码校验 
		static int32_t verify(std::string idcard, int32_t& gender/*0: 女 1::表示男*/);

	private:
		static bool checkdate(const std::string& strDate);
		//计算校验码
		static char checksum(std::string eightcardid);
		//把15位身份证升级到18位身份证号码 
		static string uptoeighteen(const std::string& fifteencardid);

		// wi =2(n-1)(mod 11) 
		static int32_t wi[18];

		// verify digit 
		static char vi[11];
};
