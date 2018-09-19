# QtAppUpdate
Logic to update app on it self

# How to build 
```
cmake -G "Visual Studio 15 2017 Win64" -DQt5Widgets_DIR=C:\Qt\Qt5.11.1\5.11.1\msvc2017_64\lib\cmake\Qt5Widgets -DQt5Network_DIR=C:\Qt\Qt5.11.1\5.11.1\msvc2017_64\lib\cmake\Qt5Network -DQT_HOME=C:\Qt\Qt5.11.1\5.11.1\msvc2017_64\bin ../
cmake --build . --target package
```

copy generated installer to www folder of you apache installation. Update latest-version and download-url in updates.json copy it to www of apache installation.
