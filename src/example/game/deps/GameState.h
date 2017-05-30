#include <string>

class GameState
{
public:
	virtual void update() = 0;
	virtual void render() = 0;

	virtual void onEnter() = 0;
	virtual void onExit() = 0;

	virtual std::string getStringID() const = 0;
};
