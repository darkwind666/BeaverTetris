using UnityEngine;
using System.Collections.Generic;

public class ServicesLocator {

    static Dictionary<string, object> services = new Dictionary<string, object>();

    public static void loadGameServices()
    {
        GamePlayerDataController player = new GamePlayerDataController();
        services.Add(typeof(GamePlayerDataController).Name, player);

        PlayersDatabaseController playersRecords = new PlayersDatabaseController();
        services.Add(typeof(PlayersDatabaseController).Name, playersRecords);
    }

    public static void setServiceForKey(object aService, string aKey)
    {
        services.Add(aKey, aService);
    }

    public static object getServiceForKey(string aKey)
    {
        return services[aKey];
    }

}
