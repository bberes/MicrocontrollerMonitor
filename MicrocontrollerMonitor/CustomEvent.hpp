#pragma once
#ifndef MM__CustomEvent__hpp
#define MM__CustomEvent__hpp

// #Standard
#include <functional>

// #Qt
#include <QEvent>


class CustomEvent final : public QEvent {
public:
	explicit CustomEvent (const std::function<void ()>& process);
	virtual ~CustomEvent () override;

	void					Process	();

private:
	virtual CustomEvent*	clone	() const override;

private:
	std::function<void ()> process;
};


#endif