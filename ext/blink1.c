#include "ruby.h"
#include "blink1-lib.h"
#include <stdio.h>

static VALUE rb_blink1_vid(VALUE self) {
  return INT2NUM(blink1_vid());
}

static VALUE rb_blink1_pid(VALUE self) {
  return INT2NUM(blink1_pid());
}

static VALUE rb_blink1_sortPaths(VALUE self) {
  blink1_sortPaths();
  return Qnil;
}

static VALUE rb_blink1_sortSerials(VALUE self) {
  blink1_sortSerials();
  return Qnil;
}

static VALUE rb_blink1_enumerate(VALUE self) {
  return INT2NUM(blink1_enumerate());
}

static VALUE rb_blink1_enumerateByVidPid(VALUE self, VALUE vid, VALUE pid) {
  return INT2NUM(blink1_enumerateByVidPid(FIX2INT(vid), FIX2INT(pid)));
}

static VALUE rb_blink1_blink1_getCachedPath(VALUE self, VALUE i) {
  return rb_str_new2(blink1_getCachedPath(FIX2INT(i)));
}

static VALUE rb_blink1_getCachedSerial(VALUE self, VALUE i) {
  const wchar_t *ret = blink1_getCachedSerial(FIX2INT(i));
  char * dest;
  wcstombs(dest, ret, sizeof(ret));
  return rb_str_new2(dest);
}

static VALUE rb_blink1_getCachedCount(VALUE self) {
  return INT2NUM(blink1_getCachedCount());
}


/*
 
 
 int blink1_getCachedCount(void);
 
 hid_device* blink1_open(void);
 hid_device* blink1_openByPath(const char* path);
 hid_device* blink1_openBySerial(const wchar_t* serial);
 hid_device* blink1_openById( int i );
 
 void blink1_close( hid_device* dev );
 
 int blink1_write( hid_device* dev, void* buf, int len);
 int blink1_read( hid_device* dev, void* buf, int len);
 
 int blink1_getSerialNumber(hid_device *dev, char* buf);
 int blink1_getVersion(hid_device *dev);
 
 int blink1_fadeToRGB(hid_device *dev, uint16_t fadeMillis,
 uint8_t r, uint8_t g, uint8_t b );
 
 int blink1_setRGB(hid_device *dev, uint8_t r, uint8_t g, uint8_t b );
 
 int blink1_eeread(hid_device *dev, uint16_t addr, uint8_t* val);
 int blink1_eewrite(hid_device *dev, uint16_t addr, uint8_t val);
 
 int blink1_serialnumread(hid_device *dev, uint8_t** serialnumstr);
 int blink1_serialnumwrite(hid_device *dev, uint8_t* serialnumstr);
 
 //int blink1_nightlight(hid_device *dev, uint8_t on);
 int blink1_serverdown(hid_device *dev, uint8_t on, uint16_t millis);
 
 int blink1_play(hid_device *dev, uint8_t play, uint8_t pos);
 int blink1_writePatternLine(hid_device *dev, uint16_t fadeMillis,
 uint8_t r, uint8_t g, uint8_t b,
 uint8_t pos);
 int blink1_readPatternLine(hid_device *dev, uint16_t* fadeMillis,
 uint8_t* r, uint8_t* g, uint8_t* b,
 uint8_t pos);
 //int blink1_playPattern(hid_device *dev,,);
 
 char *blink1_error_msg(int errCode);
 
 void blink1_enableDegamma();
 void blink1_disableDegamma();
 int blink1_degamma(int n);
 
 void blink1_sleep(uint16_t delayMillis);
 
 */

void Init_blink1() {
  VALUE module;
  VALUE klass = rb_define_class("Blink1", rb_cObject);
  rb_define_singleton_method(klass, "vid", rb_blink1_vid, 0);
  rb_define_singleton_method(klass, "pid", rb_blink1_pid, 0);
  rb_define_singleton_method(klass, "sort_paths", rb_blink1_sortPaths, 0);
  rb_define_singleton_method(klass, "sort_serials", rb_blink1_sortSerials, 0);
  rb_define_singleton_method(klass, "enumerate", rb_blink1_enumerate, 0);
  rb_define_singleton_method(klass, "enumerate_vid_pid", rb_blink1_enumerateByVidPid, 2);
  rb_define_singleton_method(klass, "cached_path", rb_blink1_blink1_getCachedPath, 1);
  rb_define_singleton_method(klass, "cached_serial", rb_blink1_getCachedSerial, 1);
  rb_define_singleton_method(klass, "cached_count", rb_blink1_getCachedCount, 0);
}
