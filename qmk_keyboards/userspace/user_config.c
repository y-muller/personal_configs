
#ifdef USER_CONFIG_ENABLE

typedef union {
  uint32_t raw;
  struct {
    bool     mods_indicators :1;        // custom mods indicators
    bool     func_indicators :1;        // main functions highlighted
    uint8_t  indicator_brightness :8;   //
    uint8_t  rgb_brightness :8;         // brightness to restore to 
  };
} user_config_t;

user_config_t user_config;

void user_config_init(void) {
    // Read the user config from EEPROM
    user_config.raw = eeconfig_read_user();
}

void eeconfig_init_user(void) {  // EEPROM is getting reset!
    user_config.raw = 0;
    //user_config.rgb_layer_change = true; // We want this enabled by default
    eeconfig_update_user(user_config.raw); // Write default value to EEPROM now
}

#endif  // USER_CONFIG_ENABLE
