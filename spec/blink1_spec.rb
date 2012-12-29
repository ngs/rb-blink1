require 'spec_helper'

describe Blink1 do

  describe 'native extention methods' do

    it 'vendor_id' do
      Blink1.vendor_id.should eql(10168)
    end

    it 'product_id' do
      p Blink1.product_id.should eql(493)
    end

  end

end
