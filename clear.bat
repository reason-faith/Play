@echo 正在清理VS2010工程中不需要的文件
@echo 请确保本文件放置在工程目录之中并关闭VS2010
@echo 开始清理请稍等......

rmdir /s /q .\debug\
rmdir /s /q .\release\
rmdir /s /q .\ipch\
rmdir /s /q .\recv\
rmdir /s /q .\send\
del /f /q .\*.sdf
pause