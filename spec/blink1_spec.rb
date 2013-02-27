require 'spec_helper'

describe Blink1 do

  context 'native extention methods' do

    it 'returns vendor_id' do
      Blink1.vendor_id.should eql(10168)
    end

    it 'returns product_id' do
      Blink1.product_id.should eql(493)
    end

  end

  context 'class methods' do

    it 'returns list' do
      Blink1.list.is_a?(Array).should be_true
    end

  end

end
