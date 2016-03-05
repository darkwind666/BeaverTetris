using UnityEngine;
using System.Collections.Generic;
using System;

public class BossMovementController : MonoBehaviour {

    public int bossMovementInterval;
    int _currentUpdateState;
    GameBoard _gameBoard;
    GameObject _savedBlock;

    Dictionary<BossDirection, Func<Vector3, Vector3>> _bossDirections;

    enum BossDirection { kTopDirection, kRightDirection, kBottomDirection, kLeftDirection };

    void Start () {

        _gameBoard = ServicesLocator.getServiceForKey(typeof(GameBoard).Name) as GameBoard;
        setupBossDirections();
        _savedBlock = null;
        _currentUpdateState = 0;

    }

    void setupBossDirections()
    {
        _bossDirections = new Dictionary<BossDirection, Func<Vector3, Vector3>>();
        _bossDirections.Add(BossDirection.kTopDirection, (Vector3 pos) => { return new Vector3(pos.x, pos.y + 1, pos.z); });
        _bossDirections.Add(BossDirection.kRightDirection, (Vector3 pos) => { return new Vector3(pos.x + 1, pos.y, pos.z); });
        _bossDirections.Add(BossDirection.kBottomDirection, (Vector3 pos) => { return new Vector3(pos.x, pos.y - 1, pos.z); });
        _bossDirections.Add(BossDirection.kLeftDirection, (Vector3 pos) => { return new Vector3(pos.x - 1, pos.y, pos.z); });
    }

    void Update () {
        
	}

    public void updateWithGameTime()
    {
        if (_gameBoard.gameBoardLocked == false)
        {
            _currentUpdateState++;

            if (_currentUpdateState >= bossMovementInterval)
            {
                _currentUpdateState = 0;
                Vector3 newBossPosition = getNewBossPosition();
                moveBossToNewPosition(newBossPosition);
            }

        }
    }

    Vector3 getNewBossPosition()
    {
        int randomNumber = UnityEngine.Random.Range(0, (int)BossDirection.kLeftDirection + 1);
        BossDirection bossDirection = (BossDirection)randomNumber;
        Func<Vector3, Vector3> positionForDirectionMaker = _bossDirections[bossDirection];
        Vector3 newBossPosition = positionForDirectionMaker(transform.localPosition);

        while(checkNewBossPosition(newBossPosition) == false)
        {
            randomNumber = UnityEngine.Random.Range(0, (int)BossDirection.kLeftDirection + 1);
            bossDirection = (BossDirection)randomNumber;
            positionForDirectionMaker = _bossDirections[bossDirection];
            newBossPosition = positionForDirectionMaker(transform.localPosition);
        }

        return newBossPosition;
    }

    bool checkNewBossPosition(Vector3 aPosition)
    {
        bool available = true;

        if(_gameBoard.checkPositionInBoard(aPosition) && aPosition.y < _gameBoard.getBoardHeight())
        {
            GameObject block = _gameBoard.getObjectForXY((int)aPosition.x, (int)aPosition.y);
            available = checkBlockType(block);
        }
        else
        {
            available = false;
        }

        return available;
    }

    bool checkBlockType(GameObject block)
    {
        bool available = true;

        if (block)
        {
            BlockType blockTypeOnPosition = block.GetComponent<BlockType>();
            BlockType bossType = gameObject.GetComponent<BlockType>();

            if (blockTypeOnPosition.blockType == bossType.blockType)
            {
                available = false;
            }
        }

        return available;
    }

    void moveBossToNewPosition(Vector3 aPosition)
    {
        _gameBoard.deleteObjectForXY((int)transform.localPosition.x, (int)transform.localPosition.y);

        placeSavedBlockOnBossPosition();
        saveBlockFromNewPosition(aPosition);

        _gameBoard.setObjectForXY(gameObject, (int)aPosition.x, (int)aPosition.y);
        transform.localPosition = new Vector3(aPosition.x, aPosition.y, 0);
    }

    void placeSavedBlockOnBossPosition()
    {
        if (_savedBlock)
        {
            _gameBoard.setObjectForXY(_savedBlock, (int)transform.localPosition.x, (int)transform.localPosition.y);
            _savedBlock.transform.localPosition = new Vector3(transform.localPosition.x, transform.localPosition.y, 0);
            _savedBlock.SetActive(true);
            _savedBlock = null;
        }
    }

    void saveBlockFromNewPosition(Vector3 aPosition)
    {
        GameObject gameBlock = _gameBoard.getObjectForXY((int)aPosition.x, (int)aPosition.y);
        if (gameBlock)
        {
            _savedBlock = gameBlock;
            _savedBlock.SetActive(false);
        }
    }

}
