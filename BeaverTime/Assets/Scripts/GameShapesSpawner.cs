using UnityEngine;
using System.Collections;

public class GameShapesSpawner : MonoBehaviour {

    public GameObject[] shapes;
    public GameObject[] gameBlocksPatterns;

    GameObject _currentShape;
    bool _currentShapeAvailable;

    int _fallenShapesCount;

    void Start () {
        _fallenShapesCount = 0;
        createNewShape();
    }

    public void createNewShape()
    {
        int shapeIndex = Random.Range(0, shapes.Length);
        _currentShape = Instantiate(shapes[shapeIndex], transform.position, Quaternion.identity) as GameObject;
        _currentShape.transform.SetParent(transform.parent, false);
        _currentShape.transform.position = transform.position;
        _currentShapeAvailable = true;
        _fallenShapesCount++;
    }

    void Update () {
	
	}

    public bool currentShapeAvailable()
    {
        return _currentShapeAvailable;
    }

    public GameObject currentShape()
    {
        return _currentShape;
    }

    public int getFallenShapesCount()
    {
        return _fallenShapesCount;
    }

}

