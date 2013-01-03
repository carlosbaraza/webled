require 'socket'
require 'sqlite3'

server = TCPServer.new 2000
loop do
  Thread.start(server.accept) do |client|
    
    db = SQLite3::Database.open "../webled/db/development.sqlite3"
    ison = db.execute "SELECT ison FROM leds WHERE id=1"
    db.close

    if ison[0][0]== "f"
      client.puts "0"
    else
      client.puts "1"
    end

    client.close
  end
end
