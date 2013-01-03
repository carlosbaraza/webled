require 'test_helper'

class LedsControllerTest < ActionController::TestCase
  test "should get turnon" do
    get :turnon
    assert_response :success
  end

  test "should get turnoff" do
    get :turnoff
    assert_response :success
  end

end
