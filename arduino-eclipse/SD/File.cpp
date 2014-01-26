/*

 SD - a slightly more friendly wrapper for sdfatlib

 This library aims to expose a subset of SD card functionality
 in the form of a higher level "wrapper" object.

 License: GNU General Public License V3
          (Because sdfatlib is licensed with this.)

 (C) Copyright 2010 SparkFun Electronics

 */

#include <SD/SD.h>

File::~File(void) {
  //  Serial.print("Deleted file object");
}

size_t File::write(uint8_t val) {
  return SD.file.write(val);
}

size_t File::write(const char *str) {
  return SD.file.write(str);
}

size_t File::write(const uint8_t *buf, size_t size) {
  return SD.file.write(buf, size);
}

int File::peek() {
  char c = SD.file.read();
  if (c != -1) SD.file.seekCur(-1);
  return c;
}

int File::read() {
  return SD.file.read();
}

int File::available() {
  return size() - position();
}

void File::flush() {
  SD.file.sync();
}

boolean File::seek(uint32_t pos) {
  return SD.file.seekSet(pos);
}

uint32_t File::position() {
  return SD.file.curPosition();
}

uint32_t File::size() {
  return SD.file.fileSize();
}

void File::close() {
  SD.file.close();
}

File::operator bool() {
  return SD.file.isOpen();
}
