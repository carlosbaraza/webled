class LedsController < ApplicationController
  def turnon
    @led = Led.find(1)
    @led.ison = true
    @led.save
  end

  def turnoff
    @led = Led.find(1)
    @led.ison = false
    @led.save
  end
  
  def show
    @led = Led.find(1)
  end
end
