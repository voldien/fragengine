#include <App.h>
#include <Engine.h>

using namespace fragengine;

class AppExample : public fragengine::App {
  public:
	virtual void start() override {}

	virtual void update() override {}
};

int main(int argc, const char **argv) {
	AppExample app;
	Engine mainEngine;
	mainEngine.registerApp(app);


	// app.run();
	// Engine::registerModule()
}
