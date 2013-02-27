require 'blink1/blink1'
require 'blink1/version'

#
# A Ruby interface for blink(1)[http://blink1.thingm.com/].
#
class Blink1

  # Fade duration in millisecond.
  attr_accessor :millis
  # Delay to next color in millisecond.
  attr_accessor :delay_millis

  # :call-seq:
  #   <span class="name">new</span> <span class="arguments">( {Fixnum} id )</span>
  #   <span class="name">new</span> <span class="arguments">( {Boolean} auto_open )</span>
  #   <span class="name">new</span> <span class="arguments">( {String} serial_id )</span>
  #   <span class="name">new</span> <span class="arguments">( :path => <em>device_path</em> )</span>
  #   <span class="name">new</span> <span class="arguments">( :serial => <em>serial_id</em> )</span>
  #
  # Returns new instance of +Blink1+
  #
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
    else
      open if option == true
    end
    @millis ||= 300
    @delay_millis ||= 500
  end

  #
  # :call-seq:
  #   <span class="name">open</span> <span class="arguments">( {Fixnum} id ) { |blink1| }</span>
  #   <span class="name">open</span> <span class="arguments">( {Boolean} autoopen ) { |blink1| }</span>
  #   <span class="name">open</span> <span class="arguments">( {String} serial_id ) { |blink1| }</span>
  #   <span class="name">open</span> <span class="arguments">( :path => <em>device_path</em> ) { |blink1| }</span>
  #   <span class="name">open</span> <span class="arguments">( :serial => <em>serial_id</em> ) { |blink1| }</span>
  #
  # If block given, yieds new instance of +Blink1+.
  #
  # If not, returns new +Blink1+
  #
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

  #
  # Blink with RGB value for +times+.
  #
  def blink r, g, b, times
    times.times do
      self.fade_to_rgb(millis, r, g, b)
      self.class.sleep(delay_millis)
      self.fade_to_rgb(millis, 0, 0, 0)
      self.class.sleep(delay_millis)
    end
  end

  #
  # Flash random color for +times+.
  #
  def random times
    times.times do
      r = rand(0xff)
      g = rand(0xff)
      b = rand(0xff)
      self.fade_to_rgb(millis, r, g, b)
      self.class.sleep(delay_millis)
    end
  end

  #
  # Turn LED white.
  #
  def on
    self.fade_to_rgb(millis, 0xff, 0xff, 0xff)
  end

  #
  # Turn LED off.
  #
  def off
    self.fade_to_rgb(millis, 0, 0, 0)
  end

  #
  # Alias for +read_pattern_line+.
  #
  def [] index
    self.read_pattern_line(index)
  end

  #
  # Write pattern line with hash with key +fade_millis+, +r+, +g+, +b+.
  #
  def []= index, prop
    fade_millis = prop[:fade_millis] || prop['fade_millis']
    r = prop[:r] || prop['r']
    g = prop[:g] || prop['g']
    b = prop[:b] || prop['b']
    self.write_pattern_line(index, fade_millis, r, g, b)
  end

  #
  # Returns array of hash with keys +:id+, +:serial+, +:path+
  #
  def self.list
    count = enumerate_vid_pid(vendor_id, product_id)
    i = 0
    devs = []
    while i < count do
      devs << {
        :id     => i,
        :serial => cached_serial(i),
        :path   => cached_path(i)
      }
      i += 1
    end
    devs
  end

end
