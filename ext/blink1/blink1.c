#include <stdlib.h>
#include "ruby.h"
#include "blink1-lib.h"
#include <stdio.h>

struct Blink1Instance {
  hid_device *dev;
  int opened;
};

static int degamma = 1;

#pragma mark - Static methods

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
  char *dest;
  wcstombs(dest, ret, sizeof(ret));
  return rb_str_new2(dest);
}

static VALUE rb_blink1_getCachedCount(VALUE self) {
  return INT2NUM(blink1_getCachedCount());
}

static VALUE rb_blink1_error_msg(VALUE self, VALUE code) {
  char *msg = blink1_error_msg(FIX2INT(code));
  return msg == NULL ? Qnil : rb_str_new2(msg);
}

static VALUE rb_blink1_getDegammaEnabled(VALUE self) {
  return degamma == 1 ? Qtrue : Qfalse;
}

static VALUE rb_blink1_setDegammaEnabled(VALUE self, VALUE enabled) {
  if(RTEST(enabled)) {
    degamma = 1;
    blink1_enableDegamma();
  } else {
    degamma = 0;
    blink1_disableDegamma();
  }
  return Qnil;
}

static VALUE rb_blink1_degamma(VALUE self, VALUE i) {
  return INT2NUM(blink1_degamma(FIX2INT(i)));
}

static VALUE rb_blink1_sleep(VALUE self, VALUE delayMillis) {
  blink1_sleep(FIX2UINT(delayMillis));
  return Qnil;
}

#pragma mark - Instance methods

void rb_blink1_free(struct Blink1Instance *ins) {
  if(ins->opened == 1) {
    blink1_close(ins->dev);
    ins->opened = 0;
  }
  // free(ins);
  ruby_xfree(ins);
}

static VALUE rb_blink1_allocate(VALUE self) {
  struct Blink1Instance *ins = malloc(sizeof(struct Blink1Instance));
  ins->opened = 0;
  return Data_Wrap_Struct(self, 0, rb_blink1_free, ins);
}

static VALUE rb_blink1_opened(VALUE self) {
  struct Blink1Instance *ins;
  Data_Get_Struct(self, struct Blink1Instance, ins);
  return ins->opened == 1 ? Qtrue : Qfalse;
}

static VALUE rb_blink1_open(VALUE self) {
  struct Blink1Instance *ins;
  Data_Get_Struct(self, struct Blink1Instance, ins);
  if(ins->opened == 0) {
    ins->dev = blink1_open();
    ins->opened = 1;
    return Qtrue;
  }
  return Qfalse;
}

static VALUE rb_blink1_openByPath(VALUE self, VALUE path) {
  struct Blink1Instance *ins;
  Data_Get_Struct(self, struct Blink1Instance, ins);
  if(ins->opened == 0) {
    ins->dev = blink1_open();
    ins->opened = 1;
    return Qtrue;
  }
  return Qfalse;
}

static VALUE rb_blink1_openBySerial(VALUE self, VALUE serial) {
  struct Blink1Instance *ins;
  Data_Get_Struct(self, struct Blink1Instance, ins);
  if(ins->opened == 0) {
    ins->dev = blink1_open();
    ins->opened = 1;
    return Qtrue;
  }
  return Qfalse;
}

static VALUE rb_blink1_openById(VALUE self, VALUE id) {
  struct Blink1Instance *ins;
  Data_Get_Struct(self, struct Blink1Instance, ins);
  if(ins->opened == 0) {
    ins->dev = blink1_open();
    ins->opened = 1;
    return Qtrue;
  }
  return Qfalse;
}

static VALUE rb_blink1_close(VALUE self) {
  struct Blink1Instance *ins;
  Data_Get_Struct(self, struct Blink1Instance, ins);
  if(ins->opened == 1) {
    blink1_close(ins->dev);
    ins->opened = 0;
  }
  return Qnil;
}

static VALUE rb_blink1_getVersion(VALUE self) {
  struct Blink1Instance *ins;
  Data_Get_Struct(self, struct Blink1Instance, ins);
  return INT2NUM(blink1_getVersion(ins->dev));
}

static VALUE rb_blink1_fadeToRGB(VALUE self, VALUE fadeMillis, VALUE r, VALUE g, VALUE b) {
  struct Blink1Instance *ins;
  Data_Get_Struct(self, struct Blink1Instance, ins);
  return INT2NUM(blink1_fadeToRGB(ins->dev, FIX2UINT(fadeMillis), FIX2UINT(r), FIX2UINT(g), FIX2UINT(b)));
}

static VALUE rb_blink1_setRGB(VALUE self, VALUE r, VALUE g, VALUE b) {
  struct Blink1Instance *ins;
  Data_Get_Struct(self, struct Blink1Instance, ins);
  return INT2NUM(blink1_setRGB(ins->dev, FIX2UINT(r), FIX2UINT(g), FIX2UINT(b)));
}

static VALUE rb_blink1_eeread(VALUE self, VALUE addr) {
  struct Blink1Instance *ins;
  uint8_t val = 0;
  Data_Get_Struct(self, struct Blink1Instance, ins);
  blink1_eeread(ins->dev, FIX2UINT(addr), &val);
  return UINT2NUM(val);
}

static VALUE rb_blink1_eewrite(VALUE self, VALUE addr, VALUE val) {
  struct Blink1Instance *ins;
  Data_Get_Struct(self, struct Blink1Instance, ins);
  return INT2NUM(blink1_eewrite(ins->dev, FIX2UINT(addr), FIX2UINT(val)));
}

static VALUE rb_blink1_serialnumread(VALUE self) {
  struct Blink1Instance *ins;
  Data_Get_Struct(self, struct Blink1Instance, ins);
  uint8_t *serialnum;
  blink1_serialnumread(ins->dev, &serialnum);
  return UINT2NUM(serialnum);
}

static VALUE rb_blink1_serialnumwrite(VALUE self, VALUE serialnumstr) {
  struct Blink1Instance *ins;
  Data_Get_Struct(self, struct Blink1Instance, ins);
  char *serialnumc = RSTRING_PTR(serialnumstr);
  char serialnum[100];
  strcpy(serialnumc, serialnum);
  return INT2NUM(blink1_serialnumwrite(ins->dev, (uint8_t *)serialnum));
}

static VALUE rb_blink1_serverdown(VALUE self, VALUE on, VALUE millis) {
  struct Blink1Instance *ins;
  Data_Get_Struct(self, struct Blink1Instance, ins);
  return INT2NUM(blink1_serverdown(ins->dev, RTEST(on) ? 1 : 0, FIX2UINT(millis)));
}

static VALUE rb_blink1_play(VALUE self, VALUE pos) {
  struct Blink1Instance *ins;
  Data_Get_Struct(self, struct Blink1Instance, ins);
  return INT2NUM(blink1_play(ins->dev, 1, FIX2UINT(pos)));
}

static VALUE rb_blink1_stop(VALUE self, VALUE pos) {
  struct Blink1Instance *ins;
  Data_Get_Struct(self, struct Blink1Instance, ins);
  return INT2NUM(blink1_play(ins->dev, 0, FIX2UINT(pos)));
}

static VALUE rb_blink1_writePatternLine(VALUE self, VALUE fadeMillis, VALUE r, VALUE g, VALUE b, VALUE pos) {
  struct Blink1Instance *ins;
  Data_Get_Struct(self, struct Blink1Instance, ins);
  return INT2NUM(blink1_writePatternLine(ins->dev, FIX2UINT(fadeMillis), FIX2UINT(r), FIX2UINT(g), FIX2UINT(b), FIX2UINT(pos)));
}

static VALUE rb_blink1_readPatternLine(VALUE self, VALUE pos) {
  struct Blink1Instance *ins;
  Data_Get_Struct(self, struct Blink1Instance, ins);
  uint16_t fadeMillis; uint8_t r; uint8_t g; uint8_t b;
  blink1_readPatternLine(ins->dev, &fadeMillis, &r, &g, &b, FIX2UINT(pos));
  VALUE hash = rb_hash_new();
  rb_hash_aset(hash, rb_str_new2("fade_millis"), UINT2NUM(fadeMillis));
  rb_hash_aset(hash, rb_str_new2("r"), UINT2NUM(r));
  rb_hash_aset(hash, rb_str_new2("g"), UINT2NUM(g));
  rb_hash_aset(hash, rb_str_new2("b"), UINT2NUM(b));
  return hash;
}

/* UNSPPORT
 int blink1_write( hid_device* dev, void* buf, int len);
 int blink1_read( hid_device* dev, void* buf, int len);
 int blink1_getSerialNumber(hid_device *dev, char* buf);
 //int blink1_playPattern(hid_device *dev,,);
 */


void Init_blink1() {
  VALUE module;
  VALUE klass = rb_define_class("Blink1", rb_cObject);

  rb_define_singleton_method(klass, "vendor_id",         rb_blink1_vid,                  0);
  rb_define_singleton_method(klass, "product_id",        rb_blink1_pid,                  0);
  rb_define_singleton_method(klass, "sort_paths",        rb_blink1_sortPaths,            0);
  rb_define_singleton_method(klass, "sort_serials",      rb_blink1_sortSerials,          0);
  rb_define_singleton_method(klass, "enumerate",         rb_blink1_enumerate,            0);
  rb_define_singleton_method(klass, "enumerate_vid_pid", rb_blink1_enumerateByVidPid,    2);
  rb_define_singleton_method(klass, "cached_path",       rb_blink1_blink1_getCachedPath, 1);
  rb_define_singleton_method(klass, "cached_serial",     rb_blink1_getCachedSerial,      1);
  rb_define_singleton_method(klass, "cached_count",      rb_blink1_getCachedCount,       0);
  rb_define_singleton_method(klass, "error_message",     rb_blink1_error_msg,            1); // Not implemented in the library
  rb_define_singleton_method(klass, "degamma_enabled",   rb_blink1_getDegammaEnabled,    0);
  rb_define_singleton_method(klass, "degamma_enabled=",  rb_blink1_setDegammaEnabled,    1);
  rb_define_singleton_method(klass, "degamma",           rb_blink1_degamma,              1);
  rb_define_singleton_method(klass, "sleep",             rb_blink1_sleep,                1);

  rb_define_alloc_func(klass, rb_blink1_allocate);

  rb_define_method(klass, "opened?",            rb_blink1_opened,           0);
  rb_define_method(klass, "open",               rb_blink1_open,             0);
  rb_define_method(klass, "open_by_path",       rb_blink1_openByPath,       1);
  rb_define_method(klass, "open_by_serial",     rb_blink1_openBySerial,     1);
  rb_define_method(klass, "open_by_id",         rb_blink1_openById,         1);
  rb_define_method(klass, "close",              rb_blink1_close,            0);
  rb_define_method(klass, "version",            rb_blink1_getVersion,       0);
  rb_define_method(klass, "fade_to_rgb",        rb_blink1_fadeToRGB,        4);
  rb_define_method(klass, "set_rgb",            rb_blink1_setRGB,           3);
  rb_define_method(klass, "eeread",             rb_blink1_eeread,           1);
  rb_define_method(klass, "eewrite",            rb_blink1_eewrite,          2);
  rb_define_method(klass, "serialnum=",         rb_blink1_serialnumwrite,   1);
  rb_define_method(klass, "serialnum",          rb_blink1_serialnumread,    0);
  rb_define_method(klass, "serverdown",         rb_blink1_serverdown,       2);
  rb_define_method(klass, "play",               rb_blink1_play,             1);
  rb_define_method(klass, "stop",               rb_blink1_stop,             1);
  rb_define_method(klass, "read_pattern_line",  rb_blink1_readPatternLine,  1);
  rb_define_method(klass, "write_pattern_line", rb_blink1_writePatternLine, 5);
}

