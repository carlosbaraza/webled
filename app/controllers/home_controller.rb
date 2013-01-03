class HomeController < ApplicationController
  def index
    @led = Led.find(1)
    
  end
end
