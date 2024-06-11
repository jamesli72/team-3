//Replace with your network credentials
const char* ssid = "James Ly";
const char* password = "12332133";
// const char* ssid2 = "Hờ Mờ Cờ";
// const char* password2 = "hmc01062002";
// const char* ssid = "TitanFall.com";
// const char* password = "haogia123";




void initWiFi() {
  bool connected = false;
  unsigned long startTime = millis(); // Record the start time
  
  // First, try connecting to the primary WiFi service
  WiFi.begin(ssid, password);
  Serial.println("Connecting to primary WiFi service...");
  
  // Wait for connection to primary service or until timeout
  while (WiFi.status() != WL_CONNECTED && millis() - startTime < 30000) { // 30 seconds timeout
    delay(1000);
    Serial.print(".");
  }
  
  // Check if connected to primary service
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected to primary WiFi service.");
    connected = true;
  }
  else {
    Serial.println("\nPrimary WiFi service not available. Trying secondary service...");
  }

  // If not connected to primary service and timeout reached, try connecting to secondary service
  if (!connected) {
    startTime = millis(); // Reset the start time for the secondary service
    WiFi.begin(ssid2, password2); // Connect to secondary service
    Serial.println("Connecting to secondary WiFi service...");
    
    // Wait for connection to secondary service or until timeout
    while (WiFi.status() != WL_CONNECTED && millis() - startTime < 30000) { // 30 seconds timeout
      delay(1000);
      Serial.print(".");
    }
    
    // Check if connected to secondary service
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("\nConnected to secondary WiFi service.");
      connected = true;
    }
    else {
      Serial.println("\nSecondary WiFi service not available.");
    }
  }

  // If still not connected to any service, proceed with the next command
  if (!connected) {
    Serial.println("Neither WiFi service available. Proceeding to next command.");
    return; // Exit the function to proceed with the next command
  }
}
