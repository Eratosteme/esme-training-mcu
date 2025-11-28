```mermaid
flowchart TD
  main[main.c]

  subgraph APP
    app[AppManager]
  end

  subgraph DRIVERS
    drv_lcd[LCD]
    drv_mcp[MCP9700]
    drv_serp[SERP]
  end

  subgraph LCD_SPLIT
    lcd_conf[LCD/Conf]
    lcd_core[LCD/Core]
  end

  subgraph HARDWARE
    hw_clock[CLOCK]
    hw_adc[ADC]
    hw_timer[TIMER]
    hw_eusart[EUSART]
    hw_i2cm[I2CM]
    hw_isr[ISR]
    clock_cfg[CLOCK/Conf]
    adc_cfg[ADC/Conf]
  end

  gpio[GPIO]
  tools[TOOLS/Common]

  %% dependencies
  main --> app
  main --> HARDWARE
  main --> tools
  app --> DRIVERS
  app --> tools
  drv_lcd --> lcd_conf
  drv_lcd --> lcd_core
  DRIVERS --> HARDWARE
  DRIVERS --> gpio
  HARDWARE --> gpio
  tools --> gpio

  ```