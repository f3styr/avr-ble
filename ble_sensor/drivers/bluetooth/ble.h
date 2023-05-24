#ifndef ble_H
#define	ble_H

#include <usart_basic.h>
#include <util/delay.h>

typedef enum {
	BLE_APPEARANCE_UNKNOWN = 0, BLE_APPEARANCE_GENERIC_PHONE = 64, 
	BLE_APPEARANCE_GENERIC_COMPUTER = 128, BLE_APPEARANCE_GENERIC_WATCH = 192,
	BLE_APPEARANCE_WATCH_SPORTS_WATCH = 193, BLE_APPEARANCE_GENERIC_CLOCK = 256, 
	BLE_APPEARANCE_GENERIC_DISPLAY = 320, BLE_APPEARANCE_GENERIC_REMOTE_CONTROL = 384,
	BLE_APPEARANCE_GENERIC_EYE_GLASSES = 448, BLE_APPEARANCE_GENERIC_TAG = 512, 
	BLE_APPEARANCE_GENERIC_KEYRING = 576, BLE_APPEARANCE_GENERIC_MEDIA_PLAYER = 640,
	BLE_APPEARANCE_GENERIC_BARCODE_SCANNER = 704, BLE_APPEARANCE_GENERIC_THERMOMETER = 768, 
	BLE_APPEARANCE_THERMOMETER_EAR = 769, BLE_APPEARANCE_GENERIC_HEART_RATE_SENSOR = 832,
	BLE_APPEARANCE_HEART_RATE_SENSOR_HEART_RATE_BELT = 833, 
	BLE_APPEARANCE_GENERIC_BLOOD_PRESSURE = 896, BLE_APPEARANCE_BLOOD_PRESSURE_ARM = 897, BLE_APPEARANCE_BLOOD_PRESSURE_WRIST = 898,
	BLE_APPEARANCE_GENERIC_HID = 960, BLE_APPEARANCE_HID_KEYBOARD = 961,
	BLE_APPEARANCE_HID_MOUSE = 962, BLE_APPEARANCE_HID_JOYSTICK = 963,
	BLE_APPEARANCE_HID_GAMEPAD = 964, BLE_APPEARANCE_HID_DIGITIZERSUBTYPE = 965, 
	BLE_APPEARANCE_HID_CARD_READER = 966, BLE_APPEARANCE_HID_DIGITAL_PEN = 967,
	BLE_APPEARANCE_HID_BARCODE = 968, BLE_APPEARANCE_GENERIC_GLUCOSE_METER = 1024,
	BLE_APPEARANCE_GENERIC_RUNNING_WALKING_SENSOR = 1088, BLE_APPEARANCE_RUNNING_WALKING_SENSOR_IN_SHOE = 1089,
	BLE_APPEARANCE_RUNNING_WALKING_SENSOR_ON_SHOE = 1090, 
	BLE_APPEARANCE_RUNNING_WALKING_SENSOR_ON_HIP = 1091, BLE_APPEARANCE_GENERIC_CYCLING = 1152, BLE_APPEARANCE_CYCLING_CYCLING_COMPUTER = 1153,
	BLE_APPEARANCE_CYCLING_SPEED_SENSOR = 1154, BLE_APPEARANCE_CYCLING_CADENCE_SENSOR = 1155, 
	BLE_APPEARANCE_CYCLING_POWER_SENSOR = 1156, BLE_APPEARANCE_CYCLING_SPEED_CADENCE_SENSOR = 1157,
	BLE_APPEARANCE_GENERIC_PULSE_OXIMETER = 3136, BLE_APPEARANCE_PULSE_OXIMETER_FINGERTIP = 3137, 
	BLE_APPEARANCE_PULSE_OXIMETER_WRIST_WORN = 3138, BLE_APPEARANCE_GENERIC_WEIGHT_SCALE = 3200,
	BLE_APPEARANCE_GENERIC_OUTDOOR_SPORTS_ACT = 5184, BLE_APPEARANCE_OUTDOOR_SPORTS_ACT_LOC_DISP = 5185, 
	BLE_APPEARANCE_OUTDOOR_SPORTS_ACT_LOC_AND_NAV_DISP = 5186, BLE_APPEARANCE_OUTDOOR_SPORTS_ACT_LOC_POD = 5187,
	BLE_APPEARANCE_OUTDOOR_SPORTS_ACT_LOC_AND_NAV_POD = 5188
} ble_gap_appearance_t;


/** Characteristic properties

*/
typedef enum  {
	BLE_PROP_FLAG_BROADCAST = (1), /**< Not supported in RN4870 */
	BLE_PROP_FLAG_READ = (1 << 1),
	BLE_PROP_FLAG_WRITE_WITHOUT_RESPONSE = (1 << 2),
	BLE_PROP_FLAG_WRITE = (1 << 3),
	BLE_PROP_FLAG_NOTIFY = (1 << 4),
	BLE_PROP_FLAG_INDICATE = (1 << 5),
	BLE_PROP_FLAG_AUTHENTICATED_WRITE = (1 << 6),
	BLE_PROP_FLAG_EXTENDED_PROP = (1 << 7), /**< Not supported in RN4870 */
						  
} ble_characteristic_prop_flag_t;

/** BLE I/O capabilities

*/
typedef enum {
      IO_CAPS_DISPLAY_ONLY     = 0x00,   /**< Display Only. */
      IO_CAPS_DISPLAY_YESNO    = 0x01,   /**< Display and Yes/No entry. */
      IO_CAPS_KEYBOARD_ONLY    = 0x02,   /**< Keyboard Only. */
      IO_CAPS_NONE             = 0x03,   /**< No I/O capabilities. */
      IO_CAPS_KEYBOARD_DISPLAY = 0x04,   /**< Keyboard and Display. */
} ble_io_capabilities_t;


enum {
	    UUID_ALERT_NOTIFICATION_SERVICE     = 0x1811,
	    UUID_BATTERY_SERVICE                = 0x180F,
	    UUID_BLOOD_PRESSURE_SERVICE         = 0x1810,
	    UUID_CURRENT_TIME_SERVICE           = 0x1805,
	    UUID_CYCLING_SPEED_AND_CADENCE      = 0x1816,
	    UUID_DEVICE_INFORMATION_SERVICE     = 0x180A,
	    UUID_GLUCOSE_SERVICE                = 0x1808,
	    UUID_HEALTH_THERMOMETER_SERVICE     = 0x1809,
	    UUID_HEART_RATE_SERVICE             = 0x180D,
	    UUID_HUMAN_INTERFACE_DEVICE_SERVICE = 0x1812,
	    UUID_IMMEDIATE_ALERT_SERVICE        = 0x1802,
	    UUID_LINK_LOSS_SERVICE              = 0x1803,
	    UUID_NEXT_DST_CHANGE_SERVICE        = 0x1807,
	    UUID_PHONE_ALERT_STATUS_SERVICE     = 0x180E,
	    UUID_REFERENCE_TIME_UPDATE_SERVICE  = 0x1806,
	    UUID_RUNNING_SPEED_AND_CADENCE      = 0x1814,
	    UUID_SCAN_PARAMETERS_SERVICE        = 0x1813,
	    UUID_TX_POWER_SERVICE               = 0x1804
};

/** Advertising mode

*/
typedef enum {
	NON_CONNECTABLE_UNDIRECTED, 
	CONNECTABLE_DIRECTED,
	CONNECTABLE_UNDIRECTED,
	SCANNABLE_UNDIRECTED,
	
} ble_gap_advertising_t;

typedef enum  {
	BLE_FAIL,
	BLE_NOERR,	
} ble_error_t;

struct gatt_characteristic {
	uint8_t*	UUID;
	uint16_t	handle; 
	uint8_t		properties;
	uint8_t		data_len; /**< Data length in octets. */
};

struct gatt_service {
	uint8_t*				UUID;
	uint16_t				handle; 
	uint16_t				characteristics_count;
	struct gatt_characteristic	*(*characteristics)[];	
};


struct ble_connection {
	uint8_t* address;
};

struct ble_server {
	
	
	uint8_t*					address; 
	uint8_t*					device_name;
	
	bool						enable_bonding;
	ble_io_capabilities_t		io_capabilities;
	uint8_t*					passkey;
	
	ble_gap_appearance_t		advertisement_appearance;
	ble_gap_advertising_t		advertisment_type;
	uint16_t					advertisement_interval;	
	uint16_t					advertisement_timeout;
	
	uint8_t						services_count;

	struct gatt_service			*(*services)[];				
	struct ble_connection*		connections;

	struct ble_sys_ops*			sys;
	struct ble_gatt_ops*		gatt;
	struct ble_gap_ops*			gap;
	struct ble_events*			events;
	
	void (*init)(struct ble_server* ctx);
	void (*probe)(struct ble_server* ctx);
	
	void (*main_loop)(struct ble_server* ctx);
};

struct ble_events {
	
	void (*cb_on_timeout)(void);
	void (*cb_on_connection)(void);
	void (*cb_on_disconnect)(void);	
	
};

struct ble_sys_ops {
	ble_error_t (*shutdown)(struct ble_server* ctx);
	ble_error_t (*reboot)(struct ble_server* ctx);
	ble_error_t (*factory_reset)(struct ble_server* ctx);
};


struct ble_gatt_ops {

	ble_error_t (*init)(struct ble_server* ctx);			
	ble_error_t	(*register_service)(struct gatt_service* service);
	ble_error_t	(*register_characteristic)(struct gatt_characteristic* characteristic);
	ble_error_t	(*read_value)(struct  gatt_characteristic* characteristic, uint8_t destination[]);
	ble_error_t	(*write_value)(struct gatt_characteristic* characteristic, const uint8_t payload[]);	
};

struct ble_gap_ops {
	
	ble_error_t (*init)(struct ble_server* ctx);	
	ble_error_t (*set_address)(struct ble_server* ctx, const uint8_t* address);
	ble_error_t (*set_device_name)(struct ble_server* ctx, const uint8_t* name);
	ble_error_t (*set_appearance)(struct ble_server* ctx, const ble_gap_appearance_t appearance);	
	ble_error_t (*set_advertising_mode)(struct ble_server* ctx, const ble_gap_advertising_t atype);
	ble_error_t (*set_advertising_interval)(struct ble_server* ctx, const uint16_t interval);	
	ble_error_t (*set_advertising_timeout)(struct ble_server* ctx, const  uint16_t timeout);	
	ble_error_t (*start_advertising)(struct ble_server* ctx);	
	ble_error_t (*stop_advertising)(struct ble_server* ctx);	
	ble_error_t (*kill_connection)(struct ble_server* ctx);
	ble_error_t (*set_security)(struct ble_server* ctx,
								const bool enable_bonding, 
								const ble_io_capabilities_t io_capabilities, 
								const uint8_t* passkey);
	


};	
	
	
#endif




/*	
	
	ble_error_t (*set_advertisment_tx_power)(int8_t power);
	ble_error_t (*set_connected_tx_power)(int8_t power);
	
	
	ble_error_t (*set_device_information) ( uint8_t* hardware_version, 
											uint8_t* model_name,
											uint8_t* manufacturer_name,
											uint8_t* software_revision,											uint8_t* serial_number);
*/

																			


/*
static struct ble_t rn487x_handle = {
	main_loop = rn487x_main_loop
	struct sys_ops
};


struct ble_t *rn487x_probe()

{
	return&rn487x_handle;
}

static void rn487x_main_loop(void)
{
	
}
*/

/*
struct sys_ops {
	reboot
	reset
	power on
	power off	
};

struct ble_t{
	main_loop
	struct sys_ops
};

struct ble_t *ble = NULL;

static ble_err_handler();

void bluetooth_init(void)
{
	ble = rn4870_probe();
	
	if(!ble)
	{
		return err
	}
	
	ble->register_characteristic();
	ble->get_characteristics();
	
	
	ble->err_handler() = ble_err_heander
	ble->pairing_request = ble_pairing_handler
	ble->characteristic_data = ble_char_data
}

void bluetooth_main_loop(void)
{
	if(ble_main_loop != NULL)
		ble->main_loop();
}

void ble_pairing_handler(.....)
{
	tl_packet packet = {
		,
		,
		,
		
	}
	
	tl_add_packet(&packet);
};

void bluetooth_register_characteristic(.....)
{
	
}
*/