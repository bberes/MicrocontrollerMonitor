#pragma once
#ifndef Data__RecorderTypes__hpp
#define Data__RecorderTypes__hpp

// #Qt
#include <QObject>

// #Communication
#include "Data\MemoryReference.hpp"
#include "ResponseListeners.hpp"


class StateListener final
	: public QObject
	, public Communication::ReadVariablesResponseListener
{
	Q_OBJECT

public:
	explicit StateListener (const Communication::MemoryRef& mr);

signals:
	void			StateReceived	(bool ready);

private:
	virtual void	Update			(const Communication::Variables& variables) override;

public:
	const Communication::MemoryRef mr;
};


class WriteListener final
	: public QObject
	, public Communication::WriteVariablesResponseListener
{
	Q_OBJECT

signals:
	void			WriteFinished	();

private:
	virtual void	Update			() override;
};


class ParamsListener final
	: public QObject
	, public Communication::ReadVariablesResponseListener
{
	Q_OBJECT

signals:
	void			ParamsReceived	();

private:
	virtual void	Update			(const Communication::Variables& variables) override;

public:
	Communication::MemoryRefs refs;
};


class ArrayListener final
	: public QObject
	, public Communication::ReadArrayResponseListener
{
	Q_OBJECT

signals:
	void			DataReceived	();

public:
	void			Init			();

private:
	virtual void	Update			(const std::vector<UInt32>& variables) override;

public:
	static constexpr UInt32	StartAddr	= 0x00000010; // #ToDo: find its origin
	static constexpr UInt16	LengthUnit	= 0x01F0;     // #ToDo: find its origin
	static constexpr UInt16	LengthLast	= 0x0080;     // #ToDo: find its origin
	static constexpr UInt16	size		= 4u * LengthUnit + LengthLast; // #ToDo: why?

	std::vector<UInt32>		data;
	size_t					iter = 0u;
	UInt32					addr = StartAddr;
	UInt16					len  = LengthUnit;
};


#endif