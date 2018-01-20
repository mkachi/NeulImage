#include <crtdbg.h>
#include "MainLoop.h"
#include "Demo.h"

int main()
{
#if defined(DEBUG) | defined(_DEBUG)
#pragma warning(disable : 4996)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//		_CrtSetBreakAlloc(29784);
	if (AllocConsole())
	{
		freopen("CONIN$", "rb", stdin);
		freopen("CONOUT$", "wb", stdout);
		freopen("CONOUT$", "wb", stderr);
	}
#endif
	MainLoop mainLoop;
	mainLoop.init(new Demo());
	mainLoop.loop();
	return 0;
}