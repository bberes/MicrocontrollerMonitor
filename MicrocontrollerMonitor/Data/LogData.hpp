#pragma once
#ifndef Data__LogData__hpp
#define Data__LogData__hpp

// #Qt
#include <QString>

// #Kernel
#include "Types\Vector.hpp"
#include "Utilities\Observer.hpp"


class LogData final : public Utilities::Subject {
public:
	void Append (const QString& logLine);
	void Store  () const;

private:
	Vector<QString> lines;
};


class LogDataObserver : public Utilities::Observer {
protected:
	explicit LogDataObserver (LogData& logData);

private:
	friend LogData;
	virtual void LineAdded (const QString& logLine) = 0;
};


#endif