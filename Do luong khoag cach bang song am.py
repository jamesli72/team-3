import RPi.GPIO as GPIO
import time

# Định nghĩa chân
TRIG_PIN = 13
ECHO_PIN = 12

def setup():
    # Thiết lập chế độ chân GPIO
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(TRIG_PIN, GPIO.OUT)
    GPIO.setup(ECHO_PIN, GPIO.IN)
    GPIO.output(TRIG_PIN, GPIO.LOW)
    print("Waiting for sensor to settle")
    time.sleep(2)

def distance():
    # Gửi xung trigger
    GPIO.output(TRIG_PIN, GPIO.HIGH)
    time.sleep(0.00001)  # 10 microseconds
    GPIO.output(TRIG_PIN, GPIO.LOW)

    # Đo thời gian xung echo
    while GPIO.input(ECHO_PIN) == 0:
        pulse_start = time.time()

    while GPIO.input(ECHO_PIN) == 1:
        pulse_end = time.time()

    pulse_duration = pulse_end - pulse_start

    # Tính toán khoảng cách
    distance = pulse_duration * 17150  # 34300/2 (tốc độ âm thanh là 34300 cm/s)
    distance = round(distance, 2)

    return distance

def loop():
    try:
        while True:
            dist = distance()
            if dist >= 200 or dist <= 0:
                print("Out of range")
            else:
                print(f"Distance: {dist} cm")
            time.sleep(0.5)
    except KeyboardInterrupt:
        print("Measurement stopped by user")
        GPIO.cleanup()

if __name__ == "__main__":
    setup()
    loop()
