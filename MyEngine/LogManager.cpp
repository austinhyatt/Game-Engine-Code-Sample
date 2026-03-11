#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdarg.h>

#include "LogManager.h"

df::LogManager::LogManager() {
	setType("logmanager");
	startUp();
	writeLog("LogManager constructed");
}

int df::LogManager::startUp() {
	logFile = fopen(LOGFILE_DEFAULT.c_str(), "w");
	m_do_flush = true; //turn to false after development
	return 0;
}

void df::LogManager::shutDown() {
	writeLog("LogManager Destructed");
	fclose(logFile);
}

df::LogManager& df::LogManager::getInstance() {
	static df::LogManager s_logManager;
	return s_logManager;
}

int df::LogManager::writeLog(const char* fmt, ...) const {
	fprintf(logFile, "Log : ");
	va_list args;
	va_start(args, fmt);
	vfprintf(logFile, fmt, args);
	fprintf(logFile, "\n");
	va_end(args);
	return 0;
}

