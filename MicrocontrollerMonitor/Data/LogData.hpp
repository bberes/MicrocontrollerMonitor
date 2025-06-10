#pragma once
#ifndef Data__LogData__hpp
#define Data__LogData__hpp

// #Standard
#include <vector>

// #Qt
#include <QString>

// #Kernel
#include "Utilities\Observer.hpp"


class LogData final : public Utilities::Subject {
public:
	void Append (const QString& logLine);
	void Store  () const;

private:
	std::vector<QString> lines;
};


class LogDataObserver : public Utilities::Observer {
protected:
	explicit LogDataObserver (LogData& logData);

private:
	friend LogData;
	virtual void LineAdded (const QString& logLine) = 0;
};


#endif