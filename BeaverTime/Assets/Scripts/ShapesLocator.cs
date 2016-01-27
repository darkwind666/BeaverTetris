using UnityEngine;
using System.Collections.Generic;

public class ShapesLocator {

    GameBoard _gameBoard;
	
    public ShapesLocator()
    {
        _gameBoard = ServicesLocator.getServiceForKey(typeof(GameBoard).Name) as GameBoard;
    }

    public void writeShapeInBoard(GameObject aShape)
    {
        List<Transform> children = new List<Transform>();

        foreach (Transform child in aShape.transform)
        {
            Vector3 childPositionOnBoard = getShapePositionOnBoard(child);
            int positionX = (int)Mathf.Round(childPositionOnBoard.x);
            int positionY = (int)Mathf.Round(childPositionOnBoard.y);
            _gameBoard.setObjectForXY(child.gameObject, positionX, positionY);
            children.Add(child);
        }

        foreach (Transform child in children)
        {
            child.parent = aShape.transform.parent;
        }

        Object.Destroy(aShape);

    }

    Vector3 getShapePositionOnBoard(Transform aChild)
    {
        Transform shapeParent = aChild.parent;
        Transform gameBoardPad = shapeParent.transform.parent;

        Vector3 shapePositionInWorldSpace = aChild.position;
        Vector3 shapePositionOnBoard = gameBoardPad.InverseTransformPoint(shapePositionInWorldSpace);
        return shapePositionOnBoard;
    }

}
