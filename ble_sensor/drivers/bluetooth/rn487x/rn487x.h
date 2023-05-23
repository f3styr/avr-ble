#ifndef RN487X
#define RN487X

struct ble_server rn487x;

struct gatt_characteristic temp_read_characteristic;
struct gatt_characteristic humidity_read_characteristic;
struct gatt_service temp_and_hum_service;

void rn487x_send_ascii_command(const uint8_t*);

#endif