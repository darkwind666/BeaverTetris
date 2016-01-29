﻿using UnityEngine;
using System.Collections.Generic;
using System.Collections;

public class GameBoardCleaner : MonoBehaviour {

    GameBoard _gameBoard;

    void Start () {

        _gameBoard = ServicesLocator.getServiceForKey(typeof(GameBoard).Name) as GameBoard;

    }
	
	void Update () {

        List<int> linesForDeliting = getLinesForDeliting();

        if(linesForDeliting.Count > 0 && _gameBoard.gameBoardLocked == false)
        {
            StartCoroutine(removeFilledLines(linesForDeliting));
        }

    }

    List<int> getLinesForDeliting()
    {
        List<int> linesForDeliting = new List<int>();

        for (int yIndex = 0; yIndex < _gameBoard.getBoardHeight(); yIndex++)
        {
            if (lineFilledForYIndex(yIndex))
            {
                linesForDeliting.Add(yIndex);
            }
        }

        return linesForDeliting;
    }

    bool lineFilledForYIndex(int yIndex)
    {
        bool empty = true;

        for (int xIndex = 0; xIndex < _gameBoard.getBoardWidth(); xIndex++)
        {
            if (_gameBoard.getObjectForXY(xIndex, yIndex) == null)
            {
                empty = false;
                break;
            }
        }

        return empty;
    }

    IEnumerator removeFilledLines(List<int> aLines)
    {
        _gameBoard.gameBoardLocked = true;
        foreach (int aLineIndex in aLines)
        {
            showExplosionEffectInLineForIndex(aLineIndex);
        }

        GameObject block = _gameBoard.getObjectForXY(0, aLines[0]);
        ParticleSystem particle = block.GetComponent<ParticleSystem>();
        float explosionDutation = particle.startLifetime;

        yield return new WaitForSeconds(explosionDutation);
        foreach (int aLineIndex in aLines)
        {
            deleteLineForIndex(aLineIndex);
        }

        aLines.Sort();

        moveLinesFromLineIndex(aLines[0]);
        _gameBoard.gameBoardLocked = false;


    }

    void showExplosionEffectInLineForIndex(int aLineIndex)
    {
        for (int xIndex = 0; xIndex < _gameBoard.getBoardWidth(); xIndex++)
        {
            GameObject block = _gameBoard.getObjectForXY(xIndex, aLineIndex);
            ParticleSystem particle = block.GetComponent<ParticleSystem>();
            particle.Clear();
            particle.Play();
        }
    }

    void deleteLineForIndex(int aLineIndex)
    {
        for (int xIndex = 0; xIndex < _gameBoard.getBoardWidth(); xIndex++)
        {
            GameObject block = _gameBoard.getObjectForXY(xIndex, aLineIndex);
            Destroy(block);
            _gameBoard.deleteObjectForXY(xIndex, aLineIndex);
        }
    }

    void moveLinesFromLineIndex(int aIndex)
    {
        for (int yIndex = aIndex + 1; yIndex < _gameBoard.getBoardHeight(); yIndex++)
        {
            if (lineEmptyForYIndex(yIndex) == false)
            {
                moveLineDown(yIndex);
            }
        }
    }

    bool lineEmptyForYIndex(int yIndex)
    {
        bool empty = true;

        for (int xIndex = 0; xIndex < _gameBoard.getBoardWidth(); xIndex++)
        {
            if (_gameBoard.getObjectForXY(xIndex, yIndex))
            {
                empty = false;
                break;
            }
        }

        return empty;
    }

    void moveLineDown(int aLineIndex)
    {
        for (int yIndex = aLineIndex - 1; yIndex >= 0; yIndex--)
        {
            if (lineEmptyForYIndex(yIndex) == false)
            {
                replaceLineFromFirstIndexToSecondIndex(aLineIndex, yIndex + 1);
                break;
            }

            if (yIndex == 0)
            {
                replaceLineFromFirstIndexToSecondIndex(aLineIndex, yIndex);
                break;
            }

        }
    }

    void replaceLineFromFirstIndexToSecondIndex(int aFirstIndex, int aSecondIndex)
    {
        for (int xIndex = 0; xIndex < _gameBoard.getBoardWidth(); xIndex++)
        {
            if(_gameBoard.getObjectForXY(xIndex, aFirstIndex))
            {
                GameObject block = _gameBoard.getObjectForXY(xIndex, aFirstIndex);
                _gameBoard.deleteObjectForXY(xIndex, aFirstIndex);
                _gameBoard.setObjectForXY(block, xIndex, aSecondIndex);
                block.transform.localPosition = new Vector3(block.transform.localPosition.x, aSecondIndex, block.transform.localPosition.z);
            }
        }
    }

}
