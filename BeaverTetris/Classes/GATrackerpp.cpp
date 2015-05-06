#include "GATrackerpp.h"

GATrackerpp::GATrackerpp(const std::string &trackingId, const std::string &clientId) :
        trackingId_(trackingId), clientId_(clientId) {
    curl_global_init(CURL_GLOBAL_ALL);
    curl_ = curl_easy_init();
}

GATrackerpp::~GATrackerpp() {
    curl_easy_cleanup(curl_);
    curl_global_cleanup();
}

void GATrackerpp::sendEvent(const std::string &eventCategory, const std::string &eventAction) {

    //Now specify event POST data
    //
    std::stringstream postFields;
    postFields << "v=1&tid=" << trackingId_ << "&cid=" << clientId_;
    postFields << "&t=event&ec=" << eventCategory << "&ea=" << eventAction;

    sendAnalytics(postFields.str());
}

void GATrackerpp::sendAppView(const std::string &appName, const std::string &appVersion, const std::string &screenName, bool startSession, bool stopSession) {

    std::stringstream postFields;
    postFields << "v=1&tid=" << trackingId_ << "&cid=" << clientId_;
    postFields << "&t=appview&an=" << appName << "&av=" << appVersion  << "&aiid=WindowsStore" << "&cd=" << screenName;

	assert(!startSession || !stopSession);

	if (startSession) {
        postFields << "&sc=start";
    }
    if (stopSession) {
        postFields << "&sc=end";
    }

    sendAnalytics(postFields.str());
}

void GATrackerpp::sendAnalytics(const std::string &payload) {

    if (curl_) {

        // First set the URL
        //
        curl_easy_setopt(curl_, CURLOPT_URL, "https://www.google-analytics.com/collect");
        curl_easy_setopt(curl_, CURLOPT_COPYPOSTFIELDS, payload.c_str());
		curl_easy_setopt(curl_, CURLOPT_SSL_VERIFYPEER, FALSE);

        //Perform the request, res will get the return code
        //
        CURLcode res = curl_easy_perform(curl_);

        /* Check for errors */
        if (res != CURLE_OK) {
            printf("curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        else {
            printf("curl_easy_perform() success\n");
        }

    }
}

