require 'spec_helper'

describe Blink1 do

  describe 'native extention methods' do

    it 'vendor_id' do
      Blink1.vendor_id.should eql(10168)
    end

    it 'product_id' do
      Blink1.product_id.should eql(493)
    end

  end

  describe 'actual device', :device => true do

    it 'matches device path, serial, id' do
      list = Blink1.list
      list.length.should == Blink1.cached_count
      list.each_with_index do |dev, i|
        dev[:path].should eql Blink1.cached_path(i)
        dev[:serial].should eql Blink1.cached_serial(i)
        dev[:id].should == i
      end
    end

    it 'open type check' do
      Blink1.open do |blink1|
        blink1.is_a?(Blink1::Device).should == true
      end
    end

  end

end
