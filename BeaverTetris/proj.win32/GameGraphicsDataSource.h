#pragma once

class string;

class GameGraphicsDataSource
{
public:
	GameGraphicsDataSource(void);
	~GameGraphicsDataSource(void);

	string getInitialGraphic();
	int getGraphicCount();
	string getGraphicForIndex(int aIndex);


};
