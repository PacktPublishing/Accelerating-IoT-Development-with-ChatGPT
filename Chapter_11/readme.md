### Local Application Logic

1. The ESP32 retrieves temperature and humidity data from the DHT11 sensor periodically.
2. The ESP32 checks the retrieved data against a preset normal range.
3. Normal Condition - If the retrieved data falls within the normal range, a green LED remains solid on without any alert beep.
4. Abnormal Condition - If the retrieved data falls below the normal range, a blinking blue LED and a beep signal this. If the data exceeds the normal range, a blinking red LED and a beep indicate this.
5. Error Condition - If the DHT11 fails to provide data, a system LED turns on red and a continuous sound indicate a failure state. The ESP32-C3 tries to read the data three times. If all attempts fail, it initiates a reboot.
