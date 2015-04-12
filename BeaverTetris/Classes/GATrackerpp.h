#pragma once

#include <string>

#include <sstream>
#include <assert.h>
#include "curl.h"

class GATrackerpp {

public:
    GATrackerpp(const std::string & trackinkId, const std::string & clientId);

    ~GATrackerpp();

    void sendEvent(const std::string & eventCategory, const std::string & eventAction, bool startSession, bool stopSession);

    void sendAppView(const std::string & appName, const std::string & appVersion, const std::string & screenName);

private:
    const std::string trackingId_;
    const std::string clientId_;

    void sendAnalytics(std::string const &payload);

    CURL *curl_;
};