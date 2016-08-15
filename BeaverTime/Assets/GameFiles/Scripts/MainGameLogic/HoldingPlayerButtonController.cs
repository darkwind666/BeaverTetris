using UnityEngine;
using System.Collections;
using UnityEngine.EventSystems;
using UnityEngine.Events;


public class HoldingPlayerButtonController : MonoBehaviour, IPointerDownHandler, IPointerUpHandler {

	public GameShapesSpawner shapesController;
	public PlayerInputController playerInputController;
	public bool isLeft;

	public int maxTime;
	public int maxClickTime;

	int holdingCurrentTime;
	bool _holding;
	bool _clicked;
	GameBoard _gameBoard;

	// Use this for initialization
	void Start () {
		_gameBoard = ServicesLocator.getServiceForKey(typeof(GameBoard).Name) as GameBoard;
		holdingCurrentTime = 0;
	}
	
	// Update is called once per frame
	void Update () {
	
		if (_holding) 
		{
			holdingCurrentTime++;

			if(holdingCurrentTime >= maxClickTime)
			{
				_clicked = true;
			}

			if(holdingCurrentTime >= maxTime && _clicked == true)
			{
				if (shapesController.currentShapeAvailable() && _gameBoard.gameBoardLocked == false)
				{
					holdingCurrentTime = 0;
					if (isLeft) 
					{
						playerInputController.moveShapeLeft();
					} 
					else 
					{
						playerInputController.moveShapeRight();
					}
				}
			}
		}
	}

	public void OnPointerDown(PointerEventData data)
	{
		holdingCurrentTime = 0;
		_holding = true;
		_clicked = false;
	}

	public void OnPointerUp(PointerEventData data)
	{
		_holding = false;
		_clicked = false;
		holdingCurrentTime = 0;
	}

}
