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
#define GLOBAL_WORD_UNKNOW					"我不了解這句話的意思"

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
