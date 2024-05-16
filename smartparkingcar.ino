#include <Wire.h> // Untuk komunikasi I2C

// Alamat OLED (ini adalah alamat yang umum; periksa dokumentasi OLED untuk alamat spesifiknya)
#define OLED_ADDRESS 0x3C

// Inisialisasi OLED
void OLED_init() {
    Wire.beginTransmission(OLED_ADDRESS);
    Wire.write(0x00); // Ini menandakan bahwa Anda akan mengirim perintah
    Wire.write(0xAE); // Display OFF
    Wire.write(0xD5); // Set display clock divide ratio/oscillator frequency
    Wire.write(0x80);
    Wire.write(0xA8); // Set multiplex ratio
    Wire.write(0x3F); // 1/64 duty
    Wire.write(0xD3); // Set display offset
    Wire.write(0x00);
    Wire.write(0x40); // Set start line
    Wire.write(0x8D); // Charge pump setting
    Wire.write(0x14); // Enable charge pump
    Wire.write(0xA1); // Segment re-map
    Wire.write(0xC8); // COM output scan direction
    Wire.write(0xDA); // Set COM pins hardware configuration
    Wire.write(0x12);
    Wire.write(0x81); // Set contrast control
    Wire.write(0xCF); // Default value
    Wire.write(0xD9); // Set pre-charge period
    Wire.write(0xF1); // Default value
    Wire.write(0xDB); // Set VCOMH deselect level
    Wire.write(0x40); // Default value
    Wire.write(0xA4); // Entire display ON
    Wire.write(0xA6); // Normal display mode
    Wire.write(0xAF); // Display ON
    Wire.endTransmission();
}

// Fungsi untuk menulis data ke OLED
void OLED_writeData(uint8_t data) {
    Wire.beginTransmission(OLED_ADDRESS);
    Wire.write(0x40); // Menandakan Anda akan mengirim data
    Wire.write(data);
    Wire.endTransmission();
}

// Fungsi untuk menulis teks ke OLED
void OLED_writeText(const char* text) {
    while (*text) {
        // Untuk setiap karakter, tulis datanya ke OLED
        OLED_writeData((uint8_t)*text);
        text++;
    }
}

// Fungsi untuk menghapus layar OLED
void OLED_clear() {
    for (int page = 0; page < 8; page++) {
        Wire.beginTransmission(OLED_ADDRESS);
        Wire.write(0x00); // Perintah
        Wire.write(0xB0 + page); // Set page address
        Wire.write(0x00); // Set column address (low nibble)
        Wire.write(0x10); // Set column address (high nibble)
        Wire.endTransmission();
        for (int col = 0; col < 128; col++) {
            OLED_writeData(0x00); // Tulis nol untuk membersihkan layar
        }
    }
}

void setup() {
    // Mulai komunikasi I2C
    Wire.begin();
    
    // Inisialisasi OLED
    OLED_init();
    
    // Bersihkan layar OLED
    OLED_clear();
    
    // Tulis teks ke OLED
    OLED_writeText("Hello, OLED!");
}

void loop() {
    // Tidak melakukan apa-apa dalam loop
}
