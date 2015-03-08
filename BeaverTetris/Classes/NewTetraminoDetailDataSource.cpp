#include "NewTetraminoDetailDataSource.h"
#include "CurrentLevelDataSource.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "Tetramino.h"
#include "TetraminoDetail.h"
#include "TetraminisDetailsFactory.h"
#include "GameHelper.h"
#include "GameDesignConstants.h"
#include "TetraminosFactory.h"
#include <ctime>
#include "stdlib.h"

NewTetraminoDetailDataSource::NewTetraminoDetailDataSource(CurrentLevelDataSource *aCurrentLevelDataSource)
{
	_currentLevelDataSource = aCurrentLevelDataSource;
	_detailsTypesData = TetraminisDetailsFactory::getDetailsTypesData();
	_createdDetailsCount = 0;
	_tetraminosFactory = (TetraminosFactory*)ServiceLocator::getServiceForKey(tetrominosFactoryKey);
}


NewTetraminoDetailDataSource::~NewTetraminoDetailDataSource(void)
{
}

TetraminoDetail* NewTetraminoDetailDataSource::getNewDetail()
{
	NewTetraminoDetailRequest tetraminoDetailRequest = getTetraminoDetailRequest();
	TetraminoDetail *newDetail = getNewDetailWithRequest(tetraminoDetailRequest);
	_createdDetailsCount++;
	return newDetail;
}

NewTetraminoDetailRequest NewTetraminoDetailDataSource::getTetraminoDetailRequest()
{
	TetraminoType tetraminoType = getRandomTetraminoType();
	TetraminoDetailType detailType = getRandomTetraminoDetailType();

	NewTetraminoDetailRequest tetraminoDetailRequest;
	tetraminoDetailRequest.tetraminoDetailType = detailType;
	tetraminoDetailRequest.tetraminoType = tetraminoType;
	return tetraminoDetailRequest;
}

TetraminoType NewTetraminoDetailDataSource::getRandomTetraminoType()
{
	GameLevelInformation currentLevel = _currentLevelDataSource->getCurrentLevelData();
	vector<TetraminoType> availableTetraminos = currentLevel.availableTetraminos;
	int randomTetraminoType = GameHelper::getRandomNumberFromUpInterval(availableTetraminos.size());
	TetraminoType tetraminoType = availableTetraminos[randomTetraminoType];
	return tetraminoType;
}

TetraminoDetailType NewTetraminoDetailDataSource::getRandomTetraminoDetailType()
{
	GameLevelInformation currentLevel = _currentLevelDataSource->getCurrentLevelData();
	vector<TetraminoDetailType> availableTetraminoDetailsType = currentLevel.availableTetraminoDetails;
	int randomDetailType = GameHelper::getRandomNumberFromUpInterval(availableTetraminoDetailsType.size());
	TetraminoDetailType detailType = availableTetraminoDetailsType[randomDetailType];
	return detailType;
}

TetraminoDetail* NewTetraminoDetailDataSource::getNewDetailWithRequest(NewTetraminoDetailRequest aRequest)
{
	TetraminoDetail *newDetail = new TetraminoDetail(standartDetailWidth,standartDetailHeight);
	setInDetailTetraminosWithRequest(newDetail, aRequest);
	setDetailStartPosition(newDetail);
	setDetailRotatebleFlagWithDetailType(newDetail, aRequest.tetraminoDetailType);
	return newDetail;
}

void NewTetraminoDetailDataSource::setInDetailTetraminosWithRequest(TetraminoDetail* aDetail, NewTetraminoDetailRequest aRequest)
{
	aDetail->setDetailTetraminosType(aRequest.tetraminoType);
	TetraminoDetailInformation newDetailInformation = _detailsTypesData[aRequest.tetraminoDetailType];
	aDetail->setDetailForms(newDetailInformation.detailForms);
	for (int yIndex = 0; yIndex < standartDetailHeight; yIndex++)
	{
		setInDetailTetraminosLineWithRequest(aDetail, yIndex, aRequest);
	}
}

void NewTetraminoDetailDataSource::setInDetailTetraminosLineWithRequest(TetraminoDetail* aDetail, int aLineIndex, NewTetraminoDetailRequest aRequest)
{
	TetraminoDetailInformation newDetailInformation = _detailsTypesData[aRequest.tetraminoDetailType];
	vector< vector<int> > detailForm = newDetailInformation.detailForms[0];
	for (int xIndex = 0; xIndex < standartDetailWidth; xIndex++)
	{
		int tetraminoFlag = detailForm[aLineIndex][xIndex];
		Tetramino *tertraminoInDetail = getTetraminoWithFlagAndType(tetraminoFlag, aRequest.tetraminoType);
		aDetail->setTetraminoForXY(tertraminoInDetail, xIndex, aLineIndex);
	}
}

Tetramino* NewTetraminoDetailDataSource::getTetraminoWithFlagAndType(int aTetraminoFlag, TetraminoType aTetraminoType)
{
	Tetramino *tertraminoInDetail;
	if (aTetraminoFlag > 0)
	{
		tertraminoInDetail = _tetraminosFactory->getNewTetraminoWithType(aTetraminoType);
	}
	else
	{
		tertraminoInDetail = _tetraminosFactory->getNewTetraminoWithType(kTetraminoEmpty);
	}
	return tertraminoInDetail;
}

void NewTetraminoDetailDataSource::setDetailStartPosition(TetraminoDetail* aDetail)
{
	GamePositionOnBoard startDetailPosition;
	startDetailPosition.xPosition = tetrisBlocksWidth / 2 - (aDetail->getDetailWidth()) / 2;
	startDetailPosition.yPosition = tetrisBlocksHeight;
	aDetail->setDetailPosition(startDetailPosition);
}

void NewTetraminoDetailDataSource::setDetailRotatebleFlagWithDetailType(TetraminoDetail* aDetail, TetraminoDetailType aTetraminoDetailType)
{
	TetraminoDetailInformation newDetailInformation = _detailsTypesData[aTetraminoDetailType];
	aDetail->setDetailRotatebleFlag(newDetailInformation.rotateble);
}

int NewTetraminoDetailDataSource::getCreatedDetailsCount()
{
	return _createdDetailsCount;
}