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
        List<Transform> children = getShapeChildren(aShape);
        replaceChildrenOnGameBoard(children);
        replaceChildrenToShapeParent(children, aShape);
        Object.Destroy(aShape);
    }

    List<Transform> getShapeChildren(GameObject aShape)
    {
        List<Transform> children = new List<Transform>();

        foreach (Transform child in aShape.transform)
        {
            children.Add(child);
        }

        return children;
    }

    void replaceChildrenOnGameBoard(List<Transform>  aChildren)
    {
        foreach (Transform child in aChildren)
        {
            Vector3 childPositionOnBoard = getShapePositionOnBoard(child);
            int positionX = (int)Mathf.Round(childPositionOnBoard.x);
            int positionY = (int)Mathf.Round(childPositionOnBoard.y);
            _gameBoard.setObjectForXY(child.gameObject, positionX, positionY);
        }
    }

    void replaceChildrenToShapeParent(List<Transform> aChildren, GameObject aShape)
    {
        foreach (Transform child in aChildren)
        {
            child.parent = aShape.transform.parent;
        }
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
