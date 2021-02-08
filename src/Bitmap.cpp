/***************************************************
    Bitmap class for SSD1351 display

    This is an adaptation by Philippe Hilger ("PeerGum")
    of the original code written by Limor Fried/Ladyada
    for Adafruit Industries.

    GNU General Public License v3.0

    For the Photon or Electron, the Adafruit_mfGFX and the
    Adafruit_SSD1351_Photon libraries are also required

    Be sure to install them!

 ****************************************************/

#include "Bitmap.h"
#include "DisplayDriver.h"

extern DisplayDriver display;

Bitmap::Bitmap(void)
{
}

Bitmap::Bitmap(const char *filename, const char *fileUrl) {
    _filename = (char *)filename;
    if (!bmpFile.open(_filename, O_READ)) {
        _missing = true;
    }
    log("BMP created %s",filename);
}

Bitmap::Bitmap(File bitmap) {
    bmpFile = bitmap;
    log("BMP created");
}

Bitmap::~Bitmap() {
    /*if (bmpFile.isOpen()) {
        bmpFile.close();
    }*/
    log("BMP deleted");
}

void Bitmap::load(const char *filename, const char *fileUrl) {
    _filename = (char *)filename;
    if (!bmpFile.open(_filename, O_READ)) {
        _missing = true;
    }
    log("BMP created %s",filename);
}

void Bitmap::draw(uint8_t x, uint8_t y) {
    displayWidth = display.width();
    displayHeight = display.height();
    rotation = display.getRotation();

    // switch display off before loading pic
    if ((x >= displayWidth) || (y >= displayHeight)) {
        return;
    }

    log("Load %s", _filename ? _filename : "");

    // Open requested file on SD card
    if (!bmpFile) {
        log("Not found");
        _missing = true;
        return;
    }

    /*display.writeCommand(SSD1351_CMD_DISPLAYOFF);*/
    if (!read(x,y)) {
        log("Can't read BMP");
        _missing = true;
    };
    bmpFile.close();
    // switch display back on
    /*display.writeCommand(SSD1351_CMD_DISPLAYON);*/
}

bool Bitmap::read(uint8_t x, uint8_t y) {
    uint32_t  buffidx;
    uint32_t dummy;

    // Parse BMP header
    if(read16() != 0x4D42) { // BMP signature
        _missing = true;
        log("Not BMP");
        return false;
    }

    dummy = read32();
    log("Sz %luB", dummy);
    (void)read32(); // Read & ignore creator bytes

    bmpImageoffset = read32(); // Start of image data
    log("Img Off. %lu", bmpImageoffset);

    // Read DIB header
    dummy = read32();
    log("Hdr sz %lu", dummy);
    bmpWidth  = read32();
    bmpHeight = read32();

    if(read16() != 1) { // # planes -- must be '1'
        log("# planes not '1'");
        return false;
    }

    bmpDepth = read16(); // bits per pixel
    log("Bits %u", bmpDepth);

    if ((bmpDepth != 16 && bmpDepth != 24) || read32() != 0) { // 0 = uncompressed
        _missing = true;
        log("Not 16/24 uncomp. BMP");
        return false;
    }

    log("Sz %ux%d", bmpWidth, bmpHeight);

    // BMP rows are padded (if needed) to 4-byte boundary
    rowSize = 4*((bmpWidth-1)/4+1);

    // If bmpHeight is negative, image is in top-down order.
    // This is not canon but has been observed in the wild.
    if (bmpHeight < 0) {
        bmpHeight = -bmpHeight;
        flip      = false;
    }

    // Crop area to be loaded
    w = bmpWidth;
    h = bmpHeight;
    if (x+w > displayWidth) {
        w = displayWidth  - x;
    }
    if (y+h > displayHeight) {
        h = displayHeight - y;
    }

    buffidx = sizeof(sdbuffer); // Force buffer reload

    uint16_t color;
    uint8_t red;
    uint8_t green;
    uint8_t blue;

    uint8_t pixelBytes = bmpDepth/8;

    uint16_t *buffer;

    buffer = (uint16_t *)malloc((size_t)(2*w*h));
    if (buffer == NULL) {
        log("Err alloc %luB", (unsigned long)2*w*h);
        return true; // not a problem with picture
    }

    bmpFile.seek(bmpImageoffset);

    for (row=0; row<h; row++) { // For each scanline...

        unsigned long pos;

        if (flip) {// Bitmap is stored bottom-to-top order (normal BMP)
            pos = bmpImageoffset + pixelBytes * (bmpHeight - 1 - row) * rowSize;
        } else {    // Bitmap is stored top-to-bottom
            pos = bmpImageoffset + pixelBytes * row * rowSize;
        }
        if (bmpFile.position() != pos) { // Need seek?
            /*log("pos = %lu, wanted = %lu",bmpFile.position(),pos);*/
            bmpFile.seek(pos);
            buffidx = sizeof(sdbuffer); // Force buffer reload
        }

        // optimize by setting pins now
        for (col=0; col<w; col++) { // For each pixel...

            // Time to read more pixel data?
            if (buffidx+pixelBytes > sizeof(sdbuffer)) { // Indeed
                for (unsigned long i=buffidx; i<sizeof(sdbuffer); i++) {
                    sdbuffer[i-buffidx] = sdbuffer[i];
                }
                // if (
                    bmpFile.read(sdbuffer+sizeof(sdbuffer)-buffidx, buffidx);
                    // <buffidx) {
                //     log("Read error.");
                // }
                buffidx = 0; // Set index to beginning
            }
            if (bmpDepth == 16) {
                color = ((uint16_t *)sdbuffer)[buffidx/2];
                buffidx+=2;
            } else if (bmpDepth == 24) {
                red = sdbuffer[buffidx++];
                green = sdbuffer[buffidx++];
                blue = sdbuffer[buffidx++];
                color = display.Color565(blue,green,red);
            }

            uint16_t r,c;

            switch(rotation) {
                case 1:
                    r = col;
                    c = h - row - 1;
                    break;
                case 2:
                    r = h - row - 1;
                    c = w - col - 1;
                    break;
                case 3:
                    r = w - col - 1;
                    c = row;
                    break;
                case 0:
                default:
                    r = row;
                    c = col;
                    break;
            }
            //display.drawPixel(x+col, flip ? y+h-1-row : y+row, color);
            *(buffer + r * w + c) = color;
            /*display.writeData(color>>8);
            display.writeData(color);*/
        } // end pixel
    } // end scanline
    delayMicroseconds(50);
    display.writeCommand(SSD1351_CMD_SETCOLUMN);
    display.writeData(x);
    display.writeData(x+w-1);
    display.writeCommand(SSD1351_CMD_SETROW);
    display.writeData(y);
    display.writeData(y+h-1);
    display.writeCommand(SSD1351_CMD_WRITERAM);
    for (int i = 0; i < w * h ; i++) {
        display.writeData(buffer[i]>>8);
        display.writeData(buffer[i]);
    }

    log("Loaded in %ld ms",millis() - startTime);
    return true;
}

// These read 16- and 32-bit types from the SD card file.
// BMP data is stored little-endian, Arduino is little-endian too.
// May need to reverse subscript order if porting elsewhere.

uint16_t Bitmap::read16() {
    uint16_t result;
    ((uint8_t *)&result)[0] = read8();
    ((uint8_t *)&result)[1] = read8();
    return result;
}

uint32_t Bitmap::read32() {
    uint32_t result;
    ((uint8_t *)&result)[0] = read8();
    ((uint8_t *)&result)[1] = read8();
    ((uint8_t *)&result)[2] = read8();
    ((uint8_t *)&result)[3] = read8();
    return result;
}

uint8_t Bitmap::read8() {
    uint8_t byte = bmpFile.read();
    /*Serial.printf("[%02X]",byte);*/
    return byte;
}

bool Bitmap::isMissing(void) {
    return _missing;
}
