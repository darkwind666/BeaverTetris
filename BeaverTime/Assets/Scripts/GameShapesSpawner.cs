using UnityEngine;
using System.Collections;

public class GameShapesSpawner : MonoBehaviour {

    public GameObject[] shapes;
    public GameObject[] gameBlocksPatterns;

    GameObject _currentShape;
    bool _currentShapeAvailable;

	void Start () {
        createNewShape();
    }

    public void createNewShape()
    {
        int shapeIndex = Random.Range(0, shapes.Length);
        _currentShape = Instantiate(shapes[shapeIndex], transform.position, Quaternion.identity) as GameObject;
        _currentShape.transform.SetParent(transform.parent, false);
        _currentShape.transform.position = transform.position;
        _currentShapeAvailable = true;
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

}

