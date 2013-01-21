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
      :product_id,
      :sleep,
      :sort_paths,
      :sort_serials,
      :vendor_id

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
    def open option = nil, &block
      b = Blink1::Device.new(option)
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

end
