#pragma once
class ResourcesLoader
{
public:
	ResourcesLoader(void);
	virtual ~ResourcesLoader(void);

	virtual void loadResources() = 0;

};

