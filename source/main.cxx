#include <Windows.h>
#include <iostream>
#include <cstdint>
#include <string>
#include <array>

int main(int argc, char** argv) {
    const auto& key_parent = HKEY_CURRENT_USER;
    const std::string& key_path = "Software\\Microsoft\\Windows\\DWM";
    const auto key_access_level = KEY_ALL_ACCESS;

    // The handle to the registry key where the AccentColor value is stored.
    HKEY key_handle;

    // Open a handle to the registry key where the AccentColor value is located.
    const auto& error_code = 
        RegOpenKeyExA(key_parent, key_path.c_str(), NULL, key_access_level, &key_handle);
    
    if(error_code == ERROR_SUCCESS) {
        std::cout << "Opened registry key @ " << key_path << std::endl;
        
        // The name of the tatget value within the opened key.
        const std::string& value_name = "AccentColor";

        // The data type of the target value.
        unsigned long value_type = REG_DWORD;
        
        // The size of the buffer that will store the target value's bytes.
        unsigned long value_buffer_size = sizeof(uint32_t);

        // The buffer that will store the target value's bytes.
        std::array<uint8_t, sizeof(uint32_t)> value_buffer;

        // Fill the buffer with nullbytes.
        std::fill(value_buffer.begin(), value_buffer.end(), 0x00);
   
        // Query the target value from the registry, into the buffer.
        RegQueryValueExA(key_handle, value_name.c_str(), NULL, &value_type, value_buffer.data(), &value_buffer_size);

        // The actual value of the current accent color as an unsigned integer.
        const uint32_t& current_accent_color = *reinterpret_cast<uint32_t*>(value_buffer.data());

        std::cout << "Current accent color: " << std::hex << current_accent_color << std::endl;

        // The new accent color value.
        const uint32_t new_value = 0x010101;

        // A byte pointer to the new accent color value.
        const uint8_t* new_value_pointer = reinterpret_cast<const uint8_t*>(&new_value);

        // A buffer that will contain the bytes of the new accent color value.
        std::array<uint8_t, sizeof(value_type)> new_value_buffer;

        // Copy the bytes from the new accent color value into the buffer using the pointer made before.
        std::copy(new_value_pointer, new_value_pointer + sizeof(uint32_t), new_value_buffer.begin());

        // Set the registry value of AccentColor to the new value stored within the buffer.
        RegSetValueExA(key_handle, "AccentColor", NULL, value_type, new_value_buffer.data(), value_buffer_size);

        std::cout << "Wrote new accent color: " << std::hex << *reinterpret_cast<uint32_t*>(new_value_buffer.data()) << std::endl;

        // Close the handle to the registry key.
        RegCloseKey(key_handle);        
        std::cout << "Closed registry key @ " << key_path << std::endl;
    } else {
        std::cerr << "Non-zero error code when attempting to open registry key: " << error_code << std::endl;

        // A buffer that will store the human readable version of the error message, as a c-string.
        std::array<uint8_t, 512> error_message_buffer;

        // Fill the buffer with nullbytes.
        std::fill(error_message_buffer.begin(), error_message_buffer.end(), 0x00);

        // Format the error code into a human readable error message.
        FormatMessage(
            FORMAT_MESSAGE_FROM_SYSTEM, 
            NULL, 
            error_code,
            NULL, 
            reinterpret_cast<LPSTR>(error_message_buffer.data()), 
            error_message_buffer.size(), 
            nullptr
        );

        std::cerr << "Error message: " << error_message_buffer.data() << std::endl;
        return error_code;
    }

    return 0;
}