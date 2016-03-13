using UnityEngine;
using System.Collections.Generic;

public class GameShapesSpawner : MonoBehaviour {

    public GameObject[] shapes;
    public GameObject[] gameBlocksPatterns;

    GameObject _currentShape;
    bool _currentShapeAvailable;

    int _fallenShapesCount;
    int _availableBlocksTypes;

    void Start () {
        _fallenShapesCount = 0;
        _availableBlocksTypes = getAvailableBlocksTypes();
        createNewShape();
    }

    int getAvailableBlocksTypes()
    {
        LevelDataStore levelDataStore = ServicesLocator.getServiceForKey(typeof(LevelDataStore).Name) as LevelDataStore;
        GameLevel currentLevel = levelDataStore.getCurrentLevelData();
        int availableBlocksTypes = currentLevel.availableBlockTypesCount;
        return availableBlocksTypes;
    }

    public void createNewShape()
    {
        _currentShape = createStandardShape();
        _currentShapeAvailable = true;
        _fallenShapesCount++;
    }

    public GameObject createStandardShape()
    {
        int shapeIndex = Random.Range(0, shapes.Length);

        GameObject shape = Instantiate(shapes[shapeIndex], transform.position, Quaternion.identity) as GameObject;

        fillShapeWithBlocks(shape);

        shape.transform.SetParent(transform.parent, false);
        shape.transform.position = transform.position;

        return shape;
    }

    void fillShapeWithBlocks(GameObject aShape)
    {
        int blockTypeIndex = Random.Range(0, _availableBlocksTypes + 1);

        List<GameObject> children = new List<GameObject>();

        foreach (Transform child in aShape.transform)
        {
            children.Add(child.gameObject);
        }

        foreach (GameObject child in children)
        {
            GameObject block = Instantiate(gameBlocksPatterns[blockTypeIndex], child.transform.position, Quaternion.identity) as GameObject;
            block.transform.localPosition = child.transform.localPosition;
            block.transform.SetParent(child.transform.parent, false);
        }

        foreach (GameObject child in children)
        {
            Destroy(child);
        }
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

