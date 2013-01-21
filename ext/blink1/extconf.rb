require 'mkmf'

uname = `uname -s`.chop.split

dir_config 'blink1'

case uname[0]
when 'Darwin'

  $CFLAGS <<
    ' -arch x86_64 -pthread '
  $LIBS <<
    ' -framework IOKit -framework CoreFoundation '

  # RbConfig::MAKEFILE_CONFIG['CC'] = 'gcc'

  $HID_C = "#{$srcdir}/hid.c.mac"

when 'Windows_NT'

  $CFLAGS <<
    ' -arch i386 -arch x86_64 ' <<
    ' -pthread '

  $LIBS <<
    ' -lsetupapi -Wl,--enable-auto-import -static-libgcc -static-libstdc++ '

  $HID_C = "#{$srcdir}/hid.c.windows"

when 'Linux'

  $CFLAGS <<
    " #{ `pkg-config libusb-1.0 --cflags`.strip } "

  $LIBS <<
    " #{ `pkg-config libusb-1.0 --libs`.strip }"
    ' -lrt -lpthread -ldl -static '

  $HID_C = "#{$srcdir}/hid.c.libusb"

when 'FreeBSD'

  $LIBS   <<
    ' -L/usr/local/lib -lusb -lrt -lpthread -liconv -static '

  $HID_C = "#{$srcdir}/hid.c.libusb"

end

FileUtils.copy $HID_C, "#{$srcdir}/hid.c"

$CFLAGS << ' -std=gnu99'

create_makefile('blink1_ext')
