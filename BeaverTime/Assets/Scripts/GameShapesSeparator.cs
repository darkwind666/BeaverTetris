using UnityEngine;
using System.Collections.Generic;
using System;

public class GameShapesSeparator {

    GameBoard _separatedDetails;
    GameBoard _mainGameBoard;

    Dictionary<Direction, Func<Vector3, Vector3> > _waveAlgoritmDirections;

    enum Direction { kTopDirection, kRightDirection, kBottomDirection, kLeftDirection };

    public GameShapesSeparator()
    {
        _mainGameBoard = ServicesLocator.getServiceForKey(typeof(GameBoard).Name) as GameBoard;
        _separatedDetails = new GameBoard(_mainGameBoard.getShapeSideInBlocks());
        setupWaveAlgoritmDirections();
    }


    void setupWaveAlgoritmDirections()
    {
        _waveAlgoritmDirections = new Dictionary<Direction, Func<Vector3, Vector3>>();
        _waveAlgoritmDirections.Add(Direction.kTopDirection, (Vector3 pos) => { return new Vector3(pos.x, pos.y + 1, pos.z); });
        _waveAlgoritmDirections.Add(Direction.kRightDirection, (Vector3 pos) => { return new Vector3(pos.x + 1, pos.y, pos.z); });
        _waveAlgoritmDirections.Add(Direction.kBottomDirection, (Vector3 pos) => { return new Vector3(pos.x, pos.y - 1, pos.z); });
        _waveAlgoritmDirections.Add(Direction.kLeftDirection, (Vector3 pos) => { return new Vector3(pos.x - 1, pos.y, pos.z); });
    }


    public List< List<GameObject> > getBlockShapesOnGameBoard()
    {
        _separatedDetails.cleanGameBoard();

        List<List<GameObject>> blockShapes = new List<List<GameObject>>();

        for(int yIndex = 0; yIndex < _mainGameBoard.getBoardHeight(); yIndex++)
        {
            setAvailableDetailsFromGameBoardRowInCollection(yIndex, blockShapes);
        }

        return blockShapes;
    }

    void setAvailableDetailsFromGameBoardRowInCollection(int aRow, List< List<GameObject> > shapesInGameBoard)
    {
        for (int xIndex = 0; xIndex < _mainGameBoard.getBoardWidth(); xIndex++)
        {
            if(checkDetailOnPositionXY(xIndex, aRow))
            {
                List<GameObject> shape = getDetailFromStartPosition(xIndex, aRow);
                shapesInGameBoard.Add(shape);
                setShapesInExtractedDetailsData(shape);
            }
        }
    }

    bool checkDetailOnPositionXY(int xPosition, int yPosition)
    {
        GameObject tetraminoInBoard = _mainGameBoard.getObjectForXY(xPosition, yPosition);
        GameObject tetraminoInExtractedDetailsData = _separatedDetails.getObjectForXY(xPosition, yPosition);
        return (tetraminoInExtractedDetailsData == null) && (tetraminoInBoard != null);
    }

    List<GameObject> getDetailFromStartPosition(int xPosition, int yPosition)
    {
        List<GameObject> shape = new List<GameObject>();
        Vector3 startPosition = new Vector3(xPosition, yPosition, 0);
        fillBlocksShapeWithPosition(shape, startPosition);
        return shape;
    }

    void fillBlocksShapeWithPosition(List<GameObject> aShape, Vector3 aStartPosition)
    {
        if (aShape.Count == 0)
        {
            GameObject blockInBoard = _mainGameBoard.getObjectForXY((int)aStartPosition.x, (int)aStartPosition.y);
            aShape.Add(blockInBoard);
            goToNewDirection(aShape, aStartPosition);
        }
        else
        {
            continueFillingTetraminoChainWithPosition(aShape, aStartPosition);
        }
    }

    void goToNewDirection(List<GameObject> aShape, Vector3 aStartPosition)
    {

        foreach(Direction direction in Enum.GetValues(typeof(Direction)))
        {
            Func<Vector3, Vector3> positionForDirectionMaker = _waveAlgoritmDirections[direction];
            Vector3 newTetraminoPosition = positionForDirectionMaker(aStartPosition);
            fillBlocksShapeWithPosition(aShape, newTetraminoPosition);
        }

    }

    void continueFillingTetraminoChainWithPosition(List<GameObject> aShape, Vector3 aStartPosition)
    {
        if (_mainGameBoard.checkPositionInBoard(aStartPosition))
        {
            if (nextChainPartOnPosition(aShape, aStartPosition))
            {
                GameObject blockInBoard = _mainGameBoard.getObjectForXY((int)aStartPosition.x, (int)aStartPosition.y);
                aShape.Add(blockInBoard);
                goToNewDirection(aShape, aStartPosition);
            }
        }
    }

    bool nextChainPartOnPosition(List<GameObject> aShape, Vector3 aStartPosition)
    {
        bool nextChainPart = true;
        GameObject tetraminoInBoard = _mainGameBoard.getObjectForXY((int)aStartPosition.x, (int)aStartPosition.y);

        if (tetraminoInBoard)
        {
            GameObject lastChainElement = aShape[0];
            bool blockInChainYet = aShape.Contains(tetraminoInBoard);
            int lastTetraminoType = lastChainElement.GetComponent<BlockType>().blockType;
            int tetraminoInBoardType = tetraminoInBoard.GetComponent<BlockType>().blockType;

            nextChainPart = ( (lastTetraminoType == tetraminoInBoardType && blockInChainYet == false) );
        }
        else
        {
            nextChainPart = false;
        }

        return nextChainPart;
    }

    void setShapesInExtractedDetailsData(List<GameObject> aShape)
    {
        foreach(GameObject block in aShape)
        {
            Vector3 blockPosition = block.transform.localPosition;
            int xPosition = (int)Mathf.Round(blockPosition.x);
            int yPosition = (int)Mathf.Round(blockPosition.y);
            _separatedDetails.setObjectForXY(block, xPosition, yPosition);
        }
    }

}
