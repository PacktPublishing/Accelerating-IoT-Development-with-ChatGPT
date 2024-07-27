// HardwareInfo.h
#ifndef HardwareInfo_h
#define HardwareInfo_h

#include <Arduino.h>
#include <WiFi.h>

class HardwareInfo
{
public:
    static void displayHardwareInfo()
    {
        Serial.println("\nESP32 Chip information:");

        Serial.print("Chip Model: ");
        Serial.println(ESP.getChipModel());

        Serial.print("Chip Revision: ");
        Serial.println(ESP.getChipRevision());

        Serial.print("SDK Version: ");
        Serial.println(ESP.getSdkVersion());

        Serial.print("Number of Cores: ");
        Serial.println(ESP.getChipCores());

        Serial.print("CPU Frequency: ");
        Serial.print(ESP.getCpuFreqMHz());
        Serial.println(" MHz");

        Serial.print("Max CPU Frequency: ");
        Serial.print(ESP.getCpuFreqMHz());
        Serial.println(" MHz");

        Serial.print("Flash Chip Size: ");
        Serial.print(ESP.getFlashChipSize());
        Serial.println(" bytes");

        Serial.print("Flash Chip Speed: ");
        Serial.print(ESP.getFlashChipSpeed());
        Serial.println(" Hz");

        Serial.print("PSRAM Size: ");
        Serial.print(ESP.getPsramSize());
        Serial.println(" bytes");

        Serial.print("Free PSRAM: ");
        Serial.print(ESP.getFreePsram());
        Serial.println(" bytes");

        Serial.print("Sketch Size: ");
        Serial.print(ESP.getSketchSize());
        Serial.println(" bytes");

        Serial.print("Free Sketch Space: ");
        Serial.print(ESP.getFreeSketchSpace());
        Serial.println(" bytes");

        Serial.print("Heap Size: ");
        Serial.print(ESP.getHeapSize());
        Serial.println(" bytes");

        Serial.print("Free Heap: ");
        Serial.print(ESP.getFreeHeap());
        Serial.println(" bytes");

        Serial.print("Min Free Heap: ");
        Serial.print(ESP.getMinFreeHeap());
        Serial.println(" bytes");

        Serial.print("Max Alloc Heap: ");
        Serial.print(ESP.getMaxAllocHeap());
        Serial.println(" bytes");

        FlashMode_t flashMode = ESP.getFlashChipMode();
        Serial.print("Flash Chip Mode: ");
        Serial.println(flashMode == FM_QIO ? "QIO" : flashMode == FM_QOUT ? "QOUT"
                                                 : flashMode == FM_DIO    ? "DIO"
                                                                          : "DOUT");

        // Print the MAC address of the ESP32
        Serial.print("WiFi MAC Address: ");
        Serial.println(WiFi.macAddress());

        // Print the MD5 value
        Serial.print("MD5: ");
        Serial.println(ESP.getSketchMD5());

        // Print the eFuse MAC address as the deviceID
        Serial.print("deviceID: ");
        Serial.println(ESP.getEfuseMac(), HEX);
    }
};

#endif // HardwareInfo_h
