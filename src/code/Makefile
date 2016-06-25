all:
	cd src && make all && cd ..
	mv src/yara .

install:
	mkdir -p /usr/local/bin
	cp yara /usr/local/bin

uninstall:
	rm -rf /usr/local/bin

clean:
	cd src && make clean && cd ..
	rm -f yara *.dot *.png
