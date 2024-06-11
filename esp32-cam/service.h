#ifndef _SERVICE_H
#define _SERVICE_H
#include "WiFi.h"
#include <Firebase_ESP_Client.h>
//Provide the token generation process info.
#include <addons/TokenHelper.h>
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert Firebase project API Key
#define API_KEY "AIzaSyBGXraIJKR9n4haHiCguy_uJu2TP68hbuQ"
// Insert Authorized Email and Corresponding Password
#define USER_EMAIL "asd123@gmail.com"
#define USER_PASSWORD "12345678"

// Insert Firebase storage bucket ID e.g bucket-name.appspot.com
#define STORAGE_BUCKET_ID "flutterfirebase-c0890.appspot.com"

String uid;


//Define Firebase Data objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

void initFirebaseService(){
  //Firebase
  // Assign the api key
  config.api_key = API_KEY;

  //Assign the user sign in credentials
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  //Assign the callback function for the long running token generation task
  config.token_status_callback = tokenStatusCallback;  //see addons/TokenHelper.h
  config.max_token_generation_retry = 5;
  Firebase.reconnectWiFi(true);

  fbdo.setBSSLBufferSize(16384, 16384);
  fbdo.setResponseSize(16384);

  Firebase.begin(&config, &auth);


  Serial.println("Getting User UID");
  while ((auth.token.uid) == "") {
    Serial.print('.');
    delay(1000);
  }
  // get user UID
  uid = auth.token.uid.c_str();
}


#endif