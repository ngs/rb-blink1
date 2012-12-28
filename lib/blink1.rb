require 'blink1/blink1'
require 'blink1/version'

class Blink1

  attr_accessor :millis
  attr_accessor :delay_millis

  def initialize option = nil
    case option
    when Fixnum
      open_by_id(option)
    when Hash
      path   = option[:path]   || option["path"]
      serial = option[:serial] || option["serial"]
      if path
        open_by_path(path)
      elsif serial
        open_by_serial(serial)
      end
    when String
      open_by_serial(option)
    end
    @millis ||= 300
    @delay_millis ||= 500
  end

  def blink r, g, b, times
    times.times do
      self.fade_to_rgb(millis, r, g, b)
      self.class.sleep(delay_millis)
      self.fade_to_rgb(millis, 0, 0, 0)
      self.class.sleep(delay_millis)
    end
  end

  def random times
    times.times do
      r = rand(0xff)
      g = rand(0xff)
      b = rand(0xff)
      self.fade_to_rgb(millis, r, g, b)
      self.class.sleep(delay_millis)
    end
  end

  def on
    self.fade_to_rgb(millis, 0xff, 0xff, 0xff)
  end

  def off
    self.fade_to_rgb(millis, 0, 0, 0)
  end

  def [] index
    self.read_pattern_line(index)
  end

  def []= index, prop
    fade_millis = prop[:fade_millis] || prop['fade_millis']
    r = prop[:r] || prop['r']
    g = prop[:g] || prop['g']
    b = prop[:b] || prop['b']
    self.write_pattern_line(index, fade_millis, r, g, b)
  end

  def self.list
    count = enumerate_vid_pid(vendor_id, product_id)
    i = 0
    devs = []
    while i < count do
      devs << {
        id: i,
        serial: cached_serial(i),
        path: cached_path(i)
      }
      i += 1
    end
    devs
  end

  def self.open option = nil, &block
    b = self.new(option)
    b.open if option.nil?
    if block
      begin
        b.instance_eval &block
      ensure
        b.close
      end
    else
      b
    end
  end

end
