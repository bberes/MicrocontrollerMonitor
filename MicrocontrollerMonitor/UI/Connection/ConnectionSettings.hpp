#pragma once
#ifndef UI__ConnectionSettings__hpp
#define UI__ConnectionSettings__hpp

// #Qt
#include <QWidget>

// #Kernel
#include "KernelTypes.hpp"


class ConnectionSettings : public QWidget {
public:
	explicit ConnectionSettings (QWidget* parent);

	virtual QString	GetTypeName	() const = 0;
	virtual bool	Connect		() = 0;
	virtual bool	Disconnect	() = 0;

	virtual bool	LoadState	(DataStream& ds) = 0;		// #TODO Move into an interface class
	virtual bool	StoreState	(DataStream& ds) const = 0;	// #TODO
};


#endif