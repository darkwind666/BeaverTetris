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

	std::vector <  std::vector<GamePositionOnBoard> > getExplosionsZones();
	std::vector<GamePositionOnBoard> getExplosionsZonesWithXPosition(int xPosition);
	GamePositionOnBoard getExplosionPositionFromMeteorX(int xPosition);
	int getExplosionHeightFromExplosionX(int xPosition);
	std::vector<GamePositionOnBoard> getExplosionZoneOnPosition(GamePositionOnBoard aExplosionPosition);
	void fillExplosionZoneRowWithPosition(std::vector<GamePositionOnBoard> &explosionZone, int row, GamePositionOnBoard aExplosionPosition);
	void reduceLivesInExplosionsZones(std::vector <  std::vector<GamePositionOnBoard> > aExplosionsZones);
	void sendMassegeToDelegateWithExplosionsZones(std::vector <  std::vector<GamePositionOnBoard> > aExplosionsZones);
	void sendDelegateExplosionPositions(std::vector <  std::vector<GamePositionOnBoard> > aExplosionsZones);
	void sendDelegateKilledTetraminos(std::vector <  std::vector<GamePositionOnBoard> > aExplosionsZones);
	void removeKilledTetraminosFromExplosionsZones(std::vector <  std::vector<GamePositionOnBoard> > aExplosionsZones);

	void makeOperationWithZonesPositions(std::vector <  std::vector<GamePositionOnBoard> > &aZones, OperationWithPosition aOperation);
	void makeOperationWithZonePositions(std::vector<GamePositionOnBoard> &aPositions, OperationWithPosition aOperation);

};

