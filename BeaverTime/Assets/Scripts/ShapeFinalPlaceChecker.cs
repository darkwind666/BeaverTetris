using UnityEngine;
using System.Collections;

public class ShapeFinalPlaceChecker : MonoBehaviour {

    public GameObject currentShapeContainer;
    public int destroyInterval;

    GameShapesSpawner _shapesSpawner;
    float _previousYPosition;
    int destroyTime;

	void Start () {

        _shapesSpawner = currentShapeContainer.GetComponent<GameShapesSpawner>();
        resetPositionAndDestroyTime();
        
    }

    void resetPositionAndDestroyTime()
    {
        _previousYPosition = _shapesSpawner.currentShape().transform.position.y;
        destroyTime = 0;
    }

    void Update () {

    }

    void FixedUpdate()
    {

        GameObject currentShape = _shapesSpawner.currentShape();
        float shapePositionDifference = Mathf.Abs(_previousYPosition - currentShape.transform.position.y);
        _previousYPosition = currentShape.transform.position.y;
        if (shapePositionDifference <= 0.001f)
        {
            destroyTime++;
            if (destroyTime >= destroyInterval)
            {
                _shapesSpawner.createNewShape();
                resetPositionAndDestroyTime();
            }

        }

    }

}
