using UnityEngine;
using System.Collections;

public class PlayerInputController : MonoBehaviour {

    public GameObject shapesContainer;
    GameShapesSpawner _shapesController;

	void Start () {

        _shapesController = shapesContainer.GetComponent<GameShapesSpawner>();

    }
	
	void Update () {
	
	}

    void FixedUpdate()
    {

        if (_shapesController.currentShapeAvailable())
        {
            checkUserInput();
        }

    }

    void checkUserInput()
    {
        /*
        GameObject currentShape = _shapesController.currentShape();
        Rigidbody2D shapeBody = currentShape.GetComponent<Rigidbody2D>();

        Debug.Log(shapeBody.velocity);

        if (Input.GetKeyDown(KeyCode.RightArrow))
        {
            Vector2 direction = new Vector2(20f, 0f);
            shapeBody.position = shapeBody.position + direction * Time.fixedDeltaTime;
            Debug.Log(Time.fixedDeltaTime);
        }
        else if (Input.GetKeyDown(KeyCode.LeftArrow))
        {
            Vector2 direction = new Vector2(20f, 0f);
            shapeBody.position = shapeBody.position - direction * Time.fixedDeltaTime;
            Debug.Log(Time.fixedDeltaTime);
        }
        else if (Input.GetKeyDown(KeyCode.UpArrow))
        {
            shapeBody.MoveRotation(shapeBody.rotation + 90);
            Debug.Log(Time.fixedDeltaTime);
        }
        else
        {
            Vector2 upDirection = new Vector2(0f, 1f);
            shapeBody.position = shapeBody.position - upDirection * Time.fixedDeltaTime;
        }
        */

    }

}
