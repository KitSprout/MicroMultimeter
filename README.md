[MicroMultimeter](https://github.com/KitSprout/MicroMultimeter)
========
* Author  : [Hom](http://about.me/Hom)
* Version : v2.0
* Update  : 2016/03/09

Description
========
MicroMultimeter 是一個多功能的數位電表，著重於簡單、攜帶以及擴充性，以應付日常電路、微控制器開發除錯及測量為主要目的。基本功能有電壓測量、二極體測量、短路斷路測量、PWM 輸入輸出、波形顯示，同時也可以透過 USB VCP 功能，將訊號傳送至 PC 端處理與儲存，另外搭配其包含 UART、SPI、I2C、PWM 的擴充埠，讓配件模組化，藉此可再增加更多樣化的應用及延伸，像是溫溼度計、轉速計、無線示波器甚至是邏輯分析功能。

License
========
* 硬體(Hardware)採用 [CC BY-SA 4.0](http://creativecommons.org/licenses/by-sa/4.0/deed.zh_TW) 方式授權 
  
　　<a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/deed.zh_TW"><img alt="創用 CC 授權條款" style="border-width:0" src="http://i.creativecommons.org/l/by-sa/3.0/tw/80x15.png" /></a>  
　　<span xmlns:dct="http://purl.org/dc/terms/" property="dct:title"> MicroMultimeter v2.0 </span>由<a xmlns:cc="http://creativecommons.org/ns#" href="https://github.com/KitSprout" property="cc:attributionName" rel="cc:attributionURL"> KitSprout </a>製作，以<a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/deed.zh_TW"> 創用CC 姓名標示-相同方式分享 4.0 國際 授權條款 </a>釋出。  

* 軟體(Software)採用 [MIT License](http://opensource.org/licenses/MIT) 方式授權  

Hardware
========
* 控制器　 : [STM32F303C](http://www.st.com/web/catalog/mmc/FM141/SC1169/SS1576/LN1531/PF253449) 48Pin 72MHz DSP FPU
* 顯示器　 : [OLED_9.6-inch](https://github.com/KitSprout/OLED_0.96-inch) ( 9.6" 96*64 RGB565 )，使用 SPI 操作
* 外接介面 : 1 x EXPANSION ( ADC、DAC、OP、SPI、I2C、UART...)、1 x USB ( Micro )
* PCB 尺寸 : 32 * 32 mm 
* 設計軟體 [Altium Designer 16](http://www.altium.com/en/products/altium-designer) ( PcbLib use AD [PcbLib v2.0](https://github.com/KitSprout/AltiumDesigner_PcbLibrary/releases/tag/v2.0) ) 

<img src="https://lh3.googleusercontent.com/KHeHo8JHtvMxOAmfu3c-jkDxX15M3w-1aBmdJhzFvVuW3Wlrw2fuiFygpnGF4bAEo1iBxPcjfzRdaaWai3o4mBLGB_WRAG4G59AHtL_lYrX2-7m7f7IrbOXd0lstqajUzjJ-Vcc1ad_nSvOLihS0-nV6QMnoWS-C52hKyh5Hw8OS-rnVnXqmviN1ghggSviJqpZ47tTUgV-roSNJ-Nqp3l8sTd1sKQHBTEM-XX-AYJQlb6WAkHeF6RjZGgYhbSipwjFraGy0lO58rXNMV1Na6TfmdoVy-oEZeyVtYfx21cAUJvmOisdtsKYzWyVyG9xbR7VXP8bNMA-7aG8wF7tDJcyghgqFT9dBZ6ymD9M1dez4jTylJOFmzCsgH1pVcT5i5NmO1jrpfLNbmT6Fz1C69NwnFHG2eAV4i7MeYhrV8WPJy7GNTj0IvjKiPTH0eQgQShaplZcuSyXVuEIw300e4zCvsQU5Ra1lNw3LRtfO5xlIo9ges0RFHjLieLZzZQXTwAmX6wXN5hMPnAARNfyv-vUUAgZIHc8npHOOt3rqqFuElRUuvtEzPo65Oy7GNYHLsr87=w1440-h684-no" />

Expansion
========
* [ExpIO](https://github.com/KitSprout/MicroMultimeter/tree/master/Hardware/ExpIO) ( 引出所有 I/O )
* [ExpProbeA](https://github.com/KitSprout/MicroMultimeter/tree/master/Hardware/ExpProbeA) ( 三用電表探棒 4mm )
* [ExpProbeB](https://github.com/KitSprout/MicroMultimeter/tree/master/Hardware/ExpProbeB) ( 示波器探棒 BNC )
* [ExpDigiPower](https://github.com/KitSprout/MicroMultimeter/tree/master/Hardware/ExpDigiPower) ( 數位電源 [LM1084](http://www.ti.com/product/lm1084) + [AD5292](http://www.analog.com/en/products/digital-to-analog-converters/precision-dac-lessthanequalto-12mhz/digital-potentiometers/ad5292.html) )

Source Code
========
[uM_ModuleHAL_BUZZER](https://github.com/KitSprout/MicroMultimeter/tree/master/Software/uM_ModuleHAL_BUZZER)  
[uM_ModuleHAL_OLED-WF](https://github.com/KitSprout/MicroMultimeter/tree/master/Software/uM_ModuleHAL_OLED-WF)  
[uM_ModuleHAL_OLED](https://github.com/KitSprout/MicroMultimeter/tree/master/Software/uM_ModuleHAL_OLED)  
[uM_PeripheralHAL_ADC](https://github.com/KitSprout/MicroMultimeter/tree/master/Software/uM_PeripheralHAL_ADC)  
[uM_PeripheralHAL_GPIO](https://github.com/KitSprout/MicroMultimeter/tree/master/Software/uM_PeripheralHAL_GPIO)  
[uM_PeripheralHAL_TIM-PWM](https://github.com/KitSprout/MicroMultimeter/tree/master/Software/uM_PeripheralHAL_TIM-PWM)  
[uM_PeripheralHAL_TIM](https://github.com/KitSprout/MicroMultimeter/tree/master/Software/uM_PeripheralHAL_TIM)  

Related Documents
========
* [Google Drive](https://goo.gl/SFBbw1)

View
========
<img src="https://lh3.googleusercontent.com/ciOJGWqwI2F39WRjL0coTzQrB_V2H_HzStXo0oVFe0WWPR0K3iLFAgX6UaA6ciaMxZHnVk3N3ODS1k7W772lCXL_IjGjcrLNWudDFC843rQXAzY3yDy2ApvpdIJXsFZ3T9iFuuM1G1cL9ygbRo9jg6wdfM_Bl0H_Wu6YZJPlbLzd7GNsbrLUmyF-w-MpMFE6hJ9uTXoenPNm4lcuDeXmYxF9kJs9K1AvPZjBLicsY1VV6dKGjw5IoFB8tQ8iLbGPVUv0URf8NFRzgSuJt6IRiFAjjoVNZuVdi62aX_dQwvW5MESeF1hkvJ-2cM9H9r1JePublF06CaJaWEzikKQEzhQxVMAKi5P9SmxnbJXPrErIw8ccyYB1TqRE3RcOmwhRCPQFdhhb-D9hk18YwLcEGE7awA77fLgLF1Faj9u3_QQpTqpTzSgQwSOHCStBcyk5RXidcfR8GxlqW2UNa4GWCSl41o86FbxeH7czdk1gwPbtVgKb3YKdIv-ToI_4tt1OQHfiwdGYkFy6CaimW8RauHmPZaFPZJVBe0fD5nKA8yJ7z4-Km5wlqaZU9wlBmSagPLOI=w972-h730-no" />

<img src="https://lh3.googleusercontent.com/cuRWvLv76u1lZEBKbDESwkIayFoNJR57zpOTKc5ZKVQac89Duvc-xUxhNsg4mer5XNBq3HKsR3QZAFHCWOmJH4Ja5-lSfS58W1MlMRbd0ddcflMYWVWzNkbN5VAaqtpyxpfLUg9q3LKDK337mCBsW3pmQXmydlPofiSMZX8_K5gjBUAJKa0CTrxIDcQeTE_W-PfBEP7VKl9ngIU0iNVJE0xXfPfb-Wr-NNI3trKvNYR2sdHLtQexNUcCkPa1QN9pANWDezsZnOaOpuLujFH4RF3DzJhie8HURh9uABHJTelgCaREAN-HsIdk93J2uu0-LU4IB-ix6KYtX4dqipzXaWMxvE2HwMuYvqshbzdVIympWGt1S-vItoPxtVGP1B2EgTg2Si4YuubTWBcDnjapyZPVznfSbDqEMAy-cbCTntnNDnW2Oub24EZkUkVSGVY4dPlAtdilENR8tKCP1mI9WWHYXmjxOvooJUIET4AV8XxZqvwFzkBVpaLuUjsij6kZfurXIK63Lo0zXE6JF688Ajuo8CeBjyW8Tly7B-WIsIoaTEW9I12XL0QriBijO12OcBv5=w1168-h545-no" />

Config
========
<img src="https://lh3.googleusercontent.com/iC9rFp3AxAaXKDUla00tPuu-v_anb5Lj_xv68fwnb0StYn18qeUn_sdIE4pq_gjjGvv8XnmDrELvttaqchNS441_WLRrDd_bfpglAJ-EPknsYm6hkp0tWcq0BzbRqm3XK3H-uY07lzgJJxKyQVghGqForxsoaoG4FXHeojZh7mIoOIEETkrfp2jaVZ7LzFczZ0n3y9hc-lHSfJxus0_AMVBaQ8pOz81aWYfrrEgRE8W9JCXwGL-bs7HL1oF5JCmQX5Pu5JhnWC__ozui4TGiDyABthvgSSFox8wBFJ-v1VpEElGJEpuFO5JZzyIQcizaa0nlasFQ3bYashVYEAotC9b2E8D-ih9J3d2rlVr4WjAP3x9r_VFY-dTWX4bLm1d1iPhQeuNxVhaXXgjK7tckwN8jEfS3FCn7qzxwkhl5FkuR7c-IZ7kMZOV_7Tm2oAytpAvco56f8cKx4B1XoTXRsl5GYDRDqB_ZEb9oEpFUNLZsShHkCxETFszGqfSy_Znquhtz1K5u526ocx0sR28agxCNbwpF9xtvqHwZX3bMZ2qXDiurCL9AzhSQ_s5EGhLDe578=w1440-h474-no" />

Schematic
========
<img src="https://lh3.googleusercontent.com/JarVK6FCJ8oB-SgJGUF4E95hVw-waF9FvZIThpWmGQs5cYzVv74JMAxCEvhkXPeFlV6Ve8kE01JJa4GrnVU96MQdEsusNFxpnotKpReuBekSbCK4MoLGanE7QQ5NoIWDDAgBK5IAfeMRxTFjN8zoNMVLJBHRzgMuPjZpA5Y1U-YpDIGwSDJDCIRFSYNTNwyW_1gdDReqg1F_0ZfA8R2K9wKXHqjsZJsy0_4OK8JB3S6wCXW9_Ct-Gi5FTEEFFHF8Cdu8pETks2rzfzYdt9L5MKEZcQWsuPswmdEV-R2NLoUeEBZCLJSGiVa1y3QkDYl_eQjHI-SrPYamwkszhF7NYJO3Di3GpHjH44lKX26Q2ZyyK7QEn8BQ-y1SBH0CpOUKKfCW7Z2IhojkSrcHQCkJhBaAwuGE1-X86o4t7EB1ki7mT6IVecAWARkvhUerPhNByGGbFr5a95wdbgPiD74giZUgtTA6qML9-bH3TmKweiQTU5zi1fFguH59kKcpfrDubSvecOEluerw-YNlOo7QoI2v2JJdlORDLRODIC4CLnhchM8V76dFO4XpAXKu6uiG7N89=w1240-h775-no" />

<img src="https://lh3.googleusercontent.com/o663TuBcxLTucUFu32unS95XyFzZWp2O3H5JjE4yRuKd-XGugwpK_auhSdpqNny32hEW6XtPnJJw28Ou839E0sgcbdtZUF9g7aXIMfDFDeFYfqFolHDb2gZK3J-um1ypHL_hGZHZprctCCqEePFtcDj-62hC1_8P68Z_b5PgqQ6-nSPWYWnAKCfFiyh9CqffsC1iM4W5KLMEvOSqT3YGTq7y59CmydYo_ZQhCgMQ5bF7cZwol8n_IgdSBdVgL8A1AQ_iYYvFr7b1nbickcnqEMp6DJLHDYE60ZzFysb8Han_CO49x2r1RYSWYnc_Cqh6JdYaBOM2Rv7Z-QDJSG__Xz7X5yop7xRhfMPsUg_GttKQvZCHFGrL5Rh16vhsSiVUHA4BngeUx7tzSk6JKgb80VwGMj6YftwFdRKhVi_6wYFcsq_JOHFPxxcyE4f5TEaaWnPwB9awVPP8Hhv5W5TQMLesuXQOeHenZ63U6CQXVPyV_T9R8cVfposKQvatACipJsJwB2CVOFpTQ6kelkCFDbtSlDXMkYEoVdBXIYWQ0Ss4Hfh8EsCrC7AKW1hhiHJS6mhr=w1386-h775-no" />
