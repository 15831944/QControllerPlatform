/*
 * LogHandler.cpp
 *
 *  Created on: 2016年5月12日
 *      Author: Jugo
 */

#pragma execution_character_set("utf-8")

#include <sys/stat.h>
#include <syslog.h>
#include <fstream>
#include <stdio.h>
#include <cstdarg> // for Variable-length argument
#include "LogHandler.h"
#include "common.h"
#include "utility.h"
#include <QDebug>

using namespace std;

static fstream fs;
static string mstrLogPath;
static string mstrLogDate;

extern char *__progname;

inline bool fileExists(const string& filename)
{
	struct stat buf;
	if(stat(filename.c_str(), &buf) != -1)
	{
		return true;
	}
	return false;
}

inline void writeLog(int nSize, const char *pLog)
{
	if(!pLog)
		return;

	extern fstream fs;
	extern string mstrLogPath;
	extern string mstrLogDate;
	string strCurrentDate = currentDate();

	if(0 != mstrLogDate.compare(strCurrentDate) || !fs.is_open() || mstrLogPath.empty() || mstrLogDate.empty()
			|| !fileExists(format("%s.%s", mstrLogPath.c_str(), mstrLogDate.c_str())))
	{
		if(mstrLogPath.empty())
			mstrLogPath = format("/data/opt/tomcat/webapps/logs/%s.log", __progname);
		mstrLogDate = strCurrentDate;
		string strPath = format("%s.%s", mstrLogPath.c_str(), mstrLogDate.c_str());
		_close();
		fs.open(strPath.c_str(), fstream::in | fstream::out | fstream::app);
		fs.rdbuf()->pubsetbuf(0, 0);
        fs << "<html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"></head><body>\r\n" << endl;
		fs << currentDateTime() + " : [LogHandler] Open File: " + strPath << endl;
        printf("[LogHandler] Open File: %s\r\n", strPath.c_str());
	}

	if(fs.is_open())
	{
		fs.write(pLog, nSize).flush();
	}
}

QString str2qstr(const string str)
{
    return QString::fromLocal8Bit(str.data());
}

string qstr2str(const QString qstr)
{
    QByteArray cdata = qstr.toLocal8Bit();
    return string(cdata);
}

void _log(const char* format, ...)
{
	va_list vl;
	va_start(vl, format);
    int size = vsnprintf(0, 0, format, vl) + (int)sizeof('\0');
	va_end(vl);

	char buffer[size];

	va_start(vl, format);
    size = vsnprintf(buffer, (ULONG)size, format, vl);
	va_end(vl);

    string strLog = string(buffer, (ULONG)size);

    strLog = "</br>" + currentDateTime() + " : " + strLog + "\r\n";

	writeLog(strLog.length(), strLog.c_str());

    qDebug() << strLog.c_str() << endl;

}

void _setLogPath(const char *ppath)
{
	if(0 == ppath)
	{
		mstrLogPath = format("/data/opt/tomcat/webapps/logs/%s.log", __progname);
	}
	else
	{
		mstrLogPath = ppath;
		if(!mstrLogPath.empty())
			mkdirp(mstrLogPath);
	}
}

void _close()
{
	if(fs.is_open())
	{
		string strPath = format("%s.%s", mstrLogPath.c_str(), mstrLogDate.c_str());
		fs << currentDateTime() + " : [LogHandler] Close File: " + strPath << endl;
		fs.close();
	}
}

void _error(const char* format, ...)
{
	va_list vl;
	va_start(vl, format);
    int size = vsnprintf(0, 0, format, vl) + (int)sizeof('\0');
	va_end(vl);

	char buffer[size];

	va_start(vl, format);
    size = vsnprintf(buffer, (ULONG)size, format, vl);
	va_end(vl);

    string strLog = string(buffer, (ULONG)size);

	strLog = currentDateTime() + " : " + strLog + "\n";

	FILE *perr = fopen("error.log", "a+");
	if(perr)
	{
		fwrite(strLog.c_str(), 1, strLog.length(), perr);
		fclose(perr);
	}
}
