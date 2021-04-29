

uint8_t  dig_num[10] = {_0,_1,_2,_3,_4,_5,_6,_7,_8,_9};   // symb 0..9
uint16_t global_i2c_err = 0;


extern I2C_HandleTypeDef hi2c1;


void tm1650_send_data(uint8_t adress, uint8_t data)
{
  uint8_t i2c_error=0;
  uint16_t err_count=0;
  
  if(HAL_I2C_Master_Transmit(&hi2c1,(TM1650_CMD_ADDRESS | adress<<1), (uint8_t*)&data,1,100)!=HAL_OK) // address command + address (68,6A,6C,6E)
    i2c_error=1;
  else
    i2c_error=0;
  
  while ((HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY)&& !i2c_error)
  {
    err_count++;
    if(err_count>=15000)
      i2c_error=1;
  }
  
  if(i2c_error)
    global_i2c_err++;
  else
    global_i2c_err=0;
  
}


void tm1650_clear(void)
{
  for (int i = 0; i < 4; i++) 
  {
    tm1650_send_data(i, 0);
  }
}


void TM1650_setup(uint8_t active, uint8_t intensity) 
{
  // For the TM1650 level 0 is maximum brightness, 1-7 is low to high.
  // To align with other TM16XX chips we translate this to the same levels (0-7)
  
  uint8_t i2c_error=0;
  uint16_t err_count=0;
  
  uint8_t data[1];
  
  data[0] = (intensity<<4) | (0x07) | (active?0x01:0x00);
  if(HAL_I2C_Master_Transmit(&hi2c1, TM1650_CMD_MODE , (uint8_t*)&data,1,100)!=HAL_OK)
    i2c_error=1;
  else
    i2c_error=0;
  
  
  while ((HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY)&& !i2c_error)
  {
    err_count++;
    if(err_count>=15000)
      i2c_error=1;
  }
  
  if(i2c_error)
    global_i2c_err++;
  else
    global_i2c_err=0;
}

void out_value(int value)
{
  uint8_t position; //
  uint8_t out_dig;
  uint8_t minus=0;
  
  
  if(value>999 || value<-99)
    return; //out of range
  
  
  if(value>99 || value<-9)
    position=3;
  

    
    if(value<0)
    {
      value* = -1;
      tm1650_send_data(0,0x40);
      minus = 1;
    }
    
    if(value == 0)
    {
      tm1650_send_data(1,0x3f); //null
      tm1650_send_data(0,0x00); //space
      return;
    }
    
    while(value!=0) 
    {
		
      out_dig = dig_num[value%10];
      position--; 
      tm1650_send_data(position,out_dig);
      value/=10;
	  
    }
    
    while(position!=0 && !minus) 
    {
      position--; 
      tm1650_send_data(position,0x00);
    }
    
}

