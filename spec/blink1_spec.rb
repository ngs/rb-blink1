require 'spec_helper'

describe Blink1 do

  describe 'native extention methods' do

    describe 'vendor_id' do
      subject { Blink1.vendor_id }
      it { should be 10168 }
    end

    describe 'product_id' do
      subject { Blink1.product_id }
      it { should be 493 }
    end

  end

  context 'class methods', :device => true do

    describe 'list' do
      subject { Blink1.list }
      it { should be_a_kind_of Array }
    end

    describe 'random' do
      subject {
        ret = nil
        Blink1.open do|b1|
          ret = b1.random 20
        end
        ret
      }
      it { should be_a_kind_of Fixnum }
    end

  end

end
