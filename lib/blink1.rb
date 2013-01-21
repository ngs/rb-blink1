require 'blink1/blink1_ext'
require 'blink1/version'
require 'blink1/pattern'
require 'blink1/device'
require 'forwardable'

#
# A Ruby interface for blink(1)[http://blink1.thingm.com/].
#
module Blink1

  attr_reader :device

  class << self
    extend Forwardable
    def_delegators :'Blink1::Device',
      :cached_count,
      :cached_path,
      :cached_serial,
      :degamma,
      :degamma_enabled,
      :degamma_enabled=,
      :enumerate,
      :enumerate_vid_pid,
      :list,
      :new,
      :open,
      :product_id,
      :sleep,
      :sort_paths,
      :sort_serials,
      :vendor_id

    def_delegators :@device,
      :[],
      :[]=,
      :blink,
      :close,
      :delay_millis,
      :eeread,
      :eewrite,
      :fade_to_rgb,
      :millis,
      :off,
      :on,
      :open,
      :open_by_id,
      :open_by_path,
      :open_by_serial,
      :opened?,
      :play,
      :random,
      :read_pattern_line,
      :serverdown,
      :set_rgb,
      :stop,
      :version,
      :write_pattern_line

    def initialize option = nil
      @device = Blink1::Device.new option
    end

  end

end
