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

  describe 'actual device', :if => Blink1.cached_count > 0 do

    it 'matches device path, serial, id' do
      list = Blink1.list
      list.length.should == Blink1.cached_count
      list.each_with_index do |dev, i|
        dev[:path].should eql Blink1.cached_path(i)
        dev[:serial].should eql Blink1.cached_serial(i)
        dev[:id].should == i
      end
    end

    it 'set_rgb' do
      Blink1.open do |blink1|
        blink1.set_rgb(255, 255, 255).should_not == -1
        Blink1.sleep 1000
        blink1.off.should_not == -1
        blink1.opened?.should == true
        blink1.close
        blink1.opened?.should == false
      end
    end

  end

end
