using UnityEngine;
using System.Collections;
using System;

[Serializable]
public class BeaverTutorialTalk
{
    public string[] talk;
}

[Serializable]
public class BeaverTutorialTalks : ScriptableObject
{

    public BeaverTutorialTalk[] talks;

}
