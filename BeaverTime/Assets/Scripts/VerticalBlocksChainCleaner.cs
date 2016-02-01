using UnityEngine;
using System.Collections.Generic;

public class VerticalBlocksChainCleaner : MonoBehaviour {

    public int maxBlocksChainCount;
    List<GameObject> _blocksForDeleting;
    GameBoard _gameBoard;

    public VerticalBlocksChainCleaner(int aMaxBlocksChainCount, List<GameObject> aBlocksForDeleting)
    {
        maxBlocksChainCount = aMaxBlocksChainCount;
        _blocksForDeleting = aBlocksForDeleting;
        _gameBoard = ServicesLocator.getServiceForKey(typeof(GameBoard).Name) as GameBoard;
    }

    public void cleanVerticalChains()
    {
        for (int xIndex = 0; xIndex < _gameBoard.getBoardWidth(); xIndex++)
        {
            cleanBlockChainsInVertical(xIndex);
        }
    }

    void cleanBlockChainsInVertical(int aVerticalIndex)
    {

        int startChainIndex = 0;
        int currentBlockType = 0;
        int currentChainCount = 0;
        for (int yIndex = 0; yIndex < _gameBoard.getBoardHeight(); yIndex++)
        {
            GameObject block = _gameBoard.getObjectForXY(aVerticalIndex, yIndex);

            if (block)
            {
                int blockType = block.GetComponent<BlockType>().blockType;
                if (currentBlockType != blockType)
                {
                    if (currentChainCount > maxBlocksChainCount)
                    {
                        removeVerticalChainFromFirstIndexToSecond(aVerticalIndex, startChainIndex, (yIndex - 1));
                    }
                    currentChainCount = 1;
                    currentBlockType = blockType;
                    startChainIndex = yIndex;
                }
                else
                {
                    currentChainCount++;
                    if (yIndex == (_gameBoard.getBoardHeight() - 1))
                    {
                        if (currentChainCount > maxBlocksChainCount)
                        {
                            removeVerticalChainFromFirstIndexToSecond(aVerticalIndex, startChainIndex, yIndex);
                        }
                    }
                }

            }
            else
            {
                if (currentChainCount > maxBlocksChainCount)
                {
                    removeVerticalChainFromFirstIndexToSecond(aVerticalIndex, startChainIndex, (yIndex - 1));
                }
                currentChainCount = 0;
                currentBlockType = 0;
                startChainIndex = 0;
            }

        }
    }

    void removeVerticalChainFromFirstIndexToSecond(int aXIndex, int aFirstYIndex, int aSecondYIndex)
    {

        for (int yIndex = aFirstYIndex; yIndex <= aSecondYIndex; yIndex++)
        {
            GameObject block = _gameBoard.getObjectForXY(aXIndex, yIndex);
            _blocksForDeleting.Add(block);
            _gameBoard.deleteObjectForXY(aXIndex, yIndex);
        }

    }

}
