using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using UnityEngine;

namespace Assets.Mediation_SDK.Demo
{
    public class MainThreadLooper
    {
        private  List<Action> mPendingTasks = new List<Action>();
        private  List<Action> mWorkingTasks = new List<Action>();
        public  void Post(Action task)
        {
            lock (mPendingTasks)
            {
                mPendingTasks.Add(task);
            }
        }

        //run on Main Thread(it's not the android UI Thread).
        public void Run()
        {
            lock (mPendingTasks)
            {
                mWorkingTasks.Clear();
                mWorkingTasks.AddRange(mPendingTasks);
                mPendingTasks.Clear();
            }
            foreach (var task in mWorkingTasks)
            {
                task();
            }
        }
    }

}
