using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class RechargeSpellIndicatorController : MonoBehaviour {

    public SpellCountdownController spellRechargeController;

    Image circularRechargeIndicator;

    void Start () {

        circularRechargeIndicator = GetComponent<Image>();
        circularRechargeIndicator.fillAmount = 0f;

    }
	
	void Update () {

        float fillAmount = ((float)spellRechargeController.spellRechargeInterval - spellRechargeController.spellRechargeState) / (float)spellRechargeController.spellRechargeInterval;
        circularRechargeIndicator.fillAmount = fillAmount;

    }
}
