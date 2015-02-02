#include "DetailsFromBoardDataSource.h"
#include "GameBoard.h"
#include "Tetramino.h"

using namespace std;

DetailsFromBoardDataSource::DetailsFromBoardDataSource(GameBoard *aGameBoard)
{
	_gameBoard = aGameBoard;
	_waveAlgoritmdirections = makeWaveAlgoritmDirections();
}

DetailsFromBoardDataSource::~DetailsFromBoardDataSource(void)
{
}

map<DirectionType, function<void(GamePositionOnBoard&)> > DetailsFromBoardDataSource::makeWaveAlgoritmDirections()
{
	map<DirectionType, function<void(GamePositionOnBoard&)> > waveAlgoritmDirections;

	waveAlgoritmDirections[kTopDirection] = [](GamePositionOnBoard &aPositon){aPositon.yPosition = aPositon.yPosition + 1;};
	waveAlgoritmDirections[kRightDirection] = [](GamePositionOnBoard &aPositon){aPositon.xPosition = aPositon.xPosition + 1;};
	waveAlgoritmDirections[kBottomDirection] = [](GamePositionOnBoard &aPositon){aPositon.yPosition = aPositon.yPosition - 1;};
	waveAlgoritmDirections[kLeftDirection] = [](GamePositionOnBoard &aPositon){aPositon.xPosition = aPositon.xPosition - 1;};

	return waveAlgoritmDirections;
}

vector < vector <GamePositionOnBoard> > DetailsFromBoardDataSource::getTetraminoDetailsInGame()
{
	_extractedDetailsData = new GameBoard(_gameBoard->getGameBoardWidth() ,_gameBoard->getGameBoardHeight());
	vector < vector <GamePositionOnBoard> > detailsInGameBoard = getAvailableDetailsFromGameBoard();
	_extractedDetailsData->deleteAllTetraminos();
	delete _extractedDetailsData;
	return detailsInGameBoard;
}

vector < vector <GamePositionOnBoard> > DetailsFromBoardDataSource::getAvailableDetailsFromGameBoard()
{
	vector < vector <GamePositionOnBoard> > detailsInGameBoard;
	for (int yIndex = 0; yIndex < _gameBoard->getGameBoardHeight(); yIndex++)
	{
		setAvailableDetailsFromGameBoardRowInCollection(yIndex, &detailsInGameBoard);
	}
	return detailsInGameBoard;
}

void DetailsFromBoardDataSource::setAvailableDetailsFromGameBoardRowInCollection(int aRow, vector < vector <GamePositionOnBoard> > *detailsInGameBoard)
{
	for (int xIndex = 0; xIndex < _gameBoard->getGameBoardWidth(); xIndex++)
	{
		if (checkDetailOnPositionXY(xIndex, aRow))
		{
			vector <GamePositionOnBoard> detailElements = getDetailFromStartPosition(xIndex, aRow);
			detailsInGameBoard->push_back(detailElements);
			setDetailsInExtractedDetailsData(detailElements);
		}
	}
}

bool DetailsFromBoardDataSource::checkDetailOnPositionXY(int xPosition, int yPosition)
{
	Tetramino *tetraminoInBoard = _gameBoard->getTetraminoForXYposition(xPosition, yPosition);
	Tetramino *tetraminoInExtractedDetailsData = _extractedDetailsData->getTetraminoForXYposition(xPosition, yPosition);
	TetraminoType tetraminoInBoardType = tetraminoInBoard->getTetraminoType();
	TetraminoType tetraminoExtractedDetailsDataType = tetraminoInExtractedDetailsData->getTetraminoType();
	return (tetraminoInBoardType > kTetraminoEmpty) && (tetraminoExtractedDetailsDataType == kTetraminoEmpty);
}

vector <GamePositionOnBoard> DetailsFromBoardDataSource::getDetailFromStartPosition(int xPosition, int yPosition)
{
	vector <GamePositionOnBoard> *tetraminoChain = new vector <GamePositionOnBoard>();
	GamePositionOnBoard startPosition;
	startPosition.xPosition = xPosition;
	startPosition.yPosition = yPosition;
	fillTetraminoChainWithPosition(tetraminoChain, startPosition);
	vector <GamePositionOnBoard> tetraminoDetailElements = getDetailElementsFromChain(tetraminoChain);
	return tetraminoDetailElements;
}

void DetailsFromBoardDataSource::fillTetraminoChainWithPosition(std::vector <GamePositionOnBoard> *aTetraminoChain, GamePositionOnBoard aPosition)
{
	if (aTetraminoChain->empty())
	{
		aTetraminoChain->push_back(aPosition);
		goToNewDirection(aTetraminoChain, aPosition);
	}
	else
	{
		continueFillingTetraminoChainWithPosition(aTetraminoChain, aPosition);
	}
}

void DetailsFromBoardDataSource::continueFillingTetraminoChainWithPosition(vector <GamePositionOnBoard> *aTetraminoChain, GamePositionOnBoard aPosition)
{
	if (positionInGameBoard(aPosition))
	{
		if (nextChainPartOnPosition(aTetraminoChain, aPosition))
		{
			aTetraminoChain->push_back(aPosition);
			goToNewDirection(aTetraminoChain, aPosition);
		}
	}
}

bool DetailsFromBoardDataSource::positionInGameBoard(GamePositionOnBoard aPosition)
{
	bool inWidthInterval = (aPosition.xPosition >= 0 && aPosition.xPosition < _gameBoard->getGameBoardWidth());
	bool inHeightInterval = (aPosition.yPosition >= 0 && aPosition.yPosition < _gameBoard->getGameBoardHeight());
	return (inWidthInterval == true && inHeightInterval == true);
}

bool DetailsFromBoardDataSource::nextChainPartOnPosition(vector <GamePositionOnBoard> *aTetraminoChain, GamePositionOnBoard aPosition)
{
	Tetramino *tetraminoInBoard = _gameBoard->getTetraminoForXYposition(aPosition.xPosition, aPosition.yPosition);
	GamePositionOnBoard lastChainElement = aTetraminoChain->back();
	Tetramino *lastTetramino = _gameBoard->getTetraminoForXYposition(lastChainElement.xPosition, lastChainElement.yPosition);
	bool positionInChainYet = checkPositionInChain(aPosition, aTetraminoChain);
	TetraminoType lastTetraminoType = lastTetramino->getTetraminoType();
	TetraminoType tetraminoInBoardType = tetraminoInBoard->getTetraminoType();
	return (lastTetraminoType == tetraminoInBoardType && positionInChainYet == false);
}

bool DetailsFromBoardDataSource::checkPositionInChain(GamePositionOnBoard aPosition, std::vector <GamePositionOnBoard> *aTetraminoChain)
{
	bool inChain = false;
	vector <GamePositionOnBoard>::iterator tetraminoChainIterator;
	for (tetraminoChainIterator = aTetraminoChain->begin(); tetraminoChainIterator != aTetraminoChain->end(); tetraminoChainIterator++)
	{
		GamePositionOnBoard chainElement = *tetraminoChainIterator;
		bool positionInChain = (chainElement.xPosition == aPosition.xPosition && chainElement.yPosition == aPosition.yPosition);
		if (positionInChain)
		{
			inChain = true;
			break;
		}
	}
	return inChain;
}

void DetailsFromBoardDataSource::goToNewDirection(vector <GamePositionOnBoard> *aTetraminoChain, GamePositionOnBoard aPosition)
{
	for (int direction = kTopDirection; direction < kEndDirection; direction++)
	{
		DirectionType directionType = (DirectionType)direction;
		GamePositionOnBoard newTetraminoPosition = aPosition;
		function<void(GamePositionOnBoard)> positionForDirectionMaker = _waveAlgoritmdirections[directionType];
		positionForDirectionMaker(newTetraminoPosition);
		fillTetraminoChainWithPosition(aTetraminoChain, newTetraminoPosition);
	}
}

vector <GamePositionOnBoard> DetailsFromBoardDataSource::getDetailElementsFromChain(vector <GamePositionOnBoard> *aTetraminoChain)
{
	vector <GamePositionOnBoard> tetraminoDetailElements;
	vector <GamePositionOnBoard>::iterator tetraminoChainIterator;
	for (tetraminoChainIterator = aTetraminoChain->begin(); tetraminoChainIterator != aTetraminoChain->end(); tetraminoChainIterator++)
	{
		GamePositionOnBoard chainElement = *tetraminoChainIterator;
		tetraminoDetailElements.push_back(chainElement);
	}
	return tetraminoDetailElements;
}

void DetailsFromBoardDataSource::setDetailsInExtractedDetailsData(vector <GamePositionOnBoard> aDetailElements)
{
	vector <GamePositionOnBoard>::iterator detailElementsIterator;
	for (detailElementsIterator = aDetailElements.begin(); detailElementsIterator != aDetailElements.end(); detailElementsIterator++)
	{
		GamePositionOnBoard detailPosition = *detailElementsIterator;
		Tetramino *tetraminoMarkInExtractedDetailsData = new Tetramino(kTetraminoBlack);
		_extractedDetailsData->setTetraminoXYposition(tetraminoMarkInExtractedDetailsData, detailPosition.xPosition, detailPosition.yPosition);
	}
}