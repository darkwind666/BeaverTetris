using UnityEngine;
using System.Collections;

public class FixVelocity : MonoBehaviour {

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {

    }

    void FixedUpdate()
    {

        Rigidbody2D body = GetComponent<Rigidbody2D>();
        body.velocity = new Vector2(0.0f, 0.0f);

    }

}
