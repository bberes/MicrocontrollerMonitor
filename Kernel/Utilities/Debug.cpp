#include "Debug.hpp"


#ifdef DEBUG_MODE
void HandleInspection (const char* condition, const char* file, int line, const char* info/* = nullptr*/)
{
}


void HandleAssertion (const char* condition, const char* file, int line, const char* info/* = nullptr*/)
{
	TODO;
}
#endif