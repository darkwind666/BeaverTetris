using Assets.Mediation_SDK.Library;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;

namespace Assets.Mediation_SDK.Demo
{
#if UNITY_ANDROID
    class BaseAdListener : AdListener
    {
        private readonly string mName;
        public BaseAdListener(string name)
        {
            mName = name;
        }

        public virtual void onClicked(Ad ad)
        {
            Debug.Log(mName + "::onClicked");
        }

        public virtual void onClosed(Ad ad)
        {
            Debug.Log(mName + "::onClosed");
        }

        public virtual void onError(Ad ad, AdError error)
        {
            Debug.Log(mName + "::onError:" + error.getErrorMsg());
        }

        public virtual void onLoaded(Ad ad)
        {
            Debug.Log(mName + "::onLoaded");
        }

        public virtual void onOpened(Ad ad)
        {
            Debug.Log(mName + "::onOpened");
        }
    }
#endif
}
