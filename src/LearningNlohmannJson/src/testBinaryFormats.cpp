//
// Created by Boran on 2025/4/25.
//
#include <nlohmann/json.hpp>
#include <iostream>
#include <vector>

using json = nlohmann::json;

int main() {
    // 创建示例JSON对象
    json data = {
        {"name", "Alice"},
        {"age", 30},
        {"scores", {95, 88, 92}},
        {"address", {
            {"street", "123 Main St"},
            {"city", "New York"}
        }}
    };

    // 1. CBOR格式 (RFC 7049)
    std::vector<std::uint8_t> cbor_data = json::to_cbor(data);
    std::cout << "CBOR size: " << cbor_data.size() << " bytes\n";
    
    json from_cbor = json::from_cbor(cbor_data);
    std::cout << "From CBOR: " << from_cbor.dump(2) << "\n\n";

    // 2. MessagePack格式
    std::vector<std::uint8_t> msgpack_data = json::to_msgpack(data);
    std::cout << "MessagePack size: " << msgpack_data.size() << " bytes\n";
    
    json from_msgpack = json::from_msgpack(msgpack_data);
    std::cout << "From MessagePack: " << from_msgpack.dump(2) << "\n\n";

    // 3. BSON格式
    std::vector<std::uint8_t> bson_data = json::to_bson(data);
    std::cout << "BSON size: " << bson_data.size() << " bytes\n";
    
    json from_bson = json::from_bson(bson_data);
    std::cout << "From BSON: " << from_bson.dump(2) << "\n";

    return 0;
}
