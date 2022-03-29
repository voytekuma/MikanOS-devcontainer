/**
 * @file logger.hpp
 *
 * カーネルロガー
 */

#pragma once

enum LogLevel {
    kError = 3,
    kWarn  = 4,
    kInfo  = 6,
    kDebug = 7,
};

/** グローバルなログ優先度のしきい値を変更する */
void SetLogLevel(LogLevel level);

/** ログを指定された優先度で記録する */
int Log(LogLevel level, const char* format, ...);