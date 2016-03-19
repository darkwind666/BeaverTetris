using UnityEngine;
using System.Collections.Generic;
using DG.Tweening;
using System.Linq;

public class FirestormSpellController : MonoBehaviour, ISpell {


    public GameObject[] meteors;
    public int meteorCount;
    public float meteorSpeed;
    public GameObject currentDetailContainer;
    GameShapesSpawner _shapesController;
    public GameObject explosionObject;

    GameBoard _gameBoard;
    float _maxMeteorDuration;
    float _explosionDuration;

    public GameObject removeBlocksConditionContainer;
    RemoveBlocksCondition _removeBlocksCondition;

    void Start () {

        _gameBoard = ServicesLocator.getServiceForKey(typeof(GameBoard).Name) as GameBoard;
        _shapesController = currentDetailContainer.GetComponent<GameShapesSpawner>();
        ParticleSystem particle = explosionObject.GetComponent<ParticleSystem>();
        _explosionDuration = particle.startLifetime;
        _removeBlocksCondition = removeBlocksConditionContainer.GetComponent<RemoveBlocksCondition>();
        SpellCountdownController countdownController = GetComponent<SpellCountdownController>();
        meteorCount = countdownController.getSpellCount();
    }
	
	void Update () {
	
	}

    public void useSpell()
    {
        _gameBoard.gameBoardLocked = true;
        Sequence explosionSequence = DOTween.Sequence();
        explosionSequence.AppendCallback(() => runFirestorm());
        explosionSequence.AppendInterval(_maxMeteorDuration + _explosionDuration);
        explosionSequence.AppendCallback(() => _gameBoard.gameBoardLocked = false);
    }

    void runFirestorm()
    {
        List<GameObject> fireballs = getFireballs();

        foreach(GameObject fireball in fireballs)
        {
            runFireball(fireball);
        }

    }

    List<GameObject> getFireballs()
    {
        List<GameObject> fireballs = new List<GameObject>();
        List<int> meteorIndexes = Enumerable.Range(0, meteors.Length).ToList();

        for(int meteorIndex = 0; meteorIndex < meteorCount; meteorIndex++)
        {
            int randomIndex = Random.Range(0, meteorIndexes.Count());
            int meteorForSpellIndex = meteorIndexes[randomIndex];
            GameObject fireball = meteors[meteorForSpellIndex];
            fireballs.Add(fireball);
            meteorIndexes.RemoveAt(randomIndex);
        }

        return fireballs;
    }

    void runFireball(GameObject aFireball)
    {
        Sequence meteorSequence = DOTween.Sequence();

        Vector3 startMeteorPosition = aFireball.transform.localPosition;
        Vector3 endMeteorPosition = getEndMeteorPosition(aFireball);

        float meteorFlyDuration = Mathf.Abs(startMeteorPosition.y - endMeteorPosition.y) * meteorSpeed / 60;
        setMaxDuration(meteorFlyDuration);

        meteorSequence.Append(aFireball.transform.DOLocalMove(endMeteorPosition, meteorFlyDuration));
        meteorSequence.AppendCallback(() => aFireball.transform.localPosition = startMeteorPosition);
        meteorSequence.AppendCallback(() => destroyBlocksAroundMeteorEndPosition(endMeteorPosition));
    }

    void setMaxDuration(float aMeteorFlyDuration)
    {
        if (aMeteorFlyDuration > _maxMeteorDuration)
        {
            _maxMeteorDuration = aMeteorFlyDuration;
        }
    }

    Vector3 getEndMeteorPosition(GameObject aFireball)
    {
        Vector3 startMeteorPosition = aFireball.transform.localPosition;
        Vector3 finalMeteorPosition = new Vector3(startMeteorPosition.x, 1, startMeteorPosition.z);
        int meteorXPosition = Mathf.RoundToInt(startMeteorPosition.x);
        for (int yIndex = _gameBoard.getBoardHeight() - 1; yIndex >= 0; yIndex--)
        {
            GameObject block = _gameBoard.getObjectForXY(meteorXPosition, yIndex);
            if(block)
            {
                finalMeteorPosition = new Vector3(startMeteorPosition.x, yIndex + 1, startMeteorPosition.z);
                break;
            }
        }

        return finalMeteorPosition;
    }

    void destroyBlocksAroundMeteorEndPosition(Vector3 aEndMeteorPosition)
    {
        int xPosition = Mathf.RoundToInt(aEndMeteorPosition.x);
        int yPosition = Mathf.RoundToInt(aEndMeteorPosition.y);
        destroyBlockOnPositionXY(xPosition - 1, yPosition + 1);
        destroyBlockOnPositionXY(xPosition, yPosition + 1);
        destroyBlockOnPositionXY(xPosition + 1, yPosition + 1);
        destroyBlockOnPositionXY(xPosition - 1, yPosition);
        destroyBlockOnPositionXY(xPosition, yPosition);
        destroyBlockOnPositionXY(xPosition + 1, yPosition);
        destroyBlockOnPositionXY(xPosition - 1, yPosition - 1);
        destroyBlockOnPositionXY(xPosition, yPosition - 1);
        destroyBlockOnPositionXY(xPosition + 1, yPosition - 1);
    }

    void destroyBlockOnPositionXY(int xPosition, int yPosition)
    {
        if(_gameBoard.checkPositionInBoard(new Vector3(xPosition, yPosition, 0))  && yPosition < _gameBoard.getBoardHeight())
        {
            GameObject block = getBlockForDestructionForXY(xPosition, yPosition);

            ParticleSystem particle = block.GetComponent<ParticleSystem>();
            particle.Clear();
            particle.Play();

            Sequence explosionSequence = DOTween.Sequence();
            explosionSequence.AppendInterval(particle.startLifetime);
            explosionSequence.AppendCallback(() => tryToRemoveBlockFromScreen(block));

        }
    }

    void tryToRemoveBlockFromScreen(GameObject aBlock)
    {
        if(aBlock)
        {
            BlockLiveController blockLives = aBlock.GetComponent<BlockLiveController>();
            if (blockLives.blockLivesCount <= 0)
            {
                BlockType type = aBlock.GetComponent<BlockType>();
                if (type)
                {
                    _removeBlocksCondition.blockWasRemoovedWithType(type.blockType);
                }

                Destroy(aBlock);
            }
        }
    }

    GameObject getBlockForDestructionForXY(int xPosition, int yPosition)
    {
        GameObject block = _gameBoard.getObjectForXY(xPosition, yPosition);

        if (block)
        {
            BlockLiveController blockLives = block.GetComponent<BlockLiveController>();
            blockLives.removeOneBlockLive();
            if (blockLives.blockLivesCount <= 0)
            {
                _gameBoard.deleteObjectForXY(xPosition, yPosition);
            }
        }
        else
        {
            Vector3 explosionPosition = transform.TransformPoint(new Vector3(xPosition, yPosition, 0));
            block = Instantiate(explosionObject, explosionPosition, Quaternion.identity) as GameObject;
        }

        return block;
    }

}
