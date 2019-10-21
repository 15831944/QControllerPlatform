/*
 * utility.h
 *
 *  Created on: 2014年12月23日
 *      Author: jugo
 */

#pragma once

#include <string>
#include <vector>
#include <iomanip>
#include <iostream>
#include <sstream>      // std::stringstream, std::stringbuf
#include <errno.h>
#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
#include <cstdarg>
#include <cstdio>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
#include <string>
#include <set>
#include <stdarg.h>  // For va_start, etc.
#include <memory>    // For std::unique_ptr
#include "common.h"

using namespace std;

#define MAX (a,b) (((a) > (b)) ? (a) : (b))
#define MIN (a,b) (((a) < (b)) ? (a) : (b))

extern char *__progname;

template<class T>
string ConvertToString(T value)
{
	stringstream ss;
	ss << value;
	return ss.str();
}

template<class T>
void convertFromString(T &value, const std::string &s)
{
	std::stringstream ss(s);
	ss >> value;
}

__attribute__ ((unused)) static int spliteData(char *pData, const char * delim, vector<string> &vData)
{
	char * pch;

	pch = strtok(pData, delim);
	while(pch != NULL)
	{
		vData.push_back(string(pch));
		pch = strtok( NULL, delim);
	}

	return vData.size();
}

__attribute__ ((unused)) static int spliteData(char *pData, const char * delim, set<string> &setData)
{
	char * pch;

	pch = strtok(pData, delim);
	while(pch != NULL)
	{
		setData.insert(string(pch));
		pch = strtok( NULL, delim);
	}

	return setData.size();
}

__attribute__ ((unused)) static bool mkdirp(string strPath)
{
	size_t found = strPath.find_last_of("/\\");
	string strDir = strPath.substr(0, found);

	mode_t mode = S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH;

	// const cast for hack
	char* p = const_cast<char*>(strDir.c_str());

	// Do mkdir for each slash until end of string or error
	while(*p != '\0')
	{
		// Skip first character
		++p;

		// Find first slash or end
		while(*p != '\0' && *p != '/')
			++p;

		// Remember value from p
		char v = *p;

		// Write end of string at p
		*p = '\0';

		// Create folder from path to '\0' inserted at p
		if(mkdir(strDir.c_str(), mode) == -1 && errno != EEXIST)
		{
			*p = v;
			return false;
		}

		// Restore path to it's former glory
		*p = v;
	}

	return true;
}

__attribute__ ((unused)) static const string currentDateTime()
{
	time_t now = time(0);
	struct tm tstruct;
	char buf[24];
	tstruct = *localtime(&now);
    int nYear = tstruct.tm_year + 1900;
    int nMonth = tstruct.tm_mon + 1;
    int nDay = tstruct.tm_mday;
    int nHour = tstruct.tm_hour;
    int nMinute = tstruct.tm_min;
    int nSecond = tstruct.tm_sec;
    sprintf(buf,"%d-%d-%d %d:%d:%d", nYear,nMonth,nDay,nHour,nMinute,nSecond);

    //strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
	return buf;
}

__attribute__ ((unused)) static void currentDateTimeNum(int &nYear, int &nMonth, int &nDay, int &nHour,
		int &nMinute, int &nSecond)
{
	time_t now = time(0);
	struct tm tstruct;

	tstruct = *localtime(&now);
	nYear = tstruct.tm_year + 1900;
	nMonth = tstruct.tm_mon + 1;
	nDay = tstruct.tm_mday;
	nHour = tstruct.tm_hour;
	nMinute = tstruct.tm_min;
    nSecond = tstruct.tm_sec;
	printf("%d %d %d %d %d %d\n", nYear, nMonth, nDay, nHour, nMinute, nSecond);
}

__attribute__ ((unused)) static const string currentDate()
{
	time_t now = time(0);
	struct tm tstruct;
	char buf[24];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);
	return buf;
}

__attribute__ ((unused)) static int currentDateNum()
{
	int nDate;
	time_t now = time(0);
	struct tm tstruct;
	char buf[24];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%04Y%02m%02d", &tstruct);
	convertFromString(nDate, buf);
	return nDate;
}

__attribute__ ((unused)) static string trim(string strSource)
{
	string strTmp;
	strTmp = strSource;
	strTmp.erase(0, strTmp.find_first_not_of(" \n\r\t"));
	strTmp.erase(strTmp.find_last_not_of(" \n\r\t") + 1);
	return strTmp;
}

__attribute__ ((unused)) static bool isValidStr(const char *szStr, int nMaxSize)
{
	if((0 != szStr) && 0 < ((int) strlen(szStr)) && nMaxSize > ((int) strlen(szStr)))
		return true;
	else
		return false;
}

__attribute__ ((unused)) static std::string format(const char* fmt, ...)
{
	va_list vl;

	va_start(vl, fmt);
    int size = vsnprintf(0, 0, fmt, vl) + (int)sizeof('\0');
	va_end(vl);

	char buffer[size];

	va_start(vl, fmt);
    size = vsnprintf(buffer, (ULONG)size, fmt, vl);
	va_end(vl);

	return std::string(buffer, size);
}

__attribute__ ((unused)) static std::string Format(const std::string fmt_str, ...) {
    int final_n, n = ((int)fmt_str.size()) * 2; /* Reserve two times as much as the length of the fmt_str */
    std::unique_ptr<char[]> formatted;
    va_list ap;
    while(1) {
        formatted.reset(new char[n]); /* Wrap the plain char array into the unique_ptr */
        strcpy(&formatted[0], fmt_str.c_str());
        va_start(ap, fmt_str);
        final_n = vsnprintf(&formatted[0], n, fmt_str.c_str(), ap);
        va_end(ap);
        if (final_n < 0 || final_n >= n)
            n += abs(final_n - n + 1);
        else
            break;
    }
    return std::string(formatted.get());
}

__attribute__ ((unused)) static long int nowSecond()
{
	time_t tnow;
	time(&tnow);
	return tnow;
}

// 將 i 的數值轉換為 16 進位表示法的字串
template<typename T>
__attribute__ ((unused)) static std::string numberToHex(T i)
{
	std::stringstream stream;
	stream << "0x" << std::setfill('0') << std::setw(sizeof(T) * 2) << std::hex << i;
	return stream.str();
}

__attribute__ ((unused)) static int getRand(int nMin, int nMax)
{
	srand(time(NULL));
	int x = rand() % (nMax - nMin + 1) + nMin;
	return x;
}

__attribute__ ((unused)) static string ReplaceAll(string str, const string& from, const string& to)
{
	size_t start_pos = 0;
	while((start_pos = str.find(from, start_pos)) != std::string::npos)
	{
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
	return str;
}

__attribute__ ((unused)) static string getConfigFile()
{
	string strProcessName = __progname;
	size_t found = strProcessName.find_last_of("/\\");
	return strProcessName.substr(++found) + ".conf";
}

__attribute__ ((unused)) static int findAllOccurances(string data, string toSearch)
{
    int nCount;
    // Get the first occurrence
    size_t pos = data.find(toSearch);

    // Repeat till end is reached
    nCount = 0;
    while( pos != string::npos)
    {
        ++nCount;
        // Get the next occurrence from the current position
        pos =data.find(toSearch, pos + toSearch.size());
    }
    return nCount;
}
