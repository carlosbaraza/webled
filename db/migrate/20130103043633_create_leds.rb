class CreateLeds < ActiveRecord::Migration
  def change
    create_table :leds do |t|
      t.boolean :ison, :default => false

      t.timestamps
    end
  end
end
