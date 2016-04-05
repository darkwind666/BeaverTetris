using UnityEngine;
using System.Collections;
using DG.Tweening;

public class RemoveCurrentShapeSpellController : MonoBehaviour, ISpell
{
    public GameShapesSpawner shapesController;
    public GameSpeedController gameSpeedController;
    public RemoveBlocksCondition removeBlocksCondition;

    public GameObject meteorParticle;
    GameBoard _gameBoard;
    Vector3 _startMeteorPosition;

    public float meteorSpeed;
    public AudioSource removeBlockSoundEffect;
    public AudioSource rocketLaunchSoundEffect;

    GamePlayerDataController _playerData;

    void Start () {

        _gameBoard = ServicesLocator.getServiceForKey(typeof(GameBoard).Name) as GameBoard;
        meteorParticle.SetActive(true);
        _startMeteorPosition = meteorParticle.transform.position;
        _playerData = ServicesLocator.getServiceForKey(typeof(GamePlayerDataController).Name) as GamePlayerDataController;

    }
	
	void Update () {
	
	}

    public bool availableSpell()
    {
        return true;
    }

    public void useSpell()
    {
        rocketLaunchSoundEffect.Play();

        _gameBoard.gameBoardLocked = true;
        Sequence explosionSequence = DOTween.Sequence();

        Vector3 endMeteorPoint = getMeteorEndPointForDeleteCurrentShape();
        float meteorDuration = Vector3.Distance(endMeteorPoint, _startMeteorPosition) * meteorSpeed / 60;

        explosionSequence.Append(meteorParticle.transform.DOMove(endMeteorPoint, meteorDuration));
        explosionSequence.AppendCallback(() => showBlockExplosionsInCurrentShape());
        explosionSequence.AppendInterval(getExplosionDuration());
        explosionSequence.AppendCallback(() => destroyCurrentShape());
        explosionSequence.AppendCallback(() => meteorParticle.transform.position = _startMeteorPosition);
        explosionSequence.AppendCallback(() => _gameBoard.gameBoardLocked = false);
    }

    Vector3 getMeteorEndPointForDeleteCurrentShape()
    {
        GameObject shape = shapesController.currentShape();
        Vector3 shapePosition = shape.transform.localPosition;
        Vector3 shapeCenterPosition = new Vector3(shapePosition.x + 1, shapePosition.y + 1, shapePosition.z);
        GameObject shapeParent = shape.transform.parent.gameObject;
        Vector3 shapeCenterPositionInWorldSpace = shapeParent.transform.TransformPoint(shapeCenterPosition);
        return shapeCenterPositionInWorldSpace;
    }

    float getExplosionDuration()
    {
        GameObject shape = shapesController.currentShape();
        GameObject block = shape.transform.GetChild(0).gameObject;
        ParticleSystem particle = block.GetComponent<ParticleSystem>();
        float explosionDutation = particle.startLifetime;
        return explosionDutation;
    }

    void showBlockExplosionsInCurrentShape()
    {
        removeBlockSoundEffect.Play();
        GameObject shape = shapesController.currentShape();
        foreach (Transform child in shape.transform)
        {
            GameObject block = child.gameObject;
            ParticleSystem particle = block.GetComponent<ParticleSystem>();
            particle.Clear();
            particle.Play();

            BlockType type = block.GetComponent<BlockType>();
            removeBlocksCondition.blockWasRemoovedWithType(type.blockType);
            _playerData.playerScore = _playerData.playerScore + type.blockReward;

        }
    }

    void destroyCurrentShape()
    {
        GameObject currentShape = shapesController.currentShape();
        gameSpeedController.stopShapeAcceleration();
        Object.Destroy(currentShape);
        shapesController.createNewShape();
    }

}
