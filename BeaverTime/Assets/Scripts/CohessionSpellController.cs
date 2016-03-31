using UnityEngine;
using System.Collections.Generic;
using DG.Tweening;

public class CohessionSpellController : MonoBehaviour, ISpell {

    GameBoard _gameBoard;
    int blockCountForCohession;
    public float blockAppearanceDuration;

    public GameShapesSpawner gameShapesSpawner;
    GameObject[] gameBlocksPatterns;

    public GameObject gameBoardPad;

    void Start () {

        _gameBoard = ServicesLocator.getServiceForKey(typeof(GameBoard).Name) as GameBoard;
        gameBlocksPatterns = gameShapesSpawner.gameBlocksPatterns;
        SpellCountdownController countdownController = GetComponent<SpellCountdownController>();
        blockCountForCohession = countdownController.getSpellCount();
    }
	
	void Update () {
	
	}

    public void useSpell()
    {
        List<Vector3> newBlockPositions = getNewBlocksPositions();
        generateNewBlocksOnPositions(newBlockPositions);
    }

    List<Vector3> getNewBlocksPositions()
    {
        List<Vector3> newBlockPositions = new List<Vector3>();

        bool keepGoing = true;

        for(int yIndex = 0; yIndex < _gameBoard.getBoardHeight() && keepGoing; yIndex++)
        {
            for(int xIndex = 0; xIndex < _gameBoard.getBoardWidth() && keepGoing; xIndex++)
            {
                GameObject block = _gameBoard.getObjectForXY(xIndex, yIndex);

                if(block == null)
                {
                    newBlockPositions.Add(new Vector3(xIndex, yIndex, 0));
                }

                if(newBlockPositions.Count >= blockCountForCohession)
                {
                    keepGoing = false;
                }

            }
        }

        return newBlockPositions;
    }

    void generateNewBlocksOnPositions(List<Vector3> aBlocksPositions)
    {
        _gameBoard.gameBoardLocked = true;
        Sequence explosionSequence = DOTween.Sequence();
        
        foreach(Vector3 blockPosition in aBlocksPositions)
        {
            GameObject block = generateBlockOnPositions(blockPosition);
            Vector3 blockScale = block.transform.localScale;
            block.transform.localScale = new Vector3(0, 0, 0);
            block.transform.parent = gameBoardPad.transform;
            explosionSequence.Append(block.transform.DOScale(blockScale, blockAppearanceDuration));
        }

        explosionSequence.AppendCallback(() => _gameBoard.gameBoardLocked = false);
    }

    GameObject generateBlockOnPositions(Vector3 aPosition)
    {
        Vector3 explosionPosition = gameBoardPad.transform.TransformPoint(new Vector3(aPosition.x, aPosition.y, 0));
        int randomIndex = Random.Range(0, gameBlocksPatterns.Length);
        GameObject block = Instantiate(gameBlocksPatterns[randomIndex], explosionPosition, Quaternion.identity) as GameObject;
        _gameBoard.setObjectForXY(block, (int)aPosition.x, (int)aPosition.y);
        return block;
    }

}
