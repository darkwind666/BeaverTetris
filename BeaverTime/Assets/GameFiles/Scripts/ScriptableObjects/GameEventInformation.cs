using UnityEngine;
using System.Collections;
using System;

[Serializable]
public class GameEventInformation : ScriptableObject
{

    public int eventType;
    public int eventInterval;
    public int eventDuration;
    public int detailsCount;
    public int fallingSpeed;

}
