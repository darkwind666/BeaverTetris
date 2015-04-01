#pragma once

#include "SpellInterface.h"
#include "ServiceInterface.h"
#include "FuctionsTypedefs.h"

class GameBoard;
class FirestormSpellDelegate;
class CurrentDetailDataSource;

class FirestromSpell :public SpellInterface, public ServiceInterface
{
public:
	FirestromSpell(void);
	~FirestromSpell(void);

	virtual bool spellAvailable(void);
	virtual void castSpell();

	void setDelegate(FirestormSpellDelegate *aDelegate);

private:

	GameBoard *_gameBoard;
	FirestormSpellDelegate *_delegate;
	int _meteorsCount;
	CurrentDetailDataSource *_currentDetailDataSource;

	GamePositionOnBoard getExplosionPositionFromMeteorX(int xPosition);
	int getExplosionHeightFromExplosionX(int xPosition);
	bool checkExplosionInCurrentDetailWithXYPosition(int xPosition, int yPosition);
	bool checkExplosionInCurrentDetailWithAbsolutePosition(GamePositionOnBoard aPosition);
	bool checkExplosionInBoardWithXYPosition(int xPosition, int yPosition);
	void throwFireballOnPosition(GamePositionOnBoard aExplosionPosition);
	bool explosionInCurrentDetailWithPosition(GamePositionOnBoard aExplosionPosition);
	void removeCurrentDetailWithPosition(GamePositionOnBoard aExplosionPosition);
	std::vector<GamePositionOnBoard> getExplosionZoneOnPosition(GamePositionOnBoard aExplosionPosition);
	void fillExplosionZoneRowWithPosition(std::vector<GamePositionOnBoard> &explosionZone, int row, GamePositionOnBoard aExplosionPosition);
	void reduceLivesInExplosionsZone(std::vector<GamePositionOnBoard> aExplosionsZone);
	void sendMassegeToDelegateToDeleteCurrentDetailWithPosition(GamePositionOnBoard aExplosionPosition);
	void sendMassegeToDelegateWithExplosionsZoneAndPosition(std::vector<GamePositionOnBoard> aExplosionsZone, GamePositionOnBoard aExplosionPosition);
	void sendDelegateExplosionPositions(std::vector<GamePositionOnBoard> aExplosionsZone);
	void sendDelegateKilledTetraminos(std::vector<GamePositionOnBoard> aExplosionsZone);
	void removeKilledTetraminosFromExplosionsZone(std::vector<GamePositionOnBoard> aExplosionsZone);

	void makeOperationWithZonePositions(std::vector<GamePositionOnBoard> &aPositions, OperationWithPosition aOperation);

};

