#pragma once

class GameSystemInterface;

class GameManager
{
public:
	GameManager(void);
	~GameManager(void);

	void setUpdateInterval(float aUpdateInterval);

	void update(float deltaTime);
	void pause();
	void start();

	void addSystem(GameSystemInterface aSystem);



};

