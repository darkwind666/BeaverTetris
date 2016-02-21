using UnityEngine;
using System.Collections;

public class BlockLiveController : MonoBehaviour {

    public int blockLivesCount;
    public GameObject[] blockLivesPoints;

	void Start () {
	
	}
	
	void Update () {
	
	}

    public void removeOneBlockLive()
    {
        blockLivesCount--;
        if(blockLivesPoints.Length > 0)
        {
            Destroy(blockLivesPoints[blockLivesCount]);
        }

    }

}
