#pragma once

#include "SpellInterface.h"
#include "ServiceInterface.h"
#include "FuctionsTypedefs.h"

class GameBoard;
class FirestormSpellDelegate;

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

	GamePositionOnBoard getExplosionPositionFromMeteorX(int xPosition);
	int getExplosionHeightFromExplosionX(int xPosition);
	std::vector<GamePositionOnBoard> getExplosionZoneOnPosition(GamePositionOnBoard aExplosionPosition);
	void fillExplosionZoneRowWithPosition(std::vector<GamePositionOnBoard> &explosionZone, int row, GamePositionOnBoard aExplosionPosition);
	void reduceLivesInExplosionsZone(std::vector<GamePositionOnBoard> aExplosionsZone);
	void sendMassegeToDelegateWithExplosionsZoneAndPosition(std::vector<GamePositionOnBoard> aExplosionsZone, GamePositionOnBoard aExplosionPosition);
	void sendDelegateExplosionPositions(std::vector<GamePositionOnBoard> aExplosionsZone);
	void sendDelegateKilledTetraminos(std::vector<GamePositionOnBoard> aExplosionsZone);
	void removeKilledTetraminosFromExplosionsZone(std::vector<GamePositionOnBoard> aExplosionsZone);

	void makeOperationWithZonePositions(std::vector<GamePositionOnBoard> &aPositions, OperationWithPosition aOperation);

};

