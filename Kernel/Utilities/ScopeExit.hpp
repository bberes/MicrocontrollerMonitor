#pragma once
#ifndef Kernel__Utilities_ScopeExit__hpp
#define Kernel__Utilities_ScopeExit__hpp


namespace Utilities {

template <typename ExitFunctor>
class [[nodiscard]] ScopeExit final {
public:
	explicit ScopeExit (ExitFunctor&& f);
	explicit ScopeExit (const ExitFunctor& f);
	~ScopeExit ();

	ScopeExit (ScopeExit&&)					= delete;
	ScopeExit (const ScopeExit&)			= delete;
	ScopeExit& operator= (ScopeExit&&)		= delete;
	ScopeExit& operator= (const ScopeExit&)	= delete;

private:
	ExitFunctor functor;
};

}


template <typename ExitFunctor>
inline Utilities::ScopeExit<ExitFunctor>::ScopeExit (ExitFunctor&& f)
	: functor (f)
{
}


template <typename ExitFunctor>
inline Utilities::ScopeExit<ExitFunctor>::ScopeExit (const ExitFunctor& f)
	: functor (f)
{
}


template <typename ExitFunctor>
inline Utilities::ScopeExit<ExitFunctor>::~ScopeExit ()
{
	functor ();
}


#endif