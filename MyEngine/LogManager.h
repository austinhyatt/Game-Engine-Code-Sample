#ifndef LOG_MANAGER_H
#define LOG_MANAGER_H

// System includes.
#include <stdio.h>
#include <map>

// Engine includes.
#include "Manager.h"

// Two-letter acronym for easier access to manager.
#define LM df::LogManager::getInstance()

namespace df {

	const std::string LOGFILE_DEFAULT = "dragonflyLog.txt";

	class LogManager : public Manager {

	private:
		LogManager();                     // Private since a singleton.
		LogManager(LogManager const&);    // Don't allow copy.
		void operator=(LogManager const&);// Don't allow assignment.
		bool m_do_flush;                  // True if flush to disk after write.
		FILE* logFile;                      // Pointer to main logfile.

	public:
		// Get the one and only instance of the LogManager.
		static LogManager& getInstance();

		// Start up LogManager (open main logfile, usually "dragonfly.log").
		// Return 0 if ok, else -1.
		int startUp() override;

		// Shut down LogManager (close all logfiles).
		void shutDown() override;

		// Write to logfile.
		// Supports printf() formatting of strings.
		// Return number of bytes written (excluding prepends), -1 if error.
		int writeLog(const char* fmt, ...) const;
	};

} // end of namespace df
#endif
