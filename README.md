## 说明
RT-Thread提供ADC设备管理接口来访问adc外设，接口文件`adc.c`位于`rt-thread-master\rt-thread\components\drivers\misc`目录下，相关接口如下所示：
|      **函数**    |        **描述** |
|        :--       |        :--      |
| rt_adc_enable()  |   使能ADC设备   |
| rt_adc_read()    |   读取ADC设备数据   |
| rt_pin_disable() |   关闭ADC设备   |

## 流程说明
RT-Thread提供了一个ADC的硬件驱动文件`drv_adc.c`,在底层驱动`adc.h`中同样定义了ADC设备的操作方法，然后在硬件驱动函数中实现对应方法；
```
// adc.h
struct rt_adc_ops
{
    rt_err_t (*enabled)(struct rt_adc_device *device, rt_uint32_t channel, rt_bool_t enabled);
    rt_err_t (*convert)(struct rt_adc_device *device, rt_uint32_t channel, rt_uint32_t *value);
};

// drv_adc.c 
static const struct rt_adc_ops stm_adc_ops =
{
    .enabled = stm32_adc_enabled,
    .convert = stm32_get_adc_value,
};
```

ADC初始化是在`drv_adc.c`中使用`stm32_adc_init()`实现，ADC的默认配置如下：
```
static ADC_HandleTypeDef adc_config[] =
{
#ifdef BSP_USING_ADC1
    ADC1_CONFIG,
#endif

#ifdef BSP_USING_ADC2
    ADC2_CONFIG,
#endif

#ifdef BSP_USING_ADC3
    ADC3_CONFIG,
#endif
};
```
使用`INIT_BOARD_EXPORT(stm32_adc_init)；`方式将初始化函数进行初始化；