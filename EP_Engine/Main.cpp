#include "EP_Engine_PCH.h"

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif

#include "SDL.h"
#include "EP_Engine.h"

int main(int, char*[]) {
	ep::EP_Engine engine;
	engine.Run();
    return 0; 
}