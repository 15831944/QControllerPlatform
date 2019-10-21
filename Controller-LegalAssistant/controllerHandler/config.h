/*
 * config.h
 *
 *  Created on: 2017年4月19日
 *      Author: Jugo
 */

#pragma once


//==================================== 字詞屬性定義 ========================================//
#define UNKNOW						0x00000000
#define SUBJECT						0x00000001		// 主詞
#define VERB						0x00000002		// 動詞
#define NOUN						0x00000003		// 名詞
#define ADJECTIVE					0x00000004		// 形容詞


//==================================== 固定回復 ===========================================//
#define RESP_WORD_UNKNOW0					"我不了解這句話的意思"
#define RESP_WORD_UNKNOW1                   "抱歉喔，我最近才開始正在努力學習中，還沒有辦法回答您詢問的問題"
#define RESP_WORD_UNKNOW2                   "我還需要再多吃一點資料才能理解您說的，所以先請旁邊的工作人員協助您解惑喔"
#define RESP_WORD_UNKNOW3                   "不要為難我嘛，我還在成長階段還沒有學到那，所以先請旁邊的工作人員協助您解惑喔"
#define RESP_WORD_END1                      " 若還想深入了解可以在詢問園區人員喔"
#define RESP_WORD_END2                      " 這樣的回覆還有哪裡不了解嗎"
#define RESP_WORD_END3                      " 有不理解的地方嗎 還有什麼想問的嗎"
#define RESP_WORD_DATABASE_ERROR            "目前資料庫更新中，請稍後再試"



//=========================== Semantic ==========================================//
/**
 *  主詞
 */
#define SUBJECT_I					1
#define SUBJECT_YOU					2
#define SUBJECT_HE					3

/**
 *  動詞
 */
#define VERB_LISTEN					1
#define VERB_SAY					2
#define VERB_READ					3
#define VERB_WRITE					4
#define VERB_REQUEST				5

//============================== MySQL ======================================//
#define DB_IP                       "127.0.0.1"
#define DB_DATABASE                 "legal"
#define DB_USER                     "legal"
#define DB_PASSWORD                 "legal"
#define DB_CONN_TIMEOUT             "5"
#define SQL_QUERY_INTENT            "SELECT intent,keyword,table_name FROM "
#define SQL_QUERY_INTENT_ORDER      " ORDER BY length(keyword) DESC"
#define SQL_QUERY_REPLIES           "SELECT reply FROM replies WHERE intent_id = "
#define SQL_INSERT_UNKNOW_START     "INSERT INTO legal.unknow (input) VALUES ('"
#define SQL_INSERT_UNKNOW_END       "')"

