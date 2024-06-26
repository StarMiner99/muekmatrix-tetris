//
// Created by leo on 03.04.24.
//

#include "color.h"


Color::Color(float red, float green, float blue) {
    this->red = checkAndReturnValid(red);
    this->green = checkAndReturnValid(green);
    this->blue = checkAndReturnValid(blue);
    brightness = 1;

}
/*
Color::Color(uint8_t red, uint8_t green, uint8_t blue) {
    this->red = checkAndReturnValid(float(red));
    this->green = checkAndReturnValid(float(green));
    this->blue = checkAndReturnValid(float(blue));

}*/

float Color::checkAndReturnValid(float value) {
    if(value>MAX_COLOR_VALUE){
        return MAX_COLOR_VALUE;
    }
    if(value<MIN_COLOR_VALUE){
        return MIN_COLOR_VALUE;
    }
    return value;
}


uint32_t Color::calc() {


    return ((uint32_t)(green*brightness) << 16) | ((uint32_t)(red*brightness) << 8) | ((uint32_t)(blue*brightness));

}

Color::Color() {
    red = 0;
    green = 0;
    blue = 0;
    brightness = 1;

}

void Color::setBrightness(float value) {
    if(value <= 1){
        brightness = 1;
    }else{
        brightness = value;
    }


}

float Color::getBrightness() {
    return brightness;
}



void Color::setRed(float value) {
    red = checkAndReturnValid(value);

}

void Color::setGreen(float value) {
    green = checkAndReturnValid(value);
}

void Color::setBlue(float value) {
    blue = checkAndReturnValid(value);
}



float Color::getRed(bool raw) {
    return red*(brightness*float((1-raw)));
}

float Color::getGreen(bool raw) {
    return green*(brightness*float((1-raw)));
}

float Color::getBlue(bool raw) {
    return blue*(brightness*float((1-raw)));
}

void Color::setRGB(uint8_t colorNumber, float value) {
    switch (colorNumber) {
        case 0:
            setRed(value);
            break;
        case 1:
            setGreen(value);
            break;
        case 2:
            setBlue(value);
            break;
    }

}



float Color::getRGB(uint8_t colorNumber, bool raw) {
    switch (colorNumber) {
        case 0:
            getRed(raw);
            break;
        case 1:
            getGreen(raw);
            break;
        case 2:
            getBlue(raw);
            break;
        default:
            return -1;
    }
    return -1;
}

bool Color::equals(Color *compare) const {
    // warning do not use for actual comparing, because comparing float should include an epsilon (this is enough for checking if a color is blank)
    return red == compare->red && green == compare->green && blue == compare->blue;
}

void Color::combine(Color *combination) {
    // calculate the avg color
    setRed((red + combination->red) /2);
    setGreen((green + combination->green) /2);
    setBlue((blue + combination->blue) /2);
}

void Color::add(Color *addition) {
    // if the value overflows max value will be used
    if (red + addition->red >= MAX_COLOR_VALUE) {
        setRed(MAX_COLOR_VALUE);
    } else {
        setRed(red + addition->red);
    }
    if (green + addition->green >= MAX_COLOR_VALUE) {
        setGreen(MAX_COLOR_VALUE);
    } else {
        setGreen(green + addition->green);
    }
    if (blue + addition->blue >= MAX_COLOR_VALUE) {
        setBlue(MAX_COLOR_VALUE);
    } else {
        setBlue(blue + addition->blue);
    }

}

void Color::multiply(float factor) {
    setRed(red * factor);
    setGreen(green * factor);
    setBlue(green * factor);
}

void Color::set(Color *newColor) {
    setRed(newColor->red);
    setGreen(newColor->green);
    setBlue(newColor->blue);
}









