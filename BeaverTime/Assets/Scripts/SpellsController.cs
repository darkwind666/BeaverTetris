using UnityEngine;
using System.Collections;
using DG.Tweening;

public class SpellsController : MonoBehaviour {

    public GameObject shapesControllerContainer;
    GameShapesSpawner _shapesController;

    public GameObject shapesSpeedControllerContainer;
    PlayerInputController _shapesSpeedController;

    public GameObject meteorParticle;
    GameBoard _gameBoard;
    Vector3 _startMeteorPosition;

    public float meteorSpeed;


    void Start () {

        _shapesController = shapesControllerContainer.GetComponent<GameShapesSpawner>();
        _shapesSpeedController = shapesSpeedControllerContainer.GetComponent<PlayerInputController>();
        _gameBoard = ServicesLocator.getServiceForKey(typeof(GameBoard).Name) as GameBoard;
        meteorParticle.SetActive(true);
        _startMeteorPosition = meteorParticle.transform.position;

    }
	
	void Update () {
	


	}

    public void removeCurrentShapeSpell()
    {
        _gameBoard.gameBoardLocked = true;
        Sequence explosionSequence = DOTween.Sequence();

        Vector3 endMeteorPoint = getMeteorEndPointForDeleteCurrentShape();
        float meteorDuration = Vector3.Distance(endMeteorPoint, _startMeteorPosition) * meteorSpeed / 60;

        explosionSequence.Append(meteorParticle.transform.DOMove(endMeteorPoint, meteorDuration));
        explosionSequence.AppendCallback(() => showBlockExplosionsInCurrentShape());
        explosionSequence.AppendInterval( getExplosionDuration() );
        explosionSequence.AppendCallback(() => destroyCurrentShape());
        explosionSequence.AppendCallback(() => meteorParticle.transform.position = _startMeteorPosition);
        explosionSequence.AppendCallback(() => _gameBoard.gameBoardLocked = false);
    }

    Vector3 getMeteorEndPointForDeleteCurrentShape()
    {
        GameObject shape = _shapesController.currentShape();
        Vector3 shapePosition = shape.transform.localPosition;
        Vector3 shapeCenterPosition = new Vector3(shapePosition.x + 1, shapePosition.y + 1, shapePosition.z);
        GameObject shapeParent = shape.transform.parent.gameObject;
        Vector3 shapeCenterPositionInWorldSpace = shapeParent.transform.TransformPoint(shapeCenterPosition);
        return shapeCenterPositionInWorldSpace;
    }

    float getExplosionDuration()
    {
        GameObject shape = _shapesController.currentShape();
        GameObject block = shape.transform.GetChild(0).gameObject;
        ParticleSystem particle = block.GetComponent<ParticleSystem>();
        float explosionDutation = particle.startLifetime;
        return explosionDutation;
    }

    void showBlockExplosionsInCurrentShape()
    {
        GameObject shape = _shapesController.currentShape();
        foreach (Transform child in shape.transform)
        {
            GameObject block = child.gameObject;
            ParticleSystem particle = block.GetComponent<ParticleSystem>();
            particle.Clear();
            particle.Play();
        }
    }

    void destroyCurrentShape()
    {
        GameObject currentShape = _shapesController.currentShape();
        _shapesSpeedController.setStandardShapeSpeed();
        Object.Destroy(currentShape);
        _shapesController.createNewShape();
    }

}
