#ifndef _FRAG_ENGINE_APP_H_
#define _FRAG_ENGINE_APP_H_ 1

class App {
	friend class Engine;
public:
	
	virtual ~App() = default;

	virtual void start() = 0;

	virtual void update() = 0;

private:
};

#endif