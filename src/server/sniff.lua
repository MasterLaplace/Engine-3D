do
    -- TODO: Dissector
    local function print_message(message)
        print(string.format("Message: %s", message))
    end

    -- function to be called when Tshark processes a packet
    local function packet_callback(pinfo, tvb)
        -- filter packets to only select packets between server and client
        if pinfo.src == "127.0.0.1" then
            print("other data")
            local data = tvb:raw(0)
            print_message(data)
        end
        print("--------------------------------")
    end

    -- register the plugin | 49154 |
    local tap = Listener.new("frame", "tcp.port==49154")

    function tap.packet(pinfo, tvb)
        packet_callback(pinfo, tvb)
    end
end

--! RUN : --------------------------------
--* sudo tshark -i any -f "tcp port 49154" -X lua_script:sniff.lua
