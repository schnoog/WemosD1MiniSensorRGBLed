/*

Copyright Nat Weerawan 2015-2016
MIT License

The MIT License (MIT)

Copyright (c) Nat Weerawan <nat.wrw@gmail.com> (cmmakerclub.com)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

#include "CMMC_OTA.h"

CMMC_OTA::CMMC_OTA() {

}

void CMMC_OTA::loop() {
  if (_initialised) {
    ArduinoOTA.handle();
  }
}

bool CMMC_OTA::initialized() {
  return _initialised;
}

void CMMC_OTA::on_start(THandlerFunction fn) {
  _user_on_start_callback = fn;
}

void CMMC_OTA::on_end(THandlerFunction fn) {
  _user_on_end_callback = fn;
}

void CMMC_OTA::on_progress(THandlerFunction_Progress fn) {
  _user_on_progress_callback = fn;
}

void CMMC_OTA::on_error(THandlerFunction_Error fn) {
  _user_on_error_callback = fn;
}

CMMC_OTA::~CMMC_OTA() {

}
