#include"renderer/IRenderer.h"

using namespace fragcore;

// TODO relocate to its own file that handles all the compute of Vulkan.
bool ICompute::supportCompute(void) { return true; }
void ICompute::OnInitialization(void) {}
void ICompute::OnDestruction(void) {}