#ifndef _ESPCAM_H
#define _ESPCAM_H
#define FILE_PHOTO_NAME "/photo.jpg"

#include "Arduino.h"
#include "esp_camera.h"
#include <FS.h>
#include <LittleFS.h>
// OV2640 camera module pins (CAMERA_MODEL_AI_THINKER)
#define PWDN_GPIO_NUM   32
#define RESET_GPIO_NUM -1
#define XCLK_GPIO_NUM   0
#define SIOD_GPIO_NUM   26
#define SIOC_GPIO_NUM   27

#define Y9_GPIO_NUM     35
#define Y8_GPIO_NUM     34
#define Y7_GPIO_NUM     39
#define Y6_GPIO_NUM     36
#define Y5_GPIO_NUM     21
#define Y4_GPIO_NUM     19
#define Y3_GPIO_NUM     18
#define Y2_GPIO_NUM     5
#define VSYNC_GPIO_NUM  25
#define HREF_GPIO_NUM   23
#define PCLK_GPIO_NUM   22
#define LED_GPIO_NUM    4

void initCamera() {
  // OV2640 camera module
  static camera_config_t camera_config = {
        .pin_pwdn       = PWDN_GPIO_NUM,
        .pin_reset      = RESET_GPIO_NUM,
        .pin_xclk       = XCLK_GPIO_NUM,
        .pin_sccb_sda   = SIOD_GPIO_NUM,
        .pin_sccb_scl   = SIOC_GPIO_NUM,
        .pin_d7         = Y9_GPIO_NUM,
        .pin_d6         = Y8_GPIO_NUM,
        .pin_d5         = Y7_GPIO_NUM,
        .pin_d4         = Y6_GPIO_NUM,
        .pin_d3         = Y5_GPIO_NUM,
        .pin_d2         = Y4_GPIO_NUM,
        .pin_d1         = Y3_GPIO_NUM,
        .pin_d0         = Y2_GPIO_NUM,
        .pin_vsync      = VSYNC_GPIO_NUM,
        .pin_href       = HREF_GPIO_NUM,
        .pin_pclk       = PCLK_GPIO_NUM,

        .xclk_freq_hz   = 20000000,
        .ledc_timer     = LEDC_TIMER_0,
        .ledc_channel   = LEDC_CHANNEL_0,
        .pixel_format   = PIXFORMAT_JPEG,
        .frame_size     = FRAMESIZE_UXGA,
        .jpeg_quality   = 8,
        .fb_count       = 1,
        .grab_mode      = CAMERA_GRAB_LATEST
    };

  // Camera init
  esp_err_t err = esp_camera_init(&camera_config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    ESP.restart();
  }
  sensor_t* s = esp_camera_sensor_get();
  // initial sensors are flipped vertically and colors are a bit saturated
  if (s->id.PID == OV2640_PID) {
    s->set_brightness(s, 0);                  // up the brightness just a bit
    s->set_saturation(s, -2);                 // lower the saturation
    s->set_aec2(s, 1);                        // 0 = disable , 1 = enable // *** User settings = 1 (AEC DSP)
    s->set_bpc(s, 1);                         // 0 = disable , 1 = enable // *** User settings = 1 (BPC)
    s->set_gainceiling(s, (gainceiling_t)6);  // 0 to 6
  }
  Serial.print("init cam success..");
}

// Photo File Name to save in SPIFFS
unsigned int pictureNumber = 11;
String photo_path = "/data1/photo" + String(pictureNumber) + ".jpg";


// Check if photo capture was successful
// bool checkPhoto(fs::FS& fs) {
//   File f_pic = fs.open(photo_path.c_str());
//   unsigned int pic_sz = f_pic.size();
//   return (pic_sz > 100);
// }

// Capture Photo and Save it to SPIFFS
void capturePhotoSaveLittleFs() {
  ledcAnalogWrite(LED_GPIO_NUM, 10);
  camera_fb_t* fb = NULL;  // pointer
  for (int i = 0; i < 5; i++) {
    fb = esp_camera_fb_get();
    esp_camera_fb_return(fb);
    fb = NULL;
  }

  bool success = false;
  do {
    // Take a photo with the camera
    Serial.println("Taking a photo...");
    fb = esp_camera_fb_get();  
    delay(1000);//This is key to avoid an issue with the image being very dark and green. If needed adjust total delay time.

    if (!fb) {
      Serial.println("Camera capture failed");
      return;
    }
    // Photo file name
    Serial.printf("Picture file name: %s\n", FILE_PHOTO_NAME);
    File file = LittleFS.open(FILE_PHOTO_NAME, FILE_WRITE);
    delay(1000);
    // Insert the data in the photo file
    if (!file) {
      Serial.println("Failed to open file in writing mode");
    } else {
      file.write(fb->buf, fb->len);  // payload (image), payload length
      Serial.print("The picture has been successfully saved as ");
      Serial.print(FILE_PHOTO_NAME);
      Serial.print(" - Size: ");
      Serial.print(file.size());
      Serial.println(" bytes");
      success = true;
    }
    // Close the file
    file.close();
    esp_camera_fb_return(fb);
  } while (!success);
  ledcAnalogWrite(LED_GPIO_NUM, 0);
}



#endif