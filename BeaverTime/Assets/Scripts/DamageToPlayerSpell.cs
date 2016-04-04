using UnityEngine;
using System.Collections.Generic;
using DG.Tweening;

public class DamageToPlayerSpell : MonoBehaviour {

    public int minNonEmptyBlocksCount;
    public AudioSource removeBlockSoundEffect;
    GameBoard _gameBoard;

    void Start () {

        _gameBoard = ServicesLocator.getServiceForKey(typeof(GameBoard).Name) as GameBoard;

    }
	
	void Update () {
	
	}

    public void castSpell()
    {
        List<int> linesWithUnpeacefulCount = getLinesWithUnpeacefulCount();
        if (linesWithUnpeacefulCount.Count > 0)
        {
            removeBlocksInLines(linesWithUnpeacefulCount);
        }
    }

    List<int> getLinesWithUnpeacefulCount()
    {
        List<int> linesWithUnpeacefulCount = new List<int>();

        for (int yIndex = 0; yIndex < _gameBoard.getBoardHeight(); yIndex++)
        {
            List<GameObject> blocksInLine = getAvailableBlocksInLine(yIndex);
            if(blocksInLine.Count > minNonEmptyBlocksCount)
            {
                linesWithUnpeacefulCount.Add(yIndex);
            }
        }

        return linesWithUnpeacefulCount;
    }

    List<GameObject> getAvailableBlocksInLine(int aLineIndex)
    {
        List<GameObject> availableBlocksInLine = new List<GameObject>();
        for(int xIndex = 0; xIndex < _gameBoard.getBoardWidth(); xIndex++)
        {
            if(availableBlockToDestroyForXY(xIndex, aLineIndex))
            {
                GameObject block = _gameBoard.getObjectForXY(xIndex, aLineIndex);
                availableBlocksInLine.Add(block);
            }
        }

        return availableBlocksInLine;
    }

    bool availableBlockToDestroyForXY(int xIndex, int yIndex)
    {
        bool available = false;

        GameObject block = _gameBoard.getObjectForXY(xIndex, yIndex);
        if (block)
        {
            BlockType bossTag = block.GetComponent<BlockType>();
            if (bossTag.boss == false)
            {
                available = true;
            }
        }
        return available;
    }

    void removeBlocksInLines(List<int> aLines)
    {
        removeBlockSoundEffect.Play();

        _gameBoard.gameBoardLocked = true;
        Sequence explosionSequence = DOTween.Sequence();
        explosionSequence.AppendCallback(() => makeExplosionsInLines(aLines));
        explosionSequence.AppendInterval(getExplosionAnimationDurationFromLines(aLines));
        explosionSequence.AppendCallback(() => _gameBoard.gameBoardLocked = false);
    }

    float getExplosionAnimationDurationFromLines(List<int> aLines)
    {
        List<GameObject> blocks = getAvailableBlocksInLine(aLines[0]);
        ParticleSystem particle = blocks[0].GetComponent<ParticleSystem>();
        float explosionAnimationDuration = particle.startLifetime;
        return explosionAnimationDuration;
    }

    void makeExplosionsInLines(List<int> aLines)
    {
        foreach(int lineIndex in aLines)
        {
            makeExplosionInHorizontal(lineIndex);
        }
    }

    void makeExplosionInHorizontal(int lineIndex)
    {
        List<GameObject> blocks = getAvailableBlocksInLine(lineIndex);

        int randomNumber = Random.Range(0, blocks.Count);
        GameObject block = blocks[randomNumber];

        ParticleSystem particle = block.GetComponent<ParticleSystem>();
        particle.Clear();
        particle.Play();

        Sequence explosionSequence = DOTween.Sequence();
        explosionSequence.AppendInterval(particle.startLifetime);
        explosionSequence.AppendCallback(() => tryToRemoveBlockFromScreen(block));
    }

    void tryToRemoveBlockFromScreen(GameObject aBlock)
    {
        BlockLiveController blockLives = aBlock.GetComponent<BlockLiveController>();
        blockLives.removeOneBlockLive();

        if (blockLives.blockLivesCount <= 0)
        {
            int blockXPosition = Mathf.RoundToInt(aBlock.transform.localPosition.x);
            int blockYPosition = Mathf.RoundToInt(aBlock.transform.localPosition.y);
            _gameBoard.deleteObjectForXY(blockXPosition, blockYPosition);
            Destroy(aBlock);
        }
    }

}
