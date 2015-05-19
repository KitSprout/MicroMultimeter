[MicroMultimeter](https://github.com/KitSprout/MicroMultimeter)
========
* Author  : [Hom](http://about.me/Hom)
* Version : v1.0
* Update  : 2015/05/18

Description
========
MicroMultimeter 是一個多功能的電表，著重於擴充性而精度，以應付日常電路、微控制器開發除錯及測量，基本功能有電阻測量、電壓測量、二極體測量、短路測量、PWM 輸入輸出、波形顯示，搭配其包含 UART、SPI、I2C、PWM 的擴充埠，可及增加更多樣化的應用及延伸。

License
========
* 硬體(Hardware)採用 [CC BY-SA 4.0](http://creativecommons.org/licenses/by-sa/4.0/deed.zh_TW) 方式授權 
  
　　<a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/deed.zh_TW"><img alt="創用 CC 授權條款" style="border-width:0" src="http://i.creativecommons.org/l/by-sa/3.0/tw/80x15.png" /></a>  
　　<span xmlns:dct="http://purl.org/dc/terms/" property="dct:title"> MicroMultimeter v1.0 </span>由<a xmlns:cc="http://creativecommons.org/ns#" href="https://github.com/KitSprout" property="cc:attributionName" rel="cc:attributionURL"> KitSprout </a>製作，以<a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/deed.zh_TW"> 創用CC 姓名標示-相同方式分享 4.0 國際 授權條款 </a>釋出。  

Hardware
========
* 控制器　 : [STM32F103C](http://www.st.com/web/catalog/mmc/FM141/SC1169/SS1031/LN1565/PF189782) 48Pin 72MHz DSP FPU
* 顯示器　 : [OLED_9.6-inch](https://github.com/KitSprout/OLED_0.96-inch) ( 9.6" 96*64 )，使用 SPI 操作
* 外接介面 : 1*UART、1*SPI、1*I2C ( EXP )、1*USB ( Micro )
* PCB 尺寸 : 43.05 * 25.4mm ( Screws M3: 33 * 20mm )
* 設計軟體 [Altium Designer 15](http://www.altium.com/en/products/altium-designer) ( PcbLib use AD [PcbLib v1.4](https://github.com/KitSprout/AltiumDesigner_PcbLibrary/releases/tag/v1.4) ) 

<img src="https://lh3.googleusercontent.com/-BLFJ7WFhlDc/VVlS1oaVRvI/AAAAAAAAMeE/n_SWnR0Ta9o/s1600/uMultimeter_System_v1.0.png" />

Expansion
========
* [ExpIO](https://github.com/KitSprout/MicroMultimeter/tree/master/Hardware/ExpIO) ( 引出所有 I/O )
* [ExpProbeA](https://github.com/KitSprout/MicroMultimeter/tree/master/Hardware/ExpProbeA) ( 三用電表探棒 4mm )
* [ExpProbeB](https://github.com/KitSprout/MicroMultimeter/tree/master/Hardware/ExpProbeB) ( 示波器探棒 BNC )
* [ExpDigiPower](https://github.com/KitSprout/MicroMultimeter/tree/master/Hardware/ExpDigiPower) ( [LM1084](http://www.ti.com/product/lm1084) + [AD5292](http://www.analog.com/en/products/digital-to-analog-converters/precision-dac-lessthanequalto-12mhz/digital-potentiometers/ad5292.html) )

Source Code
========


Related Documents
========
* [Google Drive](https://goo.gl/SFBbw1)

View
========
<img src="https://lh3.googleusercontent.com/-leH5S9zszFY/VVo6V22YJMI/AAAAAAAAMos/vQzQOE1hWxM/s1200/DSC_2852-ANIMATION.gif"/>

Schematic
========
<img src="https://lh3.googleusercontent.com/-JycHgmM4Ze4/VVlIJ4r1ryI/AAAAAAAAMdo/AOCWgxlcUX0/s1600/MicroMultimeter%252520-%252520Main.png" />
<img src="https://lh3.googleusercontent.com/-_oee-WzoS0w/VVlIJ3AlDtI/AAAAAAAAMdk/Ne3U4tB2Ppc/s1600/MicroMultimeter%252520-%252520All.png" />
