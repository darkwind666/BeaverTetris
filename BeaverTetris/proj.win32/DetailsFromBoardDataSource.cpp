#include "DetailsFromBoardDataSource.h"

using namespace std;

DetailsFromBoardDataSource::DetailsFromBoardDataSource(GameBoard *aGameBoard)
{
	_gameBoard = aGameBoard;
}


DetailsFromBoardDataSource::~DetailsFromBoardDataSource(void)
{
}


vector < vector <GamePositionOnBoard> > DetailsFromBoardDataSource::getTetraminoDetailsInGame()
{

	vector < vector <GamePositionOnBoard> > detailsInGameBoard = vector < vector <GamePositionOnBoard> >();

	GameBoard *extractedDetailsData = new GameBoard(_gameBoard->getGameBoardWidth ,_gameBoard->getGameBoardHeight);

	for (int yIndex = 0; yIndex < _gameBoard->getGameBoardHeight; yIndex++)
	{

		for (int xIndex = 0; xIndex < _gameBoard->getGameBoardWidth; xIndex++)
		{
			Tetramino *tetraminoInBoard = _gameBoard->getTetraminoForXYposition(xIndex, yIndex);
			Tetramino *tetraminoInExtractedDetailsData = extractedDetailsData->getTetraminoForXYposition(xIndex, yIndex);


			if (tetraminoInBoard->getTetraminoType > kTetraminoEmpty && tetraminoInExtractedDetailsData->getTetraminoType = kTetraminoEmpty)
			{

				vector <GamePositionOnBoard> detailElements = getDetailFromStartPosition(xIndex, yIndex);
				detailsInGameBoard.push_back(detailElements);
				setDetailsInExtractedDetailsData(detailElements, extractedDetailsData);
			}

		}

	}
	return detailsInGameBoard;
}

vector <GamePositionOnBoard> DetailsFromBoardDataSource::getDetailFromStartPosition(int xPosition, int yPosition)
{

	vector <GamePositionOnBoard*> *tetraminoChain = new vector <GamePositionOnBoard*>();
	fillTetraminoChainWithPositionXY(tetraminoChain,xPosition, yPosition);

	vector <GamePositionOnBoard> tetraminoDetailElements;

	vector <GamePositionOnBoard*>::iterator tetraminoChainIterator;

	for (tetraminoChainIterator = tetraminoChain->begin; tetraminoChainIterator != tetraminoChain->end; tetraminoChainIterator++)
	{
		GamePositionOnBoard *chainElement = *tetraminoChainIterator;
		tetraminoDetailElements.push_back(*chainElement);
	}

	return tetraminoDetailElements;

}

void DetailsFromBoardDataSource::fillTetraminoChainWithPositionXY(std::vector <GamePositionOnBoard*> *aTetraminoChain, int xPosition, int yPosition)
{

	GamePositionOnBoard tetraminoPosition;
	tetraminoPosition.xPosition = xPosition;
	tetraminoPosition.yPosition = yPosition;

	if (aTetraminoChain->empty)
	{
		GamePositionOnBoard *chainElement = new GamePositionOnBoard;
		chainElement->xPosition = xPosition;
		chainElement->yPosition = yPosition;
		aTetraminoChain->push_back(chainElement);
	}
	else
	{

		if (xPosition >= 0 && xPosition <= _gameBoard->getGameBoardWidth && yPosition >= 0 && yPosition <= _gameBoard->getGameBoardHeight)
		{

			Tetramino *tetraminoInBoard = _gameBoard->getTetraminoForXYposition(xPosition, yPosition);
			GamePositionOnBoard *lastChainElement = aTetraminoChain->back;
			Tetramino *lastTetramino = _gameBoard->getTetraminoForXYposition(lastChainElement->xPosition, lastChainElement->yPosition);
			
			if (lastTetramino->getTetraminoType == tetraminoInBoard->getTetraminoType)
			{
				GamePositionOnBoard *chainElement = new GamePositionOnBoard;
				*chainElement = tetraminoPosition;
				aTetraminoChain->push_back(chainElement);
			}
			else
			{
				return;
			}

		}
		else
		{
			return;
		}

	}

	goToNewDirection(aTetraminoChain, xPosition, yPosition);

}

void DetailsFromBoardDataSource::goToNewDirection(vector <GamePositionOnBoard*> *aTetraminoChain, int xPosition, int yPosition)
{

	for (DirectionType direction = kTopDirection; direction < kEndDirection; direction + 1)
	{

		switch (direction)
		{
		case kTopDirection:
			fillTetraminoChainWithPositionXY(aTetraminoChain, xPosition, yPosition + 1);
			break;
		case kRightDirection:
			fillTetraminoChainWithPositionXY(aTetraminoChain, xPosition + 1, yPosition);
			break;
		case kBottomDirection:
			fillTetraminoChainWithPositionXY(aTetraminoChain, xPosition, yPosition - 1);
			break;
		case kLeftDirection:
			fillTetraminoChainWithPositionXY(aTetraminoChain, xPosition - 1, yPosition);
			break;
		case kEndDirection:
			break;
		default:
			break;
		}
	
	}

}

void DetailsFromBoardDataSource::setDetailsInExtractedDetailsData(vector <GamePositionOnBoard> aDetailElements, GameBoard *aExtractedDetailsData)
{

	vector <GamePositionOnBoard>::iterator detailElementsIterator;

	for (detailElementsIterator = aDetailElements.begin; detailElementsIterator != aDetailElements.end; detailElementsIterator++)
	{
		GamePositionOnBoard detailPosition = *detailElementsIterator;
		Tetramino *tetraminoMarkInExtractedDetailsData = new Tetramino(kTetramino2);
		aExtractedDetailsData->setTetraminoXYposition(tetraminoMarkInExtractedDetailsData, detailPosition.xPosition, detailPosition.yPosition);
	}

}