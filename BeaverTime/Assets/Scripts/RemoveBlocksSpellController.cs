using UnityEngine;
using System.Collections.Generic;
using DG.Tweening;

public class RemoveBlocksSpellController : MonoBehaviour, ISpell {

    public GameObject shapesControllerContainer;
    GameShapesSpawner _shapesController;

    GameBoard _gameBoard;

    public int randomExplosionsCount;

    public GameObject removeBlocksConditionContainer;
    RemoveBlocksCondition _removeBlocksCondition;

    void Start () {

        _gameBoard = ServicesLocator.getServiceForKey(typeof(GameBoard).Name) as GameBoard;
        _shapesController = shapesControllerContainer.GetComponent<GameShapesSpawner>();
        _removeBlocksCondition = removeBlocksConditionContainer.GetComponent<RemoveBlocksCondition>();
        SpellCountdownController countdownController = GetComponent<SpellCountdownController>();
        randomExplosionsCount = countdownController.getSpellCount();
    }

    void Update () {
	
	}

    public void useSpell()
    {
        List<GameObject> blocksInGameBoard = getAvailableBlocksInGameBoard();

        if (blocksInGameBoard.Count > randomExplosionsCount)
        {
            _gameBoard.gameBoardLocked = true;
            List<GameObject> blocksForRemoving = getBlocksForRemovingFromAvailableBlocks(blocksInGameBoard);
            Sequence explosionSequence = DOTween.Sequence();
            explosionSequence.AppendCallback(() => removeBlocksInGameBoard(blocksForRemoving));
            explosionSequence.AppendCallback(() => showExplosionsInBlocks(blocksForRemoving));
            explosionSequence.AppendInterval(getExplosionDuration());
            explosionSequence.AppendCallback(() => removeBlocks(blocksForRemoving));
            explosionSequence.AppendCallback(() => _gameBoard.gameBoardLocked = false);
        }

    }

    List<GameObject> getAvailableBlocksInGameBoard()
    {
        List<GameObject> blocksInGameBoard = new List<GameObject>();

        for (int heightIndex = 0; heightIndex < _gameBoard.getBoardHeight(); heightIndex++)
        {
            for (int widthIndex = 0; widthIndex < _gameBoard.getBoardWidth(); widthIndex++)
            {
                GameObject block = _gameBoard.getObjectForXY(widthIndex, heightIndex);
                if (block)
                {
                    blocksInGameBoard.Add(block);
                }
            }
        }

        return blocksInGameBoard;
    }

    List<GameObject> getBlocksForRemovingFromAvailableBlocks(List<GameObject> aAvailableBlocks)
    {
        List<GameObject> blocksForRemoving = new List<GameObject>();

        for (int explosionIndex = 0; explosionIndex < randomExplosionsCount; explosionIndex++)
        {
            int randomExplosionIndex = Random.Range(0, aAvailableBlocks.Count);
            GameObject block = aAvailableBlocks[randomExplosionIndex];
            blocksForRemoving.Add(block);
            aAvailableBlocks.RemoveAt(randomExplosionIndex);
        }

        return blocksForRemoving;
    }

    void removeBlocksInGameBoard(List<GameObject> aBlocksForRemoving)
    {
        foreach (GameObject block in aBlocksForRemoving)
        {
            BlockLiveController blockLives = block.GetComponent<BlockLiveController>();
            blockLives.removeOneBlockLive();
            if (blockLives.blockLivesCount <= 0)
            {
                int xPosition = (int)Mathf.Round(block.transform.localPosition.x);
                int yPosition = (int)Mathf.Round(block.transform.localPosition.y);
                _gameBoard.deleteObjectForXY(xPosition, yPosition);
            }
        }
    }

    void showExplosionsInBlocks(List<GameObject> aBlocksForRemoving)
    {
        foreach (GameObject block in aBlocksForRemoving)
        {
            ParticleSystem particle = block.GetComponent<ParticleSystem>();
            particle.Clear();
            particle.Play();
        }
    }

    float getExplosionDuration()
    {
        GameObject shape = _shapesController.currentShape();
        GameObject block = shape.transform.GetChild(0).gameObject;
        ParticleSystem particle = block.GetComponent<ParticleSystem>();
        float explosionDutation = particle.startLifetime;
        return explosionDutation;
    }

    void removeBlocks(List<GameObject> aBlocksForRemoving)
    {
        foreach (GameObject block in aBlocksForRemoving)
        {
            BlockLiveController blockLives = block.GetComponent<BlockLiveController>();
            if (blockLives.blockLivesCount <= 0)
            {
                BlockType type = block.GetComponent<BlockType>();
                _removeBlocksCondition.blockWasRemoovedWithType(type.blockType);
                Object.Destroy(block);
            }
        }
    }

}

