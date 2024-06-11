#include "soc/soc.h"           // Disable brownout problems
#include "soc/rtc_cntl_reg.h"  // Disable brownout problems
#include "driver/rtc_io.h"
#include "time.h"
#include "espcam.h"
#include "service.h"
// use 12 bit precission for LEDC timer
#define LEDC_TIMER_12_BIT  12

// use 5000 Hz as a LEDC base frequency
#define LEDC_BASE_FREQ     5000
//===============================================
int timestamp;
const char* ntpServer = "asia.pool.ntp.org";
//=============================================================
//=============================================================

unsigned long sendPicturePrevMillis = 0;
unsigned long timerFrameDelay = 60000;  //1 minute


boolean takeNewPhoto = true;
//==========================================
//=======================================================

bool taskCompleted = false;
//================================================
void ledcAnalogWrite(uint8_t pin, uint32_t value, uint32_t valueMax = 255) {
  // calculate duty, 4095 from 2 ^ 12 - 1
  uint32_t duty = (4095 / valueMax) * min(value, valueMax);

  // write duty to LEDC
  ledcWrite(pin, duty);
}
//================================================
void setup() {
  // Turn-off the 'brownout detector'
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
  // Serial port for debugging purposes
  Serial.begin(115200);
  //hwSerial.begin(9600, SERIAL_8N1, RX, TX);
  //pinMode(LED_GPIO_NUM, OUTPUT);
  ledcAttach(LED_GPIO_NUM, LEDC_BASE_FREQ, LEDC_TIMER_12_BIT);
  
  initWiFi();

  initLittleFS();
  
  initCamera();

  configTime(0, 0, ntpServer);

  initFirebaseService();
}

void loop() {
  //=====================================================================================================
  if (Firebase.ready() && ((millis() - sendPicturePrevMillis > timerFrameDelay) || (sendPicturePrevMillis == 0))) {
      sendPicturePrevMillis = millis();
      if (takeNewPhoto) 
      {
        capturePhotoSaveLittleFs();
        taskCompleted = false;
      }
      else {
        Serial.println("Capture picture failed, wait for the next iteration!");
        return;
      }
      if(pictureNumber > 21) pictureNumber = 0;
  }
  //==================================================================================================
  //==================================================================================================
  //==================================================================================================
  //================================================================================================
  if (Firebase.ready() && !taskCompleted) {
    Serial.print("Uploading picture... ");
    //MIME type should be valid to avoid the download problem.
    //The file systems for flash and SD/SDMMC can be changed in FirebaseFS.h.
    if (!Firebase.Storage.upload( &fbdo, STORAGE_BUCKET_ID ,  FILE_PHOTO_NAME,
                                    mem_storage_type_flash , photo_path.c_str() ,
                                  "image/jpeg" /* mime type */, fcsUploadCallback)) {
      Serial.println(fbdo.errorReason());
    }
    pictureNumber++;
    photo_path = "/data1/photo" + String(pictureNumber) + ".jpg";
    Serial.print("Next photo remote path is");
    Serial.println(photo_path.c_str());
    taskCompleted = true;
  }
}