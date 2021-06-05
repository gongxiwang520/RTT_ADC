#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

/*
 * 程序清单： ADC 设备使用例程
 * 例程导出了 adc_sample 命令到控制终端
 * 命令调用格式：adc_sample
 * 程序功能：通过 ADC 设备采样电压值并转换为数值。
 *           示例代码参考电压为3.3V,转换位数为12位。
*/


#define ADC_DEV_NAME        "adc1"      // ADC设备名称
#define ADC_DEV_CHANNEL     9           // ADC通道     
#define REFER_VOLAGE        330         // 参考电压3.3V
#define CONVERT_BITS        (1 << 12)   // 分辨率12位

static int adc_sample(int argc, char *argv[])
{
  rt_adc_device_t adc_dev;
  rt_uint32_t value, vol;
  rt_err_t ret = RT_EOK;
  // 查找设备
  adc_dev = (rt_adc_device_t)rt_device_find(ADC_DEV_NAME);
  if (adc_dev == RT_NULL)
  {
    rt_kprintf("adc sample run failed! can't find %s device!\n", ADC_DEV_NAME);
    return RT_ERROR;
  }

  // 使能设备
  ret = rt_adc_enable(adc_dev, ADC_DEV_CHANNEL);

  // 读取采样值
  value = rt_adc_read(adc_dev, ADC_DEV_CHANNEL);
  rt_kprintf("the value is: %d\n", value);

  // 转换为对应的电压值
  vol = value * REFER_VOLAGE / CONVERT_BITS;
  rt_kprintf("the voltage is: %d.%02d\n", vol / 100, vol % 100);

  // 关闭通道
  ret = rt_adc_disable(adc_dev, ADC_DEV_CHANNEL);

  return ret;
}

MSH_CMD_EXPORT(adc_sample, adc sample);

