#include "FillingGapInBoardAnimationController.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "FillingGapInBoardSystem.h"
#include "GameBoardController.h"
#include "TetraminoColorsDataSource.h"


FillingGapInBoardAnimationController::FillingGapInBoardAnimationController(GameBoardController *aGameBoardController)
{
	_gameBoardController = aGameBoardController;
	FillingGapInBoardSystem *fillingGapInBoardSystem = (FillingGapInBoardSystem*)ServiceLocator::getServiceForKey(fillingGapInBoardSystemKey);
	fillingGapInBoardSystem->setDelegate(this);
	_tetraminoColorsDataSource = new TetraminoColorsDataSource();
}


FillingGapInBoardAnimationController::~FillingGapInBoardAnimationController(void)
{
}

void FillingGapInBoardAnimationController::replaceDetailToPosition(TetraminoDetail *aDetail, GamePositionOnBoard aPosition)
{

}