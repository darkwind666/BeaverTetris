using UnityEngine;
using System.Collections;
using System;

[Serializable]
public struct GameEvent
{
    public int gameEventType;
    public int eventInterval;
    public int eventDuration;
    public int detailsCount;
    public int fallingSpeed;
}

[Serializable]
public struct BlocksForRemoving
{
    public int blockType;
    public int blocksCount;
}

[Serializable]
public struct LevelSpell
{
    public int spellType;
    public int spellCount;
    public int spellRechargeInterval;
}

[Serializable]
public class GameLevel : ScriptableObject {

    public int levelAward;
    public int availableBlockTypesCount;

    public GameEvent[] levelEvents;

    public int bossType;

    public int winConditionType;
    public int needToPlaceDetailsCount;
    public int remainTimes;
	public int bossLivesCount;

    public BlocksForRemoving[] blocks;
    public LevelSpell[] levelSpells;

    public int tutorialIndex;

}
