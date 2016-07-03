using UnityEngine;
using System.Collections.Generic;

public class HorizontalBlocksChainCleaner {

    public int maxBlocksChainCount;
    List<GameObject> _blocksForDeleting;
    GameBoard _gameBoard;

    public HorizontalBlocksChainCleaner(int aMaxBlocksChainCount, List<GameObject> aBlocksForDeleting)
    {
        maxBlocksChainCount = aMaxBlocksChainCount;
        _blocksForDeleting = aBlocksForDeleting;
        _gameBoard = ServicesLocator.getServiceForKey(typeof(GameBoard).Name) as GameBoard;
    }

    public void cleanHorizontalChains()
    {
        for (int yIndex = 0; yIndex < _gameBoard.getBoardHeight(); yIndex++)
        {
            cleanBlockChainsInHorizontal(yIndex);
        }
    }

    void cleanBlockChainsInHorizontal(int aHorizontalIndex)
    {

        int startChainIndex = 0;
        int currentBlockType = 0;
        int currentChainCount = 0;
        for (int xIndex = 0; xIndex < _gameBoard.getBoardWidth(); xIndex++)
        {
            GameObject block = _gameBoard.getObjectForXY(xIndex, aHorizontalIndex);

            if (block)
            {
                int blockType = block.GetComponent<BlockType>().blockType;
                if (currentBlockType != blockType)
                {
                    if (currentChainCount > maxBlocksChainCount)
                    {
                        removeHorizontalChainFromFirstIndexToSecond(aHorizontalIndex, startChainIndex, (xIndex - 1));
                    }
                    currentChainCount = 1;
                    currentBlockType = blockType;
                    startChainIndex = xIndex;
                }
                else
                {
                    currentChainCount++;
                    if (xIndex == (_gameBoard.getBoardWidth() - 1))
                    {
                        if (currentChainCount > maxBlocksChainCount)
                        {
                            removeHorizontalChainFromFirstIndexToSecond(aHorizontalIndex, startChainIndex, xIndex);
                        }
                    }
                }

            }
            else
            {
                if (currentChainCount > maxBlocksChainCount)
                {
                    removeHorizontalChainFromFirstIndexToSecond(aHorizontalIndex, startChainIndex, (xIndex - 1));
                }
                currentChainCount = 0;
                currentBlockType = 0;
                startChainIndex = 0;
            }

        }
    }

    void removeHorizontalChainFromFirstIndexToSecond(int aYIndex, int aFirstXIndex, int aSecondXIndex)
    {

        for (int xIndex = aFirstXIndex; xIndex <= aSecondXIndex; xIndex++)
        {
            GameObject block = _gameBoard.getObjectForXY(xIndex, aYIndex);
            _blocksForDeleting.Add(block);
            _gameBoard.deleteObjectForXY(xIndex, aYIndex);
        }

    }


}
