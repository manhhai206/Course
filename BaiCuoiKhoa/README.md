# EMBEDDED PROJECT TEMPLATE

![image](docs/img/EmWi-STM32-boards-2048x1122.png)

## Table of content

[[_TOC_]]

## Summary

After a long chaotic, lawless period, Its time to conquer a new order world with only one template for all embedded project. The purpose of this project is to create a new template, so people should be reduced when working on a new project. There are two way to develop - integrate with this template. The first is use vendor-IDE and others text editor (Visual Code). Beside development, Testing is also an urge need and will be implemented to this template.

---
## Workspace Stucture
![image](docs/img/STM32_Software_Aritech.drawio.png)
![image](docs/img/BSP_Inside.drawio.png)

According to the above diagrams, Our source codes will be divided into 5 sections related to their business. Based on that, we have 5 folders for 5 sections accordingly.

- /.vscode : Configuration env for visual code
- /app : Application codes
- /bsp : Board support package code from vendor
- /build : Meson build folder
- /docs : Documents and resources
- /drvs : Device drivers codes
- /libs : 3rd Party Middileware codes
- /tests : Future reserved
- /tools : script to easy life
- /utils : Utilites codes

<details>
 <summary>Files Tree</summary>

```
HELLOWORLD_ARM
|   .vscode
└───app
|   └───inc
|   |   | ...
|   |
|   |   app_main.c
|   |   meson.build
└───bsp
|   └───.settings
|   |    | ...
|   |    
|   └───Core
|   |   | ...
|   |
|   └───...
└───build
|   └───...
|
└───docs
|   └───img
|   |    | ...
|   | ... 
|  
└───drvs
|   └───...   
```
</details>

---
## Build system
![image](docs/img/meson.png)

The main build system for this template is ``MESON``. Which pythonic syntax, its easy to debug and write the desire dream system.

Meson build system requires ```meson.build``` file and ```arm-none-eabi.txt``` to support cross-compilation system.

![image](docs/img/4d8c0b80-7bed-11e9-9338-fb7021245dd1.png)

Beside meson, STM32CubeIDE always be with us. You can you IDE to develop and release project along side with the meson.

The binary output of boths system will be slightly different due to unknow reason. But everything will be alright.

---
## Basic Use Tutorial

How long have you wait for this ?

### Prerequisite
- Linux Machine (Windown maybe later) (Ubuntu 22.04 is tested)
- Python 3.6.5
- Meson 1.1.0 
- GNU Arm Embedded Toolchain 10-2020-q4-major (arm-none-eabi)
- STM32CubeIDE 1.9.0
- Visual Studio Code
  - Cortex-Debug extension
  - SonarLint extension

### Installation
- ```sudo apt-get install python```
- ```sudo pip3 install meson```
- ```https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads```
- ```https://www.st.com/en/development-tools/stm32cubeide.html#tools-software```
- ```https://code.visualstudio.com/```
- ```https://marketplace.visualstudio.com/items?itemName=marus25.cortex-debug```

### Configuration

Here is how you start running this repos and the example firmware.

#### Using STM32CubeIDE

1. File -> Open Projects from File System -> Directory -> ../helloworld_arm/bsp/.project

![image](docs/img/Screenshot%20from%202023-04-26%2009-02-47.png)

![image](docs/img/Screenshot%20from%202023-04-26%2009-05-59.png)

2. Project -> Build

![image](docs/img/Screenshot%20from%202023-04-26%2010-03-03.png)

#### Using Meson
- ``` cd .../helloworld_arm ```
- ``` ./tools/init.sh freertos enabled ```

![image](docs/img/Screenshot%20from%202023-04-26%2010-08-26.png)

- ``` ./tools/build.sh ```

![image](docs/img/Screenshot%20from%202023-04-26%2010-10-15.png)

### Porting To New Project

1. Download the template 

``` 
https://rtgit.rta.vn/rtr/incubated-projects/embedded-project-template/-/archive/template/embedded-project-template-template.zip
```

2. Reconfigure general settings
```
mv embedded-project-template project-name
cd project-name
git init
git submodule https://rtgit.rta.vn/rtr/incubated-projects/cpputest.git subprojects/Cpputest
git submodule https://rtgit.rta.vn/rtr/incubated-projects/Unity.git subprojects/Unity
mkdir bsp
mv meson_bsp.build ./bsp/meson.build
source ./tools/setup.sh

====================================================================
Edit Unity Testing framework

add `native: true` to `./subprojects/Unity/meson.build` at `line:48`
====================================================================

unity_lib = static_library(meson.project_name(),
sources: unity_src,
include_directories: unity_inc,
install: not meson.is_subproject(),
native: true
)
```



3. Generate BSP folder 
- Using STM32CubeIDE to generate project bsp setting (move the ``meson.build`` in ``bsp`` somewhere else before generation and move the ``meson.build`` back) or Copy the already exist in to **/bsp** directory.

![image](docs/img/Screenshot%20from%202023-04-26%2011-34-49.png)

- If you are generating a new project, tick **Copy only necessary library files** in Code Generator Options section.

![image](docs/img/Screenshot%20from%202023-04-26%2011-39-15.png)

- Configure desire setting for your project.

4. Setup STM32CubeIDE

![image](docs/img/Screenshot%20from%202023-04-26%2011-54-08.png)

- Add basic directories into your workspace **/app /drvs /libs /utils**
  - File -> New -> Folder
  - Choose the settings follows below image

![image](docs/img/Screenshot%20from%202023-04-26%2011-59-11.png)

  - Do all the rest directories like the above

![image](docs/img/Screenshot%20from%202023-04-26%2013-11-42.png)

- Set **/app /drvs /libs /utils** as a source code folders
  - File -> New -> Source Folder

![image](docs/img/Screenshot%20from%202023-04-26%2013-14-20.png)
  - Choose the settings follows below image

![image](docs/img/Screenshot%20from%202023-04-26%2013-15-39.png)

  - Do all the rest

![image](docs/img/Screenshot%20from%202023-04-26%2013-17-14.png)

- Add **/app /drvs /libs /utils** into include directories
  - Right Click to the folder and click **Add/remove include path**
![image](docs/img/Screenshot%20from%202023-04-26%2013-25-12.png)
  - Select All
![image](docs/img/Screenshot%20from%202023-04-26%2013-25-24.png)
  - Do the rest of the directories and **inner folder** such as **/app/inc**
![image](docs/img/Screenshot%20from%202023-04-26%2013-43-05.png)

- Build

5. Setup Meson

- Firstly, check if arm-none-eabi-* is available
```
which arm-none-eabi-gcc
#~ /usr/lib/ccache/arm-none-eabi-gcc
```
- If not, change the field ``com_path`` in **arm-none-eabi.txt**
![image](docs/img/Screenshot%20from%202023-04-27%2008-24-20.png)

- Modify the ``arm-none-eabi.txt`` to match with the CubeIDE Configuration (``c_arg, c_macro, asm_args , c_link_arg,...``)

![image](docs/img/Screenshot%20from%202024-07-01%2015-07-36.png)

![image](docs/img/Screenshot%20from%202024-07-01%2015-09-06.png)

![image](docs/img/Screenshot%20from%202024-07-01%2015-09-24.png)

![image](docs/img/Screenshot%20from%202024-07-01%2015-09-43.png)

![image](docs/img/Screenshot%20from%202024-07-01%2014-56-16.png)

- Modify the ``cpu_family`` and ``cpu``
![image](docs/img/Screenshot%20from%202024-07-01%2014-56-31.png)



- Run first setup or wipe and init
```
./tools/init.sh freertos enabled
```

- Build
```
./tools/build.sh -v
```
---

### Addtional usage

*Some of common usage*
#### Add Vendor MiddileWare from STM32CubeIDE to Meson Build

``` 
cd ./bsp
```
- We will add **FATFS** MiddleWare from STM32CubeIDE to Meson build

  ![image](docs/img/Screenshot%20from%202023-04-27%2016-09-24.png) 

  MiddileWare from STM32CubeIDE include two main folder ```./FATFS``` and ```./Middilewares/Third_Party/FatFs```

- First, create an option to enable ***FatFS***
  - Add below line to  `./meson.options` 
  ![image](docs/img/Screenshot%20from%202023-04-28%2014-18-36.png) 
  - ```option('fatfs', type : 'feature', value : 'disabled', description : 'Include fatfs into main code')```
- Second, Add global variable name ``` fatfs_enable ``` to `./meson.build` by add ```fatfs_enable = get_option('fatfs').enabled()```

  ![image](docs/img/Screenshot%20from%202023-04-28%2014-22-27.png) 

- Third, you have to edit `./bsp/meson.build` by add include path and source code of the middleware

  ![image](docs/img/Screenshot%20from%202023-04-28%2014-27-47.png)

  ![image](docs/img/Screenshot%20from%202023-04-28%2014-49-26.png)

- Finally, we set fatfs option to meson by ```cd ./build``` and ```meson configure -Dfatfs=enabled```

- we can build using script now

#### Add Code to generic folder

- just copy and paste, meson auto detected new code add to folder.

#### Meson command (without using script)
- `meson compile` in **/build** folder to build the project
- `meson compile --clean` to clean the proejct
- `meson setup build --cross-file arm-none-eabi.txt` to init the build system
- `meson setup --reconfigure build --cross-file arm-none-eabi.txt` reinit if you already init

---
### FAQ
- Q: Any real example ?
  - A: `https://rtgit.rta.vn/rtr/incubated-projects/uart-mixer-new-template`
--
- Q: 



### TODO List
- [ ] Testing Features
- [ ] Static Analysis
- [ ] Complexity check
- [ ] Format
- [ ] Documantation
