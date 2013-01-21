require 'spec_helper'

describe Blink1::Device do

  describe 'actual deviec control', :device => true do

    it 'open/close' do
      blink1 = Blink1.new
      blink1.opened?.should == false
      blink1.open
      blink1.opened?.should == true
      blink1.close
      blink1.opened?.should == false
    end

    it 'on/off' do
      Blink1.open do |blink1|
        blink1.on.should_not == -1
        Blink1.sleep 100
        blink1.off.should_not == -1
      end
    end

    it 'set_rgb' do
      Blink1.open do |blink1|
        blink1.set_rgb(255, 0, 255).should_not == -1
        Blink1.sleep 100
        blink1.set_rgb(0, 0, 0).should_not == -1
      end
    end

  end

end
