using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class BossLifeCountController : MonoBehaviour {

    public BlockLiveController bossLives;

    Text _bossLivesCount;

	void Start () {

        _bossLivesCount = GetComponent<Text>();

    }

	void Update () {

        _bossLivesCount.text = bossLives.blockLivesCount.ToString();

    }
}
