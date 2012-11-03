
(Your feed needs to exist first, so run this if it's not existent; all one line)

curl --request POST
     --data '{"title":"My feed", "version":"1.0.0"}'
     --header "X-ApiKey: YOUR_API_KEY_HERE"
     --verbose
     http://api.cosm.com/v2/feeds


	How to Update your "fake" COSM feeds: 

curl --request PUT --data-binary @cosm.jso --header "X-ApiKey:lNgyMDzsImHKVGM5NqHCutoin36SAKxOUHdBSzZVMkQ0VT0g" --verbose http://api.cosm.com/v2/feeds/83731