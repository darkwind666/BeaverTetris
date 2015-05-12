#include "GATrackerpp.h"
#include "cocos2d.h"

using namespace std;

void sendAnalyticData(std::string aData, int *handle, bool *onLine);

GATrackerpp::GATrackerpp(const string &trackingId, const string &clientId, std::string appName, std::string appVersion) :
        trackingId_(trackingId), clientId_(clientId), _appName(appName), _appVersion(appVersion) 
{
    curl_global_init(CURL_GLOBAL_ALL);
	_handle = 0;
	_onLine = true;
}

GATrackerpp::~GATrackerpp() 
{
    curl_global_cleanup();
}

void GATrackerpp::sendEvent(const std::string & eventCategory, const std::string & eventAction)
{
	stringstream postFields;
    postFields << "v=1&tid=" << trackingId_ << "&cid=" << clientId_;
    postFields << "&t=event&ec=" << eventCategory << "&ea=" << eventAction;
    sendAnalytics(postFields.str());
}

void GATrackerpp::sendEvent(const string &eventCategory, const string &eventAction, int value) 
{

    stringstream postFields;
    postFields << "v=1&tid=" << trackingId_ << "&cid=" << clientId_;
    postFields << "&t=event&ec=" << eventCategory << "&ea=" << eventAction << "&ev=" << value;
    sendAnalytics(postFields.str());
}

void GATrackerpp::sendEvent(const string & eventCategory, const string & eventAction, string eventLabel)
{
	stringstream postFields;
	postFields << "v=1&tid=" << trackingId_ << "&cid=" << clientId_;
	postFields << "&t=event&ec=" << eventCategory << "&ea=" << eventAction << "&el=" << eventLabel;
	sendAnalytics(postFields.str());
}

void GATrackerpp::sendEvent(const string & eventCategory, const string & eventAction, string eventLabel , int value)
{
	stringstream postFields;
	postFields << "v=1&tid=" << trackingId_ << "&cid=" << clientId_;
	postFields << "&t=event&ec=" << eventCategory << "&ea=" << eventAction << "&el=" << eventLabel << "&ev=" << value;
	sendAnalytics(postFields.str());
}

void GATrackerpp::sendAppView(const string &screenName) {

    stringstream postFields;
    postFields << "v=1&tid=" << trackingId_ << "&cid=" << clientId_;
    postFields << "&t=appview&an=" << _appName << "&av=" << _appVersion << "&cd=" << screenName;
    sendAnalytics(postFields.str());
}

void GATrackerpp::sendStartAppView(const string & screenName, string shop, string language)
{
	stringstream postFields;
    postFields << "v=1&tid=" << trackingId_ << "&cid=" << clientId_;
    postFields << "&t=appview&an=" << _appName << "&av=" << _appVersion  << "&aiid=" << shop << "&cd=" << screenName << "&ul=" << language << "&sc=start";
	sendAnalytics(postFields.str());
}

void GATrackerpp::sendEndAppView(const string & screenName)
{
	stringstream postFields;
    postFields << "v=1&tid=" << trackingId_ << "&cid=" << clientId_;
    postFields << "&t=appview&an=" << _appName << "&av=" << _appVersion << "&cd=" << screenName << "&sc=end";
    sendFinalAnalytics(postFields.str());
}

void GATrackerpp::sendAnalytics(const string &payload) 
{
	if (_onLine)
	{
		thread thread(sendAnalyticData, payload, &_handle, &_onLine);
		thread.detach();
	}
}

void GATrackerpp::sendFinalAnalytics(string const &payload)
{
	if (_onLine)
	{
		thread thread(sendAnalyticData, payload, &_handle, &_onLine);
		thread.join();
	}
}

void sendAnalyticData(string aData, int *handle, bool *onLine)
{

	CURL *curl = NULL;
	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, "https://www.google-analytics.com/collect");
	curl_easy_setopt(curl, CURLOPT_COPYPOSTFIELDS, aData.c_str());
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, FALSE);
	
	while (true)
	{
		if (*onLine == false)
		{
			break;
		}

		if (*handle == 0)
		{
			*handle = 1;
			CURLcode result = curl_easy_perform(curl);
			if (result != CURLE_OK)
			{
				*onLine = false;
			}
			*handle = 0;
			break;
		}
	}
	curl_easy_cleanup(curl);
}

