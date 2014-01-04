@echo off
del *.pmw
del *.clw
del *.aps
del *.bak
del *.ncb
del *.plg
del *.tsv
del RELEASE\*.* /Q
rd  RELEASE
del DEBUG\*.* /Q
rd  DEBUG