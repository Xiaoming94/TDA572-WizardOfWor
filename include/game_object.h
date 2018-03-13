#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

// GameObject represents objects which moves are drawn
#include <vector>

enum Message { HIT, HIT_BURWOR, GAME_OVER, LEVEL_WIN, NO_MSG, PLAYER_HIT };

class Component;

class GameObject
{
protected:
	std::vector<GameObject*> receivers;
	std::vector<Component*> components;

public:
	double horizontalPosition;
	double verticalPosition;
	bool enabled;

	virtual ~GameObject();

	virtual void Create();
	virtual void AddComponent(Component * component);

	virtual void Init();
	virtual void Update(float dt);
	virtual void Destroy();
	virtual void AddReceiver(GameObject *go);
	virtual void Receive(Message m) {}
	void Send(Message m);
};
#endif // GAME_OBJECT_H
