#pragma once
class PlayerStatusDelegateInterface
{
public:
	PlayerStatusDelegateInterface(void);
	virtual ~PlayerStatusDelegateInterface(void);

	virtual void showPlayerStatus() = 0;

};

