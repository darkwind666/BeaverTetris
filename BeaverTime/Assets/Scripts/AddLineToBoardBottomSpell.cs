using UnityEngine;
using System.Collections;
using DG.Tweening;

public class AddLineToBoardBottomSpell : MonoBehaviour {

    GameBoard _gameBoard;
    public float moveUpBlocksAnimationDuration;
    public float blockAppearanceDuration;

    public GameObject gameShapesSpawnerContainer;
    GameObject[] gameBlocksPatterns;
    public GameObject gameBoardPad;

    void Start ()
    {
        _gameBoard = ServicesLocator.getServiceForKey(typeof(GameBoard).Name) as GameBoard;
        GameShapesSpawner gameShapesSpawner = gameShapesSpawnerContainer.GetComponent<GameShapesSpawner>();
        gameBlocksPatterns = gameShapesSpawner.gameBlocksPatterns;
    }

    void Update() {

    }

    public void castSpell()
    {
        _gameBoard.gameBoardLocked = true;
        Sequence explosionSequence = DOTween.Sequence();
        explosionSequence.AppendCallback(() => raiseAllBlocksOnGameBoard());
        explosionSequence.AppendInterval(moveUpBlocksAnimationDuration);
        addfillEmptyButtomLineActionToSequence(explosionSequence);
        explosionSequence.AppendCallback(() => _gameBoard.gameBoardLocked = false);
    }

    void raiseAllBlocksOnGameBoard()
    {
        for(int yIndex = _gameBoard.getBoardHeight() - 1; yIndex >= 0; yIndex--)
        {
            raiseLine(yIndex);
        }
    }

    void raiseLine(int aLineIndex)
    {
        for(int xIndex = 0; xIndex < _gameBoard.getBoardWidth(); xIndex++)
        {
            GameObject block = _gameBoard.getObjectForXY(xIndex, aLineIndex);
            if(block)
            {
                raiseBlockForXY(xIndex, aLineIndex);
            }
        }
    }

    void raiseBlockForXY(int xIndex, int yIndex)
    {
        GameObject block = _gameBoard.getObjectForXY(xIndex, yIndex);

        _gameBoard.deleteObjectForXY(xIndex, yIndex);

        if (yIndex >= _gameBoard.getBoardHeight() - 1)
        {
            GameObject.Destroy(block);
        }
        else
        {
            _gameBoard.setObjectForXY(block, xIndex, yIndex + 1);
            Vector3 newBlockPosition = block.transform.localPosition + new Vector3(0, 1, 0);
            block.transform.DOLocalMove(newBlockPosition, moveUpBlocksAnimationDuration);
        }

    }

    void addfillEmptyButtomLineActionToSequence(Sequence aSequence)
    {
        int emptyBlockXIndex = Random.Range(0, _gameBoard.getBoardWidth() - 1);
        setBlockInBoardBottomExceptIndex(aSequence, emptyBlockXIndex);
    }

    void setBlockInBoardBottomExceptIndex(Sequence aSequence, int aExceptXIndex)
    {
        for(int xIdex = 0; xIdex < _gameBoard.getBoardWidth(); xIdex++)
        {
            if(xIdex != aExceptXIndex)
            {
                addShowBlockToAnimationOnXPosition(aSequence, xIdex);
            }
        }
    }

    void addShowBlockToAnimationOnXPosition(Sequence aSequence, int xIdex)
    {
        int randomIndex = Random.Range(0, gameBlocksPatterns.Length);

        Vector3 blockPosition = new Vector3(xIdex, 0, 0);
        Vector3 blockGlobalPosition = gameBoardPad.transform.TransformPoint(blockPosition);

        GameObject block = GameObject.Instantiate(gameBlocksPatterns[randomIndex], blockGlobalPosition, Quaternion.identity) as GameObject;
        Vector3 blockScale = block.transform.localScale;
        block.transform.localScale = new Vector3(0, 0, 0);
        block.transform.parent = gameBoardPad.transform;

        aSequence.AppendCallback(() => _gameBoard.setObjectForXY(block, (int)blockPosition.x, (int)blockPosition.y));
        aSequence.Append(block.transform.DOScale(blockScale, blockAppearanceDuration));
    }

}
