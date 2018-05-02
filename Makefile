BUILD_TARGET=net
TARGET_IP=192.168.2.2

localhost: app.localhost

ar7: app.ar7

wp7: app.wp7

ar86: app.ar86

wp85: app.wp85

app.%:
	mkapp $(BUILD_TARGET).adef -t $* -v

clean:
	rm -rf _build_* *.update

install:
	app install $(BUILD_TARGET).wp85.update $(TARGET_IP)
start:
	app start $(BUILD_TARGET) $(TARGET_IP)
stop:	
	app stop $(BUILD_TARGET) $(TARGET_IP)
	
