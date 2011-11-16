#cc main.c -L. -lusb-1.0 -framework IOKit -framework CoreFoundation

iphone_detect:
	cc $@.c -L. -lusb-1.0 -framework IOKit -framework CoreFoundation -o $@
