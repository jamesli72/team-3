from gpiozero import LED
from time import sleep

led1 = LED(14)
led2 = LED(15)
num_blinks = 5

for i in range (num_blinks):
  led1.on()
  sleep(1)
  led1.off()

  led2.on()
  sleep(1)
  led2.off
