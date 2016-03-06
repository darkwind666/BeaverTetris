using UnityEngine;
using System.Collections.Generic;
using DG.Tweening;

public class BlocksChainCleaner : MonoBehaviour {

    public int maxBlocksChainCount;
    public GameObject animationTimeContainer;
    GameBoard _gameBoard;
    float _moveTimeForOneBlock;
    List<GameObject> _blocksForDeleting;

    HorizontalBlocksChainCleaner _horizontalCleaner;
    VerticalBlocksChainCleaner _verticalCleaner;

    public GameObject removeBlocksConditionContainer;
    RemoveBlocksCondition _removeBlocksCondition;

    void Start () {

        _blocksForDeleting = new List<GameObject>();
        _horizontalCleaner = new HorizontalBlocksChainCleaner(maxBlocksChainCount, _blocksForDeleting);
        _verticalCleaner = new VerticalBlocksChainCleaner(maxBlocksChainCount, _blocksForDeleting);
        _moveTimeForOneBlock = animationTimeContainer.GetComponent<GameBoardCleaner>().moveTimeForOneBlock;
        _gameBoard = ServicesLocator.getServiceForKey(typeof(GameBoard).Name) as GameBoard;
        _removeBlocksCondition = removeBlocksConditionContainer.GetComponent<RemoveBlocksCondition>();

    }
	
	void Update () {

        if(_gameBoard.gameBoardLocked == false)
        {
            _blocksForDeleting.Clear();
            cleanBlockChains();
            if (_blocksForDeleting.Count > 0)
            {
                _gameBoard.gameBoardLocked = true;
                Sequence explosionSequence = DOTween.Sequence();

                GameObject block = _blocksForDeleting[0];
                ParticleSystem particle = block.GetComponent<ParticleSystem>();
                float explosionDutation = particle.startLifetime;

                explosionSequence.AppendCallback(() => showExplosionsInBlocks(_blocksForDeleting));
                explosionSequence.AppendInterval(explosionDutation);
                explosionSequence.AppendCallback(() => deleteBlocks(_blocksForDeleting));
                explosionSequence.AppendCallback(() => _gameBoard.gameBoardLocked = false);
            }
            
        }

    }

    void cleanBlockChains()
    {
        _horizontalCleaner.cleanHorizontalChains();
        _verticalCleaner.cleanVerticalChains();
    }

    void showExplosionsInBlocks(List<GameObject> aBlocks)
    {
        foreach (GameObject block in aBlocks)
        {
            ParticleSystem particle = block.GetComponent<ParticleSystem>();
            particle.Clear();
            particle.Play();
        }
    }

    void deleteBlocks(List<GameObject> aBlocks)
    {
        foreach (GameObject block in aBlocks)
        {
            BlockType type = block.GetComponent<BlockType>();
            _removeBlocksCondition.blockWasRemoovedWithType(type.blockType);
            Destroy(block);
        }

    }

}
