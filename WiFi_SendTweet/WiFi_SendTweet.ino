/*
  WiFi_SendTweet
  
  Arduino & Temboo examples, as well as support documents are available at http://www.temboo.com/arduino
  
  **** A Temboo account and application key are necessary to run all Temboo examples. ****
  http://www.temboo.com
  
  In order to run this sketch, you'll need to register an application using
  the Twitter dev console at https://dev.twitter.com. Note that since this 
  sketch creates a new tweet, your application will need to be configured with
  read+write permissions.
  Use the OAuth credentials provided at the above site.
  
  This example code is in the public domain.
*/

// Arduino libraries
#include <Bridge.h>
#include <Temboo.h>

// Special header files
/*
  You can find your Temboo App Key information on the Temboo website, 
  under My Account > Application Keys
  The same TembooAccount.h file settings can be used for all Temboo SDK sketches.
  Keeping your account information in a separate file means you can share the main .ino file without worrying 
  that you forgot to delete your credentials.
*/
#include "TembooAccount.h" // Temboo Account Information
#include "TwitterAccount.h" // Twitter Account Information

int numRuns = 1; // execution count, so this sketch doesn't run forever
int maxRuns = 3; // the max number of times the Twitter Update Choreo should run

void setup() 
{
  Serial.begin(9600);

  // Wait until a serial console is connected
  delay(4000);
  while(!Serial);

  Bridge.begin();
}

void loop()
{
  // only try to send the tweet if we haven't already sent it successfully
  if (numRuns <= maxRuns) 
  {
    Serial.println("Running SendATweet - Run #" + String(numRuns++) + "...");
    String keyboardInput = "Ask the user for a Tweet to send.";
    // define the text of the tweet we want to send
    String tweetText(keyboardInput);
    
    TembooChoreo StatusesUpdateChoreo;

    // Invoke the Temboo client
    // NOTE: Client must be reinvoked, and repopulated with
    // appropriate arguments, each time its run() method is called.
    StatusesUpdateChoreo.begin();
    
    // set Temboo account credentials
    StatusesUpdateChoreo.setAccountName(TEMBOO_ACCOUNT);
    StatusesUpdateChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
    StatusesUpdateChoreo.setAppKey(TEMBOO_APP_KEY);

    // Identify the Temboo Library choreo to run (Twitter > Tweets > StatusesUpdate)
    StatusesUpdateChoreo.setChoreo("/Library/Twitter/Tweets/StatusesUpdate");

    // ** Required Choreo inputs are explained here: https://www.temboo.com/library/Library/Twitter/Tweets/StatusesUpdate/ ** //
    // Twitter account information
    StatusesUpdateChoreo.addInput("AccessToken", TWITTER_ACCESS_TOKEN);
    StatusesUpdateChoreo.addInput("AccessTokenSecret", TWITTER_ACCESS_TOKEN_SECRET);
    StatusesUpdateChoreo.addInput("ConsumerKey", TWITTER_CONSUMER_KEY);    
    StatusesUpdateChoreo.addInput("ConsumerSecret", TWITTER_CONSUMER_SECRET);

    // Contents of the tweet to be sent
    StatusesUpdateChoreo.addInput("StatusUpdate", tweetText);

    // returnCode signifies whether the Temboo client 
    // was able to send a request to the Temboo servers
    unsigned int returnCode = StatusesUpdateChoreo.run();

    // returnCode of zero means everything worked
    if (returnCode == 0) 
    {
        Serial.println("Success! Tweet sent!");
    } else 
    {
      // Any other returnCode means there was some sort of error
      while (StatusesUpdateChoreo.available()) 
      {
        // Read the error message
        char c = StatusesUpdateChoreo.read();
        // Prin the error message for debugging purposes
        Serial.print(c);
      }
    } 
    // End the process
    StatusesUpdateChoreo.close();

    // do nothing for the next 90 seconds
    Serial.println("Waiting...");
    delay(90000);
  }
}
