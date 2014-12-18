#pragma once
class GameSystemInterface
{
public:

	GameSystemInterface(void);
	~GameSystemInterface(void);

	virtual void updateSystem(float deltaTime) = 0;
};

