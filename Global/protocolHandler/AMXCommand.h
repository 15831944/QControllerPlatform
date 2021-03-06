/*
 * AMXCommand.h
 *
 *  Created on: 2016年10月18日
 *      Author: Jugo
 */

#pragma once

#include<string>

using namespace std;

#define CTL_OK					"CTL_OK"
#define CTL_ERROR				"CTL_ERROR"

/**
 * {
 "function": 1,
 "device": 0,
 "control": 1
 }

 */

template<typename T, typename U>
class create_amx_map
{
private:
	std::map<T, U> m_map;
public:
	create_amx_map(const T& key, const U& val)
	{
		m_map[key] = val;
	}

	create_amx_map<T, U>& operator()(const T& key, const U& val)
	{
		m_map[key] = val;
		return *this;
	}

	operator std::map<T, U>()
	{
		return m_map;
	}

};
static map<int, string> AMX_CONTROL_REQUEST =
		create_amx_map<int, string>(10001, "CTL_SYSTEM_ON")(10002, "CTL_SYSTEM_OFF")(20100, "CTL_MODE_SPEECH")(20200,
				"CTL_MODE_BRIEF")(20300, "CTL_MODE_CINEMA")(30009, "CTL_MATRIX_INPUT1")(30010, "CTL_MATRIX_INPUT2")(
				30011, "CTL_MATRIX_INPUT3")(30012, "CTL_MATRIX_INPUT4")(30013, "CTL_MATRIX_INPUT5")(30014,
				"CTL_MATRIX_INPUT6")(30015, "CTL_MATRIX_INPUT7")(30016, "CTL_MATRIX_INPUT8")(40101, "CTL_PROJ_ON_LEFT")(
				40102, "CTL_PROJ_OFF_LEFT")(40107, "CTL_PROJ_HDMI_LEFT")(40108, "CTL_PROJ_VGA_LEFT")(40103,
				"CTL_PROJ_MUTE_LEFT")(40104, "CTL_PROJ_UNMUTE_LEFT")(40105, "CTL_SCREEN_UP_LEFT")(40106,
				"CTL_SCREEN_DOWN_LEFT")(40201, "CTL_PROJ_ON_CENTER")(40202, "CTL_PROJ_OFF_CENTER")(40207,
				"CTL_PROJ_HDMI_CENTER")(40208, "CTL_PROJ_VGA_CENTER")(40203, "CTL_PROJ_MUTE_CENTER")(40204,
				"CTL_PROJ_UNMUTE_CENTER")(40205, "CTL_SCREEN_UP_CENTER")(40206, "CTL_SCREEN_DOWN_CENTER")(40301,
				"CTL_PROJ_ON_RIGHT")(40302, "CTL_PROJ_OFF_RIGHT")(40307, "CTL_PROJ_HDMI_RIGHT")(40308,
				"CTL_PROJ_VGA_RIGHT")(40303, "CTL_PROJ_MUTE_RIGHT")(40304, "CTL_PROJ_UNMUTE_RIGHT")(40305,
				"CTL_SCREEN_UP_RIGHT")(40306, "CTL_SCREEN_DOWN_RIGHT")(50105, "CTL_INPUT1_VOL_UP")(50106,
				"CTL_INPUT1_VOL_DOWN")(50103, "CTL_INPUT1_MUTE")(50104, "CTL_INPUT1_UNMUTE")(50205, "CTL_INPUT2_VOL_UP")(
				50206, "CTL_INPUT2_VOL_DOWN")(50203, "CTL_INPUT2_MUTE")(50204, "CTL_INPUT2_UNMUTE")(50305,
				"CTL_INPUT3_VOL_UP")(50306, "CTL_INPUT3_VOL_DOWN")(50303, "CTL_INPUT3_MUTE")(50304, "CTL_INPUT3_UNMUTE")(
				50405, "CTL_INPUT4_VOL_UP")(50406, "CTL_INPUT4_VOL_DOWN")(50403, "CTL_INPUT4_MUTE")(50404,
				"CTL_INPUT4_UNMUTE")(50505, "CTL_INPUT5_VOL_UP")(50506, "CTL_INPUT5_VOL_DOWN")(50503, "CTL_INPUT5_MUTE")(
				50504, "CTL_INPUT5_UNMUTE")(50605, "CTL_INPUT6_VOL_UP")(50606, "CTL_INPUT6_VOL_DOWN")(50603,
				"CTL_INPUT6_MUTE")(50604, "CTL_INPUT6_UNMUTE")(50705, "CTL_INPUT7_VOL_UP")(50706, "CTL_INPUT7_VOL_DOWN")(
				50703, "CTL_INPUT7_MUTE")(50704, "CTL_INPUT7_UNMUTE")(50805, "CTL_INPUT9_VOL_UP")(50806,
				"CTL_INPUT9_VOL_DOWN")(50803, "CTL_INPUT9_MUTE")(50804, "CTL_INPUT9_UNMUTE")(50905,
				"CTL_INPUT10_VOL_UP")(50906, "CTL_INPUT10_VOL_DOWN")(50903, "CTL_INPUT10_MUTE")(50904,
				"CTL_INPUT10_UNMUTE")(51005, "CTL_OUTPUT1_VOL_UP")(51006, "CTL_OUTPUT1_VOL_DOWN")(51003,
				"CTL_OUTPUT1_MUTE")(51004, "CTL_OUTPUT1_UNMUTE")(51105, "CTL_OUTPUT2_VOL_UP")(51106,
				"CTL_OUTPUT2_VOL_DOWN")(51103, "CTL_OUTPUT2_MUTE")(51104, "CTL_OUTPUT2_UNMUTE")(51205,
				"CTL_OUTPUT3_VOL_UP")(51206, "CTL_OUTPUT3_VOL_DOWN")(51203, "CTL_OUTPUT3_MUTE")(51204,
				"CTL_OUTPUT3_UNMUTE")(51305, "CTL_OUTPUT6_VOL_UP")(51306, "CTL_OUTPUT6_VOL_DOWN")(51303,
				"CTL_OUTPUT6_MUTE")(51304, "CTL_OUTPUT6_UNMUTE")(60005, "CTL_CURTAIN_UP")(60006, "CTL_CURTAIN_DOWN")(
				70101, "CTL_LIGHT1_ON")(70102, "CTL_LIGHT1_OFF")(70201, "CTL_LIGHT2_ON")(70202, "CTL_LIGHT2_OFF")(70301,
				"CTL_LIGHT3_ON")(70302, "CTL_LIGHT3_OFF")(70401, "CTL_LIGHT4_ON")(70402, "CTL_LIGHT4_OFF")(70501,
				"CTL_LIGHT5_ON")(70502, "CTL_LIGHT5_OFF")(70601, "CTL_LIGHT6_ON")(70602, "CTL_LIGHT6_OFF")(70701,
				"CTL_LIGHT7_ON")(70702, "CTL_LIGHT7_OFF")(79901, "CTL_LIGHT_ALL_ON")(79902, "CTL_LIGHT_ALL_OFF")(80018,
				"CTL_BD_OPEN")(80019, "CTL_BD_PLAY")(80020, "CTL_BD_STOP")(80021, "CTL_BD_PAUSE")(80022, "CTL_BD_NEXT")(
				80023, "CTL_BD_PREVIEW")(80024, "CTL_BD_FORWARD")(80025, "CTL_BD_REVIEW")(80026, "CTL_BD_UP")(80027,
				"CTL_BD_DOWN")(80028, "CTL_BD_LEFT")(80029, "CTL_BD_RIGHT")(80030, "CTL_BD_OK")(80031, "CTL_BD_BACK")(
				80032, "CTL_BD_MENU")(80033, "CTL_BD_TOPMENU")(80034, "CTL_BD_HOME")(80035, "CTL_BD_SUBTITLE")(70800,
				"CTL_LIGHT_BRIEF")(80017, "CTL_BD_POWER");

static map<int, string> AMX_STATUS_REQUEST =
		create_amx_map<int, string>(10001, "STATUS_SYSTEM")(30004, "STATUS_MATRIX")(40101, "STATUS_PROJ_POWER_LEFT")(
				40102, "STATUS_PROJ_SIGNAL_LEFT")(40103, "STATUS_PROJ_MUTE_LEFT")(40201, "STATUS_PROJ_POWER_CENTER")(
				40202, "STATUS_PROJ_SIGNAL_CENTER")(40203, "STATUS_PROJ_MUTE_CENTER")(40301, "STATUS_PROJ_POWER_RIGHT")(
				40302, "STATUS_PROJ_SIGNAL_RIGHT")(40303, "STATUS_PROJ_MUTE_RIGHT")(50103, "STATUS_INPUT1_MUTE")(50203,
				"STATUS_INPUT2_MUTE")(50303, "STATUS_INPUT3_MUTE")(50403, "STATUS_INPUT4_MUTE")(50503,
				"STATUS_INPUT5_MUTE")(50603, "STATUS_INPUT6_MUTE")(50703, "STATUS_INPUT7_MUTE")(50803,
				"STATUS_INPUT9_MUTE")(50903, "STATUS_INPUT10_MUTE")(51003, "STATUS_OUTPUT1_MUTE")(51103,
				"STATUS_OUTPUT2_MUTE")(51203, "STATUS_OUTPUT3_MUTE")(51303, "STATUS_OUTPUT6_MUTE")(70101,
				"STATUS_LIGHT1")(70201, "STATUS_LIGHT2")(70301, "STATUS_LIGHT3")(70401, "STATUS_LIGHT4")(70501,
				"STATUS_LIGHT5")(70601, "STATUS_LIGHT6")(70701, "STATUS_LIGHT7")(80001, "STATUS_BD_POWER")(50105,
				"STATUS_INPUT1_VOL")(50205, "STATUS_INPUT2_VOL")(50305, "STATUS_INPUT3_VOL")(50405, "STATUS_INPUT4_VOL")(
				50505, "STATUS_INPUT5_VOL")(50605, "STATUS_INPUT6_VOL")(50705, "STATUS_INPUT7_VOL")(50805,
				"STATUS_INPUT9_VOL")(50905, "STATUS_INPUT10_VOL")(51005, "STATUS_OUTPUT1_VOL")(51105,
				"STATUS_OUTPUT2_VOL")(51205, "STATUS_OUTPUT3_VOL")(51305, "STATUS_OUTPUT6_VOL");

static map<string, int> AMX_STATUS_RESP =
		create_amx_map<string, int>("STATUS_SYSTEM_ON", 10001)("STATUS_SYSTEM_OFF", 10002)("STATUS_MATRIX_INPUT1",
				30009)("STATUS_MATRIX_INPUT2", 30010)("STATUS_MATRIX_INPUT3", 30011)("STATUS_MATRIX_INPUT4", 30012)(
				"STATUS_MATRIX_INPUT5", 30013)("STATUS_MATRIX_INPUT6", 30014)("STATUS_MATRIX_INPUT7", 30015)(
				"STATUS_MATRIX_INPUT8", 30016)("STATUS_PROJ_ON_LEFT", 40101)("STATUS_PROJ_OFF_LEFT", 40102)(
				"STATUS_PROJ_HDMI_LEFT", 40107)("STATUS_PROJ_VGA_LEFT", 40108)("STATUS_PROJ_MUTE_LEFT", 40103)(
				"STATUS_PROJ_UNMUTE_LEFT", 40104)("STATUS_PROJ_ON_CENTER", 40201)("STATUS_PROJ_OFF_CENTER", 40202)(
				"STATUS_PROJ_HDMI_CENTER", 40207)("STATUS_PROJ_VGA_CENTER", 40208)("STATUS_PROJ_MUTE_CENTER", 40203)(
				"STATUS_PROJ_UNMUTE_CENTER", 40204)("STATUS_PROJ_ON_RIGHT", 40301)("STATUS_PROJ_OFF_RIGHT", 40302)(
				"STATUS_PROJ_HDMI_RIGHT", 40307)("STATUS_PROJ_VGA_RIGHT", 40308)("STATUS_PROJ_MUTE_RIGHT", 40303)(
				"STATUS_PROJ_UNMUTE_RIGHT", 40304)("STATUS_INPUT1_MUTE", 50103)("STATUS_INPUT1_UNMUTE", 50104)(
				"STATUS_INPUT2_MUTE", 50203)("STATUS_INPUT2_UNMUTE", 50204)("STATUS_INPUT3_MUTE", 50303)(
				"STATUS_INPUT3_UNMUTE", 50304)("STATUS_INPUT4_MUTE", 50403)("STATUS_INPUT4_UNMUTE", 50404)(
				"STATUS_INPUT5_MUTE", 50503)("STATUS_INPUT5_UNMUTE", 50504)("STATUS_INPUT6_MUTE", 50603)(
				"STATUS_INPUT6_UNMUTE", 50604)("STATUS_INPUT7_MUTE", 50703)("STATUS_INPUT7_UNMUTE", 50704)(
				"STATUS_INPUT9_MUTE", 50803)("STATUS_INPUT9_UNMUTE", 50804)("STATUS_INPUT10_MUTE", 50903)(
				"STATUS_INPUT10_UNMUTE", 50904)("STATUS_OUTPUT1_MUTE", 51003)("STATUS_OUTPUT1_UNMUTE", 51004)(
				"STATUS_OUTPUT2_MUTE", 51103)("STATUS_OUTPUT2_UNMUTE", 51104)("STATUS_OUTPUT3_MUTE", 51203)(
				"STATUS_OUTPUT3_UNMUTE", 51204)("STATUS_OUTPUT6_MUTE", 51303)("STATUS_OUTPUT6_UNMUTE", 51304)(
				"STATUS_LIGHT1_ON", 70101)("STATUS_LIGHT1_OFF", 70102)("STATUS_LIGHT2_ON", 70201)("STATUS_LIGHT2_OFF",
				70202)("STATUS_LIGHT3_ON", 70301)("STATUS_LIGHT3_OFF", 70302)("STATUS_LIGHT4_ON", 70401)(
				"STATUS_LIGHT4_OFF", 70402)("STATUS_LIGHT5_ON", 70501)("STATUS_LIGHT5_OFF", 70502)("STATUS_LIGHT6_ON",
				70601)("STATUS_LIGHT6_OFF", 70602)("STATUS_LIGHT7_ON", 70701)("STATUS_LIGHT7_OFF", 70702)(
				"STATUS_BD_POWER_ON", 80001)("STATUS_BD_POWER_OFF", 80002)("STATUS_INPUT1_VOL", 50100)(
				"STATUS_INPUT2_VOL", 50200)("STATUS_INPUT3_VOL", 50300)("STATUS_INPUT4_VOL", 50400)("STATUS_INPUT5_VOL",
				50500)("STATUS_INPUT6_VOL", 50600)("STATUS_INPUT7_VOL", 50700)("STATUS_INPUT9_VOL", 50800)(
				"STATUS_INPUT10_VOL", 50900)("STATUS_OUTPUT1_VOL", 51000)("STATUS_OUTPUT2_VOL", 51100)(
				"STATUS_OUTPUT3_VOL", 51200)("STATUS_OUTPUT6_VOL", 51300);

// ===== AMX Device Current Status ==== //
static map<string, string> AMX_STATUS_CURRENT = create_amx_map<string, string>("STATUS_SYSTEM", "STATUS_SYSTEM_ON")(
		"STATUS_MATRIX", "STATUS_MATRIX_INPUT1")("STATUS_PROJ_POWER_LEFT", "STATUS_PROJ_OFF_LEFT")(
		"STATUS_PROJ_SIGNAL_LEFT", "STATUS_PROJ_VGA_LEFT")("STATUS_PROJ_MUTE_LEFT", "STATUS_PROJ_UNMUTE_LEFT")(
		"STATUS_PROJ_POWER_CENTER", "STATUS_PROJ_OFF_CENTER")("STATUS_PROJ_SIGNAL_CENTER", "STATUS_PROJ_VGA_CENTER")(
		"STATUS_PROJ_MUTE_CENTER", "STATUS_PROJ_UNMUTE_CENTER")("STATUS_PROJ_POWER_RIGHT", "STATUS_PROJ_OFF_RIGHT")(
		"STATUS_PROJ_SIGNAL_RIGHT", "STATUS_PROJ_VGA_RIGHT")("STATUS_PROJ_MUTE_RIGHT", "STATUS_PROJ_UNMUTE_RIGHT")(
		"STATUS_INPUT1_MUTE", "STATUS_INPUT1_UNMUTE")("STATUS_INPUT2_MUTE", "STATUS_INPUT2_UNMUTE")(
		"STATUS_INPUT3_MUTE", "STATUS_INPUT3_UNMUTE")("STATUS_INPUT4_MUTE", "STATUS_INPUT4_UNMUTE")(
		"STATUS_INPUT5_MUTE", "STATUS_INPUT5_UNMUTE")("STATUS_INPUT6_MUTE", "STATUS_INPUT6_UNMUTE")(
		"STATUS_INPUT7_MUTE", "STATUS_INPUT7_UNMUTE")("STATUS_INPUT9_MUTE", "STATUS_INPUT9_UNMUTE")(
		"STATUS_INPUT10_MUTE", "STATUS_INPUT10_UNMUTE")("STATUS_OUTPUT1_MUTE", "STATUS_OUTPUT1_UNMUTE")(
		"STATUS_OUTPUT2_MUTE", "STATUS_OUTPUT2_UNMUTE")("STATUS_OUTPUT3_MUTE", "STATUS_OUTPUT3_UNMUTE")(
		"STATUS_OUTPUT6_MUTE", "STATUS_OUTPUT6_UNMUTE")("STATUS_LIGHT1", "STATUS_LIGHT1_OFF")("STATUS_LIGHT2",
		"STATUS_LIGHT2_OFF")("STATUS_LIGHT3", "STATUS_LIGHT3_OFF")("STATUS_LIGHT4", "STATUS_LIGHT4_OFF")(
		"STATUS_LIGHT5", "STATUS_LIGHT5_OFF")("STATUS_LIGHT6", "STATUS_LIGHT6_OFF")("STATUS_LIGHT7",
		"STATUS_LIGHT7_OFF")("STATUS_BD_POWER", "STATUS_BD_POWER_OFF");

// ==== AMX Status Response to Status Command ==== //
static map<string, string> AMX_STATUS_TO_CMD = create_amx_map<string, string>("STATUS_SYSTEM_ON", "STATUS_SYSTEM")(
		"STATUS_SYSTEM_OFF", "STATUS_SYSTEM")("STATUS_MATRIX_INPUT1", "STATUS_MATRIX")("STATUS_MATRIX_INPUT2",
		"STATUS_MATRIX")("STATUS_MATRIX_INPUT3", "STATUS_MATRIX")("STATUS_MATRIX_INPUT4", "STATUS_MATRIX")(
		"STATUS_MATRIX_INPUT5", "STATUS_MATRIX")("STATUS_MATRIX_INPUT6", "STATUS_MATRIX")("STATUS_MATRIX_INPUT7",
		"STATUS_MATRIX")("STATUS_MATRIX_INPUT8", "STATUS_MATRIX")("STATUS_PROJ_ON_LEFT", "STATUS_PROJ_POWER_LEFT")(
		"STATUS_PROJ_OFF_LEFT", "STATUS_PROJ_POWER_LEFT")("STATUS_PROJ_HDMI_LEFT", "STATUS_PROJ_SIGNAL_LEFT")(
		"STATUS_PROJ_VGA_LEFT", "STATUS_PROJ_SIGNAL_LEFT")("STATUS_PROJ_MUTE_LEFT", "STATUS_PROJ_MUTE_LEFT")(
		"STATUS_PROJ_UNMUTE_LEFT", "STATUS_PROJ_MUTE_LEFT")("STATUS_PROJ_ON_CENTER", "STATUS_PROJ_POWER_CENTER")(
		"STATUS_PROJ_OFF_CENTER", "STATUS_PROJ_POWER_CENTER")("STATUS_PROJ_HDMI_CENTER", "STATUS_PROJ_SIGNAL_CENTER")(
		"STATUS_PROJ_VGA_CENTER", "STATUS_PROJ_SIGNAL_CENTER")("STATUS_PROJ_MUTE_CENTER", "STATUS_PROJ_MUTE_CENTER")(
		"STATUS_PROJ_UNMUTE_CENTER", "STATUS_PROJ_MUTE_CENTER")("STATUS_PROJ_ON_RIGHT", "STATUS_PROJ_POWER_RIGHT")(
		"STATUS_PROJ_OFF_RIGHT", "STATUS_PROJ_POWER_RIGHT")("STATUS_PROJ_HDMI_RIGHT", "STATUS_PROJ_SIGNAL_RIGHT")(
		"STATUS_PROJ_VGA_RIGHT", "STATUS_PROJ_SIGNAL_RIGHT")("STATUS_PROJ_MUTE_RIGHT", "STATUS_PROJ_MUTE_RIGHT")(
		"STATUS_PROJ_UNMUTE_RIGHT", "STATUS_PROJ_MUTE_RIGHT")("STATUS_INPUT1_MUTE", "STATUS_INPUT1_MUTE")(
		"STATUS_INPUT1_UNMUTE", "STATUS_INPUT1_MUTE")("STATUS_INPUT2_MUTE", "STATUS_INPUT2_MUTE")(
		"STATUS_INPUT2_UNMUTE", "STATUS_INPUT2_MUTE")("STATUS_INPUT3_MUTE", "STATUS_INPUT3_MUTE")(
		"STATUS_INPUT3_UNMUTE", "STATUS_INPUT3_MUTE")("STATUS_INPUT4_MUTE", "STATUS_INPUT4_MUTE")(
		"STATUS_INPUT4_UNMUTE", "STATUS_INPUT4_MUTE")("STATUS_INPUT5_MUTE", "STATUS_INPUT5_MUTE")(
		"STATUS_INPUT5_UNMUTE", "STATUS_INPUT5_MUTE")("STATUS_INPUT6_MUTE", "STATUS_INPUT6_MUTE")(
		"STATUS_INPUT6_UNMUTE", "STATUS_INPUT6_MUTE")("STATUS_INPUT7_MUTE", "STATUS_INPUT7_MUTE")(
		"STATUS_INPUT7_UNMUTE", "STATUS_INPUT7_MUTE")("STATUS_INPUT9_MUTE", "STATUS_INPUT9_MUTE")(
		"STATUS_INPUT9_UNMUTE", "STATUS_INPUT9_MUTE")("STATUS_INPUT10_MUTE", "STATUS_INPUT10_MUTE")(
		"STATUS_INPUT10_UNMUTE", "STATUS_INPUT10_MUTE")("STATUS_OUTPUT1_MUTE", "STATUS_OUTPUT1_MUTE")(
		"STATUS_OUTPUT1_UNMUTE", "STATUS_OUTPUT1_MUTE")("STATUS_OUTPUT2_MUTE", "STATUS_OUTPUT2_MUTE")(
		"STATUS_OUTPUT2_UNMUTE", "STATUS_OUTPUT2_MUTE")("STATUS_OUTPUT3_MUTE", "STATUS_OUTPUT3_MUTE")(
		"STATUS_OUTPUT3_UNMUTE", "STATUS_OUTPUT3_MUTE")("STATUS_OUTPUT6_MUTE", "STATUS_OUTPUT6_MUTE")(
		"STATUS_OUTPUT6_UNMUTE", "STATUS_OUTPUT6_MUTE")("STATUS_LIGHT1_ON", "STATUS_LIGHT1")("STATUS_LIGHT1_OFF",
		"STATUS_LIGHT1")("STATUS_LIGHT2_ON", "STATUS_LIGHT2")("STATUS_LIGHT2_OFF", "STATUS_LIGHT2")("STATUS_LIGHT3_ON",
		"STATUS_LIGHT3")("STATUS_LIGHT3_OFF", "STATUS_LIGHT3")("STATUS_LIGHT4_ON", "STATUS_LIGHT4")("STATUS_LIGHT4_OFF",
		"STATUS_LIGHT4")("STATUS_LIGHT5_ON", "STATUS_LIGHT5")("STATUS_LIGHT5_OFF", "STATUS_LIGHT5")("STATUS_LIGHT6_ON",
		"STATUS_LIGHT6")("STATUS_LIGHT6_OFF", "STATUS_LIGHT6")("STATUS_LIGHT7_ON", "STATUS_LIGHT7")("STATUS_LIGHT7_OFF",
		"STATUS_LIGHT7")("STATUS_BD_POWER_ON", "STATUS_BD_POWER")("STATUS_BD_POWER_OFF", "STATUS_BD_POWER");

inline static string getAMXControlRequest(const int nFunction, const int nDevice, const int nControl)
{
	string strCommand;
	int nId = (10000 * nFunction) + (100 * nDevice) + nControl;
	map<int, string>::const_iterator it = AMX_CONTROL_REQUEST.find(nId);
	if(AMX_CONTROL_REQUEST.end() != it)
		strCommand = AMX_CONTROL_REQUEST[nId];
	return strCommand;
}

inline static string getAMXStatusRequest(const int nFunction, const int nDevice, const int nControl)
{
	string strCommand;
	int nId = (10000 * nFunction) + (100 * nDevice) + nControl;
	map<int, string>::const_iterator it = AMX_STATUS_REQUEST.find(nId);
	if(AMX_STATUS_REQUEST.end() != it)
		strCommand = AMX_STATUS_REQUEST[nId];
	return strCommand;
}

inline static int getAMXStatusResponse(const char * szCommand)
{
	int nStatus = -1;
	map<string, int>::const_iterator it;
	it = AMX_STATUS_RESP.find(szCommand);
	if(AMX_STATUS_RESP.end() != it)
		nStatus = AMX_STATUS_RESP[szCommand];
	return nStatus;
}

//================================================================================================================================
/** deprecated **/
template<typename T, typename U, typename V, typename W>
class map_amx
{
private:
	map<T, map<U, map<V, W> > > m_map;
public:
	map_amx(const T& key1, const U& key2, const V& key3, const W& val)
	{
		map<V, W> m1;
		m1[key3] = val;
		map<U, map<V, W> > m2;
		m2[key2] = m1;
		m_map[key1] = m2;
		m1.clear();
		m2.clear();
	}

	map_amx<T, U, V, W>& operator()(const T& key1, const U& key2, const V& key3, const W& val)
	{
		map<V, W> m1;
		m1[key3] = val;
		map<U, map<V, W> > m2;
		m2[key2] = m1;
		m_map[key1] = m2;
		m1.clear();
		m2.clear();
		return *this;
	}

	operator std::map<T, map<U, map<V, W> > >()
	{
		return m_map;
	}

	string find(const T& key1, const U& key2, const V& key3)
	{
		return m_map.find(key1).find(key2).find(key2);
	}
};

//static map<int, map<int, map<int, string> > > mapAMXCommand = map_amx<int, int, int, string>(1, 0, 1, "CTL_SYSTEM_ON");
