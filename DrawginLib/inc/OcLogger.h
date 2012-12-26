#ifndef OcLogger_h__
#define OcLogger_h__

#include <glog/logging.h>

class OcNullLogger : public google::base::Logger
{
public:
	virtual void Write(bool should_flush, time_t timestamp, const char * message, int length)
	{
	}
	virtual void Flush() {}
	virtual google::uint32 LogSize() { return 0; }
};

class OcLogger
{
	OcLogger() {}
	OcLogger(const OcLogger &) {}
	OcLogger & operator=(const OcLogger&) {}
	google::base::Logger * SetLoggerToNullLogger(int severity)
	{
		google::base::Logger * pOldLogger = google::base::GetLogger(severity);
		google::base::SetLogger(severity, &m_nullLogger);
		google::FlushLogFiles(severity);
		return pOldLogger;
	}

	OcNullLogger m_nullLogger;
public:
	OcLogger(const char * pArg)
	{
        google::InitGoogleLogging(pArg);
		SetLoggerToNullLogger(google::WARNING);
		SetLoggerToNullLogger(google::ERROR);
		SetLoggerToNullLogger(google::FATAL);

        google::SetLogFilenameExtension(".log.");

	}
	virtual ~OcLogger()
	{
		google::ShutdownGoogleLogging();
	}
};

#endif // OcLogger_h__
